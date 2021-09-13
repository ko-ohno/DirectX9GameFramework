/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_1.cpp] エネミーファクトリの第1状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第1状態クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "EnemyFactoryState_1.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EnemyFactoryState_1::EnemyFactoryState_1(class Game* game)
	: EnemyFactoryState(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EnemyFactoryState_1::~EnemyFactoryState_1(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool EnemyFactoryState_1::Init(void)
{
	//spawn_count = 5;
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void EnemyFactoryState_1::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void EnemyFactoryState_1::Update(float deltaTime)
{
	//
	// 開始座標を同じにして生成時間をずらす
	//

	if (spawn_count >= MAX_SPAWN_COUNT_) { return; }

	// エネミーを生成するための情報を初期化
	class WeakEnemy* enemy = nullptr;

	// 生成するフラグを初期化
	is_spawn = false;

	// 移動ベクトルの差分
	const float move_vector_diff   = 4.f;

	// 移動への情報を生成
	const float start_position_x = 35.f;
	const float start_position_y =  5.f;
	const float start_position_z = 15.f;

	// 移動ベクトルの長さ
	const float move_vector_length = (start_position_x * 2.f) + (move_vector_diff * HALF_SPAWN_COUNT_);

	// エネミーを生成する差分の時間を求める
	const float spawn_time = (SPAWN_DIFF_TIME_ * spawn_count);

	// 実行時間を計算
	execute_time_ += deltaTime;

	// エネミーの生成を行うか？
	const bool is_execute_spawn = ((execute_time_ >= spawn_time ) && (is_spawn == false));
	if (is_execute_spawn)
	{
		if(!(spawn_count >= HALF_SPAWN_COUNT_))
		{
			// 生成
			enemy = NEW WeakEnemy(game_);

			// 行動ステートを設定
			enemy->SetEnemyState(EnemyState::MoveStraightWaitOneTime);

			// 開始座標
			enemy->SetStartPosition(-start_position_x - ((move_vector_diff * spawn_count))
								   , start_position_y
								   , start_position_z);

			// 最大行動時間
			enemy->SetMaxExecuteTime(8.f);

			// 移動する向きと距離
			enemy->SetRotationMoveDirection(90.f, 0.f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// 移動アクションの深さ
			//enemy->SetMoveActionMagnitude(3.f);
		}
		else
		{
			// 生成
			enemy = NEW WeakEnemy(game_);

			// 行動ステートを設定
			enemy->SetEnemyState(EnemyState::MoveStraightWaitOneTime);

			// 開始座標
			enemy->SetStartPosition(start_position_x + (move_vector_diff * (spawn_count - HALF_SPAWN_COUNT_))
								   , -start_position_y
								   ,  start_position_z);

			// 最大行動時間
			enemy->SetMaxExecuteTime(8.f);

			// 移動する向きと距離
			enemy->SetRotationMoveDirection(-90.f, 0.f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// 移動アクションの深さ
			//enemy->SetMoveActionMagnitude(3.f);

		}

		// 生成カウントを加算
		spawn_count++;

		// 生成したことを記憶
		is_spawn = true;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/