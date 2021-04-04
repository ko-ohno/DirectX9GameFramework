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

//���͑���
#include "../../Input/InputCheck.h"

#include "../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
CameraComponent::CameraComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, is_camera_moved_(false)
	, is_rotation_lookat_(false)
	, is_rotation_yaw_(false)
	, is_rotation_pitch_(false)
	, is_rotation_roll_(false)
	, eye_point_(0.f, 0.f, 0.f)
	, old_eye_point_(0.f, 0.f, 0.f)
	, lookat_point_(0.f, 0.f, 0.f)
	, front_vector_(0.f, 0.f, 1.f)
	, up_vector_(0.f, 1.f, 0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, degree_yaw_(0.f)
	, degree_pitch_(0.f)
	, degree_roll_(0.f)
	, degree_lookat_yaw_(0.f)
	, degree_lookat_pitch_(0.f)
	, degree_lookat_roll_(0.f)
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

	eye_point_	   = { 0.f, 0.f, -10.f };
	old_eye_point_ = eye_point_;
	lookat_point_  = { 0.f, 0.f,   0.f };
	old_eye_point_ = lookat_point_;

	//
	// �J�����̉�]���
	//

	degree_yaw_   =
	degree_pitch_ =
	degree_roll_  = 0.f;

	degree_lookat_yaw_	 =
	degree_lookat_pitch_ =
	degree_lookat_roll_  = 0.f;

	//
	//	�J�����̎p���x�N�g��
	//


	//�O�x�N�g�������߂�
	front_vector_ = lookat_point_ - eye_point_;
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
	UNREFERENCED_PARAMETER(deltaTime);

	if (InputCheck::KeyPress(DIK_LEFTARROW))
	{
		is_rotation_lookat_ = true;
		is_rotation_yaw_ = true;
		this->AddLookAtRotationYaw(30 * deltaTime);
	} 


	if (InputCheck::KeyPress(DIK_RIGHTARROW))
	{
		is_rotation_lookat_ = true;
		is_rotation_yaw_ = true;
		this->AddLookAtRotationYaw(-30 * deltaTime);
	}


	if (InputCheck::KeyPress(DIK_UP))
	{
		is_rotation_lookat_ = true;
		is_rotation_pitch_  = true;
		this->AddLookAtRotationPitch(30 * deltaTime);
	}


	if (InputCheck::KeyPress(DIK_DOWN))
	{
		is_rotation_lookat_ = true;
		is_rotation_pitch_	= true;
		this->AddLookAtRotationPitch(-30 * deltaTime);
	}



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
				ImGui::Text("%f:lookat.x\n", lookat_point_.x);
				ImGui::Text("%f:lookat.y\n", lookat_point_.y);
				ImGui::Text("%f:lookat.z\n", lookat_point_.z);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("eye_point"))
			{
				ImGui::Text("%f:eye.x\n", eye_point_.x);
				ImGui::Text("%f:eye.y\n", eye_point_.y);
				ImGui::Text("%f:eye.z\n", eye_point_.z);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("camera_deg"))
		{
			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("deg"))
			{
				ImGui::Text("%f:deg_yaw_\n", degree_yaw_);
				ImGui::Text("%f:deg_pitch_\n", degree_pitch_);
				ImGui::Text("%f:deg_roll_\n", degree_roll_);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("deg_lookat")) {
				ImGui::Text("%f:deg_lookat_yaw_\n", degree_lookat_yaw_);
				ImGui::Text("%f:deg_lookat_pitch_\n", degree_lookat_pitch_);
				ImGui::Text("%f:deg_lookat_roll_\n", degree_lookat_roll_);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}
	ImGui::End();


	//is_rotation_lookat_	= true;
	//is_rotation_yaw_	= true;
	//is_rotation_pitch_	= true;
	//is_rotation_roll_		= true;

	//�����x�N�g���̒����̍X�V
	{
		this->UpdateViewingVectorLength();
	}

	//�J�����̎p�������X�V
	{
		if (is_rotation_lookat_)
		{
			this->UpdateLookatPosition();
		}
		else
		{
			this->UpdateCameraPosition();
		}
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
	old_eye_point_ = eye_point_;
}

/*-----------------------------------------------------------------------------
/*�@�J�����̏�ԍX�V����
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateCameraState(void)
{
	//�J�������ړ��������H
	if (old_eye_point_ != eye_point_)
	{
		is_camera_moved_ = true;
	}
	else
	{
		is_camera_moved_ = false;
	}

	//�t���O�����Ƃɖ߂�
	is_rotation_lookat_ = false;
	is_rotation_yaw_	= false;
	is_rotation_pitch_  = false;
	is_rotation_roll_	= false;
}

/*-----------------------------------------------------------------------------
/*�@�����x�N�g���̒������X�V
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateViewingVectorLength(void)
{
	D3DXVECTOR3 direction = eye_point_ - lookat_point_;
	viewing_vector_length_ = D3DXVec3Length(&direction);
}

/*-----------------------------------------------------------------------------
/*�@�J�������W�̍X�V
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateCameraPosition(void)
{
	if (is_rotation_yaw_)   { this->ComputeRotationYaw(); }
	if (is_rotation_pitch_) { this->ComputeRotationPitch(); }
	if (is_rotation_roll_)	{ this->ComputeRotationRoll(); }
}

/*-----------------------------------------------------------------------------
/*�@�����_���W�̍X�V
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateLookatPosition(void)
{
	if (is_rotation_yaw_)   { this->ComputeRotationLookatYaw(); }
	if (is_rotation_pitch_) { this->ComputeRotationLookatPitch(); }
	if (is_rotation_roll_)	{ this->ComputeRotationLookatRoll(); }
}

/*-----------------------------------------------------------------------------
/*�@�J�������W���S�̉�]�FYaw
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationYaw(void)
{
	// ���K�������x�N�g���̍쐬
	D3DXVECTOR3 viewing_vector = lookat_point_ - eye_point_;
	D3DXVec3Normalize(&viewing_vector, &viewing_vector);

	// �����x�N�g���̉�]
	const float radian = Math::ToRadian(degree_yaw_ - DEGREE_NORMALIZE_OFFSET);
	{
		viewing_vector.x = Math::Sin(radian);
		viewing_vector.y = 0.f;
		viewing_vector.z = Math::Cos(radian);
	}

	// �����x�N�g����O�x�N�g���Ƃ��ĕۑ�
	front_vector_ = viewing_vector;

	// Yaw����]�̂��߁A�E�x�N�g���̎Z�o�F�O�x�N�g���Ə�x�N�g���̊O��
	D3DXVec3Cross(&right_vector_, &front_vector_, &up_vector_);
	D3DXVec3Normalize(&right_vector_, &right_vector_);
	
	// �J�������W�F�����_�Ɏ����x�N�g�������Z���邱�ƂŁA�J�������W���X�V����
	eye_point_ = lookat_point_ + (viewing_vector * viewing_vector_length_); //�����x�N�g���̒���1 * �����̒���N

	// �J�������W���S�̉�]�p�x:Yaw�̐��K��
	degree_yaw_ = Math::NormalizeDegree(degree_yaw_);
}

/*-----------------------------------------------------------------------------
/*�@�J�������W���S�̉�]�FPitch
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationPitch(void)
{
	// ���K�������x�N�g���̍쐬
	D3DXVECTOR3 viewing_vector = eye_point_ - lookat_point_;
	D3DXVec3Normalize(&viewing_vector, &viewing_vector);

	// �����x�N�g���̉�]
	const float radian = Math::ToRadian(degree_pitch_ - DEGREE_NORMALIZE_OFFSET);
	{
		viewing_vector.x = 0.f;
		viewing_vector.y = Math::Sin(radian);
		viewing_vector.z = Math::Cos(radian);
	}

	// �����x�N�g����O�x�N�g���Ƃ��ĕۑ�
	front_vector_ = viewing_vector;

	// Pitch����]�̂��߁A��x�N�g���̎Z�o�F�E�x�N�g���Ə�x�N�g���̊O��
	D3DXVec3Cross(&up_vector_, &front_vector_, &right_vector_);
	D3DXVec3Normalize(&up_vector_, &up_vector_);

	// �J�������W�F�����_�Ɏ����x�N�g�������Z���邱�ƂŁA�J�������W���X�V����
	eye_point_ = lookat_point_ + (viewing_vector * viewing_vector_length_); //�����x�N�g���̒���1 * �����̒���N

	// �J�������W���S�̉�]�p�x:Pitch�̐��K��
	degree_pitch_ = Math::NormalizeDegree(degree_pitch_);
}

/*-----------------------------------------------------------------------------
/*�@�J�������W���S�̉�]�FRoll
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationRoll(void)
{
	// �����x�N�g���̉�]
	const float radian = Math::ToRadian(degree_roll_ + degree_lookat_roll_);
	{
		D3DXMATRIX rotation_matrix;
		D3DXMatrixRotationAxis(&rotation_matrix, &front_vector_, radian);

		right_vector_.x	= rotation_matrix._11;
		right_vector_.y	= rotation_matrix._12;
		right_vector_.z	= rotation_matrix._13;

		up_vector_.x = rotation_matrix._21;
		up_vector_.y = rotation_matrix._22;
		up_vector_.z = rotation_matrix._23;
	}

	// �J�������W�F�����_�Ɍ����x�N�g�������Z���邱�ƂŁA�J�������W���X�V����
	eye_point_ = lookat_point_ + (front_vector_ * viewing_vector_length_); //�����x�N�g���̒���1 * �����̒���N

	// �J�������W���S�̉�]�p�x:Roll�̐��K��
	degree_roll_ = Math::NormalizeDegree(degree_roll_);
}

/*-----------------------------------------------------------------------------
/*�@�����_���W���S�̉�]�FYaw
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationLookatYaw(void)
{
	// ���K�������x�N�g���̍쐬
	D3DXVECTOR3 viewing_vector = eye_point_ - lookat_point_;
	D3DXVec3Normalize(&viewing_vector, &viewing_vector);

	// �����x�N�g���̉�]
	const float radian = Math::ToRadian(degree_lookat_yaw_);
	{
		viewing_vector.x = Math::Sin(radian);
		viewing_vector.y = 0.f;
		viewing_vector.z = Math::Cos(radian);
	}

	// �����x�N�g����O�x�N�g���Ƃ��ĕۑ�
	front_vector_ = viewing_vector;

	// Yaw����]�̂��߁A�E�x�N�g���̎Z�o�F�O�x�N�g���Ə�x�N�g���̊O��
	D3DXVec3Cross(&right_vector_, &front_vector_, &up_vector_);
	D3DXVec3Normalize(&right_vector_, &right_vector_);

	// �����_���W�F�J�������W�Ɏ����x�N�g�������Z���邱�ƂŁA�����_���W���X�V����
	lookat_point_ = eye_point_  + (viewing_vector * viewing_vector_length_); //�����x�N�g���̒���1 * �����̒���N

	// �J�������W���S�̉�]�p�x:Yaw�̐��K��
	degree_lookat_yaw_ = Math::NormalizeDegree(degree_lookat_yaw_);
}

/*-----------------------------------------------------------------------------
/*�@�����_���W���S�̉�]�FPitch
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationLookatPitch(void)
{
	// ���K�������x�N�g���̍쐬
	D3DXVECTOR3 viewing_vector = eye_point_ - lookat_point_;
	D3DXVec3Normalize(&viewing_vector, &viewing_vector);

	// �����x�N�g���̉�]
	const float radian = Math::ToRadian(degree_lookat_pitch_);
	{
		viewing_vector.x = 0.f;
		viewing_vector.y = Math::Sin(radian);
		viewing_vector.z = Math::Cos(radian);
	}

	// �����x�N�g����O�x�N�g���Ƃ��ĕۑ�
	front_vector_ = viewing_vector;

	// Pitch����]�̂��߁A��x�N�g���̎Z�o�F�E�x�N�g���Ə�x�N�g���̊O��
	D3DXVec3Cross(&up_vector_, &right_vector_, &front_vector_);
	D3DXVec3Normalize(&up_vector_, &up_vector_);

	// �����_���W�F�J�������W�Ɏ����x�N�g�������Z���邱�ƂŁA�����_���W���X�V����
	lookat_point_ = eye_point_ + (viewing_vector * viewing_vector_length_); //�����x�N�g���̒���1 * �����̒���N

	// �J�������W���S�̉�]�p�x:Pitch�̐��K��
	degree_lookat_pitch_ = Math::NormalizeDegree(degree_lookat_pitch_);
}

/*-----------------------------------------------------------------------------
/*�@�����_���W���S�̉�]�FRoll
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationLookatRoll(void)
{
	// �����x�N�g���̉�]
	const float radian = Math::ToRadian(degree_roll_ + degree_lookat_roll_);
	{
		D3DXMATRIX rotation_matrix;
		D3DXMatrixRotationAxis(&rotation_matrix, &front_vector_, radian);

		right_vector_.x = rotation_matrix._11;
		right_vector_.y = rotation_matrix._12;
		right_vector_.z = rotation_matrix._13;

		up_vector_.x = rotation_matrix._21;
		up_vector_.y = rotation_matrix._22;
		up_vector_.z = rotation_matrix._23;
	}

	// �J�������W�F�����_�Ɍ����x�N�g�������Z���邱�ƂŁA�J�������W���X�V����
	eye_point_ = lookat_point_ + (front_vector_ * viewing_vector_length_); //�����x�N�g���̒���1 * �����̒���N

	// �J�������W���S�̉�]�p�x:Roll�̐��K��
	degree_roll_ = Math::NormalizeDegree(degree_roll_);
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
						  , &eye_point_	 	// ���_
						  , &lookat_point_	// �����_
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