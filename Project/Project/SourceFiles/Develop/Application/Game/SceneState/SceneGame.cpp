/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneGame.cpp] ゲーム場面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲーム場面クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "../GameObjects/GameObject.h"

// ゲーム管理ゲームオブジェクト
#include "../GameObjects/GameObject/GameManager.h"

// カメラ
#include "../GameObjects/GameObject/Camera/GameCamera.h"

// 背景レイヤー
#include "../GameObjects/GameObject/BackGround/SkyBox.h"
#include "../GameObjects/GameObject/BackGround/Planet.h"

// サンドボックスレイヤー
#include "../GameObjects/GameObject/SandBox/Actor/Player.h"

// UIレイヤー
#include "../GameObjects/GameObject/UI/HUD.h"

// 入力
#include "../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SceneGame::SceneGame(Game* game)
	: ISceneState(game)
{
	// Game::SetSceneState()で初期化されるため、ここでSceneGame::Init()は呼ばない。
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SceneGame::~SceneGame(void)
{
	// Game::SetSceneState()で終了化されるため、ここでSceneGame::Uninit()は呼ばない。
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SceneGame::Init(void)
{
	// ゲーム場面のゲームオブジェクトの生成
	{
		// ゲームのステートを設定
		game_->SetGameState(Game::GameState::Gameplay);

		// ゲームカメラ
		NEW GameCamera(game_);

		//ゲーム管理ゲームオブジェクト
		NEW GameManager(game_);

		// 背景レイヤーのオブジェクト作成
		NEW SkyBox(game_);
		NEW Planet(game_);

		// サンドボックスレイヤーのオブジェクト作成
		NEW Player(game_);

		// UIレイヤーのオブジェクト作成
		NEW HUD(game_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SceneGame::Uninit(void)
{
	// ゲームオブジェクトの総終了化
	auto game_objects = game_->GetGameObjects();
	for (auto game_object : game_objects)
	{
		// ゲームオブジェクトの種類を取得
		auto game_object_type = game_object->GetType();

		// フェードのゲームオブジェクトのみ破棄しない
		if (game_object_type == GameObject::TypeID::Fade)
		{
			continue;
		}
		game_object->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void SceneGame::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void SceneGame::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if ( InputCheck::KeyTrigger(DIK_SPACE))
	{
		this->ChangeScene();
	}
}

/*-----------------------------------------------------------------------------
/* シーンの切り替え処理
-----------------------------------------------------------------------------*/
void SceneGame::ChangeScene(void)
{
	game_->SetSceneState(NEW SceneResult(game_));
}

/*=============================================================================
/*		End of File
=============================================================================*/