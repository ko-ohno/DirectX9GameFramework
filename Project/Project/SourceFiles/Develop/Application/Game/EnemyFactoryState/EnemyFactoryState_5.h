/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_5.h] �G�l�~�[�t�@�N�g���̑�5��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�5��ԃN���X
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_5_H_
#define	ENEMY_FACTORY_STATE_5_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* �G�l�~�[�t�@�N�g���̑�5��ԃN���X
-------------------------------------*/
class EnemyFactoryState_5 : public EnemyFactoryState
{
public:
	EnemyFactoryState_5(class Game* game);
	~EnemyFactoryState_5(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;

private:
};

#endif //ENEMY_FACTORY_STATE_5_H_
/*=============================================================================
/*		End of File
=============================================================================*/