/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Player.h] プレイヤーゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：プレイヤーゲームオブジェクト
=============================================================================*/
#ifndef PLAYER_H_
#define	PLAYER_H_

/*--- インクルードファイル ---*/
#include "../Actor.h"

/*-------------------------------------
/* プレイヤーのゲームオブジェクト
-------------------------------------*/
class Player : public Actor
{
public:
	Player(class Game* game);
	~Player(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	TypeID GetType(void) const override { return TypeID::Player; }

private:
	// 値コンポーネントの更新
	void UpdateParameter(float deltaTime);

	// 武器の更新
	void UpdateWeapon(float deltaTime);

	// エフェクトの更新
	void UpdatePirticleEffect(float deltaTime);

	// 衝突判定の更新
	void UpdateCollision(float deltaTime);

private:
	// 移動コンポーネント
	class PlayerMoveComponent*			 player_move_;

	//
	// 描画コンポーネント
	//

	class EffectRendererComponent*		 effect_after_burner_;
	class EffectRendererComponent*		 effect_enemy_attack_hit_;

	// レティクル

	class BillboardRendererComponent*	 far_reticle_;
	class BillboardRendererComponent*	 near_reticle_;
	
	// 武器コンポーネント

	class BlasterWeaponComponent*		 left_blaster_;
	class BlasterWeaponComponent*		 right_blaster_;
	class ChargeBlasterWeaponComponent*	 charge_blaster_;

	//
	// 音声コンポーネント
	//

	class AudioComponent*				 player_damege_sound_effect_;

	//
	// 値コンポーネント
	//

	// プレイヤーの最大HPの値コンポーネント
	class FloatParameterComponent*		max_hp_param_;
	//int								max_hp_value_;	//Actorクラスで設定済み

	// プレイヤーのHPの値コンポーネント
	class FloatParameterComponent*		hp_param_;
	//int								hp_value_;		//Actorクラスで設定済み

private:
	// 光線銃を発射するか 
	bool								is_blaster_fire_;

	// キー入力を有効にするか
	bool								is_enable_key_input_;

private:
	//
	// プレイヤーへの衝突判定
	//

	// プレイヤーに敵の攻撃がヒットしたか？
	bool					is_received_damage_;

	// 次にプレイヤーがダメージを受けるまでの時間
	static constexpr float	MAX_DAMAGE_RECIEVE_INTERVAL_TIME_ = 2.f;

	// ボスへのダメージを与えるインターバルの時間
	float					damage_recieve_interval_time_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/