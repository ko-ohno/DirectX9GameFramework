/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_2.cpp] エネミーファクトリの第2状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第2状態クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "EnemyFactoryState_2.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EnemyFactoryState_2::EnemyFactoryState_2(class Game* game)
	: EnemyFactoryState(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EnemyFactoryState_2::~EnemyFactoryState_2(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool EnemyFactoryState_2::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void EnemyFactoryState_2::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void EnemyFactoryState_2::Update(float deltaTime)
{
	//
	// 開始座標を同じにして生成時間をずらす
	//

	if (spawn_count_ >= MAX_SPAWN_COUNT_) { return; }

	// エネミーを生成するための情報を初期化
	class WeakEnemy* enemy = nullptr;

	// 生成するフラグを初期化
	is_spawn_ = false;

	// 移動ベクトルの差分
	const float move_vector_diff = 4.f;

	// 移動への情報を生成
	const float start_position_x =  30.f;
	const float start_position_y =  25.f;
	const float start_position_z =  20.f;

	// 移動ベクトルの長さ
	const float move_vector_length = start_position_x * 2.f;

	// 移動アクションの大きさ
	const float move_action_magnitude = 20.f;

	// エネミーを生成する差分の時間を求める
	const float spawn_time = (SPAWN_DIFF_TIME_ * spawn_count_);

	// 実行時間を計算
	execute_time_ += deltaTime;

	// エネミーの生成を行うか？
	const bool is_execute_spawn = ((execute_time_ >= spawn_time) && (is_spawn_ == false));
	if (is_execute_spawn)
	{
		// 生成数が半分以下だったら
		if (!(spawn_count_ >= HALF_SPAWN_COUNT_))
		{
			// 生成
			enemy = NEW WeakEnemy(game_);

			// 行動ステートを設定
			enemy->SetEnemyState(EnemyState::MoveRoundHorizontal);

			// 開始座標
			enemy->SetStartPosition(-start_position_x
								   , start_position_y
								   , start_position_z);

			// 最大行動時間
			enemy->SetMaxExecuteTime(8.f);

			// 移動する向きと距離
			enemy->SetRotationMoveDirection(90.f, 0.f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// 移動アクションの深さ
			enemy->SetMoveActionMagnitude(-move_action_magnitude);
		}
		else
		{
			// 生成
			enemy = NEW WeakEnemy(game_);

			// 行動ステートを設定
			enemy->SetEnemyState(EnemyState::MoveRoundHorizontal);

			// 開始座標
			enemy->SetStartPosition(start_position_x
								   , -start_position_y
								   , start_position_z);

			// 最大行動時間
			enemy->SetMaxExecuteTime(8.f);

			// 移動する向きと距離
			enemy->SetRotationMoveDirection(-90.f, 0.f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// 移動アクションの深さ
			enemy->SetMoveActionMagnitude(move_action_magnitude);
		}

		// 生成カウントを加算
		spawn_count_++;

		// 生成したことを記憶
		is_spawn_ = true;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/