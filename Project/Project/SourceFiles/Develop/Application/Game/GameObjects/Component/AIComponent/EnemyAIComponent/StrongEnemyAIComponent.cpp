/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyAIComponent.cpp] �����G��AI�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����G��AI�R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "StrongEnemyAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemyAIComponent::StrongEnemyAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, strong_enemy_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemyAIComponent::~StrongEnemyAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool StrongEnemyAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Uninit(void)
{
	// �X�e�[�g�}�V�����폜
	SAFE_DELETE_(strong_enemy_state_machine_);
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �G�̃X�e�[�g�𑀍삷��
	this->EnemyStateController();
	
	ImGui::Begin("strong_enemy_ai_state");
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
			assert(!"StrongEnemyAIComponent::Update()�F�{�X��AI���s���ȏ�Ԃł��I");
			break;
		}
	}
	ImGui::End();

	switch (enemy_state_)
	{
	case EnemyState::Idle:
		this->ChangeState(NEW StrongEnemyStateIdle());
		break;

	case EnemyState::MoveStraight:
		this->ChangeState(NEW StrongEnemyStateMoveStraight());
		break;

	case EnemyState::MoveStraightWaitOneTime:
		this->ChangeState(NEW StrongEnemyStateMoveStraightWaitOneTime());
		break;

	case EnemyState::MoveStraightWaitUpDown:
		this->ChangeState(NEW StrongEnemyStateMoveStraightWaitUpDown());
		break;

	case EnemyState::MoveRoundVertical:
		this->ChangeState(NEW StrongEnemyStateMoveRoundVertical());
		break;

	case EnemyState::MoveRoundHorizontal:
		this->ChangeState(NEW StrongEnemyStateMoveRoundHorizontal());
		break;

	case EnemyState::MoveLoopUpDown:
		this->ChangeState(NEW StrongEnemyStateMoveLoopUpDown());
		break;

	case EnemyState::MoveLoopLeftRight:
		this->ChangeState(NEW StrongEnemyStateMoveLoopLeftRight());
		break;

	case EnemyState::MoveShowOneTime:
		this->ChangeState(NEW StrongEnemyStateMoveShowOneTime());
		break;

	case EnemyState::Destroy:
		break;	

	default:
		assert(!"StrongEnemyAIComponent::Update()�F�{�X��AI���s���ȏ�Ԃł��I");
		break;
	}

	//����AI�̃X�e�[�g�}�V����nullptr���H
	if (strong_enemy_state_machine_ != nullptr)
	{
		strong_enemy_state_machine_->Update(this, deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/*�@�X�e�[�g�̐��䏈��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::EnemyStateController(void)
{
	const bool is_controll = true;
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
			//this->SetEnemyState(EnemyState::MoveLoopUpDown);
			//this->SetEnemyState(EnemyState::MoveLoopLeftRight);
			//this->SetEnemyState(EnemyState::MoveRoundHorizontal);
			//this->SetEnemyState(EnemyState::MoveRoundVertical);
			//this->SetEnemyState(EnemyState::MoveShowOneTime);
			//this->SetEnemyState(EnemyState::MoveSShapedCurve);
		}

		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_RIGHT_SHOULDER))
		{
			this->SetEnemyState(EnemyState::Shooting);
		}
	}
}

/*-----------------------------------------------------------------------------
/*�@�����G�̃X�e�[�g�}�V���̕ύX
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::ChangeState(StrongEnemyStateMachine* strongEnemyStateMachine)
{
	if (strong_enemy_state_machine_ != nullptr)
		delete strong_enemy_state_machine_;

	strong_enemy_state_machine_ = strongEnemyStateMachine;

	if (strong_enemy_state_machine_ != nullptr)
		strong_enemy_state_machine_->Init();
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Idle(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveStraight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveStraightWaitOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveStraightWaitUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveRoundVertical(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveRoundHorizontal(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveLoopUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveLoopLeftRight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@�����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveShowOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/