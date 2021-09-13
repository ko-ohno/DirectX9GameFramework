/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState.h] エネミーファクトリの状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの状態クラス
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_H_
#define	ENEMY_FACTORY_STATE_H_

/*--- インクルードファイル ---*/
#include "GameObjects/GameObject/SandBox/Actor/Enemy/Boss.h"
#include "GameObjects/GameObject/SandBox/Actor/Enemy/StrongEnemy.h"
#include "GameObjects/GameObject/SandBox/Actor/Enemy/WeakEnemy.h"

/*-------------------------------------
/* エネミーファクトリの状態クラス
-------------------------------------*/
class EnemyFactoryState
{
public:
	EnemyFactoryState(class Game* game)
		: game_(game)
		, execute_time_(0.f)
		, is_spawn(false)
		, spawn_count(0)
	{}
	virtual ~EnemyFactoryState(void) {}

	virtual bool Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(float deltaTime) = 0;

protected:
	class Game* game_;

	// 各ステートの最大生成数
	static constexpr int	MAX_SPAWN_COUNT_ = 10;

	// 最大生成数の半分の数
	static constexpr int	HALF_SPAWN_COUNT_ = static_cast<int>(MAX_SPAWN_COUNT_ * 0.5f);

	// 生成の差分時間
	static constexpr float	SPAWN_DIFF_TIME_ = 1.0f;
	
	// 実行時間
	float execute_time_;

	// 生成するか？
	bool is_spawn;

	// 生成したか？
	int  spawn_count;
};


#endif //ENEMY_FACTORY_STATE_H_
/*=============================================================================
/*		End of File
=============================================================================*/