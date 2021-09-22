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

	// 体力
	void UpdateHealthBarHUD(float deltaTime);

	// 射撃のアラートHUD
	void UpdateAlertShootHUD(float deltaTime);

	// 巨大レーザーと体当たり攻撃のアラートのHUD
	void UpdateHorizontalAlertHUD(float deltaTime);

private:
	// 値コンポーネント取得用ゲームマネージャーへのポインタ
	class GameObject*				game_manager_;

	// ボスへのポインタ
	class Enemy*					boss_;

	// エネミーの状態
	enum class EnemyState			boss_state_;

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
	// ボスの弱点表示
	class BillboardRendererComponent* weak_point_;

private:
	//
	//	ボスの攻撃アラート
	//

	static constexpr float			  MAX_ALERT_TIME = 3.f;

	// アラートを実行するか
	bool							  is_alert_;

	// アラートの全体の実行時間
	float							  alert_execute_time_;

	// アラートの局所の実行時間
	float							  alert_time_;

	// ビックリマーク
	class BillboardRendererComponent* alert_exclamation_;

	// 背景
	class BillboardRendererComponent* alert_bg_;

	// アラートのSE
	class AudioComponent*			  alert_se_;
	
};


#endif //BOSS_HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/