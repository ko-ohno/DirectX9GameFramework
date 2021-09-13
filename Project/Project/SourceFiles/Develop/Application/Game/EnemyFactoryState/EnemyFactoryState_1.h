/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_1.h] エネミーファクトリの第1状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第1状態クラス
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_1_H_
#define	ENEMY_FACTORY_STATE_1_H_

/*--- インクルードファイル ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* エネミーファクトリの第1状態クラス
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