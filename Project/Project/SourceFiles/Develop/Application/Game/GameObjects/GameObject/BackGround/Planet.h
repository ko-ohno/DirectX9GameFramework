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
	class BillboardRendererComponent*	planet_billboard_;

	// 惑星を大きくする最大の時間
	static constexpr float MAX_PLANET_SCALE_TIME_ = 99.f;

	// 惑星の最大の大きさ
	static constexpr float MAX_PLANET_SIZE_		= 150.f;
	static constexpr float DEFAULT_PLANET_SIZE_ =  50.f;

	// 現在進行形で惑星への影響時間
	float planet_scaling_time_;


	// 惑星をオフセットする最大の時間
	static constexpr float MAX_PLANET_OFFSET_TIME_ = 99.f;

	// 惑星のY座標の高さ
	static constexpr float MAX_PLANET_OFFSET_HEIGHT		= -30;
	static constexpr float DEFAULT_PLANET_OFFSET_HEIGHT = -20;

	// 惑星の現在のY座標の高さ
	float planet_offset_time_;

};

#endif //PLANET_H_
/*=============================================================================
/*		End of File
=============================================================================*/