/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LargeLaser.h] 大型レーザーゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：大型レーザーゲームオブジェクト
=============================================================================*/
#ifndef LARGE_LASER_H_
#define	LARGE_LASER_H_

/*--- インクルードファイル ---*/
#include "../SandBox.h"

/*-------------------------------------
/* 大型レーザーゲームオブジェクト
-------------------------------------*/
class LargeLaser : public SandBox
{
public:
	LargeLaser(class Game* game);
	~LargeLaser(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
};


#endif //LARGE_LASER_H_
/*=============================================================================
/*		End of File
=============================================================================*/