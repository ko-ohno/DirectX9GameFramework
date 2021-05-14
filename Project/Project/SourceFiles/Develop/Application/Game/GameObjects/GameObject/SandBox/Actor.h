/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Actor.h] アクターゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アクターゲームオブジェクト
=============================================================================*/
#ifndef ACTOR_H_
#define	ACTOR_H_

/*--- インクルードファイル ---*/
#include "../GameObject.h"

/*-------------------------------------
/* アクターゲームオブジェクト
-------------------------------------*/
class Actor : public GameObject
{
public:
	Actor(class Game* game);
	virtual ~Actor(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Actor; }

private:
};


#endif //ACTOR_H_
/*=============================================================================
/*		End of File
=============================================================================*/