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
	, is_using_camera_controller_(false)
	, is_rotation_lookat_(false)
	, is_execute_slerp_(false)
	, view_matrix_(D3DXMATRIX())
	, view_inverse_matrix_(D3DXMATRIX())
	, projection_matrix_2d_(D3DXMATRIX())
	, projection_matrix_3d_(D3DXMATRIX())
	, screen_aspect_size_(Vector2())
	, front_vector_(0.f, 0.f, 0.f)
	, up_vector_(0.f, 0.f, 0.f)
	, right_vector_(0.f, 0.f, 0.f)
	, degree_yaw_(0.f)
	, degree_pitch_(0.f)
	, degree_roll_(0.f)
	, degree_lookat_yaw_(0.f)
	, degree_lookat_pitch_(0.f)
	, degree_lookat_roll_(0.f)
	, slerp_spped_(0.f)
	, slerp_runtime_(0.f)
	, quaternion_(D3DXQUATERNION())
	, lookat_quaternion_(D3DXQUATERNION())
	, translation_matrix_(D3DXMATRIX())
	, rotation_lookat_matrix_(D3DXMATRIX())
	, rotation_matrix_(D3DXMATRIX())
	, world_matrix_(D3DXMATRIX())
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

	eye_point_	  = { 0.f, 0.f, -10.f };
	lookat_point_ = { 0.f, 0.f,   0.f };
						
	//
	//	�J�����̎p���x�N�g��
	//

	up_vector_	  = { 0.f, 1.f,  0.f };

	//�O�x�N�g�������߂�
	front_vector_ = lookat_point_ - eye_point_;
	D3DXVec3Normalize(&front_vector_, &front_vector_);

	//�E�x�N�g�������߂�
	D3DXVec3Cross(&right_vector_, &up_vector_, &front_vector_);
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



			//��]�s��
	//D3DXMatrixRotationQuaternion(&rotation_matrix_, &quaternion_);

	degree_yaw_ += deltaTime;

	//D3DXMATRIX rot_mat, trans_mat;

	//D3DXMatrixTranslation(&trans_mat, eye_point_.x, eye_point_.y, eye_point_.z);

	////trans_mat = trans_mat * rotation_matrix_;

	//rot_mat = rotation_matrix_;

	//D3DXMatrixInverse(&rot_mat, nullptr, &rot_mat);
	//D3DXMatrixInverse(&trans_mat, nullptr, &trans_mat);

	////view_matrix_ =  rot_mat * trans_mat;


	//{
	//	degree_yaw_ = Math::NormalizeDegree(degree_yaw_);
	//	degree_pitch_ = Math::NormalizeDegree(degree_pitch_);
	//	degree_roll_ = Math::NormalizeDegree(degree_roll_);
	//}

	//D3DXMatrixInverse(,nullptr,);
	//view_matrix_ = ;

	//�J�������W�̍X�V
	this->UpdateCameraPosition(deltaTime);

	//�����_���W�̍X�V
	//this->UpdateLookatPosition(deltaTime);

	////�p���x�N�g���̍X�V
	//this->ComputeTransformVector();

	//�e�J�����̍s��̗v�f���X�V
	{
		this->ComputeViewMatrix();
		this->ComputeViewInverseMatrix();
		this->ComputeProjection2DMatrix();
		this->ComputeProjection3DMatrix();
	}

	//�J�������ړ��������H
	if (old_eye_point_ != eye_point_)
	{
		is_camera_moved_ = true;
	}
	else
	{
		is_camera_moved_ = false;
	}

	ImGui::Begin("camera");
	ImGui::Text("%s", is_camera_moved_ ? "true" : "false");

	ImGui::Text("%f:lookat.x\n", lookat_point_.x);
	ImGui::Text("%f:lookat.y\n", lookat_point_.y);
	ImGui::Text("%f:lookat.z\n", lookat_point_.z);


	ImGui::Text("%f:eye.x\n", eye_point_.x);
	ImGui::Text("%f:eye.y\n", eye_point_.y);
	ImGui::Text("%f:eye.z\n", eye_point_.z);

	ImGui::Text("%f:deg\n", degree_yaw_);
	ImGui::Text("%f:deg\n", degree_pitch_);
	ImGui::Text("%f:deg\n", degree_roll_);

	ImGui::Text("%f:deg_lookat\n", degree_lookat_yaw_);
	ImGui::Text("%f:deg_lookat\n", degree_lookat_pitch_);
	ImGui::Text("%f:deg_lookat\n", degree_lookat_roll_);

	ImGui::End();

	//1�t���[���O�̏����X�V
	old_eye_point_ = eye_point_;
}

/*-----------------------------------------------------------------------------
/*�@�J�������W�̍X�V����
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateCameraPosition(float deltaTime)
{
	D3DXMATRIX rotation_matrix;


	//��]���̐���
	{
		//��]�N�H�[�^�j�I��
		//D3DXQuaternionRotationYawPitchRoll(&quaternion_
		//							   	  , Math::ToRadian(degree_yaw_)
		//							   	  , Math::ToRadian(degree_pitch_)
		//							   	  , Math::ToRadian(degree_roll_));

		D3DXQuaternionRotationAxis(&quaternion_, &up_vector_, Math::ToRadian(30 * deltaTime)); //�����_���S�̉�]�͂���łł���B

		//��]�s��
		D3DXMatrixRotationQuaternion(&rotation_matrix, &quaternion_);

	}

	//�J�������W�̍X�V
	{
		//��]�s������ƂɁA�����x�N�g������]������
		D3DXVECTOR3 direction = eye_point_ - lookat_point_;
		D3DXVec3TransformNormal(&direction, &direction, &rotation_matrix);

		//up_vector_.x = rotation_matrix_._21;
		//up_vector_.y = rotation_matrix_._22;
		//up_vector_.z = rotation_matrix_._23;

		//�J�������W�F�����_�Ɍ����x�N�g�������Z���邱�ƂŁA�J�������W���X�V����
		eye_point_ = lookat_point_ + direction;
		eye_point_ = eye_point_;
	}

	//�J�������W���S�̉�]�p�x�𐳋K��
	{
		degree_yaw_		= Math::NormalizeDegree(degree_yaw_);
		degree_pitch_	= Math::NormalizeDegree(degree_pitch_);
		degree_roll_	= Math::NormalizeDegree(degree_roll_);
	}
}

/*-----------------------------------------------------------------------------
/*�@�����_���W�̍X�V����
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateLookatPosition(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);


	//��]���̐���
	{
		//��]�N�H�[�^�j�I��
		D3DXQuaternionRotationYawPitchRoll(&lookat_quaternion_
										  , Math::ToRadian(degree_lookat_yaw_)
										  , Math::ToRadian(degree_lookat_pitch_)
										  , Math::ToRadian(degree_lookat_roll_));

		//��]�s��
		D3DXMatrixRotationQuaternion(&rotation_lookat_matrix_, &lookat_quaternion_);
	}

	//�����_���W�̍X�V
	{

		//��]�s������ƂɁA�����x�N�g������]������
		D3DXMATRIX rotation_matrix;
		D3DXVECTOR3 direction = lookat_point_ - eye_point_;
		D3DXVec3TransformNormal(&direction, &direction, &rotation_matrix);

		////�����_���W�F�J�������W�Ɍ����x�N�g�������Z���邱�ƂŁA�����_���X�V����
		lookat_point_ = eye_point_ + direction;
		lookat_point_ = lookat_point_;
	}

	//�����_���W���S�̉�]�p�x�𐳋K��
	{
		degree_lookat_yaw_   = Math::NormalizeDegree(degree_lookat_yaw_);
		degree_lookat_pitch_ = Math::NormalizeDegree(degree_lookat_pitch_);
		degree_lookat_roll_  = Math::NormalizeDegree(degree_lookat_roll_);
	}
}

void CameraComponent::ComputeWorldMatrix(void)
{
}

void CameraComponent::ComputeLocalMatrix(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�p���x�N�g���̍X�V����
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeTransformVector(void)
{
	front_vector_ = lookat_point_ - eye_point_;
	D3DXVec3Normalize(&front_vector_, &front_vector_);

	up_vector_ = { 0.f, 1.f, 0.f };
	up_vector_;
	up_vector_;

	right_vector_ = { 1.f, 0.f, 0.f };

	//right_vector_.x = 1.0f;
	//right_vector_.y = 0.f;
	//right_vector_.z = 0.f;

	D3DXVec3Normalize(&right_vector_, &right_vector_);
}


/*-----------------------------------------------------------------------------
/*�@�r���[�s��̌v�Z
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeViewMatrix(void)
{
	// �r���[�s��쐬
	{
		//auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

		//
		//�@�r���[�s��̌v�Z��
		//
		// view_matrix = rotation_matrix�̋t�s�� * translation_matrix�̋t�s��
		//

		D3DXMATRIX camera_matrix = local_matrix_ * world_matrix_;

		D3DXVECTOR3 eye_point	 = { camera_matrix._11, camera_matrix._12, camera_matrix._13 };
		D3DXVECTOR3 lookat_point = { camera_matrix._31, camera_matrix._32, camera_matrix._33 };
		D3DXVECTOR3 up_vector	 = { camera_matrix._21, camera_matrix._22, camera_matrix._23 };


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

		//�]�u��̗v�f�A�ړ������폜
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