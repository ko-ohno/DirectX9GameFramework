/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_3.h] エネミーファクトリの第3状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第3状態クラス
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_3_H_
#define	ENEMY_FACTORY_STATE_3_H_

/*--- インクルードファイル ---*/
#include "../EnemyFactoryState.h"


/*-------------------------------------
/* エネミーファクトリの第3状態クラス
-------------------------------------*/
class EnemyFactoryState_3 : public EnemyFactoryState
{
public:
	EnemyFactoryState_3(class Game* game);
	~EnemyFactoryState_3(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;

private:
};

#endif //ENEMY_FACTORY_STATE_3_H_
/*=============================================================================
/*		End of File
=============================================================================*/