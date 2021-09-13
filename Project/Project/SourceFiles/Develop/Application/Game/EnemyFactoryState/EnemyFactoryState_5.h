/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_5.h] エネミーファクトリの第5状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第5状態クラス
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_5_H_
#define	ENEMY_FACTORY_STATE_5_H_

/*--- インクルードファイル ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* エネミーファクトリの第5状態クラス
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