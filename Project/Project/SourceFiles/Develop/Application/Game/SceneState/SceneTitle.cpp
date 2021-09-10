/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneTitle.cpp] タイトル場面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：タイトル場面クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "../GameObjects/GameObject.h"

// カメラ
#include "../GameObjects/GameObject/Camera.h"

// タイトル画面
#include "../GameObjects/GameObject/UI/Title.h"

// 入力
#include "../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SceneTitle::SceneTitle(Game* game)
	: ISceneState(game)
	, title_(nullptr)
{
	// Game::SetSceneState()で初期化されるため、ここでSceneTitle::Init()は呼ばない。
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SceneTitle::~SceneTitle(void)
{
	// Game::SetSceneState()で終了化されるため、ここでSceneTitle::Uninit()は呼ばない。
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SceneTitle::Init(void)
{
	// ゲームのステートを設定
	game_->SetGameState(Game::GameState::Title);

	// タイトル場面のゲームオブジェクトの生成
	{
		// カメラの作成
		NEW Camera(game_);

		// タイトル画面の作成
		title_ = NEW Title(game_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SceneTitle::Uninit(void)
{
	// ゲームの状態を取得
	auto game_state = game_->GetGameState();

	// ゲームオブジェクトの総終了化
	auto game_objects = game_->GetGameObjects();
	for (auto game_object : game_objects)
	{
		// ゲームオブジェクトの種類を取得
		auto game_object_type = game_object->GetType();

		// ゲームが終了状態じゃなかったら
		if (game_state != Game::GameState::Quit)
		{		
			// フェードのゲームオブジェクトのみ破棄しない
			if (game_object_type == GameObject::TypeID::Fade)
			{
				continue;
			}
		}
		game_object->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void SceneTitle::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void SceneTitle::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	auto title_menu_state = title_->GetTitleMenuState();
	switch (title_menu_state)
	{
	case TitleMenuState::GameStart:
		if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
		{
			// ゲーム開始
			this->ChangeScene();
		}
		break;

	case TitleMenuState::GameQuit:
		if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
		{
			// ゲーム終了
			game_->SetGameState(Game::GameState::Quit);
		}
		break;

	default:
		assert("SceneTitle::Update()：タイトルのステートが不正な状態です！");
		break;
	}
}

/*-----------------------------------------------------------------------------
/* シーンの切り替え処理
-----------------------------------------------------------------------------*/
void SceneTitle::ChangeScene(void)
{
	game_->SetSceneState(NEW SceneGame(game_));
}

/*=============================================================================
/*		End of File
=============================================================================*/