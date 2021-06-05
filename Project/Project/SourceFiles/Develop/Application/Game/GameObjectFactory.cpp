/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameObjectFactory.cpp] ゲームオブジェクトのファクトリクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームオブジェクトのファクトリクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "GameObjectFactory.h"
#include "Game.h"
#include "GameObjects/GameObject.h"

//テスト用ゲームオブジェクト
#include "GameObjects/GameObject/_Test/_CameraTest.h"
#include "GameObjects/GameObject/_Test/_SpriteTest.h"
#include "GameObjects/GameObject/_Test/_MeshTest.h"
#include "GameObjects/GameObject/_Test/_BillboardTest.h"
#include "GameObjects/GameObject/_Test/_EffectTest.h"
#include "GameObjects/GameObject/_Test/_AudioTest.h"
#include "GameObjects/GameObject/_Test/_ColliderTest.h"
#include "GameObjects/GameObject/_Test/_SaveDataTest.h"

//ゲーム用ゲームオブジェクト
#include "GameObjects/GameObject/GameManager.h"
#include "GameObjects/GameObject/BackGround/SkyBox.h"
#include "GameObjects/GameObject/BackGround/Planet.h"

#include "GameObjects/GameObject/SandBox/GameCamera.h"
#include "GameObjects/GameObject/SandBox/Actor/Player.h"
#include "GameObjects/GameObject/SandBox/Actor/Enemy.h"
#include "GameObjects/GameObject/SandBox/Actor/Enemy/Boss.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
GameObjectFactory::GameObjectFactory(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
GameObjectFactory::~GameObjectFactory(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
GameObjectFactory* GameObjectFactory::Create(Game* game)
{
	return NEW GameObjectFactory(game);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool GameObjectFactory::StartUp(void)
{
	//コンテナの初期化
	game_objects_.clear();

	//ゲームオブジェクトの作成と追加
	const bool isTestMode = false;
	if(isTestMode)
	{
		this->AddGameObject(NEW CameraTest(game_));
		this->AddGameObject(NEW SpriteTest(game_));
		this->AddGameObject(NEW BillboardTest(game_));
		this->AddGameObject(NEW MeshTest(game_));
		this->AddGameObject(NEW EffectTest(game_));
		this->AddGameObject(NEW AudioTest(game_));
		this->AddGameObject(NEW ColliderTest(game_));
		this->AddGameObject(NEW SaveDataTest(game_));
	}
	else
	{
		this->AddGameObject(NEW GameManager(game_));
		this->AddGameObject(NEW GameCamera(game_));

		this->AddGameObject(NEW Player(game_));
		this->AddGameObject(NEW Boss(game_));


		this->AddGameObject(NEW SkyBox(game_));
		this->AddGameObject(NEW Planet(game_));

	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void GameObjectFactory::ShutDown(void)
{
	this->RemoveGameObjectAll();
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void GameObjectFactory::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void GameObjectFactory::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの追加
-----------------------------------------------------------------------------*/
void GameObjectFactory::AddGameObject(GameObject* gameObject)
{
	game_objects_.emplace_back(gameObject);
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの削除
-----------------------------------------------------------------------------*/
void GameObjectFactory::RemoveGameObjectAll(void)
{
	//Game.cppでやっているので削除処理は不要
	//while (!game_objects_.empty())
	//{
	//	delete game_objects_.back();
	//}
}

/*=============================================================================
/*		End of File
=============================================================================*/