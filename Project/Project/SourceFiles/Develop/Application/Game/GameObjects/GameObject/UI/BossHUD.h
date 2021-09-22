/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossHUD.h] ボスのHUDクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスのHUDクラス
=============================================================================*/
#ifndef BOSS_HUD_H_
#define	BOSS_HUD_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/*　ボスのHUDクラス
-------------------------------------*/
class BossHUD : public UI
{
public:
	BossHUD(class Game* game);
	~BossHUD(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;


private:
	// 値コンポーネント取得用ゲームマネージャーへのポインタ
	class GameObject*				game_manager_;

private:
	// ボスの体力ゲージ
	class SpriteRendererComponent*	health_bar_;
	class SpriteRendererComponent*	health_bar_blank_;
	class SpriteRendererComponent*	health_bar_bg_;

	// 最大の体力値
	float	max_hp_value_;

	// 体力値
	float	hp_value_;

	// 現在のHPの割合
	float	hp_rate_;

private:



};


#endif //BOSS_HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/