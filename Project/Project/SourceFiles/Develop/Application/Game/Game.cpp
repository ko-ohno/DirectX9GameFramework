/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[game.cpp] ゲームの状態やオブジェクトの管理モジュール
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲーム状態とオブジェクトの管理。追加と削除。入力、更新、描画など
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "Game.h"
#include "Renderer.h"


#include "Manager/ShaderManager.h"
#include "Manager/TextureManager.h"


#include "GameObjectFactory.h"
#include "GameObjects/GameObject.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Game::Game(void)
	: updating_game_objects_(false)
	, game_state_(GameState::None)
	, dx9_graphics_(nullptr)
	, renderer_(nullptr)

	, shader_manager_(nullptr)

	, game_object_fuctory_(nullptr)
{
	pending_game_objects_.clear();
	game_objects_.clear();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Game::~Game(void)
{
	pending_game_objects_.clear();
	game_objects_.clear();
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
Game* Game::Create(void)
{
	return NEW Game();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Game::StartUp(class DX9Graphics* dx9Graphics)
{
	//グラフィックスの立ち上げやセーブデータのロードなどを行う

	//グラフィックスのコピー
	dx9_graphics_ = dx9Graphics;

	//ゲームの状態
	game_state_ = GameState::Gameplay;

	//マネージャーのファクトリをつくる
	{
		//シェーダーマネージャの起動
		shader_manager_ = shader_manager_->Create(this);
		const bool shader_manager_init = shader_manager_->StartUp();
		if (shader_manager_init == false)
		{
			return false;
		}

		//シェーダーマネージャの起動
		texture_manager_ = texture_manager_->Create(this);
		const bool texture_manager_init = texture_manager_->StartUp();
		if (texture_manager_init == false)
		{
			return false;
		}
	}

	//レンダラーの起動
	renderer_ = renderer_->Create(this);
	const bool renderer_init = renderer_->StartUp();
	if (renderer_init == false)
	{
		return false;	//レンダラの起動に失敗したら
	}

	//ゲームオブジェクトのファクトリの起動
	game_object_fuctory_ = game_object_fuctory_->Create(this);
	const bool game_object_fuctory_init = game_object_fuctory_->StartUp();
	if(game_object_fuctory_init == false)
	{
		return false;
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Game::ShutDown(void)
{
	//ゲームオブジェクトをすべて破棄
	while (!game_objects_.empty())
	{
		delete game_objects_.back();
	}

	//ゲームオブジェクトのファクトリの破棄
	{
		game_object_fuctory_->ShutDown();
		SAFE_DELETE_(game_object_fuctory_);
	}

	//シェーダーマネージャの破棄
	{
		shader_manager_->Shutdown();
		SAFE_DELETE_(shader_manager_);
	}
	 
	//レンダラーの破棄
	{
		renderer_->ShutDown();
		SAFE_DELETE_(renderer_);
	}
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void Game::Input(void)
{
	if (game_state_ == GameState::Gameplay)
	{
		//ゲームオブジェクトの入力処理
		for (auto game_object : game_objects_)
		{
			game_object->Input();
		}
	}
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Game::Update(float deltaTime)
{
	if (game_state_ == GameState::Gameplay)
	{
		//ゲームオブジェクトの更新
		this->UpdateGameObjects(deltaTime);
	}


	switch (game_state_)
	{
	case Game::GameState::Title:
		break;

	case Game::GameState::Gameplay:
		break;

	case Game::GameState::Result:
		break;

	case Game::GameState::Paused:
		break;

	case Game::GameState::Quit:
		break;

	default:
		assert(!"ゲームの不正な状態遷移を検知！");
		break;
	}
}

/*-----------------------------------------------------------------------------
/* 出力生成処理
-----------------------------------------------------------------------------*/
void Game::GenerateOutput(void)
{
	//レンダラーによる描画処理
	renderer_->Draw();
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの追加処理
-----------------------------------------------------------------------------*/
void Game::AddGameObject(GameObject* gameObject)
{
	// ゲームオブジェクトの更新中かで登録先を変更
	if (updating_game_objects_)
	{
		pending_game_objects_.emplace_back(gameObject);//待機コンテナ
	}
	else
	{
		game_objects_.emplace_back(gameObject);//稼働コンテナ
	}
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの削除処理
-----------------------------------------------------------------------------*/
void Game::RemoveGameObject(GameObject* gameObject)
{
	// 待機コンテナ
	// "gameObject"をコンテナの中から探し出して破棄する
	auto iter = std::find(pending_game_objects_.begin(), pending_game_objects_.end(), gameObject);
	if (iter != pending_game_objects_.end())
	{
		//一致する"gameObject"をコンテナの末尾へ移動させ、メモリ自体を破棄する
		std::iter_swap(iter, pending_game_objects_.end() - 1);
		pending_game_objects_.pop_back();
	}

	// 稼働コンテナ
	// "gameObject"をコンテナの中から探し出して破棄する
	iter = std::find(game_objects_.begin(), game_objects_.end(), gameObject);
	if (iter != game_objects_.end())
	{
		//一致する"gameObject"をコンテナの末尾へ移動させ、メモリ自体を破棄する
		std::iter_swap(iter, game_objects_.end() - 1);
		game_objects_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの検索処理
-----------------------------------------------------------------------------*/
//GameObject* Game::FindGameObject(TypeID gameObjectTypeID)
//{
//	for (auto game_object : game_objects_)
//	{
//		auto game_object_type_id = game_object->GetType();
//
//		if (game_object_type_id == gameObjectTypeID)
//		{
//			return game_object;
//		}
//	}
//	assert(!"gameObjectTypeIDは、ゲームオブジェクトのリストに一致するものがありませんでした！");
//	return nullptr;
//}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの総更新処理
-----------------------------------------------------------------------------*/
void Game::UpdateGameObjects(float deltaTime)
{
	//すべてのゲームオブジェクトの更新
	updating_game_objects_ = true;
	for (auto game_object : game_objects_)
	{
		game_object->Update(deltaTime);
	}
	updating_game_objects_ = false;

	//待機リストのゲームオブジェクトの操作
	for (auto pending_game_object : pending_game_objects_)
	{
		pending_game_object->Update(deltaTime);
		game_objects_.emplace_back(pending_game_object);
	}
	pending_game_objects_.clear();

	//ゲームオブジェクトが破棄の状態かチェック
	std::vector<class GameObject*> dead_game_objects;
	for (auto game_object : game_objects_)
	{
		if (game_object->GetState() == GameObject::State::Dead)
		{
			dead_game_objects.emplace_back(game_object);
		}
	}

	//破棄予定のゲームオブジェクトのメモリを破棄
	for (auto dead_game_object : dead_game_objects)
	{
		delete dead_game_object;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/