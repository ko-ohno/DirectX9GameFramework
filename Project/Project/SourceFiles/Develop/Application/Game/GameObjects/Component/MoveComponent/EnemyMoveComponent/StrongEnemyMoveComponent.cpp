/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyMoveComponent.cpp] �{�X�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�̈ړ��R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "StrongEnemyMoveComponent.h"
#include "../../../GameObject.h"
#include "../../../../../Math.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemyMoveComponent::StrongEnemyMoveComponent(GameObject* owner, int updateOrder)
	: EnemyMoveComponent(owner, updateOrder)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemyMoveComponent::~StrongEnemyMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool StrongEnemyMoveComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ���@�̊e��]�l�̎擾
	yaw_	= owner_transform_->GetAngleYaw();
	pitch_	= owner_transform_->GetAnglePitch();
	roll_	= owner_transform_->GetAngleRoll();

	// ��]�̕�Ԃ��s���t���O��ON��
	{
		owner_transform_->IsSetExecuteSlerpRotation(true);
	}

	// ���g�̏�Ԃ�\�L
	ImGui::Begin("strong_enemy_move_state");
	{
		switch (enemy_state_)
		{
		case EnemyState::Idle:
			ImGui::Text("idle");
			break;

		case EnemyState::MoveStraight:
			ImGui::Text("move_straight");
			break;

		case EnemyState::MoveStraightWaitOneTime:
			ImGui::Text("move_straight_wait_one_time");
			break;

		case EnemyState::MoveStraightWaitUpDown:
			ImGui::Text("move_straight_wait_up_down");
			break;

		case EnemyState::MoveRoundVertical:
			ImGui::Text("move_round_vertical");
			break;

		case EnemyState::MoveRoundHorizontal:
			ImGui::Text("move_round_horizontal");
			break;

		case EnemyState::MoveLoopUpDown:
			ImGui::Text("move_loop_up_down");
			break;

		case EnemyState::MoveLoopLeftRight:
			ImGui::Text("move_loop_left_right");
			break;

		case EnemyState::MoveShowOneTime:
			ImGui::Text("move_show_one_time");
			break;

		case EnemyState::Destroy:
			ImGui::Text("destroy");
			break;

		default:
			assert(!"StrongEnemyMoveComponent::Update()�F�����G���s���ȍs���X�e�[�g�ɂ���܂��I");
			break;
		}
	}
	ImGui::End();

	// �G�̏�ԍX�V
	switch (enemy_state_)
	{	
	case EnemyState::Idle:
		this->MoveActionIdle(deltaTime);
		break;

	case EnemyState::MoveStraight:
		this->MoveActionStraight(deltaTime);
		break;

	case EnemyState::MoveStraightWaitOneTime:
		this->MoveActionStraightWaitOneTime(deltaTime);
		break;

	case EnemyState::MoveStraightWaitUpDown:
		this->MoveActionStraightWaitUpDown(deltaTime);
		break;

	case EnemyState::MoveRoundVertical:
		this->MoveActionRoundVertical(deltaTime);
		break;

	case EnemyState::MoveRoundHorizontal:
		this->MoveActionRoundHorizontal(deltaTime);
		break;

	case EnemyState::MoveLoopUpDown:
		this->MoveActionLoopUpDown(deltaTime);
		break;

	case EnemyState::MoveLoopLeftRight:
		this->MoveActionLoopLeftRight(deltaTime);
		break;

	case EnemyState::MoveShowOneTime:
		this->MoveActionShowOneTime(deltaTime);
		break;

	case EnemyState::Destroy:
		break;

	default:
		assert(!"StrongEnemyMoveComponent::Update()�F�����G���s���ȍs���X�e�[�g�ɂ���܂��I");
		break;
	}

	//�{�X�̃X�e�[�g�̍X�V
	enemy_state_old_ = enemy_state_;
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionIdle(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*�@�����G�̈ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionStraight(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*�@�����G�̈ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionStraightWaitOneTime(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*�@�����G�̈ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionStraightWaitUpDown(float deltaTime)
{
}

/*-----------------------------------------------------------------------------
/*�@�����G�̈ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionRoundVertical(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*�@�����G�̈ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionRoundHorizontal(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*�@�����G�̈ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionLoopUpDown(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*�@�����G�̈ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionLoopLeftRight(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*�@�����G�̈ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionShowOneTime(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*�@�����G�̈ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionSShapedCurve(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/