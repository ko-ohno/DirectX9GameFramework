/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemy.h] 弱い敵のゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明： 弱い敵のゲームオブジェクト
=============================================================================*/
#ifndef STRONG_ENEMY_H_
#define	STRONG_ENEMY_H_

/*--- インクルードファイル ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  敵ゲームオブジェクト
-------------------------------------*/
class StrongEnemy : public Enemy
{
public:
	StrongEnemy(class Game* game);
	~StrongEnemy(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::StrongEnemy; }

	// 光線銃の更新
	void UpdateBlaster(float deltaTime, enum class EnemyState enemyState, enum class EnemyMotionState motionState);

	// 衝突判定の更新
	void UpdateCollision(float deltaTime);

	void TestMoveStraight();
	void TestMoveStraightWaitOneTime();
	void TestMoveRoundVertical();
	void TestMoveRoundHorizontal();
	void TestMoveLoopUpDown();
	void TestMoveLoopLeftRight();
	void TestMoveShowOneTime();
	void TestMoveStraightWaitUpDown();

private:
	//
	// エフェクトコンポーネント
	//
	class EffectRendererComponent*		effect_enemy_action_shoot_;

private:
	static constexpr float				ATTACK_VALUE_SHOOT		= 5.f;

	// 敵の武器コンポーネント
	class EnemyBlasterWeaponComponent*	enemy_blaster_;

	// ブラスターを発射するまでの時間
	float								blaster_execute_time_;

	// 武器の発射用
	bool								is_ready_;
	bool								is_fire_;
};

#endif //STRONG_ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/