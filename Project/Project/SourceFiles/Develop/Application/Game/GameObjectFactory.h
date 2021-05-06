/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameObjectFactory.h] ゲームオブジェクトのファクトリクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームオブジェクトの生成と削除を管理するクラス
=============================================================================*/
#ifndef GAME_OBJECT_FACTORY_H_
#define	GAME_OBJECT_FACTORY_H_

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"

/*-------------------------------------
/* ゲームオブジェクトのファクトリクラス
-------------------------------------*/
class GameObjectFactory
{
public:
	GameObjectFactory(class Game* game);
	~GameObjectFactory(void);

	static GameObjectFactory* Create(class Game* game);

	bool StartUp(void);
	void ShutDown(void);

	void Input(void);
	void Update(float deltaTime);

private:
	void AddGameObject(class GameObject* gameObject);
	void RemoveGameObjectAll(void);

private:
	std::vector<class GameObject*> game_objects_;
	class Game* game_;

};

#endif //GAME_OBJECT_FACTORY_H_
/*=============================================================================
/*		End of File
=============================================================================*/