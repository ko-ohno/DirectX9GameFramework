/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardTest.h] ビルボードをテストするためのゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ビルボードをテストするためのゲームオブジェクト
=============================================================================*/
#ifndef BILLBOARD_TEST_H_
#define	BILLBOARD_TEST_H_

/*--- インクルードファイル ---*/
#include "../GameObject.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* クラス
-------------------------------------*/
class BillboardTest : public GameObject
{
public:
	BillboardTest(class Game* game);
	~BillboardTest(void);

	static BillboardTest* Create(class Game* game);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
	class BillboardRendererComponent* billboard_;
	class BillboardRendererComponent* billboard_a_;
};


#endif //BILLBOARD_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/