/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_2.h] エネミーファクトリの第2状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第2状態クラス
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_2_H_
#define	ENEMY_FACTORY_STATE_2_H_

/*--- インクルードファイル ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* エネミーファクトリの第2状態クラス
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