/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectTest.h] エフェクトテストゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エフェクトテストゲームオブジェクト
=============================================================================*/
#ifndef EFFECT_TEST_H_
#define	EFFECT_TEST_H_

/*--- インクルードファイル ---*/
#include "../../GameObject.h"


/*-------------------------------------
/* エフェクトテストゲームオブジェクト
-------------------------------------*/
class EffectTest : public GameObject
{
public:
	EffectTest(class Game* game);
	~EffectTest(void);

	static EffectTest* Create(class Game* game);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
	class EffectRendererComponent* effect_renderer_comp_;

	class EffectRendererComponent* effect_renderer_comp_a;
	class EffectRendererComponent* effect_renderer_comp_b;

};

#endif //EFFECT_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/