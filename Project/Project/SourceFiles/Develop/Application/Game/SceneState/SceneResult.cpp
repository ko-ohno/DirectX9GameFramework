/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneResult.cpp] リザルト場面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：リザルト場面クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "SceneResult.h"
#include "SceneTitle.h"
#include "../GameObjects/GameObject.h"

// カメラ
#include "../GameObjects/GameObject/Camera.h"

// タイトル画面
#include "../GameObjects/GameObject/UI/Result.h"

// 入力
#include "../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SceneResult::SceneResult(Game* game)
	: ISceneState(game)
{
	// Game::SetSceneState()で終了化されるため、ここでSceneResult::Init()は呼ばない。
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SceneResult::~SceneResult(void)
{
	// Game::SetSceneState()で終了化されるため、ここでSceneResult::Uninit()は呼ばない。
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SceneResult::Init(void)
{
	// ゲームのステートを設定
	//game_->SetGameState(Game::GameState::Result);

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

	// リザルト場面のゲームオブジェクトの生成
	{
		// カメラ
		NEW Camera(game_);

		// リザルト画面
		NEW Result(game_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SceneResult::Uninit(void)
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

		// ロード画面のゲームオブジェクトは破棄しない
		if (game_object_type == GameObject::TypeID::LoadingScreen)
		{
			continue;
		}

		game_object->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void SceneResult::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void SceneResult::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const bool is_show_game_screen = parameter_is_show_game_screen_->GetBool();
	if (is_show_game_screen)
	{
		// ゲームの状態をタイトル画面の状態として設定
		game_->SetGameState(Game::GameState::Result);
	}

	if (is_scene_change_tirgger_ == false)
	{
		const bool is_input_key_space = (InputCheck::KeyTrigger(DIK_SPACE));
		const bool is_input_button_A  = (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_A));
		if (is_input_key_space || is_input_button_A)
		{
			// 場面切り替えのトリガーをONにして入力を無効化
			is_scene_change_tirgger_ = true;

			// 場面切り替えを申請
			this->is_need_scene_changed_ = true;
		}
	}

	// 切り替わる瞬間のみを取得
	if (this->is_need_scene_changed_ == true)
	{
		// 値コンポーネントにフェードを実行することを通知
		parameter_is_fade_execute_->SetBool(true);

		// 元に戻す
		this->is_need_scene_changed_ = false;
	}

	// フェードゲームオブジェクトがフェードを完了したかを取得
	const bool is_scene_changed = parameter_is_scene_changed->GetBool();
	if (is_scene_changed)
	{
		// ゲームの状態をロード画面の状態として設定
		game_->SetGameState(Game::GameState::Loading);

		// タイトル場面へ
		this->ChangeScene();
	}
}

/*-----------------------------------------------------------------------------
/* シーンの切り替え処理
-----------------------------------------------------------------------------*/
void SceneResult::ChangeScene(void)
{
	game_->SetSceneState(NEW SceneTitle(game_));
}

/*=============================================================================
/*		End of File
=============================================================================*/