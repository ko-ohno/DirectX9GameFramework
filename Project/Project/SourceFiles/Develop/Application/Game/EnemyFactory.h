/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactory.h] エネミーのファクトリクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーのファクトリクラス
=============================================================================*/
#ifndef ENEMY_FACTORY_H_
#define	ENEMY_FACTORY_H_

/*--- インクルードファイル ---*/

/*-------------------------------------
/* エネミーのファクトリクラス
-------------------------------------*/
class EnemyFactory
{
public:
	EnemyFactory(class Game* game);
	~EnemyFactory(void);

	bool Init(void);
	void Uninit(void);
	void Input(void);
	void Update(float deltaTime);

	// ファクトリの状態切り替え処理
	void ChangeFactoryState(class EnemyFactoryState* factory_state_);

private:
	class Game*				 game_;

	// エネミーのファクトリの状態クラス
	class EnemyFactoryState* enemy_factory_state_;
};

#endif //ENEMY_FACTORY_H_
/*=============================================================================
/*		End of File
=============================================================================*/