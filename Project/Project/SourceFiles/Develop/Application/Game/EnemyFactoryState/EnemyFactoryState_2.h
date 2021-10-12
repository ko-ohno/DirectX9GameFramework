/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_2.h] �G�l�~�[�t�@�N�g���̑�2��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�2��ԃN���X
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_2_H_
#define	ENEMY_FACTORY_STATE_2_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* �G�l�~�[�t�@�N�g���̑�2��ԃN���X
-------------------------------------*/
class EnemyFactoryState_2 : public EnemyFactoryState
{
public:
	EnemyFactoryState_2(class Game* game);
	~EnemyFactoryState_2(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;

private:
};

#endif //ENEMY_FACTORY_STATE_2_H_
/*=============================================================================
/*		End of File
=============================================================================*/