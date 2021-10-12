/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TransformComponent.cpp] �p������R���|�[�l���g�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�p������R���|�[�l���g�ɋ��ʂ��鏈���̒�`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "TransformComponent.h"
#include "../../../Math.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
TransformComponent::TransformComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, is_set_rotation_matrix_(false)
	, is_execute_slerp_(false)

	, front_vector_(0.f, 0.f, 1.f)
	, up_vector_(0.f, 1.f, 0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, direction_(0.f, 0.f, 0.f)

	, position_(0.f, 0.f, 0.f)
	, old_position_(0.f, 0.f, 0.f)

	, scale_(1.f, 1.f, 1.f)
	, old_scale_(1.f, 1.f, 1.f)

	, degree_yaw_(0.f)
	, degree_pitch_(0.f)
	, degree_roll_(0.f)

	, slerp_spped_(1.f)
	, slerp_runtime_(0.f)

	, quaternion_(0.f, 0.f, 0.f, 0.f)
	, direction_quaternion_(0.f, 0.f, 0.f, 0.f)

	, rotation_matrix_(D3DXMATRIX())
	, world_matrix_(D3DXMATRIX())
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
TransformComponent::~TransformComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool TransformComponent::Init(void)
{
	D3DXQuaternionIdentity(&quaternion_);
	D3DXQuaternionIdentity(&direction_quaternion_);
	D3DXMatrixIdentity(&rotation_matrix_);
	D3DXMatrixIdentity(&world_matrix_);
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void TransformComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void TransformComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void TransformComponent::Update(float deltaTime)
{
	//�����x�N�g���̏�񐶐�
	this->ComputeDirectionVector();

	//�p���x�N�g���̏��̐���
	this->ComputeTransformVector();

	const bool is_need_update = this->IsNeedUpdate();
	if (is_need_update == false) { return; }

	//��]�s�񂪂ق��̃N���X����ݒ肳��Ă��邩
	if (is_set_rotation_matrix_ == false)
	{
		//��]�s��̐���
		this->ComputeRotationMatrixQuaternion(deltaTime);
	}

	//���[���h�s��̐���
	this->ComputeWorldMatrix();
}

/*-----------------------------------------------------------------------------
/*�@�X�V���K�v���̃`�F�b�N
-----------------------------------------------------------------------------*/
bool TransformComponent::IsNeedUpdate(void)
{
	//�O�x�N�g���ƌ����x�N�g������v���Ă��Ȃ�
	const bool is_direction_not_front = (front_vector_ != direction_);

	//�P�t���[���O�̊g�k��񂪈�v���Ă��Ȃ�
	const bool is_old_scale_non_matched = (old_scale_ != scale_);

	//�P�t���[���O�̊g�k��񂪈�v���Ă��Ȃ�
	const bool is_old_position_non_matched = (old_position_ != position_);

	//�X�V���邩�H
	const bool is_need_update = (is_direction_not_front
								|| is_old_scale_non_matched
								|| is_old_position_non_matched);
	if (is_need_update == false)
	{
		return false; 
	}
	return true;
}

/*-----------------------------------------------------------------------------
/*�@�����x�N�g�����̐���
-----------------------------------------------------------------------------*/
void TransformComponent::ComputeDirectionVector(void)
{
	//�����s��
	D3DXMATRIX direction_matrix;

	//�����N�H�[�^�j�I�����쐬
	{
		D3DXQuaternionRotationYawPitchRoll(&direction_quaternion_
										  , Math::ToRadian(degree_yaw_)
										  , Math::ToRadian(degree_pitch_)
										  , Math::ToRadian(degree_roll_));
	}
	 
	//�����s��ƁA�����x�N�g�����쐬
	{
		//�����s����쐬
		D3DXMatrixRotationQuaternion(&direction_matrix, &direction_quaternion_);

		//�����x�N�g���̍쐬
		{
			direction_.x = direction_matrix._31;
			direction_.y = direction_matrix._32;
			direction_.z = direction_matrix._33;
		}
	}

	// �N�H�[�^�j�I���̊p�x�� 0.f �` 360.f �Ő��K��
	{
		degree_yaw_   = Math::NormalizeDegree(degree_yaw_);
		degree_pitch_ = Math::NormalizeDegree(degree_pitch_);
		degree_roll_  = Math::NormalizeDegree(degree_roll_);
	}

}

/*-----------------------------------------------------------------------------
/*�@�p���x�N�g�����̐���
-----------------------------------------------------------------------------*/
void TransformComponent::ComputeTransformVector(void)
{
	// �E�x�N�g�����̐���
	right_vector_.x = world_matrix_._11;
	right_vector_.y = world_matrix_._12;
	right_vector_.z = world_matrix_._13;

	// ��x�N�g�����̐���
	up_vector_.x	= world_matrix_._21;
	up_vector_.y	= world_matrix_._22;
	up_vector_.z	= world_matrix_._23;

	// �O�x�N�g�����̐���
	front_vector_.x = world_matrix_._31;
	front_vector_.y = world_matrix_._32;
	front_vector_.z = world_matrix_._33;
}

/*-----------------------------------------------------------------------------
/*�@�N�H�[�^�j�I���ɂ���]�s��̐���
-----------------------------------------------------------------------------*/
void TransformComponent::ComputeRotationMatrixQuaternion(float deltaTime)
{
	//���ʕ�Ԃ����邩�H
	if (is_execute_slerp_ == false)
	{
		D3DXQuaternionSlerp(&quaternion_
						   , &quaternion_
						   , &direction_quaternion_
						   , 1.f);
	}
	else
	{
		//�e�x�N�g�����擾
		D3DXVECTOR3 front_vector = front_vector_;
		D3DXVECTOR3 direction = direction_;

		//���K��
		D3DXVec3Normalize(&front_vector, &front_vector);
		D3DXVec3Normalize(&direction, &direction);
		{
			if (front_vector_ != direction_)
			{
				slerp_runtime_ = 0.f;
			}

			if (slerp_runtime_ <= 0.999f)
			{
				//��Ԃ̎��s�l�ւ̉��Z
				slerp_runtime_ += slerp_spped_ * deltaTime;

				//��Ԃ̎��s�l�𐳋K��
				if (slerp_runtime_ >= 1.000f)
				{
					slerp_runtime_ = 1.f;
				}
			}
		
			D3DXQuaternionSlerp(&quaternion_
							   , &quaternion_
							   , &direction_quaternion_
							   , slerp_runtime_);
		}
	}

	//�N�H�[�^�j�I�������]�s��𐶐�
	D3DXMatrixRotationQuaternion(&rotation_matrix_, &quaternion_);
}

/*-----------------------------------------------------------------------------
/*�@���[���h�s��̐���
-----------------------------------------------------------------------------*/
void TransformComponent::ComputeWorldMatrix(void)
{

	//�ʒu���A�g�k���
	D3DXVECTOR3 position
			  , scale;

	position = *this->GetPosition();
	scale	 = *this->GetScale();


	//��]���
	D3DXMATRIX rotation_matrix;

	rotation_matrix = *this->GetRotationMatrix();


	//
	// ���[���h�s��ւ̍���
	//

	//1�t���[���O�̏����X�V
	old_position_ = position;
	old_scale_ = scale;

	//�g�k�̃x�N�g���l�ɁA��]�s��̒l�����킦�Čv�Z

	//X��
	world_matrix_._11 = scale.x * rotation_matrix._11;
	world_matrix_._12 = scale.x * rotation_matrix._12;
	world_matrix_._13 = scale.x * rotation_matrix._13;

	//Y��
	world_matrix_._21 = scale.y * rotation_matrix._21;
	world_matrix_._22 = scale.y * rotation_matrix._22;
	world_matrix_._23 = scale.y * rotation_matrix._23;

	//Z��
	world_matrix_._31 = scale.z * rotation_matrix._31;
	world_matrix_._32 = scale.z * rotation_matrix._32;
	world_matrix_._33 = scale.z * rotation_matrix._33;

	//���s�ړ�
	world_matrix_._41 = position.x;
	world_matrix_._42 = position.y;
	world_matrix_._43 = position.z;

	//W����
	world_matrix_._14 = world_matrix_._24 = world_matrix_._34 = 0.0f;

	//1.0f�ɐݒ肷�邱�Ƃ�world_matrix_._4*���x�N�g����
	world_matrix_._44 = 1.0f;
}

/*=============================================================================
/*		End of File
=============================================================================*/