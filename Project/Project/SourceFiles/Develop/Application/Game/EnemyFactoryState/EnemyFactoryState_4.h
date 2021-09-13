/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_4.h] エネミーファクトリの第4状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第4状態クラス
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_4_H_
#define	ENEMY_FACTORY_STATE_4_H_

/*--- インクルードファイル ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* エネミーファクトリの第4状態クラス
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