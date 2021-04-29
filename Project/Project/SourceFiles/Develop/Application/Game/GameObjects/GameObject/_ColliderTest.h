/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderTest.h] 衝突判定テスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：テスト用ゲームオブジェクト
=============================================================================*/
#ifndef ColliderTest_H_
#define	ColliderTest_H_

/*--- インクルードファイル ---*/
#include "../GameObject.h"

/*-------------------------------------
/* テスト用ゲームオブジェクト
-------------------------------------*/
class ColliderTest : public GameObject
{
public:
	ColliderTest(class Game* game);
	~ColliderTest(void);

	static ColliderTest* Create(class Game* game);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
};


#endif //ColliderTest_H_
/*=============================================================================
/*		End of File
=============================================================================*/