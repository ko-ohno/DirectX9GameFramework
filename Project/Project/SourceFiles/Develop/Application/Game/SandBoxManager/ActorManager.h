/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ActorManager.h] アクター管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アクター管理クラス
=============================================================================*/
#ifndef ACTOR_MANAGER_H_
#define	ACTOR_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* アクター管理クラス
-------------------------------------*/
class ActorManager
{
public:
	ActorManager(class Game* game);
	~ActorManager(void);

	static ActorManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止	

private:
	bool Init(void);	 //初期化
	void Uninit(void);	 //終了化

public:
	//
	// アクターの追加と削除
	//

	void AddActorGameObjectAddress(class Actor* Actor);
	void RemoveActorGameObjectAddress(class Actor* Actor);

	std::vector<class Actor*> GetActorGameObjectList(void) { return actor_list_; }

	class Game* GetGame(void) { return game_; }

private:
	// マネージャーの所有者
	class Game* game_;

	// アクターのコンテナ
	std::vector<class Actor*> actor_list_;
};

#endif //ACTOR_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/