/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Planet.h] 惑星ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：惑星ゲームオブジェクト
=============================================================================*/
#ifndef PLANET_H_
#define	PLANET_H_

/*--- インクルードファイル ---*/
#include "../BackGround.h"

/*-------------------------------------
/* 惑星ゲームオブジェクト
-------------------------------------*/
class Planet : public BackGround
{
public:
	Planet(class Game* game);
	~Planet(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Planet; }

private:
};

#endif //PLANET_H_
/*=============================================================================
/*		End of File
=============================================================================*/