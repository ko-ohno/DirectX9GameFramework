/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_Last.h] �G�l�~�[�t�@�N�g���̍Ō�̏�ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�6��ԃN���X
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_LAST_H_
#define	ENEMY_FACTORY_STATE_LAST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* �G�l�~�[�t�@�N�g���̍Ō�̏�ԃN���X
-------------------------------------*/
class EnemyFactoryState_Last : public EnemyFactoryState
{
public:
	EnemyFactoryState_Last(class Game* game);
	~EnemyFactoryState_Last(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;

private:
};

#endif //ENEMY_FACTORY_STATE_LAST_H_
/*=============================================================================
/*		End of File
=============================================================================*/