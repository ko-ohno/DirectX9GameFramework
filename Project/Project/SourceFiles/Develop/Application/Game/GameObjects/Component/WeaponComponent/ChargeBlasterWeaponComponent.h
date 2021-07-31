/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBlasterWeaponComponent.h]  �����e����R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e����R���|�[�l���g
=============================================================================*/
#ifndef CHARGE_BLASTER_WEAPON_COMPONENT_H_
#define	CHARGE_BLASTER_WEAPON_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../WeaponComponent.h"
#include "../../GameObject/SandBox/ChargeBullet.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �����e����R���|�[�l���g
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

	// �`���[�W�e�̍쐬
	void CreateChargeBullet(void);

	// �`���[�W�e�̔���
	void Fire(void);

	// ���b�N�I�������Ă��邩
	void IsSetLockon(bool isLockon) { is_lockon_ = isLockon; }

	// �`���[�W�e�̃C���X�^���X���m�F
	bool IsCheckChargeBulletInstance(void);

	// ���e�B�N���̃C���X�^���X��
	void SetLockonReticle(class BillboardRendererComponent* lockonReticle) { lockon_reticle_ = lockonReticle; }

	// �`���[�W�e�̏�Ԃ̐ݒ�
	ChargeBulletState GetChargeBulletState(void);
	void SetChargeBulletState(ChargeBulletState chargeBulletState);

private:
	bool								is_lockon_;
	bool								is_fire_;

	class ChargeBullet*					charge_bullet_;

protected:
	// �e�̔��˃G�t�F�N�g
	class EffectRendererComponent*		muzzle_flash_;

	// ���b�N�I���̃��e�B�N��
	class BillboardRendererComponent*	lockon_reticle_;
	
	// ���̃R���|�[�l���g�̈ʒu������gizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //BLASTER_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/