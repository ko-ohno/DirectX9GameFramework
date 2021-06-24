/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemy.h] 弱い敵のゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明： 弱い敵のゲームオブジェクト
=============================================================================*/
#ifndef WEAK_ENEMY_H_
#define	WEAK_ENEMY_H_

/*--- インクルードファイル ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  敵ゲームオブジェクト
-------------------------------------*/
class WeakEnemy : public Enemy
{
public:
	WeakEnemy(class Game* game);
	~WeakEnemy(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::WeakEnemy; }

private:
};

#endif //WeakEnemy_H_
/*=============================================================================
/*		End of File
=============================================================================*/