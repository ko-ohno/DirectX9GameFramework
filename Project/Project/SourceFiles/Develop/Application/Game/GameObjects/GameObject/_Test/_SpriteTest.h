/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteTest.h] スプライトテスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトテスト用ゲームオブジェクト
=============================================================================*/
#ifndef SPRITE_TEST_H_
#define	SPRITE_TEST_H_

/*--- インクルードファイル ---*/
#include "../../GameObject.h"

/*-------------------------------------
/* スプライトテスト用ゲームオブジェクト
-------------------------------------*/
class SpriteTest : public GameObject
{
public:
	SpriteTest(class Game* game);
	~SpriteTest(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化
	
	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::SpriteTest; }

private:
	class SpriteRendererComponent* sprite_;
	class SpriteRendererComponent* sprite_a_;
	class SpriteRendererComponent* sprite_b_;
};


#endif //SPRITE_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/