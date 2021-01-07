/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Player.h] �v���C���[�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�v���C���[�̃Q�[���I�u�W�F�N�g�N���X��`
=============================================================================*/
#ifndef PLAYER_H_
#define	PLAYER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �v���C���[�̃Q�[���I�u�W�F�N�g�N���X
-------------------------------------*/
class Player : public GameObject
{
public:
	Player(class GameManager* gameManager);
	~Player(void);

	void UpdateGameObject(float deltaTime) override;

	TypeID GetType(void) const override { return TypeID::Player; }

private:
	class SpriteComponent* sprite_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/