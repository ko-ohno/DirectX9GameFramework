/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LaserCannonWeaponComponent.h]  レーザー砲武器コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：レーザー砲武器コンポーネント
=============================================================================*/
#ifndef LASER_CANNON_WEAPON_COMPONENT_H_
#define	LASER_CANNON_WEAPON_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../WeaponComponent.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"

/*-------------------------------------
/* レーザー砲武器コンポーネント
-------------------------------------*/
class LaserCannonWeaponComponent : public WeaponComponent
{
public:
	LaserCannonWeaponComponent(class GameObject* owner, int updateOrder = 100);
	~LaserCannonWeaponComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::LaserCannonWeaponComponent; };

private:
	class LargeLaser*					large_laser_;

private:
	// 銃の発射エフェクト
	class EffectRendererComponent*		test_effect_;

	// このコンポーネントの位置を示すgizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //LASER_CANNON_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/