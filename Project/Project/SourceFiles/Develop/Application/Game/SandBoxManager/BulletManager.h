/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BulletManager.h] アクター管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アクター管理クラス
=============================================================================*/
#ifndef BULLET_MANAGER_H_
#define	BULLET_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* バレット管理クラス
-------------------------------------*/
class BulletManager
{
public:
	BulletManager(class Game* game);
	~BulletManager(void);

	static BulletManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止	

private:
	bool Init(void);	 //初期化
	void Uninit(void);	 //終了化

public:
	//
	// バレットの追加と削除と検索
	//

	void AddBulletGameObjectAddress(class Bullet* bullet);
	void RemoveBulletGameObjectAddress(class Bullet* bullet);
	class Bullet* FindBulletGameObjectAddress(class Bullet* bullet);

	const std::vector<class Bullet*>& GetBulletGameObjectList(void) const { return bullet_list_; }

	class Game* GetGame(void) { return game_; }

private:
	// マネージャーの所有者
	class Game* game_;

	// バレットのコンテナ
	std::vector<class Bullet*> bullet_list_;
};

#endif //BULLET_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/