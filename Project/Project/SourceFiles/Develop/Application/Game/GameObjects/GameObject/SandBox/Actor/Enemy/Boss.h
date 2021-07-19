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

private:
	static constexpr float ATTACK_VALUE_BODY_PRESS		= 10.f;
	static constexpr float ATTACK_VALUE_SHOOT			=  5.f;
	static constexpr float ATTACK_VALUE_LASER_CANNON	= 10.f;

	// 最大武器数
	static constexpr int MAX_WEAPON_COUNT = 3;
	
	class BlasterWeaponComponent* blaster_[MAX_WEAPON_COUNT];
};

#endif //BOSS_H_
/*=============================================================================
/*		End of File
=============================================================================*/