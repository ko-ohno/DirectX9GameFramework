/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[HUD.h] ゲーム画面のHUDクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲーム画面のHUDの挙動を定義したクラス
=============================================================================*/
#ifndef HUD_H_
#define	HUD_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* ゲーム画面のHUDクラス
-------------------------------------*/
class HUD : public UI
{
public:
	HUD(class Game* game);
	~HUD(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::HUD; }

	// 体力
	void UpdateHealthBarHUD(float deltaTime);
	
	//　ゴールまでの距離
	void UpdateGoalMeterHUD(float deltaTime);

	//　ゴールまでの距離
	void UpdateScoreHUD(float deltaTime);

private:
	// 体力ゲージ
	class SpriteRendererComponent* health_bar_;
	class SpriteRendererComponent* health_bar_blank_;
	class SpriteRendererComponent* health_bar_bg_;

	// 体力値
	float health_value_;

private:
	// ゴールまでの距離のHUD
	class SpriteRendererComponent* meter_center_bg_;
	class SpriteRendererComponent* meter_left_bg_;
	class SpriteRendererComponent* meter_right_bg_;

	// 数字桁の表示
	class SpriteDigitRendererComponent* distance_digit_;

	// ゴールまでの距離の値
	int distance_value_;


private:
	// 数字桁の表示
	class SpriteDigitRendererComponent* score_digit_;

	// ゴールまでの距離の値
	int score_value_;
};

#endif //HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/