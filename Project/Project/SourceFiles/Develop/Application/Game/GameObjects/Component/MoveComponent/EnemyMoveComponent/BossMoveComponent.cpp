/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossMoveComponent.cpp] ボスの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスの移動コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "BossMoveComponent.h"
#include "../../../GameObject.h"
#include "../../../../../Math.h"
#include "../../../../SandBoxManager/ActorManager.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BossMoveComponent::BossMoveComponent(GameObject* owner, int updateOrder)
	: EnemyMoveComponent(owner, updateOrder)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ 
-----------------------------------------------------------------------------*/
BossMoveComponent::~BossMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BossMoveComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void BossMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void BossMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void BossMoveComponent::Update(float deltaTime)
{
	// 各回転値の取得
	yaw_   = owner_transform_->GetAngleYaw();
	pitch_ = owner_transform_->GetAnglePitch();
	roll_  = owner_transform_->GetAngleRoll();

	// 回転の補間を行うフラグをONに
	{
		owner_transform_->IsSetExecuteSlerpRotation(true);
	}

	// 自身の状態を表記
	ImGui::Begin("boss_move_state");
	{
		switch (enemy_state_)
		{
		case EnemyState::Enter:
			ImGui::Text("enter");
			break;

		case EnemyState::Idle:
			ImGui::Text("idle");
			break;

		case EnemyState::BodyPress:
			ImGui::Text("body_press");
			break;

		case EnemyState::Shooting:
			ImGui::Text("shooting");
			break;

		case EnemyState::LaserCannon:
			ImGui::Text("laser_cannon");
			break;
		}
	}
	ImGui::End();

	// 敵の状態更新
	switch (enemy_state_)
	{
	case EnemyState::Enter:
		this->MoveActionEnter(deltaTime);
		break;
	
	case EnemyState::Idle:
		this->MoveActionIdle(deltaTime);
		break;

	case EnemyState::BodyPress:
		this->MoveActionBodyPress(deltaTime);
		break;

	case EnemyState::Shooting:
		this->MoveActionShoot(deltaTime);
		break;
	
	case EnemyState::LaserCannon:
		this->MoveActionLaserCannon(deltaTime);
		break;

	default:
		assert(!"BossMoveComponent::Update()：ボスが不正な行動ステートにあります！");
		break;
	}

	//ボスのステートの更新
	enemy_state_old_ = enemy_state_;
}

/*-----------------------------------------------------------------------------
/*　ボスの登場行動
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionEnter(float deltaTime)
{
	//回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotationPitch(10);
	owner_transform_->AddRotationYaw(4);

	//1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::MoveState_0;
		execute_time_ = 0.f;
	}

	//アニメーションの時間
	const float MAX_EXE_TIME = 2.f;
	execute_time_ += deltaTime;

	switch (enemy_motion_state_)
	{
	case EnemyMotionState::MoveState_0:
		// 座標の補間
		D3DXVec3Lerp(&position_
					, &enter_from_right_idle_position_
					, &enter_from_left_idle_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
		}
		break;

	case EnemyMotionState::MoveState_1:
		// 座標の補間
		D3DXVec3Lerp(&position_
					, &enter_from_left_idle_position_
					, &enter_from_right_idle_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::MoveState_2;
		}
		break;

	case EnemyMotionState::MoveState_2:
		// 座標の補間
		D3DXVec3Lerp(&position_
					, &enter_from_under_idle_position_
					, &idle_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Complete;
		}
		break;

	case EnemyMotionState::Complete:
		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		break;

	default:
		assert(!"BossMoveComponent::MoveActionEnter()：不正なモーションの状態！");
		break;
	}

	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/*　ボスの待機行動
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionIdle(float deltaTime)
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
/*　ボスのボディプレス攻撃行動
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionBodyPress(float deltaTime)
{
	//回転の処理
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->AddRotationYaw(4);

	//アニメーションの時間
	const float MAX_STATE_TIME = 1.0f;
	const float MAX_EXE_TIME = 1.0f;
	execute_time_ += deltaTime;

	//1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:	//いったん下がって
		// 座標の補間
		D3DXVec3Lerp(&position_
					, &idle_position_
					, &body_press_startup_position_
					, Easing::SineIn(execute_time_));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Relay;
		}
		break;

	case EnemyMotionState::Relay:	//初期座標に戻ってから

		// 移動速度を二倍に
		execute_time_ += deltaTime;

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &body_press_startup_position_
					, &idle_position_
					, Easing::SineIn(execute_time_));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Attack;
		}
		break;

	case EnemyMotionState::Attack:	//攻撃

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &idle_position_
					, &body_press_position_
					, Easing::SineIn(execute_time_));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Complete;
		}
		break;

	case EnemyMotionState::Complete:	//余韻を残して待機行動へ

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &body_press_position_
					, &idle_position_
					, Easing::SineIn(execute_time_));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		break;

	default:
		assert(!"BossMoveComponent::MoveActionBodyPress()：不正なモーションの状態！");
		break;
	}

	// 移動
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/*　ボスの射撃攻撃行動
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionShoot(float deltaTime)
{
	//1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	//アニメーションの時間
	const float MAX_START_UP_TIME = 1.f;
	const float MAX_RELAY_TIME = 2.f;
	const float MAX_STATE_TIME = 7.f;
	const float MAX_EXE_TIME = 1.f;
	execute_time_ += deltaTime;

	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:

		// 回転の更新
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &idle_position_
					, &shoot_position_
					, Easing::SineIn(execute_time_));

		//状態の遷移
		if (execute_time_ >= MAX_START_UP_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Relay;
		}
		break;

	case EnemyMotionState::Relay:
		// 回転の更新
		owner_transform_->SetSlerpSpeed(5.0f);

		// プレイヤーの位置に合わせて角度を調整する
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(90.f, pitch_, 90.f);
		owner_transform_->AddRotationPitch(4);

		if (execute_time_ >= MAX_RELAY_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Attack;
		}
		break;

	case EnemyMotionState::Attack:

		//回転の更新
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(90.f, pitch_, 90.f);
		owner_transform_->AddRotationPitch(4);

		//状態の遷移
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Complete;
		}
		break;

	case EnemyMotionState::Complete:
		//回転の更新
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &shoot_position_
					, &idle_position_
					, Easing::SineIn(execute_time_));

		//状態の遷移
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		break;

	default:
		assert(!"BossMoveComponent::MoveActionShoot()：不正なモーションの状態！");
		break;
	}

	//移動
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/*　ボスのレーザー砲攻撃行動
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionLaserCannon(float deltaTime)
{
	//1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;

		//エフェクトの再生

	}
	static float angle = 45.f;


	//アニメーションの時間
	const float MAX_STATE_TIME	= 1.f;
	const float MAX_ATTACK_TIME = 7.f;
	const float MAX_RELAY_TIME	= 1.f;

	execute_time_ += deltaTime;

	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// 回転の更新
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &idle_position_
					, &shoot_position_
					, Easing::SineIn(execute_time_));


		// 回転の更新
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Relay;
		}
		break;

	case EnemyMotionState::Relay:
		// 回転の更新
		owner_transform_->SetSlerpSpeed(3.0f);

		// プレイヤーの位置に合わせて角度を調整する
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(45, 90, 0);

		if (execute_time_ >= MAX_RELAY_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Attack;
		}
		break;

	case EnemyMotionState::Attack:
		// 回転の更新
		owner_transform_->SetSlerpSpeed(3.0f);

		// プレイヤーの位置に合わせて角度を調整する
		owner_transform_->SetRotation(yaw_, 90, 0);
		yaw_ = Math::Lerp(45.f, -45.f, Easing::CubicInOut(execute_time_ / 7.f));
		owner_transform_->SetRotationYaw(yaw_);

		// 回転の更新
		if (execute_time_ >= MAX_ATTACK_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Complete;
		}
		break;

	case EnemyMotionState::Complete:
		// 回転の更新
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &shoot_position_
					, &idle_position_
					, Easing::SineIn(execute_time_));

		// 回転の更新
		if (execute_time_ >= 1.f)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		break;

	default:
		assert(!"BossMoveComponent::MoveActionLaserCannon()：不正なモーションの状態！");
		break;
	}

	//移動
	owner_transform_->SetTranslation(position_);
}

/*=============================================================================
/*		End of File
=============================================================================*/