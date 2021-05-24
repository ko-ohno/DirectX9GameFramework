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
	class FFPMeshRendererComponent* mesh_space_ship_;

	class FFPMeshRendererComponent* test_mesh_;

	class EffectRendererComponent*  effect_after_burner_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/