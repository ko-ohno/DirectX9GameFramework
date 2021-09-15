/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_1.h] �G�l�~�[�t�@�N�g���̑�1��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�1��ԃN���X
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_1_H_
#define	ENEMY_FACTORY_STATE_1_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* �G�l�~�[�t�@�N�g���̑�1��ԃN���X
-------------------------------------*/
class EnemyFactoryState_1 : public EnemyFactoryState
{
public:
	EnemyFactoryState_1(class Game* game);
	~EnemyFactoryState_1(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;

private:
};

#endif //ENEMY_FACTORY_STATE_1_H_
/*=============================================================================
/*		End of File
=============================================================================*/