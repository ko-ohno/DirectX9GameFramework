/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyAIComponent.cpp] ボスAIコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスAIコンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "WeakEnemyAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
WeakEnemyAIComponent::WeakEnemyAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, weak_enemy_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
WeakEnemyAIComponent::~WeakEnemyAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool WeakEnemyAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Uninit(void)
{
	// ステートマシンを削除
	SAFE_DELETE_(weak_enemy_state_machine_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 敵のステートを操作する
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
			assert(!"WeakEnemyAIComponent::Update()：弱い敵のAIが不正な状態です！");
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
		assert(!"WeakEnemyAIComponent::Update()：弱い敵のAIが不正な状態です！");
		break;
	}

	// このAIのステートマシンがnullptrか？
	if (weak_enemy_state_machine_ != nullptr)
	{
		weak_enemy_state_machine_->Update(this, deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/*　ステートの制御処理
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
/*　弱い敵のステートマシンの変更
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
/*　弱い敵の待機行動
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Idle(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　弱い敵の直線移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveStraight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// ゲームオブジェクトの状態を終了状態へ移行
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*　弱い敵の直線移動：一時待機：直線移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveStraightWaitOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// ゲームオブジェクトの状態を終了状態へ移行
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*　弱い敵の直線移動：一時待機：直線移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveStraightWaitUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// ゲームオブジェクトの状態を終了状態へ移行
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*　弱い敵の垂直に半円を描く移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveRoundVertical(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// ゲームオブジェクトの状態を終了状態へ移行
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*　弱い敵の水平に半円を描く移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveRoundHorizontal(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// ゲームオブジェクトの状態を終了状態へ移行
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*　弱い敵の上下ループ移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveLoopUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// ゲームオブジェクトの状態を終了状態へ移行
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*　弱い敵の左右ループ移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveLoopLeftRight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// ゲームオブジェクトの状態を終了状態へ移行
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/*　弱い敵の画面の端から顔出し行動
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::MoveShowOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Idle;

		// ゲームオブジェクトの状態を終了状態へ移行
		owner_->SetGameObjectState(GameObject::State::Dead);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/