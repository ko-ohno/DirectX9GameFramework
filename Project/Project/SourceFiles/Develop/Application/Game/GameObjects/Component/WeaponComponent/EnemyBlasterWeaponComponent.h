/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyBlasterWeaponComponent.h]  �R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�R���|�[�l���g
=============================================================================*/
#ifndef ENEMY_BLASTER_WEAPON_COMPONENT_H_
#define	ENEMY_BLASTER_WEAPON_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../WeaponComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �G�̕���R���|�[�l���g
-------------------------------------*/
class EnemyBlasterWeaponComponent : public WeaponComponent
{
public:
	EnemyBlasterWeaponComponent(class GameObject* owner, int updateOrder = 100);
	~EnemyBlasterWeaponComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::EnemyBlasterWeaponComponent; };

	// �G�̃^�[�Q�b�g�������鏈��
	class Actor* FindPlayerGameObject(void);

	// �U��
	void Fire(void);

protected:
	// �e�̔��˃G�t�F�N�g
	class EffectRendererComponent*		muzzle_flash_;

	// ���̃R���|�[�l���g�̈ʒu������gizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/