/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Boss.h] ボスゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明： ボスゲームオブジェクト
=============================================================================*/
#ifndef BOSS_H_
#define	BOSS_H_

/*--- インクルードファイル ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  敵ゲームオブジェクト
-------------------------------------*/
class Boss : public Enemy
{
public:
	Boss(class Game* game);
	~Boss(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Boss; }

	// 光線銃の更新
	void UpdateBlaster(float deltaTime, enum class EnemyState enemyState, enum class EnemyMotionState motionState);

	// レーザー砲の更新
	void UpdateLaserCannon(enum class EnemyState enemyState, enum class EnemyMotionState motionState);

private:
	static constexpr float ATTACK_VALUE_BODY_PRESS		= 10.f;
	static constexpr float ATTACK_VALUE_SHOOT			=  5.f;
	static constexpr float ATTACK_VALUE_LASER_CANNON	= 10.f;

	// 自身のステート情報
	EnemyState			enemy_state_old_;
	EnemyMotionState	motion_state_old_;

	// 最大武器数
	static constexpr int MAX_WEAPON_COUNT = 3;

	// 武器の発射用
	bool	is_fire_;
	int		blaster_index_;
	float	switch_time_;
	
	class EnemyBlasterWeaponComponent* enemy_blaster_[MAX_WEAPON_COUNT];
	class LaserCannonWeaponComponent*  laser_cannon_;
};

#endif //BOSS_H_
/*=============================================================================
/*		End of File
=============================================================================*/