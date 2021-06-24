/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemy.h] �ア�G�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F �ア�G�̃Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef WEAK_ENEMY_H_
#define	WEAK_ENEMY_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  �G�Q�[���I�u�W�F�N�g
-------------------------------------*/
class StrongEnemy : public Enemy
{
public:
	StrongEnemy(class Game* game);
	~StrongEnemy(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::StrongEnemy; }

private:
};

#endif //StrongEnemy_H_
/*=============================================================================
/*		End of File
=============================================================================*/