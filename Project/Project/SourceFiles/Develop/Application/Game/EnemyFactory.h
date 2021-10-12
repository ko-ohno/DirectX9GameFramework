/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactory.h] �G�l�~�[�̃t�@�N�g���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�̃t�@�N�g���N���X
=============================================================================*/
#ifndef ENEMY_FACTORY_H_
#define	ENEMY_FACTORY_H_

/*--- �C���N���[�h�t�@�C�� ---*/

/*-------------------------------------
/* �G�l�~�[�̃t�@�N�g���N���X
-------------------------------------*/
class EnemyFactory
{
public:
	EnemyFactory(class Game* game);
	~EnemyFactory(void);

	bool Init(void);
	void Uninit(void);
	void Input(void);
	void Update(float deltaTime);

	// �t�@�N�g���̏�Ԑ؂�ւ�����
	void ChangeFactoryState(class EnemyFactoryState* factory_state_);

private:
	class Game*				 game_;

	// �G�l�~�[�̃t�@�N�g���̏�ԃN���X
	class EnemyFactoryState* enemy_factory_state_;
};

#endif //ENEMY_FACTORY_H_
/*=============================================================================
/*		End of File
=============================================================================*/