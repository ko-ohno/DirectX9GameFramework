/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_6.h] エネミーファクトリの第6状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第6状態クラス
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_6_H_
#define	ENEMY_FACTORY_STATE_6_H_

/*--- インクルードファイル ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* エネミーファクトリの第6状態クラス
-------------------------------------*/
class EnemyFactoryState_6 : public EnemyFactoryState
{
public:
	EnemyFactoryState_6(class Game* game);
	~EnemyFactoryState_6(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;

private:
};

#endif //ENEMY_FACTORY_STATE_6_H_
/*=============================================================================
/*		End of File
=============================================================================*/