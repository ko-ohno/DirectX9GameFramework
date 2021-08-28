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

private:
	static constexpr float ATTACK_VALUE_SHOOT		= 5.f;

	// 敵の武器コンポーネント
	class EnemyBlasterWeaponComponent* enemy_blaster_;
};

#endif //STRONG_ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/