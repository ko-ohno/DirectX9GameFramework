/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameManager.cpp] ゲーム進行管理オブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲーム進行管理オブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "GameManager.h"
#include "../../ResourceManager/SaveDataManager.h"

// 敵の生成ファクトリ
#include "../../EnemyFactory.h"
#include "../../EnemyFactoryState.h"

// エネミーのファクトリの状態クラス
#include "../../EnemyFactoryState/EnemyFactoryState_1.h"
#include "../../EnemyFactoryState/EnemyFactoryState_2.h"
#include "../../EnemyFactoryState/EnemyFactoryState_3.h"
#include "../../EnemyFactoryState/EnemyFactoryState_4.h"
#include "../../EnemyFactoryState/EnemyFactoryState_5.h"
#include "../../EnemyFactoryState/EnemyFactoryState_6.h"
#include "../../EnemyFactoryState/EnemyFactoryState_Last.h"

// ボスのHUD
#include "../GameObject/UI/HUD.h"
#include "../GameObject/UI/BossHUD.h"

// 描画コンポーネント
#include "../Component/RendererComponent/EffectRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/GridGizmoRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"

// 値コンポーネント
#include "../Component/ParameterComponent/IntParameterComponent.h"
#include "../Component/ParameterComponent/FloatParameterComponent.h"

// 音声コンポーネント
#include "../Component/AudioComponent.h"

#include "../../../ImGui/ImGuiManager.h"

#include "../../Input/InputCheck.h"

#include "../GameObject/UI/GameOver.h"
#include "../GameObject/UI/GameClear.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
GameManager::GameManager(Game* game)
	: GameObject(game)
	, is_secen_change_(false)
	, is_create_player_hud_(false)
	, is_create_boss_hud_(false)
	, enemy_factory_(nullptr)
	, player_(nullptr)
	, boss_(nullptr)
	, grid_gizmo_(nullptr)
	, player_sandbox_gizmo_(nullptr)
	, effect_space_dust_(nullptr)
	, bgm_(nullptr)
	, bgm_volume_(0.f)
	, is_bgm_change_(false)
	, player_max_hp_param_(nullptr)
	, player_max_hp_value_(0.f)
	, player_hp_param_(nullptr)
	, player_hp_value_(0.f)
	, progress_param_(nullptr)
	, progress_value_(0)
	, score_param_(nullptr)
	, score_value_(0)
	, boss_max_hp_param_(nullptr)
	, boss_max_hp_value_(0.f)
	, boss_hp_param_(nullptr)
	, boss_hp_value_(0.f)
	, is_enemy_spawn_(false)
	, spawn_count_(0)
	, game_left_time_(0.f)
{
	// 描画レイヤーを指定
	this->renderer_layer_type_ = RendererLayerType::Game;

	//　初期化
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
GameManager::~GameManager(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool GameManager::Init(void)
{
	// 値を初期化
	{
		player_hp_value_ = 1.f;
		boss_hp_value_ = 1.f;
	}

	// エネミーのファクトリを生成
	enemy_factory_ = NEW EnemyFactory(game_);

	// ギズモコンポーネント
	{
		// グリッドの表示
		grid_gizmo_ = NEW GridGizmoRendererComponent(this);
		//grid_gizmo_->IsSetDrawable(false);

		// プレイヤーのサンドボックスを表示
		player_sandbox_gizmo_ = NEW BoxGizmoRendererComponent(this);
		player_sandbox_gizmo_->SetScaleX(5.5f);
		player_sandbox_gizmo_->SetScaleY(3.5f);
		//player_sandbox_gizmo_->IsSetDrawable(false);
	}

	// エフェクトコンポーネント
	{
		// 宇宙のチリのエフェクトを表示
		effect_space_dust_ = NEW EffectRendererComponent(this);
		effect_space_dust_->SetEffect(EffectType::SpaceDustYellow);
		effect_space_dust_->Play();	//再生開始 
	}

	// 値コンポーネントの生成
	{
		// プレイヤー
		{
			// プレイヤーの最大HP
			player_max_hp_param_ = NEW FloatParameterComponent(this);
			player_max_hp_param_->SetParameterType(ParameterType::MaxHP);

			// プレイヤーのHP
			player_hp_param_ = NEW FloatParameterComponent(this);
			player_hp_param_->SetParameterType(ParameterType::HP);

			// ゲームの進行度
			progress_param_ = NEW IntParameterComponent(this);
			progress_param_->SetParameterType(ParameterType::GameProgress);

			// ゲームのスコア
			score_param_ = NEW IntParameterComponent(this);
			score_param_->SetParameterType(ParameterType::Score);
		}
	
		// ボス
		{
			// ボスの最大HP
			boss_max_hp_param_ = NEW FloatParameterComponent(this);
			boss_max_hp_param_->SetParameterType(ParameterType::BossMaxHP);

			// ボスのHP
			boss_hp_param_ = NEW FloatParameterComponent(this);
			boss_hp_param_->SetParameterType(ParameterType::BossHP);
		}
	}

	// ゲームの残り時間
	game_left_time_ = MAX_SPAWN_TIME_;

	// ボスだけの生成処理
	{
		//game_left_time_ = 0.f;
		//spawn_count_ = 6;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void GameManager::Uninit(void)
{
	// bgmの停止
	bgm_->Stop();

	SAFE_DELETE_(enemy_factory_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void GameManager::InputGameObject(void)
{
	// エネミーのファクトリの入力処理
	if (enemy_factory_ != nullptr)
	{
		enemy_factory_->Input();
	}
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void GameManager::UpdateGameObject(float deltaTime)
{
	// BGMの生成
	if (bgm_ == nullptr)
	{
		// 音量を設定
		bgm_volume_ = MAX_BGM_VOLUME_;

		bgm_ = NEW AudioComponent(this);
		bgm_->SetSound(SoundType::WonderLand);
		bgm_->SetAudioVolume(bgm_volume_);
		bgm_->PlayLoop();
	}

	// ゲームの状態を取得
	auto game_state = game_->GetGameState();

	// 場面切り替えを行うか？	 
	if (is_secen_change_ == false)
	{
		// セーブデータのマネージャへのポインタ
		auto save_data_manager = game_->GetSaveDataManager();

		const bool is_game_state_game_clear_ = (game_state == Game::GameState::GameClear);
		if (is_game_state_game_clear_)
		{
			NEW GameClear(game_);
			is_secen_change_ = true;

			// 現在のスコアをセーブデータへ追加
			save_data_manager->AddNewSaveData(NEW SaveData(score_value_));
		}

		const bool is_game_state_game_over_ = (game_state == Game::GameState::GameOver);
		if (is_game_state_game_over_)
		{
			NEW GameOver(game_);
			is_secen_change_ = true;

			// 現在のスコアをセーブデータへ追加
			save_data_manager->AddNewSaveData(NEW SaveData(score_value_));
		}
	}

	if (game_state != Game::GameState::Gameplay) { return; }

	// 値コンポーネントの更新
	this->UpdateParameterComponent(deltaTime);

	// プレイヤーのHUDを生成する
	{
		bool is_game_state_game_play_ = (game_state == Game::GameState::Gameplay);
		if (is_game_state_game_play_)
		{
			if (is_create_player_hud_ == false)
			{
				NEW HUD(game_);
				is_create_player_hud_ = true;
			}
		}
	}

	// ボスのHUDを生成する
	if (is_create_boss_hud_)
	{
		NEW BossHUD(game_);
		is_create_boss_hud_ = false;
	}

	// BGMの切り替え処理
	if (is_bgm_change_ == true)
	{
		this->UpdateBGM(deltaTime);
	}

	// 敵のウェーブの生成
	{
		const int MAX_SPAWN_COUNT = 7;
		if (spawn_count_ >= MAX_SPAWN_COUNT) { return; }

		// エネミーのファクトリの更新処理
		if (enemy_factory_ != nullptr)
		{
			// 生成するフラグを初期化
			is_enemy_spawn_ = false;

			// エネミーを生成する差分の時間を求める
			const float spawn_time = MAX_SPAWN_TIME_ - (SPAWN_DIFF_TIME_ * spawn_count_);

			// エネミーの生成を行うか？
			const bool is_execute_spawn = ((game_left_time_ <= spawn_time) && (is_enemy_spawn_ == false));
			if (is_execute_spawn)
			{
				if (game_left_time_ >= 0.1f)
				{
					switch (spawn_count_)
					{
					case 0:
						enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_1(game_));
						break;

					case 1:
						enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_2(game_));
						break;

					case 2:
						enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_3(game_));
						break;

					case 3:
						enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_4(game_));

						// 現在のエフェクトの停止
						effect_space_dust_->Stop();

						// エフェクトの切り替え
						effect_space_dust_->SetEffect(EffectType::SpaceDustBlue);
						effect_space_dust_->Play();
						break;

					case 4:
						enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_5(game_));
						break;

					case 5:
						enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_6(game_));
						break;

					default:
						break;
					}
				}
				else
				{
					// ボスの生成
					enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_Last(game_));

					// BGMの切り替えを有効に
					is_bgm_change_ = true;

					// ボスのHUDを生成を有効にする
					is_create_boss_hud_ = true;

					// 現在のエフェクトの停止
					effect_space_dust_->Stop();

					// エフェクトの切り替え
					effect_space_dust_->SetEffect(EffectType::SpaceDustRed);
					effect_space_dust_->Play();
				}

				// 生成カウントを加算
				spawn_count_++;

				// 生成したことを記憶
				is_enemy_spawn_ = true;
			}
			enemy_factory_->Update(deltaTime);
		}
	}
}

/*-----------------------------------------------------------------------------
/* 値コンポーネントの更新処理
-----------------------------------------------------------------------------*/
void GameManager::UpdateParameterComponent(float deltaTime)
{
	// プレイヤーへのポインタの取得
	{
		// プレイヤーへのポインタは、未取得か？
		if (player_ == nullptr)
		{
			player_ = this->FindGameObject(GameObject::TypeID::Player);
			player_hp_param_->SetFloat(player_hp_value_);
		}

		if (player_ != nullptr)
		{
			//　プレイヤーの値コンポーネントを検索
			auto parameter_components = player_->GetParameterComponents();
			for (auto parameter_component : parameter_components)
			{
				// 値コンポーネントの型を調べる
				auto parameter_component_type = parameter_component->GetParameterType();

				// プレイヤーの最大HP値の更新
				if (parameter_component_type == ParameterType::MaxHP)
				{
					player_max_hp_value_ = parameter_component->GetFloat();
					player_max_hp_param_->SetFloat(player_max_hp_value_);
				}

				// プレイヤーのHP値の更新
				if (parameter_component_type == ParameterType::HP)
				{
					player_hp_value_ = parameter_component->GetFloat();
					player_hp_param_->SetFloat(player_hp_value_);
				}
			}
		}
	}

	// ボスへのポインタの取得
	{
		// ボスへのポインタは、未取得か？
		if (boss_ == nullptr)
		{
			boss_ = this->FindGameObject(GameObject::TypeID::Boss);
			boss_hp_param_->SetFloat(boss_hp_value_);
		}

		if (boss_ != nullptr)
		{
			//　ボスの値コンポーネントを検索
			auto parameter_components = boss_->GetParameterComponents();
			for (auto parameter_component : parameter_components)
			{
				// 値コンポーネントの型を調べる
				auto parameter_component_type = parameter_component->GetParameterType();

				// ボスへの最大HP値の更新
				if (parameter_component_type == ParameterType::BossMaxHP)
				{
					boss_max_hp_value_ = parameter_component->GetFloat();
					boss_max_hp_param_->SetFloat(boss_max_hp_value_);
				}

				// ボスのHP値の更新
				if (parameter_component_type == ParameterType::BossHP)
				{
					boss_hp_value_ = parameter_component->GetFloat();
					boss_hp_param_->SetFloat(boss_hp_value_);
				}
			}
		}
	}

	// ゲームの進行度の値の更新
	{
		game_left_time_ -= deltaTime;

		if (game_left_time_ <= 0.f)
		{
			game_left_time_ = 0.f;
		}
		
		progress_value_ = static_cast<int>(game_left_time_);
		progress_param_->SetInt(progress_value_);
	}

	// スコアの値の更新
	{
		score_value_ = score_param_->GetInt();
		score_param_->SetInt(score_value_);
	}
}

/*-----------------------------------------------------------------------------
/* BGMの更新処理
-----------------------------------------------------------------------------*/
void GameManager::UpdateBGM(float deltaTime)
{
	// 音量を小さく
	bgm_volume_ -= deltaTime;
	bgm_->SetAudioVolume(bgm_volume_);

	// BGMの切り替え
	if (bgm_volume_ <= 0.f)
	{
		// 現在のBGMを停止
		bgm_->Stop();

		// BGMの切り替えと再生
		bgm_->SetSound(SoundType::JetPenguin_2nd);
		bgm_->SetAudioVolume(MAX_BGM_VOLUME_);
		bgm_->PlayLoop();

		is_bgm_change_ = false;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/