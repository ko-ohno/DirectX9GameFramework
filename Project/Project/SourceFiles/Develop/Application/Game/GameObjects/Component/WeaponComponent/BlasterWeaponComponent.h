/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BlasterComponent.h]  �����e����R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e����R���|�[�l���g
=============================================================================*/
#ifndef BLASTER_WEAPON_COMPONENT_H_
#define	BLASTER_WEAPON_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../WeaponComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �����e����R���|�[�l���g
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

	// �U��
	void Fire(void);

protected:
	// �e�̔��˃G�t�F�N�g
	class EffectRendererComponent*		muzzle_flash_;

	// ���̃R���|�[�l���g�̈ʒu������gizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //BLASTER_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/