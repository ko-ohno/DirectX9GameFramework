/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BackGround.h] 背景ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：背景ゲームオブジェクト
=============================================================================*/
#ifndef BACK_GROUND_H_
#define	BACK_GROUND_H_

/*--- インクルードファイル ---*/
#include "../GameObject.h"

/*-------------------------------------
/* 背景ゲームオブジェクト
-------------------------------------*/
class BackGround : public GameObject
{
public:
	BackGround(class Game* game);
	virtual ~BackGround(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::BackGround; }

private:
};


#endif //BACK_GROUND_H_
/*=============================================================================
/*		End of File
=============================================================================*/