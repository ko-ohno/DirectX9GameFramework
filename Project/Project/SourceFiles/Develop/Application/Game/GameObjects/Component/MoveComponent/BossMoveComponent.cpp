/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossMoveComponent.cpp] ボスの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスの移動コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "BossMoveComponent.h"
#include "../../GameObject.h"
#include "../../../../Math.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BossMoveComponent::BossMoveComponent(GameObject* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
	, boss_ai_(nullptr)
	, enter_motion_state_(EnterMotionState::NONE)
	, attack_motion_state_(AttackMotionState::NONE)
	, boss_motion_state_(BossMotionState::NONE)
	, boss_motion_state_old_(BossMotionState::NONE)
	, position_(0.f, 0.f, 0.f)
	, yaw_(0.f)
	, pitch_(0.f)
	, roll_(0.f)
	, execute_time_(0.f)
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
	if (this->boss_ai_ == nullptr)
	{
		auto owner_component_list = owner_->GetComponents();

		//　総当たり検索をする
		for (auto owner_component : owner_component_list)
		{
			//
			auto type_id = owner_component->GetComponentType();
			if (type_id == Component::TypeID::BossAIComponent)
			{
				auto ai = owner_component;

				//ai->ge
				break;
			}
		}
	}

	// 各回転値の取得
	yaw_   = owner_transform_->GetAngleYaw();
	pitch_ = owner_transform_->GetAnglePitch();
	roll_  = owner_transform_->GetAngleRoll();

	// 線形球面保管を行うフラグをONに
	{
		owner_transform_->IsSetExecuteSlerp(true);
	}

	//owner_transform_->SetTranslation();

	//ボスのステートの更新
	boss_motion_state_old_ = boss_motion_state_;
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
	if (boss_motion_state_ != boss_motion_state_old_)
	{
		//攻撃状態の初期化
		enter_motion_state_ = EnterMotionState::FROM_RIGHT;
		execute_time_ = 0.f;
	}

	//アニメーションの時間
	const float MAX_EXE_TIME = 2.f;
	execute_time_ += deltaTime;

	switch (enter_motion_state_)
	{
	case EnterMotionState::FROM_RIGHT:
		// 座標の補間
		D3DXVec3Lerp(&position_
					, &enter_from_right_wait_position_
					, &enter_from_left_wait_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enter_motion_state_ = EnterMotionState::FLOM_LEFT;
		}
		break;

	case EnterMotionState::FLOM_LEFT:
		// 座標の補間
		D3DXVec3Lerp(&position_
					, &enter_from_left_wait_position_
					, &enter_from_right_wait_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enter_motion_state_ = EnterMotionState::FLOM_UNDER;
		}
		break;

	case EnterMotionState::FLOM_UNDER:
		// 座標の補間
		D3DXVec3Lerp(&position_
					, &enter_from_under_wait_position_
					, &wait_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enter_motion_state_ = EnterMotionState::END;
		}
		break;

	case EnterMotionState::END:
		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			boss_motion_state_ = BossMotionState::WAIT;
		}
		break;

	default:
		assert("不正なアニメーション遷移！！");
		break;
	}

	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/*　ボスの待機行動
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionWait(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// アニメーションの時間
	const float MAX_STATE_TIME = 5.f;
	execute_time_ += deltaTime;

	// モーションの実行時間が最大を超えたら
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		boss_motion_state_ = BossMotionState::WAIT;
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
	if (boss_motion_state_ != boss_motion_state_old_)
	{
		//攻撃状態の初期化
		attack_motion_state_ = AttackMotionState::START_UP;
		execute_time_ = 0.f;
	}

	switch (attack_motion_state_)
	{
	case AttackMotionState::START_UP:	//いったん下がって
		// 座標の補間
		D3DXVec3Lerp(&position_
					, &wait_position_
					, &body_press_startup_position_
					, Easing::SineIn(execute_time_));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::RELAY;
		}
		break;

	case AttackMotionState::RELAY:	//初期座標に戻ってから

		// 移動速度を二倍に
		execute_time_ += deltaTime;

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &body_press_startup_position_
					, &wait_position_
					, Easing::SineIn(execute_time_));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::ATTACK;
		}
		break;

	case AttackMotionState::ATTACK:	//攻撃

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &wait_position_
					, &body_press_position_
					, Easing::SineIn(execute_time_));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::END;
		}
		break;

	case AttackMotionState::END:	//余韻を残して待機行動へ

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &body_press_position_
					, &wait_position_
					, Easing::SineIn(execute_time_));

		// モーションの実行時間が最大を超えたら
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			boss_motion_state_ = BossMotionState::WAIT;
		}
		break;

	default:
		assert("ボスが不正な攻撃状態！！");
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
	if (boss_motion_state_ != boss_motion_state_old_)
	{
		//攻撃状態の初期化
		execute_time_ = 0.f;
		attack_motion_state_ = AttackMotionState::START_UP;
	}

	//アニメーションの時間
	const float MAX_STATE_TIME = 7.f;
	const float MAX_EXE_TIME = 1.f;
	execute_time_ += deltaTime;


	switch (attack_motion_state_)
	{
	case AttackMotionState::START_UP:

		// 回転の更新
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &wait_position_
					, &shoot_position_
					, Easing::SineIn(execute_time_));

		//状態の遷移
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::ATTACK;
		}
		break;

	case AttackMotionState::ATTACK:
		//回転の更新
		owner_transform_->SetSlerpSpeed(3.0f);
		owner_transform_->SetRotation(0, 90, roll_);
		owner_transform_->AddRotationRoll(4);

		//状態の遷移
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::END;
		}
		break;

	case AttackMotionState::END:
		//回転の更新
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &shoot_position_
					, &wait_position_
					, Easing::SineIn(execute_time_));

		//状態の遷移
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			boss_motion_state_ = BossMotionState::WAIT;
		}
		break;

	default:
		assert("ボスの不正な攻撃状態！！");
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
	if (boss_motion_state_ != boss_motion_state_old_)
	{
		//攻撃状態の初期化
		execute_time_ = 0.f;
		attack_motion_state_ = AttackMotionState::START_UP;

		//エフェクトの再生

	}

	//アニメーションの時間
	const float MAX_STATE_TIME = 7.f;
	execute_time_ += deltaTime;

	switch (attack_motion_state_)
	{
	case AttackMotionState::START_UP:
		// 回転の更新
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &wait_position_
					, &shoot_position_
					, Easing::SineIn(execute_time_));


		// 回転の更新
		if (execute_time_ >= 1.f)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::ATTACK;
		}
		break;

	case AttackMotionState::ATTACK:
		// 回転の更新
		owner_transform_->SetSlerpSpeed(3.0f);

		// プレイヤーの位置に合わせて角度を調整する
		owner_transform_->SetRotation(yaw_, 90, 0);
		owner_transform_->SetRotationYaw(45);

		// 回転の更新
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::END;
		}
		break;

	case AttackMotionState::END:
		// 回転の更新
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// 座標の補間
		D3DXVec3Lerp(&position_
					, &shoot_position_
					, &wait_position_
					, Easing::SineIn(execute_time_));

		// 回転の更新
		if (execute_time_ >= 1.f)
		{
			execute_time_ = 0.f;
			boss_motion_state_ = BossMotionState::WAIT;
		}
		break;

	default:
		assert("ボスの不正な攻撃状態！！");
		break;
	}

	//移動
	owner_transform_->SetTranslation(position_);
}

/*=============================================================================
/*		End of File
=============================================================================*/