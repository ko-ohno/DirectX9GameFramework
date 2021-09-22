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


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
GameManager::GameManager(Game* game)
	: GameObject(game)
	, enemy_factory_(nullptr)
	, player_(nullptr)
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
	// エネミーのファクトリを生成
	enemy_factory_ = NEW EnemyFactory(game_);

	// ギズモコンポーネント
	{
		// グリッドの表示
		grid_gizmo_ = NEW GridGizmoRendererComponent(this);

		// プレイヤーのサンドボックスを表示
		player_sandbox_gizmo_ = NEW BoxGizmoRendererComponent(this);
		player_sandbox_gizmo_->SetScaleX(11.0f);
		player_sandbox_gizmo_->SetScaleY(7.0f);
	}

	// 宇宙のチリのエフェクトを表示
	effect_space_dust_ = NEW EffectRendererComponent(this);
	effect_space_dust_->SetEffect(EffectType::SpaceDustYellow);
	effect_space_dust_->Play();	//再生開始 

	// BGMを設定
	bgm_volume_ = MAX_BGM_VOLUME_;

	bgm_ = NEW AudioComponent(this);
	bgm_->SetSound(SoundType::WonderLand);
	bgm_->SetAudioVolume(bgm_volume_);
	bgm_->PlayLoop();

	// 値コンポーネントの生成
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

	//enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_Last(game_));


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
	// 値コンポーネントの更新
	this->UpdateParameterComponent(deltaTime);

	// BGMの切り替え処理
	if (is_bgm_change_ == true)
	{
		this->UpdateBGM(deltaTime);
	}

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
				enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_Last(game_));

				// BGMの切り替えを有効に
				is_bgm_change_ = true;

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

/*-----------------------------------------------------------------------------
/* 値コンポーネントの更新処理
-----------------------------------------------------------------------------*/
void GameManager::UpdateParameterComponent(float deltaTime)
{
	// 最大HPへのポインタは、取得済みか？
	if (player_ == nullptr)
	{
		player_ = this->FindGameObject(GameObject::TypeID::Player);
	}

	// nullチェック
	if (player_ == nullptr)
	{
		assert(!"GameManager::UpdateParameterComponent:プレイヤーへのポインタが”nullptr”でした");
		return;
	}

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


	//ImGui::Begin("HUD");
	//ImGui::SliderInt("##score_value_", &score_value_, 0, 999);
	//ImGui::End();

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