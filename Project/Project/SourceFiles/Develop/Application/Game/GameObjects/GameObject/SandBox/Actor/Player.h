/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Player.h] �v���C���[�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�v���C���[�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef PLAYER_H_
#define	PLAYER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Actor.h"

/*-------------------------------------
/* �v���C���[�̃Q�[���I�u�W�F�N�g
-------------------------------------*/
class Player : public Actor
{
public:
	Player(class Game* game);
	~Player(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	TypeID GetType(void) const override { return TypeID::Player; }

private:
	// �l�R���|�[�l���g�̍X�V
	void UpdateParameter(float deltaTime);

	// ����̍X�V
	void UpdateWeapon(float deltaTime);

	// �G�t�F�N�g�̍X�V
	void UpdatePirticleEffect(float deltaTime);

private:
	// �ړ��R���|�[�l���g
	class PlayerMoveComponent*			 player_move_;

	//
	// �`��R���|�[�l���g
	//

	class EffectRendererComponent*		 effect_after_burner_;

	// ���e�B�N��

	class BillboardRendererComponent*	 far_reticle_;
	class BillboardRendererComponent*	 near_reticle_;
	class BillboardRendererComponent*	 lockon_reticle_;
	
	// ����R���|�[�l���g

	class BlasterWeaponComponent*		 left_blaster_;
	class BlasterWeaponComponent*		 right_blaster_;
	class ChargeBlasterWeaponComponent*	 charge_blaster_;

	// ���b�N�I���p�Փ˔���R���|�[�l���g

	class OBBColliderComponent*			 lockon_collider_;
	class BoxGizmoRendererComponent*	 lockon_gizmo_;

	//
	// �l�R���|�[�l���g�̍X�V
	//

	// �v���C���[�̍ő�HP�̒l�R���|�[�l���g
	class FloatParameterComponent*		max_hp_param_;
	//int								max_hp_value_;	//Actor�N���X�Őݒ�ς�

	// �v���C���[��HP�̒l�R���|�[�l���g
	class FloatParameterComponent*		hp_param_;
	//int								hp_value_;		//Actor�N���X�Őݒ�ς�

	// �����e�𔭎˂��邩 
	bool is_blaster_fire_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/