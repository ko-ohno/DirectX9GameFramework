/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LaserCannonWeaponComponent.h]  ���[�U�[�C����R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���[�U�[�C����R���|�[�l���g
=============================================================================*/
#ifndef LASER_CANNON_WEAPON_COMPONENT_H_
#define	LASER_CANNON_WEAPON_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../WeaponComponent.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"

/*-------------------------------------
/* ���[�U�[�C����R���|�[�l���g
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
	// �e�̔��˃G�t�F�N�g
	class EffectRendererComponent*		test_effect_;

	// ���̃R���|�[�l���g�̈ʒu������gizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //LASER_CANNON_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/