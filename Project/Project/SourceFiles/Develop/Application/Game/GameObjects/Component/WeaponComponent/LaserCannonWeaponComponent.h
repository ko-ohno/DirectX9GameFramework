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
#include "../MoveComponent/EnemyMoveComponent.h"

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

	void Shoot(void);

	void SetEnemyMotionState(EnemyMotionState motionState) { enemy_motion_state_ = motionState; }

private:
	// �G�̃X�e�[�g���擾
	EnemyMotionState					enemy_motion_state_;

	// ���[�U�[�̃Q�[���I�u�W�F�N�g
	class LargeLaser*					large_laser_;

	// ���[�U�[�𔭎˂��邩
	bool								is_fire_;

private:
	// ���̃R���|�[�l���g�̈ʒu������gizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //LASER_CANNON_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/