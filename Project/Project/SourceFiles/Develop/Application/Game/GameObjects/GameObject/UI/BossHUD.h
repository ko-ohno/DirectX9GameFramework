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

	virtual TypeID GetType(void) const { return TypeID::BossHUD; }

	// HUDの値を更新
	void UpdateHUDValue(float deltaTime);

	// 体力
	void UpdateHealthBarHUD(float deltaTime);

	// 射撃のアラートHUD
	void UpdateWeakPointHUD(float deltaTime);

	// 射撃のアラートHUD
	void UpdateAlertShootHUD(float deltaTime);

	// 巨大レーザーと体当たり攻撃のアラートのHUD
	void UpdateHorizontalAlertHUD(float deltaTime);

private:
	// 値コンポーネント取得用ゲームマネージャーへのポインタ
	class GameObject*				game_manager_;

	// エネミーの状態
	enum class EnemyState			boss_state_;
	enum class EnemyState			boss_state_old_;

	// ボスの動きの状態
	enum class EnemyMotionState		boss_motion_state_;

	float							delete_time_;

private:
	// ボスの体力ゲージ
	class SpriteRendererComponent*	health_bar_;
	class SpriteRendererComponent*	health_bar_blank_;
	class SpriteRendererComponent*	health_bar_bg_;

	// ボス最大の体力値
	float	max_boss_hp_value_;

	// ボスの体力値
	float	boss_hp_value_;

	// 現在のHPの割合
	float	boss_hp_rate_;

	// プレイヤーの体力値
	float	player_hp_value_;

private:
	// ボスの弱点表示
	class BillboardRendererComponent* weak_point_hud_;

	static constexpr float			  MAX_HUD_ANIMATION_TIME_ = 1.f;

	float							  hud_animation_time_;

private:
	//
	//	ボスの攻撃アラート
	//

	static constexpr float			  MAX_ALERT_TIME_ = 2.5f;

	// アラートを発生させているか
	bool							  is_execute_alert_;

	// アラートを発生させているか
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