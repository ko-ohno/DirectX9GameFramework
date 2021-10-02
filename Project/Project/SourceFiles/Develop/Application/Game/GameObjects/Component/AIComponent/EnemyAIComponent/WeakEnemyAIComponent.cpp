/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyAIComponent.cpp] �{�XAI�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�XAI�R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "WeakEnemyAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
WeakEnemyAIComponent::WeakEnemyAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, weak_enemy_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
WeakEnemyAIComponent::~WeakEnemyAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool WeakEnemyAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Uninit(void)
{
	// �X�e�[�g�}�V�����폜
	SAFE_DELETE_(weak_enemy_state_machine_);
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �G�̃X�e�[�g�𑀍삷��
	this->EnemyStateController();
	
#ifdef DEBUG_MODE_
	ImGui::Begin("week_enemy_ai_state");
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
			assert(!"WeakEnemyAIComponent::Update()�F�ア�G��AI���s���ȏ�Ԃł��I");
			break;
		}
	}
	ImGui::End();
#endif

	switch (enemy_state_)
	{
	case EnemyState::Idle:
		this->ChangeState(NEW WeakEnemyStateIdle());
		break;

	case EnemyState::MoveStraight:
		this->ChangeState(NEW WeakEnemyStateMoveStraight());
		break;

	case EnemyState::MoveStraightWaitOneTime:
		this->ChangeState(NEW WeakEnemyStateMoveStraightWaitOneTime());
		break;

	case EnemyState::MoveStraightWaitUpDown:
		this->ChangeState(NEW WeakEnemyStateMoveStraightWaitUpDown());
		break;

	case EnemyState::MoveRoundVertical:
		this->ChangeState(NEW WeakEnemyStateMoveRoundVertical());
		break;

	case EnemyState::MoveRoundHorizontal:
		this->ChangeState(NEW WeakEnemyStateMoveRoundHorizontal());
		break;

	case EnemyState::MoveLoopUpDown:
		this->ChangeState(NEW WeakEnemyStateMoveLoopUpDown());
		break;

	case EnemyState::MoveLoopLeftRight:
		this->ChangeState(NEW WeakEnemyStateMoveLoopLeftRight());
		break;

	case EnemyState::MoveShowOneTime:
		this->ChangeState(NEW WeakEnemyStateMoveShowOneTime());
		break;

	case EnemyState::Destroy:
		owner_->SetGameObjectState(GameObject::State::Destroy);
		break;

	case EnemyState::End:
		owner_->SetGameObjectState(GameObject::State::Dead);
		break;

	default:
		assert(!"WeakEnemyAIComponent::Update()�F�ア�G��AI���s���ȏ�Ԃł��I");
		break;
	}

	// ����AI�̃X�e�[�g�}�V����nullptr���H
	if (weak_enemy_state_machine_ != nullptr)
	{
		weak_enemy_state_machine_->Update(this, deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/*�@�X�e�[�g�̐��䏈��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::EnemyStateController(void)
{
	const bool is_controll = false;
	if (is_controll)
	{
		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_LEFT_SHOULDER))
		{
			this->SetEnemyState(EnemyState::Idle);
		}

		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_Y))
		{
			this->SetEnemyState(EnemyState::MoveStraight);
			//this->SetEnemyState(EnemyState::MoveStraightWaitOneTime);
		}

		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_X))
		{
			this->SetEnemyState(EnemyState::MoveRoundVertical);
			//this->SetEnemyState(EnemyState::MoveRoundHorizontal);
			//this->SetEnemyState(EnemyState::MoveLoopUpDown);
			//this->SetEnemyState(EnemyState::MoveLoopLeftRight);
		}

		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_B))
		{
			this->SetEnemyState(EnemyState::MoveShowOneTime);
			//this->SetEnemyState(EnemyState::MoveSShapedCurve);
		}
	}
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̃X�e�[�g�}�V���̕ύX
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::ChangeState(WeakEnemyStateMachine* weakEnemyStateMachine)
{
	if (weak_enemy_state_machine_ != nullptr)
		delete weak_enemy_state_machine_;

	weak_enemy_state_machine_ = weakEnemyStateMachine;

	if (weak_enemy_state_machine_ != nullptr)
		weak_enemy_state_machine_->Init();
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Idle(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̒����ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveStraight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// �Q�[���I�u�W�F�N�g�̏�Ԃ��I����Ԃֈڍs
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̒����ړ��F�ꎞ�ҋ@�F�����ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveStraightWaitOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// �Q�[���I�u�W�F�N�g�̏�Ԃ��I����Ԃֈڍs
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̒����ړ��F�ꎞ�ҋ@�F�����ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveStraightWaitUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// �Q�[���I�u�W�F�N�g�̏�Ԃ��I����Ԃֈڍs
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̐����ɔ��~��`���ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveRoundVertical(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// �Q�[���I�u�W�F�N�g�̏�Ԃ��I����Ԃֈڍs
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̐����ɔ��~��`���ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveRoundHorizontal(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// �Q�[���I�u�W�F�N�g�̏�Ԃ��I����Ԃֈڍs
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̏㉺���[�v�ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveLoopUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// �Q�[���I�u�W�F�N�g�̏�Ԃ��I����Ԃֈڍs
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̍��E���[�v�ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveLoopLeftRight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// �Q�[���I�u�W�F�N�g�̏�Ԃ��I����Ԃֈڍs
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*�@�ア�G�̉�ʂ̒[�����o���s��
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveShowOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// �Q�[���I�u�W�F�N�g�̏�Ԃ��I����Ԃֈڍs
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/