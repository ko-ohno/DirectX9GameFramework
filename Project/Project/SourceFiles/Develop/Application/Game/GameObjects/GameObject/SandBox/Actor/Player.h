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

	GameObject::TypeID GetType(void) const override { return GameObject::TypeID::Player; }

private:
	class SpriteRendererComponent* sprite_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/