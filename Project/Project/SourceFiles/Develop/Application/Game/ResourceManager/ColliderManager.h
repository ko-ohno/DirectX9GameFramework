/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderManager.h] コライダ管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：コライダ管理クラス
=============================================================================*/
#ifndef COLLIDER_MANAGER_H_
#define	COLLIDER_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* コライダの種類
-------------------------------------*/
enum class ColliderType
{
	None = -1
	, Circle
	, Rectangle
	, Sphere
	, OBB

	, Max
};

/*-------------------------------------
/* コライダ管理クラス
-------------------------------------*/
class ColliderManager
{
public:
	static const char* ColliderTypeNames[static_cast<int>(ColliderType::Max)];

public:
	ColliderManager(class Game* game);
	~ColliderManager(void);

	static ColliderManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止	

private:
	bool Init(void);	 //初期化
	void Uninit(void);	 //終了化

public:
	//
	// コライダの追加と削除
	//

	void AddColliderComponentAddress(class ColliderComponent* colliderComponent);
	void RemoveColliderComponentAddress(class ColliderComponent* colliderComponent);

	std::vector<class ColliderComponent*>& GetColliderComponentList(void) { return collider_list_; }

	class Game* GetGame(void) { return game_; }

private:
	// マネージャーの所有者
	class Game* game_;

	// コライダのコンテナ
	std::vector<class ColliderComponent*> collider_list_;
};


#endif //COLLIDER_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/