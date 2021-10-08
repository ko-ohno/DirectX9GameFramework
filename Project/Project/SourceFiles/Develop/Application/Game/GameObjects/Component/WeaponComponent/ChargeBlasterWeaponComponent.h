/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBlasterWeaponComponent.h]  光線銃武器コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：光線銃武器コンポーネント
=============================================================================*/
#ifndef CHARGE_BLASTER_WEAPON_COMPONENT_H_
#define	CHARGE_BLASTER_WEAPON_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../WeaponComponent.h"
#include "../../GameObject/SandBox/Bullet/ChargeBullet.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 光線銃武器コンポーネント
-------------------------------------*/
class ChargeBlasterWeaponComponent : public WeaponComponent
{
public:
	ChargeBlasterWeaponComponent(class GameObject* owner, int updateOrder = 100);
	~ChargeBlasterWeaponComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BlasterComponent; };

	// チャージ弾の作成
	void CreateChargeBullet(void);

	// チャージ弾の発射
	void Fire(void);

	// ロックオンの標的を更新
	void UpdateLockonTarget(float deltaTime);

	// チャージ弾のインスタンスを確認
	bool IsCheckChargeBulletInstance(void);

	// チャージ弾の状態の設定
	ChargeBulletState GetChargeBulletState(void);
	void SetChargeBulletState(ChargeBulletState chargeBulletState);

private:
	bool								is_bullet_created_;
	bool								is_fire_;

private: 
	// 標的へのポインタ
	class Enemy*						target_enemy_;

	// ロックオンが有効になっているか？
	bool								is_enable_lockon_;

	// 現在のロックオンの状態が解除されるまでの最大時間
	static constexpr float				MAX_LOCKON_RELEASE_TIME_ = 2.f;

	// 現在のロックオンの状態が解除されるまでの現在時間
	float								lockon_release_time_;

	// ロックオンの最大アニメーション時間
	static constexpr float				MAX_LOCKON_RETICLE_ANIMATION_TIME_ = 0.5f;

	// ロックオンの現在のアニメーション時間
	float								lockon_reticle_animation_time_;

	// ロックオンのHUDの最大アニメーション時間
	static constexpr float				MAX_LOCKON_RETICLE_HUD_ANIMATION_TIME_ = 1.f;

	// ロックオンのHUDの現在のアニメーション時間
	float								lockon_reticle_hud_animation_time_;

	// ロックオンのレティクルの座標
	D3DXVECTOR3							lockon_reticle_src_pos_;
	D3DXVECTOR3							lockon_reticle_dst_pos_;

private:
	// チャージ弾へのポインタ
	class ChargeBullet*					charge_bullet_;

protected:
	// 銃の発射エフェクト
	class EffectRendererComponent*		muzzle_flash_;

	// ロックオンのレティクル
	class BillboardRendererComponent*	lockon_reticle_;

	// ロックオンのレティクル：所有者の姿勢の影響を受けている
	class BillboardRendererComponent*   lockon_reticle_owner_transform_order_;

	// ロックオンの警告音
	class AudioComponent*				lockon_alert_se_;

	// ロックオン用衝突判定コンポーネント
	class OBBColliderComponent*			lockon_collider_;
	class BoxGizmoRendererComponent*	lockon_gizmo_;

	// このコンポーネントの位置を示すgizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //BLASTER_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/