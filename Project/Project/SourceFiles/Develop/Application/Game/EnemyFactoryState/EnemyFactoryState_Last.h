/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_Last.h] エネミーファクトリの最後の状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第6状態クラス
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_LAST_H_
#define	ENEMY_FACTORY_STATE_LAST_H_

/*--- インクルードファイル ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* エネミーファクトリの最後の状態クラス
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