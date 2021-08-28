/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyMoveComponent.cpp] ボスの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスの移動コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "StrongEnemyMoveComponent.h"
#include "../../../GameObject.h"
#include "../../../../../Math.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
StrongEnemyMoveComponent::StrongEnemyMoveComponent(GameObject* owner, int updateOrder)
	: EnemyMoveComponent(owner, updateOrder)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
StrongEnemyMoveComponent::~StrongEnemyMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool StrongEnemyMoveComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 自機の各回転値の取得
	yaw_	= owner_transform_->GetAngleYaw();
	pitch_	= owner_transform_->GetAnglePitch();
	roll_	= owner_transform_->GetAngleRoll();

	// 回転の補間を行うフラグをONに
	{
		owner_transform_->IsSetExecuteSlerpRotation(true);
	}

	// 自身の状態を表記
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
			assert(!"StrongEnemyMoveComponent::Update()：強い敵が不正な行動ステートにあります！");
			break;
		}
	}
	ImGui::End();

	// 敵の状態更新
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
		assert(!"StrongEnemyMoveComponent::Update()：強い敵が不正な行動ステートにあります！");
		break;
	}

	//ボスのステートの更新
	enemy_state_old_ = enemy_state_;
}

/*-----------------------------------------------------------------------------
/*　強い敵の待機行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionIdle(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*　強い敵の移動行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionStraight(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*　強い敵の移動行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionStraightWaitOneTime(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*　強い敵の移動行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionStraightWaitUpDown(float deltaTime)
{
}

/*-----------------------------------------------------------------------------
/*　強い敵の移動行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionRoundVertical(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*　強い敵の移動行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionRoundHorizontal(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*　強い敵の移動行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionLoopUpDown(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*　強い敵の移動行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionLoopLeftRight(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*　強い敵の移動行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionShowOneTime(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*　強い敵の移動行動
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionSShapedCurve(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/