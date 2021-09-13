/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_3.h] �G�l�~�[�t�@�N�g���̑�3��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�3��ԃN���X
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_3_H_
#define	ENEMY_FACTORY_STATE_3_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* �G�l�~�[�t�@�N�g���̑�3��ԃN���X
-------------------------------------*/
class EnemyFactoryState_3 : public EnemyFactoryState
{
public:
	EnemyFactoryState_3(class Game* game);
	~EnemyFactoryState_3(void) override;

	bool Init(void) override;
	void Uninit(void) override;

private:
};

#endif //ENEMY_FACTORY_STATE_3_H_
/*=============================================================================
/*		End of File
=============================================================================*/