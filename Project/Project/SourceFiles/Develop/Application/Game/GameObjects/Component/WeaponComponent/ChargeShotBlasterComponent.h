/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeShotBlasterComponent.h]  �`���[�W�V���b�g�����e�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�`���[�W�V���b�g�����e�R���|�[�l���g
=============================================================================*/
#ifndef CHARGE_SHOT_BLASTER_COMPONENT_H_
#define	CHARGE_SHOT_BLASTER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../WeaponComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* ����R���|�[�l���g
-------------------------------------*/
class ChargeShotBlasterComponent : public WeaponComponent
{
public:
	ChargeShotBlasterComponent(class GameObject* owner, int updateOrder = 100);
	~ChargeShotBlasterComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::ChargeShotBlasterComponent; };

private:
	// �e�̔��˃G�t�F�N�g
	//class EffectRendererComponent* muzzle_flash_;
};

#endif //CHARGE_SHOT_BLASTER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/