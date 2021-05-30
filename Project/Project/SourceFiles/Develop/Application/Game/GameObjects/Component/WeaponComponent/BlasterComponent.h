/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BlasterComponent.h]  �����e�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e�R���|�[�l���g
=============================================================================*/
#ifndef BLASTER_COMPONENT_H_
#define	BLASTER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../WeaponComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* ����R���|�[�l���g
-------------------------------------*/
class BlasterComponent : public WeaponComponent
{
public:
	BlasterComponent(class GameObject* owner, int updateOrder = 100);
	~BlasterComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BlasterComponent; };

	void Fire(void);

private:
	// �e�̔��˃G�t�F�N�g
	class EffectRendererComponent* muzzle_flash_;
};

#endif //WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/