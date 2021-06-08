/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Enemy.h] 敵ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明： 敵ゲームオブジェクト
=============================================================================*/
#ifndef ENEMY_H_
#define	ENEMY_H_

/*--- インクルードファイル ---*/
#include "../Actor.h"

/*-------------------------------------
/*  敵ゲームオブジェクト
-------------------------------------*/
class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	~Enemy(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Enemy; }

protected:
};

#endif //ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/