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
#include "ISceneState.h"
#include "SceneState/SceneTitle.h"
#include "SceneState/SceneGame.h"
#include "SceneState/SceneResult.h"
#include "Renderer.h"

#include "ResourceManager/ShaderManager.h"
#include "ResourceManager/TextureManager.h"
#include "ResourceManager/MeshManager.h"
#include "ResourceManager/EffectManager.h"
#include "ResourceManager/LightManager.h"
#include "ResourceManager/SoundManager.h"
#include "ResourceManager/ColliderManager.h"
#include "ResourceManager/SaveDataManager.h"

#include "SandBoxManager/ActorManager.h"
#include "SandBoxManager/EnemieManager.h"

#include "GameObjectFactory.h"
#include "GameObjects/GameObject.h"

#include "../ImGui/ImGuiManager.h"

// 静的変数のプロトタイプ宣言
ISceneState* Game::scene_state_ = nullptr;

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Game::Game(void)
	: is_shutdown_(false)
	, input_game_objects_(false)
	, updating_game_objects_(false)
	, game_state_(GameState::None)
	, game_object_fuctory_(nullptr)
	, dx9_graphics_(nullptr)
	, renderer_(nullptr)

	, shader_manager_(nullptr)
	, texture_manager_(nullptr)
	, mesh_manager_(nullptr)
	, effect_manager_(nullptr)
	, light_manager_(nullptr)
	, sound_manager_(nullptr)
	, collider_manager_(nullptr)
	, save_data_manager_(nullptr)

	, actor_manager_(nullptr)
	, enemie_manager_(nullptr)

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

	//リソース用の各マネージャーの起動
	{
		//シェーダーマネージャの起動
		shader_manager_ = shader_manager_->Create(this);
		const bool shader_manager_init = shader_manager_->StartUp();
		if (shader_manager_init == false)
		{
			assert(!"Game::StartUp()：シェーダーマネージャの起動に失敗しました。");
			return false;
		}

		//テクスチャマネージャの起動
		texture_manager_ = texture_manager_->Create(this);
		const bool texture_manager_init = texture_manager_->StartUp();
		if (texture_manager_init == false)
		{
			assert(!"Game::StartUp()：テクスチャマネージャの起動に失敗しました。");
			return false;
		}
	
		//メッシュマネージャの起動
		mesh_manager_ = mesh_manager_->Create(this);
		const bool mesh_manager_init = mesh_manager_->StartUp();
		if (texture_manager_init == false)
		{
			assert(!"Game::StartUp()：メッシュマネージャの起動に失敗しました。");
			return false;
		}

		//エフェクトマネージャの起動
		effect_manager_ = effect_manager_->Create(this);
		const bool effect_manager_init = effect_manager_->StartUp();
		if (effect_manager_init == false)
		{
			assert(!"Game::StartUp()：エフェクトマネージャの起動に失敗しました。");
			return false;
		}

		//ライトマネージャの起動
		light_manager_ = light_manager_->Create(this);
		const bool light_manager_init = light_manager_->StartUp();
		if (light_manager_init == false)
		{
			assert(!"Game::StartUp()：ライトマネージャの起動に失敗しました。");
			return false;
		}

		//サウンドマネージャの起動
		sound_manager_ = sound_manager_->Create(this);
		const bool sound_manager_init = sound_manager_->StartUp();
		if (sound_manager_init == false)
		{
			assert(!"Game::StartUp()：サウンドマネージャの起動に失敗しました。");
			return false;
		}
	
		//コライダマネージャの起動
		collider_manager_ = collider_manager_->Create(this);
		const bool collider_manager_init = collider_manager_->StartUp();
		if (collider_manager_init == false)
		{
			assert(!"Game::StartUp()：コライダマネージャの起動に失敗しました。");
			return false;
		}

		//セーブデータマネージャの起動
		save_data_manager_ = save_data_manager_->Create(this);
		const bool save_data_manager_init = save_data_manager_->StartUp();
		if (save_data_manager_init == false)
		{
			assert(!"Game::StartUp()：セーブデータマネージャの起動に失敗しました。");
			return false;
		}
	}

	// サンドボックス用のマネージャの起動
	{
		//アクターのマネージャの起動
		actor_manager_ = actor_manager_->Create(this);
		const bool actor_manager_init = actor_manager_->StartUp();
		if (actor_manager_init == false)
		{
			assert(!"Game::StartUp()：アクターマネージャの起動に失敗しました。");
			return false;
		}

		//エネミーのマネージャの起動
		enemie_manager_ = enemie_manager_->Create(this);
		const bool enemie_manager_init = enemie_manager_->StartUp();
		if (enemie_manager_init == false)
		{
			assert(!"Game::StartUp()：エネミーマネージャの起動に失敗しました。");
			return false;
		}
	}

	//レンダラーの起動
	renderer_ = renderer_->Create(this);
	const bool renderer_init = renderer_->StartUp();
	if (renderer_init == false)
	{
		assert(!"Game::StartUp()：レンダラーの起動に失敗しました。");
		return false;	//レンダラの起動に失敗したら
	}

	//ゲームオブジェクトのファクトリの起動
	game_object_fuctory_ = game_object_fuctory_->Create(this);
	const bool game_object_fuctory_init = game_object_fuctory_->StartUp();
	if(game_object_fuctory_init == false)
	{
		assert(!"Game::StartUp()：ゲームオブジェクトのファクトリの起動に失敗しました。");
		return false;
	}

	// 場面の初期化
	{
		this->SetSceneState(NEW SceneTitle(this));
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

	// サンドボックスの各マネージャの破棄
	{
		//アクターマネージャの破棄
		actor_manager_->Shutdown();
		SAFE_DELETE_(actor_manager_);

		//エネミーマネージャの破棄
		enemie_manager_->Shutdown();
		SAFE_DELETE_(enemie_manager_);

	}

	// リソースの各マネージャーの破棄
	{
		//セーブデータマネージャの破棄
		{
			save_data_manager_->Shutdown();
			SAFE_DELETE_(save_data_manager_);
		}

		//サウンドマネージャの破棄
		{
			sound_manager_->Shutdown();
			SAFE_DELETE_(sound_manager_);
		}

		//コライダマネージャの破棄
		{
			collider_manager_->Shutdown();
			SAFE_DELETE_(collider_manager_);
		}

		//コライダマネージャの破棄
		{
			light_manager_->Shutdown();
			SAFE_DELETE_(light_manager_);
		}

		//エフェクトマネージャの破棄
		{
			effect_manager_->Shutdown();
			SAFE_DELETE_(effect_manager_);
		}

		//メッシュマネージャの破棄
		{
			mesh_manager_->Shutdown();
			SAFE_DELETE_(mesh_manager_);
		}

		//テクスチャマネージャの破棄
		{
			texture_manager_->Shutdown();
			SAFE_DELETE_(texture_manager_);
		}

		//シェーダーマネージャの破棄
		{
			shader_manager_->Shutdown();
			SAFE_DELETE_(shader_manager_);
		}
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
	// 場面ごとの入力処理
	if (scene_state_ != nullptr)
	{
		scene_state_->Input();
	}

	// ゲームオブジェクトの入力処理
	this->InputGameObjects();
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Game::Update(float deltaTime)
{
	// FPSの表示
	ImGui::ShowFPS(deltaTime);

	// 場面ごとの入力処理
	if (scene_state_ != nullptr)
	{
		scene_state_->Update(deltaTime);
	}

	//ゲームオブジェクトの総更新
	this->UpdateGameObjects(deltaTime);

	// ゲームを終了する
	if (game_state_ == Game::GameState::Quit)
	{
		is_shutdown_ = true;
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
/* 場面の切り替え処理
-----------------------------------------------------------------------------*/
void Game::SetSceneState(ISceneState* sceneState)
{
	if (scene_state_ != nullptr)
		scene_state_->Uninit();

	scene_state_ = sceneState;

	if (scene_state_ != nullptr)
		scene_state_->Init();
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの追加処理
-----------------------------------------------------------------------------*/
void Game::AddGameObject(GameObject* gameObject)
{
	// ゲームオブジェクトの更新中かで登録先を変更
	if (updating_game_objects_ == true
		|| input_game_objects_ == true)
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
/* ゲームオブジェクトの総入力処理
-----------------------------------------------------------------------------*/
void Game::InputGameObjects(void)
{
	//ゲームオブジェクトの入力処理
	input_game_objects_ = true;
	for (auto game_object : game_objects_)
	{
		game_object->Input();
	}
	input_game_objects_ = false;
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの総更新処理
-----------------------------------------------------------------------------*/
void Game::UpdateGameObjects(float deltaTime)
{
	//ゲームオブジェクトとエフェクトの総更新処理
	{
		//エフェクトマネージャの更新開始
		//effect_manager_->GetEffekseerManager()->BeginUpdate();

		//すべてのゲームオブジェクトの更新
		updating_game_objects_ = true;
		for (auto game_object : game_objects_)
		{
			if (game_state_ == GameState::Paused)
			{
				// ポーズメニューのゲームオブジェクトだけを更新する
				auto game_object_type = game_object->GetType();
				if (game_object_type == GameObject::TypeID::PauseMenu)
				{
					game_object->Update(deltaTime);
				}

				// フェードも更新する
				if (game_object_type == GameObject::TypeID::Fade)
				{
					game_object->Update(deltaTime);
				}
			}
			else
			{
				game_object->Update(deltaTime);
			}
		}
		updating_game_objects_ = false;

		//エフェクトマネージャの一括更新処理
		if (game_state_ != GameState::Paused)
		{
			effect_manager_->GetEffekseerManager()->Update();
		}

		//エフェクトマネージャの更新終了
		//effect_manager_->GetEffekseerManager()->EndUpdate();
	}

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
		if (game_object->GetGameObjectState() == GameObject::State::Dead)
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