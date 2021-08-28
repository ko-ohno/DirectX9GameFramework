/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyMoveComponent.cpp] ボスの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスの移動コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "WeakEnemyMoveComponent.h"
#include "../../../GameObject.h"
#include "../../../../../Math.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
WeakEnemyMoveComponent::WeakEnemyMoveComponent(GameObject* owner, int updateOrder)
	: EnemyMoveComponent(owner, updateOrder)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ 
-----------------------------------------------------------------------------*/
WeakEnemyMoveComponent::~WeakEnemyMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool WeakEnemyMoveComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 自機の各回転値の取得
	yaw_   = owner_transform_->GetAngleYaw();
	pitch_ = owner_transform_->GetAnglePitch();
	roll_  = owner_transform_->GetAngleRoll();

	// 回転の補間を行うフラグをONに
	{
		owner_transform_->IsSetExecuteSlerpRotation(true);
	}

	// 始点座標から、補間する終点座標の計算
	{
		this->ComputeLerpPosition();
	}

	// 自身の状態を表記
	ImGui::Begin("week_enemy_move_state");
	{
		// 自分の行動状態
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
			assert(!"WeakEnemyMoveComponent::Update()：弱い敵が不正な行動ステートにあります！");
			break;
		}
	}
	ImGui::Text("PosX:%f", position_.x);
	ImGui::Text("PosY:%f", position_.y);
	ImGui::Text("PosZ:%f", position_.z);

	// 実行時間
	ImGui::Text("move_exe_time:%f",execute_time_);

	// 自分のモーションの状態
	ImGui::Text("motion_state:");
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		ImGui::Text("StartUp");
		break;
	case EnemyMotionState::MoveState_0:
		ImGui::Text("MoveState_0");
		break;
	case EnemyMotionState::MoveState_1:
		ImGui::Text("MoveState_1");
		break;
	case EnemyMotionState::MoveState_2:
		ImGui::Text("MoveState_2");
		break;
	case EnemyMotionState::MoveState_3:
		ImGui::Text("MoveState_3");
		break;
	case EnemyMotionState::MoveState_4:
		ImGui::Text("MoveState_4");
		break;
	case EnemyMotionState::Complete:
		ImGui::Text("Complete");
		break;
	case EnemyMotionState::End:
		ImGui::Text("End");
		break;
	default:
		break;
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
		assert(!"WeakEnemyMoveComponent::Update()：弱い敵が不正な行動ステートにあります！");
		break;
	}

	//ボスのステートの更新
	enemy_state_old_ = enemy_state_;
}

/*-----------------------------------------------------------------------------
/* 待機行動
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::MoveActionIdle(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

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
/* 直線移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::MoveActionStraight(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// 所有者の状態が、1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::MoveState_0;
		execute_time_ = 0.f;
	}

	// アニメーションの実行時間が最大実行時間を上回ったら
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// 実際の挙動を定義
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::MoveState_0:
		// 座標を補間
		D3DXVec3Lerp(&position_												// 現在座標
					, &position_start_										// 始点座標
					, &position_finish_										// 終点座標
					, Easing::Linear(execute_time_, max_execute_time_));	// 補間の仕方
		
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::MoveState_0;
		execute_time_ = 0.f;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionStraight()：不正なモーションの状態！");
		break;
	}

	// 移動
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* 直線移動して一回待つ行動
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::MoveActionStraightWaitOneTime(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// 所有者の状態が、1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// アニメーションの実行時間が最大実行時間を上回ったら
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// 実際の挙動を定義
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// 座標を補間
		D3DXVec3Lerp(&position_
					, &position_start_
					, &position_finish_
					, Easing::SineInOut(execute_time_, max_execute_time_));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_ * 0.5f))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::MoveState_0:

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			execute_time_ = (max_execute_time_ * 0.5f);
		}
		break;

	case EnemyMotionState::MoveState_1:
		// 座標を補間
		D3DXVec3Lerp(&position_
					, &position_start_
					, &position_finish_
					, Easing::SineInOut(execute_time_, max_execute_time_));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
		}
		break;


	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp; // 最初に戻る
		break;


	default:
		assert(!"EnemyMoveComponent::MoveActionStraightWaitOneTime()：不正なモーションの状態！");
		break;
	}

	// 移動
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* 直線移動して上下運動と複数回待つ行動
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::MoveActionStraightWaitUpDown(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// 所有者の状態が、1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// アニメーションの実行時間が最大実行時間を上回ったら
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// X・Z軸上は、通常どおり移動
	{
		position_.x = Math::Lerp(position_start_.x, position_finish_.x, Easing::SineInOut(execute_time_, max_execute_time_));
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	// 各ステートの時間を分割した倍率
	const float max_state_div_value = 0.083f; // 1を12分割
	
	//　補間中のy軸座標
	float axis_y_lerping_position = 0.f;

	// 実際の挙動を定義
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:

		position_.y = Math::Lerp(position_start_.y 
								, position_finish_.y + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value) * 0.5f));


		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= ((max_execute_time_ * max_state_div_value) * 0.5f))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_2;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::MoveState_1:
		// 上昇
		position_.y = Math::Lerp(position_start_.y + move_action_magnitude_ 
								, position_finish_.y + move_action_magnitude_ * -1.f
								, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// 終了ステートへ
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			break;
		}

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_2;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::MoveState_2:
		// 下降
		position_.y = Math::Lerp(position_start_.y + move_action_magnitude_
								, position_finish_.y + move_action_magnitude_ * -1.f
								, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));


		// 終了ステートへ
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			break;
		}

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::MoveState_3:
		//待機


		//
		// 上の時と下の時で一時停止と条件分岐をはさむ
		//

		// 上だった場合
		{
			axis_y_lerping_position = Math::Lerp(position_start_.y + move_action_magnitude_
												, position_finish_.y + move_action_magnitude_ * -1.f
												, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));
	
			if (position_.y >= axis_y_lerping_position)
			{
				axis_y_lerping_position = axis_y_lerping_position;
			} 
		}
	

		//　下だった場合
		{
			axis_y_lerping_position = Math::Lerp(position_start_.y + move_action_magnitude_
												, position_finish_.y + move_action_magnitude_ * -1.f
												, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));



			if (position_.y <= axis_y_lerping_position)
			{
				axis_y_lerping_position = axis_y_lerping_position;
			}
		}
		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_ * ((max_state_div_value * 2.f) * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp; // 最初に戻る
		execute_time_ = 0.f;
		state_loop_count_ = 0;
		break;


	default:
		assert(!"EnemyMoveComponent::MoveActionStraightWaitUpDown()：不正なモーションの状態！");
		break;
	}

	// 移動
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* 垂直に半円を描く移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::MoveActionRoundVertical(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// 所有者の状態が、1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// アニメーションの実行時間が最大実行時間を上回ったら
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// Y・Z軸上は、通常どおり移動
	{
		position_.y = Math::Lerp(position_start_.y, position_finish_.y, Easing::SineInOut(execute_time_, max_execute_time_));
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	right_vector_;

	// 実際の挙動を定義
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// 座標を補間
		position_.x = Math::Lerp(position_start_.x 
								, position_finish_.x + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * 0.5f)));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_ * 0.5f))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			//execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::MoveState_0:

		// 座標を補間
		position_.x = Math::Lerp(position_finish_.x 
								, position_finish_.x + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * 0.5)));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_))
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionRoundVertical()：不正なモーションの状態！");
		break;
	}

	// 移動
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* 水平に半円を描く移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::MoveActionRoundHorizontal(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// 所有者の状態が、1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// アニメーションの実行時間が最大実行時間を上回ったら
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// X・Z軸上は、通常どおり移動
	{
		position_.x = Math::Lerp(position_start_.x, position_finish_.x, Easing::SineInOut(execute_time_, max_execute_time_));
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	// 実際の挙動を定義
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// 座標を補間
		position_.y = Math::Lerp(position_finish_.y
								, position_finish_.y + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * 0.5f)));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_ * 0.5f))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
		}
		break;

	case EnemyMotionState::MoveState_0:
		// 座標を補間
		position_.y = Math::Lerp(position_finish_.y
								, position_finish_.y + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * 0.5f)));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_))
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionRoundHorizontal()：不正なモーションの状態！");
		break;
	}

	// 移動
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* 上下ループ移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::MoveActionLoopUpDown(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// 所有者の状態が、1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// アニメーションの実行時間が最大実行時間を上回ったら
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// X・Z軸上は、通常どおり移動
	{
		position_.x = Math::Lerp(position_start_.x, position_finish_.x, Easing::SineInOut(execute_time_, max_execute_time_));
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	// 各ステートの時間を分割した倍率
	const float max_state_div_value = 0.143f; // 1を7分割

	// 実際の挙動を定義
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp: 
		// 導入 
		position_.y = Math::Lerp(position_start_.y
								, position_finish_.y + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
		}
		break;

	case EnemyMotionState::MoveState_0: 
		// 上昇
		position_.y = Math::Lerp(position_finish_.y + move_action_magnitude_ * -1.f
								, position_finish_.y + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// 条件を満たしたら終了ステートへ
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
			state_loop_count_ = 0;
			break;
		}

		// 次のステートへ
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::MoveState_1:
		// 下降
		position_.y = Math::Lerp((position_finish_.y + move_action_magnitude_) * -1.f
								, position_finish_.y + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// 条件を満たしたら終了ステートへ
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
			state_loop_count_ = 0;
			break;
		}

		// ひとつ前のステートへ
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionLoopUpDown()：不正なモーションの状態！");
		break;
	}

	// 移動
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* 左右ループ移動行動
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::MoveActionLoopLeftRight(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// 所有者の状態が、1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// アニメーションの実行時間が最大実行時間を上回ったら
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// Y・Z軸上は、通常どおり移動
	{
		position_.y = Math::Lerp(position_start_.y, position_finish_.y, Easing::SineInOut(execute_time_, max_execute_time_));
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	// 各ステートの時間を分割した倍率
	const float max_state_div_value = 0.143f;  // 1を7分割

	// 実際の挙動を定義
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// 導入 
		position_.x = Math::Lerp(position_start_.x
								, position_finish_.x + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
		}
		break;

	case EnemyMotionState::MoveState_0:
		// 左へ
		position_.x = Math::Lerp((position_finish_.x + move_action_magnitude_) * -1.f
								, position_finish_.x + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// 条件を満たしたら終了ステートへ
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
			state_loop_count_ = 0;
			break;
		}

		// 次のステートへ
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::MoveState_1:
		// 右へ
		position_.x = Math::Lerp((position_finish_.x + move_action_magnitude_) * -1.f
								, position_finish_.x + move_action_magnitude_
								, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// 条件を満たしたら終了ステートへ
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
			state_loop_count_ = 0;
			break;
		}

		// ひとつ前のステートへ
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionLoopLeftRight()：不正なモーションの状態！");
		break;
	}

	// 移動
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* 画面の端からひょっこり顔をだす
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::MoveActionShowOneTime(float deltaTime)
{
	// 回転の更新
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// 所有者の状態が、1フレーム前と差異があった場合
	if (enemy_state_ != enemy_state_old_)
	{
		//攻撃状態の初期化
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// アニメーションの実行時間が最大実行時間を上回ったら
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// 実際の挙動を定義
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// 座標を補間
		D3DXVec3Lerp(&position_
					, &position_start_
					, &position_finish_
					, Easing::SineInOut(execute_time_, max_execute_time_));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= (max_execute_time_ * 0.5f))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::MoveState_0:

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= max_execute_time_ * 0.5f)
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			execute_time_ = (max_execute_time_ * 0.5f);
		}
		break;

	case EnemyMotionState::MoveState_1:
		// 座標を補間
		D3DXVec3Lerp(&position_
					, &position_finish_
					, &position_start_
					, Easing::SineInOut(execute_time_, max_execute_time_));

		// 条件を満たしたら次のモーションステートへ
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp; // 最初に戻る
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionStraightWaitOneTime()：不正なモーションの状態！");
		break;
	}

	// 移動
	owner_transform_->SetTranslation(position_);
}

/*=============================================================================
/*		End of File
=============================================================================*/