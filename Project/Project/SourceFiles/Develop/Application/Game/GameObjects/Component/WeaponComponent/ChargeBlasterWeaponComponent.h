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
#include "../../GameObject/SandBox/ChargeBullet.h"

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

	// ロックオンをしているか
	void IsSetLockon(bool isLockon) { is_lockon_ = isLockon; }

	// チャージ弾のインスタンスを確認
	bool IsCheckChargeBulletInstance(void);

	// レティクルのインスタンスを
	void SetLockonReticle(class BillboardRendererComponent* lockonReticle) { lockon_reticle_ = lockonReticle; }

	// チャージ弾の状態の設定
	ChargeBulletState GetChargeBulletState(void);
	void SetChargeBulletState(ChargeBulletState chargeBulletState);

private:
	bool								is_lockon_;
	bool								is_fire_;

	class ChargeBullet*					charge_bullet_;

protected:
	// 銃の発射エフェクト
	class EffectRendererComponent*		muzzle_flash_;

	// ロックオンのレティクル
	class BillboardRendererComponent*	lockon_reticle_;
	
	// このコンポーネントの位置を示すgizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //BLASTER_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/