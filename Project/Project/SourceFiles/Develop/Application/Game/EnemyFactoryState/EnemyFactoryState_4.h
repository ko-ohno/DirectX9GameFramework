/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_4.h] �G�l�~�[�t�@�N�g���̑�4��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�4��ԃN���X
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_4_H_
#define	ENEMY_FACTORY_STATE_4_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* �G�l�~�[�t�@�N�g���̑�4��ԃN���X
-------------------------------------*/
class EnemyFactoryState_4 : public EnemyFactoryState
{
public:
	EnemyFactoryState_4(class Game* game);
	~EnemyFactoryState_4(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;

private:
};

#endif //ENEMY_FACTORY_STATE_4_H_
/*=============================================================================
/*		End of File
=============================================================================*/