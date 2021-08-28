/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyAIComponent.cpp] 強い敵のAIコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：強い敵のAIコンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "StrongEnemyAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
StrongEnemyAIComponent::StrongEnemyAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, strong_enemy_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
StrongEnemyAIComponent::~StrongEnemyAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool StrongEnemyAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Uninit(void)
{
	// ステートマシンを削除
	SAFE_DELETE_(strong_enemy_state_machine_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 敵のステートを操作する
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
			assert(!"StrongEnemyAIComponent::Update()：ボスがAIが不正な状態です！");
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
		assert(!"StrongEnemyAIComponent::Update()：ボスがAIが不正な状態です！");
		break;
	}

	//このAIのステートマシンがnullptrか？
	if (strong_enemy_state_machine_ != nullptr)
	{
		strong_enemy_state_machine_->Update(this, deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/*　ステートの制御処理
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
/*　強い敵のステートマシンの変更
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
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Idle(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveStraight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveStraightWaitOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveStraightWaitUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveRoundVertical(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveRoundHorizontal(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveLoopUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveLoopLeftRight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::MoveShowOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/