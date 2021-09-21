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
	// 値コンポーネント取得用ゲームマネージャーへのポインタ
	class GameObject*					game_manager_;

private:
	class BillboardRendererComponent*	planet_billboard_;

	// 惑星の最大の大きさ
	static constexpr float MAX_PLANET_SCALE = 99;

	// 惑星の大きさ
	float planet_scale_;

	// 惑星の最大の大きさ
	static constexpr float MAX_PLANET_OFFSET_HEIGHT = -30;

	// 惑星のオフセット座標の高さ
	float planet_offset_height_;

	// ゲームの進行度
	int game_progress_value_;
};

#endif //PLANET_H_
/*=============================================================================
/*		End of File
=============================================================================*/