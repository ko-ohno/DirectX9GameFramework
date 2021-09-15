/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_6.h] �G�l�~�[�t�@�N�g���̑�6��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�6��ԃN���X
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_6_H_
#define	ENEMY_FACTORY_STATE_6_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* �G�l�~�[�t�@�N�g���̑�6��ԃN���X
-------------------------------------*/
class EnemyFactoryState_6 : public EnemyFactoryState
{
public:
	EnemyFactoryState_6(class Game* game);
	~EnemyFactoryState_6(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;

private:
};

#endif //ENEMY_FACTORY_STATE_6_H_
/*=============================================================================
/*		End of File
=============================================================================*/