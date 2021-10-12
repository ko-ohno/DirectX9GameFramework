/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BlasterComponent.h]  光線銃武器コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：光線銃武器コンポーネント
=============================================================================*/
#ifndef BLASTER_WEAPON_COMPONENT_H_
#define	BLASTER_WEAPON_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../WeaponComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 光線銃武器コンポーネント
-------------------------------------*/
class BlasterWeaponComponent : public WeaponComponent
{
public:
	BlasterWeaponComponent(class GameObject* owner, int updateOrder = 100);
	~BlasterWeaponComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BlasterComponent; };

	// 攻撃
	void Fire(void);

protected:
	// 銃の発射エフェクト
	class EffectRendererComponent*		muzzle_flash_;

	// このコンポーネントの位置を示すgizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //BLASTER_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/