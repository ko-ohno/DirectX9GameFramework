/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CameraComponent.cpp] �J�����̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�����R���|�[�l���g�̋��ʂɂȂ鏈�����`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "CameraComponent.h"
#include "../../../Math.h"
#include "../GameObject.h"

#include "../../Input/InputCheck.h"
#include "../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
CameraComponent::CameraComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, is_need_update_(false)
	, is_camera_moved_(false)
	, is_camera_controlling_(true)
	, position_(0.f, 0.f, 0.f)
	, old_position_(0.f, 0.f, 0.f)
	, lookat_position_(0.f, 0.f, 0.f)
	, move_direction_(0.f, 0.f, 0.f)
	, front_vector_(0.f, 0.f, 1.f)
	, up_vector_(0.f, 1.f, 0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, move_speed_(10.f)
	, rotation_degree_(45.f)
	, viewing_vector_length_(0.f)
	, screen_aspect_size_(Vector2())
	, view_matrix_(D3DXMATRIX())
	, view_inverse_matrix_(D3DXMATRIX())
	, projection_matrix_2d_(D3DXMATRIX())
	, projection_matrix_3d_(D3DXMATRIX())
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
CameraComponent::~CameraComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool CameraComponent::Init(void)
{
	//
	//	��ʃA�X�y�N�g�䗦�̎擾
	//

	screen_aspect_size_ = owner_->GetGame()->GetGraphics()->GetScreenSize();

	//
	//	�J�������W�ƒ����_
	//

	position_	   = { 0.f, 0.f, -10.f };
	old_position_ = position_;
	lookat_position_  = { 0.f, 0.f,   0.f };

	//
	//	�J�����̎p���x�N�g��
	//

	//�O�x�N�g�������߂�
	front_vector_ = lookat_position_ - position_;
	D3DXVec3Normalize(&front_vector_, &front_vector_);

	up_vector_ = { 0.f, 1.f,  0.f };
	D3DXVec3Normalize(&up_vector_, &up_vector_);

	//�E�x�N�g�������߂�
	D3DXVec3Cross(&right_vector_, &front_vector_, &up_vector_);
	D3DXVec3Normalize(&right_vector_, &right_vector_); 


	//
	//	�J�����̊e�v�f�̏�����
	//
	{
		this->ComputeViewMatrix();
		this->ComputeViewInverseMatrix();
		this->ComputeProjection2DMatrix();
		this->ComputeProjection3DMatrix();
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void CameraComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void CameraComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void CameraComponent::Update(float deltaTime)
{
	ImGui::Begin("camera");
	{
		ImGui::Text("is_camera_moved_:%s", is_camera_moved_ ? "true" : "false");

		if (ImGui::TreeNode("transform_vector_"))
		{
			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("front_vector_"))
			{
				ImGui::Text("%05f:front_vector_.x\n", front_vector_.x);
				ImGui::Text("%05f:front_vector_.y\n", front_vector_.y);
				ImGui::Text("%05f:front_vector_.z\n", front_vector_.z);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("up_vector_"))

			{
				ImGui::Text("%0f:up_vector_.x\n", up_vector_.x);
				ImGui::Text("%0f:up_vector_.y\n", up_vector_.y);
				ImGui::Text("%0f:up_vector_.z\n", up_vector_.z);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("right_vector_"))
			{
				ImGui::Text("%0f:right_vector_.x\n", right_vector_.x);
				ImGui::Text("%0f:right_vector_.y\n", right_vector_.y);
				ImGui::Text("%0f:right_vector_.z\n", right_vector_.z);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("camera_position"))
		{
			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("lookat_point"))
			{
				ImGui::Text("%f:lookat.x\n", lookat_position_.x);
				ImGui::Text("%f:lookat.y\n", lookat_position_.y);
				ImGui::Text("%f:lookat.z\n", lookat_position_.z);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("eye_point"))
			{
				ImGui::Text("%f:eye.x\n", position_.x);
				ImGui::Text("%f:eye.y\n", position_.y);
				ImGui::Text("%f:eye.z\n", position_.z);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

	}
	ImGui::End();

	//�����x�N�g���̒����̍X�V
	{
		this->UpdateViewingVectorLength();
	}

	//�p���x�N�g���̍X�V
	{
		this->UpdateTransform(deltaTime);
	}

	//�J�������ړ��������̏�Ԃ��X�V
	{
		this->UpdateCameraState();
	}

	//�e�J�����̍s��̗v�f���X�V
	{
		this->ComputeViewMatrix();
		this->ComputeViewInverseMatrix();
		this->ComputeProjection2DMatrix();
		this->ComputeProjection3DMatrix();
	}

	//1�t���[���O�̏����X�V
	old_position_ = position_;
}

/*-----------------------------------------------------------------------------
/*�@�J�����̏�ԍX�V����
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateCameraState(void)
{
	//�J�������ړ��������H
	if (old_position_ != position_)
	{
		is_camera_moved_ = true;
	}
	else
	{
		is_camera_moved_ = false;
	}
}

/*-----------------------------------------------------------------------------
/*�@�����x�N�g���̒������X�V
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateViewingVectorLength(void)
{
	D3DXVECTOR3 viewing_vector = position_ - lookat_position_;
	viewing_vector_length_ = D3DXVec3Length(&viewing_vector);
}

/*-----------------------------------------------------------------------------
/*�@�ړ������x�N�g���̍X�V
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateTransform(float deltaTime)
{
	//�O�x�N�g�����Z�o�B�����_����J�����̈ʒu��������
	front_vector_ = lookat_position_ - position_;

	//�p���x�N�g���̍X�V
	{
		//�O�x�N�g���𐳋K��
		D3DXVec3Normalize(&front_vector_, &front_vector_);

		//�O�ςŉE�x�N�g�������߂�
		D3DXVec3Cross(&right_vector_, &up_vector_, &front_vector_);
		D3DXVec3Normalize(&right_vector_, &right_vector_);

		//�O�ςŏ�x�N�g�������߂�
		D3DXVec3Cross(&up_vector_, &front_vector_, &right_vector_);
		D3DXVec3Normalize(&up_vector_, &up_vector_);
	}

	//�J�����𑀍삷�邩
	if (is_camera_controlling_)
	{
		this->ComputeCameraMovement(deltaTime);
		this->ComputeRotationCameraPosition(deltaTime);
		this->ComputeRotationLookatPosition(deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/*�@�J�����̈ړ��R���g���[��
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeCameraMovement(float deltaTime)
{
	const bool is_move_front = InputCheck::KeyPress(DIK_W);
	const bool is_move_back  = InputCheck::KeyPress(DIK_S);
	const bool is_move_left	 = InputCheck::KeyPress(DIK_A);
	const bool is_move_right = InputCheck::KeyPress(DIK_D);
	const bool is_move_up	 = InputCheck::KeyPress(DIK_Q);
	const bool is_move_down  = InputCheck::KeyPress(DIK_E);

	const bool is_moving = (is_move_front || is_move_back || is_move_left || is_move_right || is_move_up || is_move_down);

	if (is_moving)
	{
		//
		// �O��ړ�
		//

		if (is_move_front)
		{
			position_		 += (front_vector_ * move_speed_) * deltaTime;
			lookat_position_ += (front_vector_ * move_speed_) * deltaTime;
		}
		
		if (is_move_back) 
		{
			position_		 -= (front_vector_ * move_speed_) * deltaTime;
			lookat_position_ -= (front_vector_ * move_speed_) * deltaTime;
		}
		
		//
		// ���E�ړ�
		//

		if (is_move_left)
		{
			position_		 += (right_vector_ * move_speed_) * deltaTime;
			lookat_position_ += (right_vector_ * move_speed_) * deltaTime;
		}
		
		if (is_move_right)
		{
			position_		 -= (right_vector_ * move_speed_) * deltaTime;
			lookat_position_ -= (right_vector_ * move_speed_) * deltaTime;
		}
		
		//
		// �㉺�ړ�
		//

		if (is_move_up)
		{
			position_		 += (up_vector_ * move_speed_) * deltaTime;
			lookat_position_ += (up_vector_ * move_speed_) * deltaTime;
		}
		
		if (is_move_down)
		{
			position_		 -= (up_vector_ * move_speed_) * deltaTime;
			lookat_position_ -= (up_vector_ * move_speed_) * deltaTime;
		}
	}
}

/*-----------------------------------------------------------------------------
/*�@�J�������W�̃R���g���[��
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationCameraPosition(float deltaTime)
{
	const bool is_rotation_up    = InputCheck::KeyPress(DIK_UPARROW);
	const bool is_rotation_down  = InputCheck::KeyPress(DIK_DOWNARROW);
	const bool is_rotation_right = InputCheck::KeyPress(DIK_RIGHTARROW);
	const bool is_rotation_left  = InputCheck::KeyPress(DIK_LEFTARROW);
	const bool is_rotation  = (is_rotation_up || is_rotation_down || is_rotation_right || is_rotation_left);

	if (is_rotation)
	{
		//��]�̑��x�����W�A���ɕϊ�
		float radian = Math::ToRadian(rotation_degree_ * deltaTime);

		//��]���
		D3DXMATRIX rotation_matrix;
		D3DXMatrixIdentity(&rotation_matrix);

		//�����x�N�g��
		D3DXVECTOR3 direction;

		/*--- �J�����̃��[���h���W���S�ɉ�] ---*/
		if (is_rotation_up)	   { D3DXMatrixRotationAxis(&rotation_matrix, &right_vector_,  radian); }
		if (is_rotation_down)  { D3DXMatrixRotationAxis(&rotation_matrix, &right_vector_, -radian); }
		if (is_rotation_right) { D3DXMatrixRotationAxis(&rotation_matrix, &up_vector_,	   radian); }
		if (is_rotation_left)  { D3DXMatrixRotationAxis(&rotation_matrix, &up_vector_,	  -radian); }

		//�����x�N�g�����쐬
		direction = position_ - lookat_position_;
		D3DXVec3Normalize(&direction, &direction);

		//�����x�N�g������]
		D3DXVec3TransformNormal(&direction, &direction, &rotation_matrix);

		//�J�������W�̍X�V
		position_ = lookat_position_ + (direction * viewing_vector_length_);
	}
}

/*-----------------------------------------------------------------------------
/*�@�����_���W�̃R���g���[��
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationLookatPosition(float deltaTime)
{
	const bool is_rotation_up    = InputCheck::KeyPress(DIK_T);
	const bool is_rotation_down  = InputCheck::KeyPress(DIK_G);
	const bool is_rotation_right = InputCheck::KeyPress(DIK_F);
	const bool is_rotation_left  = InputCheck::KeyPress(DIK_H);
	const bool is_rotation = (is_rotation_up || is_rotation_down || is_rotation_right || is_rotation_left);

	if (is_rotation)
	{
		//��]�̑��x�����W�A���ɕϊ�
		float radian = Math::ToRadian(rotation_degree_ * deltaTime);

		//��]���
		D3DXMATRIX rotation_matrix;
		D3DXMatrixIdentity(&rotation_matrix);

		//�����x�N�g��
		D3DXVECTOR3 direction;

		/*--- �J�����̃��[���h���W���S�ɉ�] ---*/
		if (is_rotation_up)		{ D3DXMatrixRotationAxis(&rotation_matrix, &right_vector_,  radian); }
		if (is_rotation_down)	{ D3DXMatrixRotationAxis(&rotation_matrix, &right_vector_, -radian); }
		if (is_rotation_right)	{ D3DXMatrixRotationAxis(&rotation_matrix, &up_vector_,		radian); }
		if (is_rotation_left)	{ D3DXMatrixRotationAxis(&rotation_matrix, &up_vector_,	   -radian); }

		//�����x�N�g�����쐬
		direction = lookat_position_ - position_;
		D3DXVec3Normalize(&direction, &direction);

		//�����x�N�g������]
		D3DXVec3TransformNormal(&direction, &direction, &rotation_matrix);

		//�J�������W�̍X�V
		lookat_position_ = position_ + (direction * viewing_vector_length_);
	}
}

/*-----------------------------------------------------------------------------
/*�@�r���[�s��̌v�Z
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeViewMatrix(void)
{
	// �r���[�s��쐬
	{
		//
		//�@�r���[�s��̌v�Z��
		//
		// view_matrix = rotation_matrix�̋t�s�� * translation_matrix�̋t�s��
		//


		D3DXMatrixLookAtLH(&view_matrix_
						  , &position_	 	// ���_
						  , &lookat_position_	// �����_
						  , &up_vector_);	// �J�����̓��̌���	
	}
}

/*-----------------------------------------------------------------------------
/*�@�t�r���[�s��̌v�Z
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeViewInverseMatrix(void)
{
	// �t�r���[�s��쐬
	{
		//�r���[�s��𕡐�
		view_inverse_matrix_ = view_matrix_;

		//�]�u�s��ϊ�
		D3DXMatrixTranspose(&view_inverse_matrix_, &view_inverse_matrix_);

		//�]�u��̗v�f�̒��́A�ړ������폜
		view_inverse_matrix_._41 = 0.0f;
		view_inverse_matrix_._42 = 0.0f;
		view_inverse_matrix_._43 = 0.0f;
	}
}

/*-----------------------------------------------------------------------------
/*�@2D�p�̃v���W�F�N�V�����s��̌v�Z
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeProjection2DMatrix(void)
{
	//���s���ɉ�ʃT�C�Y��ύX�������ꍇ�́A���̕ϊ��s���"�X�V"�ł���悤�ɂ���
	//�ˉe�ϊ��s��̍쐬
	{
		Vector2 screen_size = owner_->GetGame()->GetGraphics()->GetScreenSize();

		projection_matrix_2d_ = {
			 (2.f / screen_size.x_),				     0.f, 0.f, 0.f,
								0.f, (-2.f / screen_size.y_), 0.f, 0.f,
								0.f,				     0.f, 1.f, 0.f,
							   -1.f,				     1.f, 0.f, 1.f,
		};
	}
}

/*-----------------------------------------------------------------------------
/*�@3D�p�̃v���W�F�N�V�����s��̌v�Z
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeProjection3DMatrix(void)
{
	// 3D�v���W�F�N�V�����ϊ��s��쐬
	{
		D3DXMatrixPerspectiveFovLH(&projection_matrix_3d_												// 3D�ˉe�ϊ��s��
								  , D3DX_PI / 3															// ����p
								  , static_cast<FLOAT>(screen_aspect_size_.x_) / screen_aspect_size_.y_	// �A�X�y�N�g��
								  , static_cast<FLOAT>(1.f)												// �j�A�N���b�v   : �J�����̕`��̈��
								  , static_cast<FLOAT>(1000.f));										// �t�@�[�N���b�v : �J�����̕`��̈�̉��܂ł̋���
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/