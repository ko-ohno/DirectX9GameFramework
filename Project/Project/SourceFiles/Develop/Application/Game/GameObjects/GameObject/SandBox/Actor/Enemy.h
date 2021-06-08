/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Enemy.h] �G�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F �G�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef ENEMY_H_
#define	ENEMY_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Actor.h"

/*-------------------------------------
/*  �G�Q�[���I�u�W�F�N�g
-------------------------------------*/
class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	~Enemy(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Enemy; }

protected:
};

#endif //ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/