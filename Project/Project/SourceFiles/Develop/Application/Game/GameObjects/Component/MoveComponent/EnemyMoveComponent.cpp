/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyMoveComponent.cpp] �G�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�̈ړ��R���|�[�l���g�̏������`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "EnemyMoveComponent.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EnemyMoveComponent::EnemyMoveComponent(GameObject* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
	, enemy_motion_state_(EnemyMotionState::None)
	, enemy_state_(EnemyState::None)
	, enemy_state_old_(EnemyState::None)
	, is_need_compute_(true)
	, position_(0.f, -100.f, 0.f)
	, position_start_(0.f, -100.f, 0.f)
	, position_finish_(0.f, 0.f, 0.f)
	, position_start_old_(0.f, 0.f, 0.f)
	, position_y_start_(0.f)
	, position_y_finish_(0.f)
	, angle_yaw_(0.f)
	, angle_pitch_(0.f)
	, angle_roll_(0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, move_direction_(0.f, 0.f, 0.f)
	, move_vector_length_(1.f)
	, move_action_magnitude_(1.f)
	, state_loop_count_(0)
	, max_execute_time_(1.f)
	, execute_time_(0.f)
	, yaw_(0.f)
	, pitch_(0.f)
	, roll_(0.f)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EnemyMoveComponent::~EnemyMoveComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* �����x�N�g���̌v�Z
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::ComputeMoveDirection(void)
{

}

/*-----------------------------------------------------------------------------
/* ��ԍ��W�̌v�Z
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::ComputeLerpPosition(void)
{
	// ���W�̌v�Z���K�v��
	is_need_compute_ = (enemy_state_old_ != enemy_state_)
					   || (position_start_ != position_start_old_);

	//�K�v�Ȃ�������v�Z���Ȃ�
	if (is_need_compute_ == false) { return; }
	

	// �������̐���
	D3DXMATRIX		direction_matrix_;		// �����s��
	D3DXQUATERNION	direction_quaternion_;	// �����N�H�[�^�j�I��

	// �e���̏�����
	D3DXMatrixIdentity(&direction_matrix_);
	D3DXQuaternionIdentity(&direction_quaternion_);

	// �����N�H�[�^�j�I���𐶐�
	D3DXQuaternionRotationYawPitchRoll(&direction_quaternion_
									  , D3DXToRadian(angle_yaw_)
									  , D3DXToRadian(angle_pitch_)
									  , D3DXToRadian(angle_roll_));

	// �����N�H�[�^�j�I���������s��֕ϊ�
	D3DXMatrixRotationQuaternion(&direction_matrix_, &direction_quaternion_);

	// �����N�H�[�^�j�I���ɂ���]�����������s�񂩂�����x�N�g���֕ϊ�
	move_direction_.x = direction_matrix_._31;
	move_direction_.y = direction_matrix_._32;
	move_direction_.z = direction_matrix_._33;

	// �����s�񂩂�E�x�N�g���𒊏o 
	right_vector_.x = direction_matrix_._11;
	right_vector_.y = direction_matrix_._12;
	right_vector_.z = direction_matrix_._13;

	// �e�x�N�g���̐��K��
	D3DXVec3Normalize(&move_direction_, &move_direction_);
	D3DXVec3Normalize(&right_vector_, &right_vector_);

	//
	// �ړ��x�N�g���̌v�Z
	//

	// �I�_���W�̌v�Z
	position_finish_ = move_direction_ * move_vector_length_; // ���_����I�t�Z�b�g�������W:�I�_���W
	position_finish_ += position_start_;					  // �ړ��x�N�g���̌��_���I�t�Z�b�g����

	// 1�t���[���O�̎n�_���W�����X�V
	position_start_old_ = position_start_;
}

/*-----------------------------------------------------------------------------
/* �ҋ@�s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionIdle(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �o��s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionEnter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �̓�����U���s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionBodyPress(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �ˌ��U���s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionShoot(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* ���[�U�[�C�U���s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionLaserCannon(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �����ړ��s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionStraight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �����ړ����Ĉ��҂s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionStraightWaitOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �����ړ����ď㉺�^��������҂�
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionStraightWaitUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �����ɔ��~��`���ړ��s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionRoundVertical(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �����ɔ��~��`���ړ��s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionRoundHorizontal(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �㉺���[�v�ړ��s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionLoopUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* ���E���[�v�ړ��s��
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionLoopLeftRight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* ��ʂ̒[����Ђ������������
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionShowOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* S���J�[�u�ňړ�
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionSShapedCurve(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/