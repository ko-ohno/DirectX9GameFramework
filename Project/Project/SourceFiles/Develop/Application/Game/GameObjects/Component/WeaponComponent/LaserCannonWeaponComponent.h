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
#include "../MoveComponent/EnemyMoveComponent.h"

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

	void Shoot(void);

	void SetEnemyMotionState(EnemyMotionState motionState) { enemy_motion_state_ = motionState; }

private:
	// 敵のステートを取得
	EnemyMotionState					enemy_motion_state_;

	// レーザーのゲームオブジェクト
	class LargeLaser*					large_laser_;

	// レーザーを発射するか
	bool								is_fire_;

private:
	// このコンポーネントの位置を示すgizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //LASER_CANNON_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/