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

// フェード画面
#include "../GameObjects/GameObject/UI/Fade.h"

// ロード画面
#include "../GameObjects/GameObject/UI/LoadingScreen.h"

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

	//
	// 既存のゲームオブジェクトから値コンポーネントの取得
	// 
 
	// ゲームオブジェクトのリストを取得
	auto game_objects = game_->GetGameObjects();
	for (auto game_object : game_objects)
	{
		//　ゲームオブジェクトが所有する値コンポーネントのリストを取得
		auto parameter_components = game_object->GetParameterComponents();

		// ゲームオブジェクトの型を調べる
		auto game_object_type = game_object->GetType();

		// 場面切り替え用の値コンポーネントの取得
		{
			// フェード画面ゲームオブジェクトから値コンポーネントのポインタを取得
			if (game_object_type == GameObject::TypeID::Fade)
			{
				// ゲームオブジェクトが所有する値コンポーネントを調べる
				for (auto parameter_component : parameter_components)
				{
					// フェードを実行するかの値コンポーネントの取得
					auto parameter_component_type = parameter_component->GetParameterType();
					if (parameter_component_type == ParameterType::IsFadeExecute)
					{
						// ポインタの取得
						this->parameter_is_fade_execute_ = parameter_component;
					}
				}
			}
	
			// ロード画面ゲームオブジェクトから値コンポーネントのポインタを取得
			if (game_object_type == GameObject::TypeID::LoadingScreen)
			{
				// ゲームオブジェクトが所有する値コンポーネントを調べる
				for (auto parameter_component : parameter_components)
				{
					// 値コンポーネントの型を調べる
					auto parameter_component_type = parameter_component->GetParameterType();
	
					// 場面を切り替えるかの値コンポーネント
					if (parameter_component_type == ParameterType::IsSceneChanged)
					{
						// ポインタの取得
						this->parameter_is_scene_changed = parameter_component;
						this->parameter_is_scene_changed->SetBool(false);
					}

					// ゲーム画面を表示するかの値コンポーネント
					if (parameter_component_type == ParameterType::IsShowGameScreen)
					{
						// ポインタの取得
						this->parameter_is_show_game_screen_ = parameter_component;
					}	
				}
			}
		}
	}
	
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
			// フェードのゲームオブジェクトは破棄しない
			if (game_object_type == GameObject::TypeID::Fade)
			{
				continue;
			}

			// ロード画面のゲームオブジェクトは破棄しない
			if (game_object_type == GameObject::TypeID::LoadingScreen)
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
		//if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
		if (InputCheck::KeyTrigger(DIK_SPACE))
		{
			this->is_input_scene_changed_ = true;
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

	// 切り替わる瞬間のみを取得
	if (this->is_input_scene_changed_ == true)
	{
		// 値コンポーネントにフェードを実行することを通知
		parameter_is_fade_execute_->SetBool(true);
	
		// 元に戻す
		this->is_input_scene_changed_ = false;
	}

	// フェードゲームオブジェクトがフェードを完了したかを取得
	const bool is_scene_changed = parameter_is_scene_changed->GetBool();
	if (is_scene_changed)
	{
		// ゲーム開始
		this->ChangeScene();
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