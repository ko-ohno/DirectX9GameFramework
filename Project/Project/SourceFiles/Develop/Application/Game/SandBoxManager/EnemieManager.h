/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemieManager.h] エネミー管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミー管理クラス
=============================================================================*/
#ifndef ENEMIE_MANAGER_H_
#define	ENEMIE_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* エネミー管理クラス
-------------------------------------*/
class EnemieManager
{
public:
	EnemieManager(class Game* game);
	~EnemieManager(void);

	static EnemieManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止	

private:
	bool Init(void);	 //初期化
	void Uninit(void);	 //終了化

public:
	//
	// エネミーの追加と削除
	//

	void AddEnemyGameObjectAddress(class Enemy* enemy);
	void RemoveEnemyGameObjectAddress(class Enemy* enemy);

	// 検索処理
	class Enemy* FindEnemyGameObjectAddress(class Enemy* enemy);

	const std::vector<class Enemy*>& GetEnemyGameObjectList(void) const { return enemy_list_; }

	class Game* GetGame(void) { return game_; }

private:
	// マネージャーの所有者
	class Game* game_;

	// アクターのコンテナ
	std::vector<class Enemy*> enemy_list_;
};

#endif //ENEMIE_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/