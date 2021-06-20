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
	// �ړ��R���|�[�l���g
	class PlayerMoveComponent*		  player_move_;

	// �`��R���|�[�l���g
	class EffectRendererComponent*    effect_after_burner_;

	// �����̃��e�B�N��
	class BillboardRendererComponent* far_reticle_;

	// ��O�̃��e�B�N��
	class BillboardRendererComponent* near_reticle_;

	// ���b�N�I���̃��e�B�N��
	class BillboardRendererComponent* lockon_reticle_;
	
	// ����R���|�[�l���g
	class BlasterComponent*			  left_blaster_;
	class BlasterComponent*			  right_blaster_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/