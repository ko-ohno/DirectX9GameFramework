/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteTest.h] スプライトのテストゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトのテストゲームオブジェクト
=============================================================================*/
#ifndef SPRITE_TEST_H_
#define	SPRITE_TEST_H_

/*--- インクルードファイル ---*/
#include "../../GameObject.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* クラス
-------------------------------------*/
class SpriteTest : public GameObject
{
public:
	SpriteTest(class Game* game);
	~SpriteTest(void);

	static SpriteTest* Create(class Game* game);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化
	
	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
	class SpriteRendererComponent* sprite_;
	 
	class SpriteRendererComponent* sprite_a_;

	class SpriteRendererComponent* sprite_b_;
};


#endif //SPRITE_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/