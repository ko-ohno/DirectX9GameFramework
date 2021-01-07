/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Enemy.h] �G�l�~�[�̃Q�[���I�u�W�F�N�g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�̃Q�[���I�u�W�F�N�g�N���X��`
=============================================================================*/
#ifndef ENEMY_H_
#define	ENEMY_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �G�l�~�[�̃Q�[���I�u�W�F�N�g�N���X
-------------------------------------*/
class Enemy : public GameObject
{
public:
	Enemy(class GameManager* gameManager);
	~Enemy(void);

	void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Enemy; }

private:
	class SpriteComponent* sprite_;
};

#endif //ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/