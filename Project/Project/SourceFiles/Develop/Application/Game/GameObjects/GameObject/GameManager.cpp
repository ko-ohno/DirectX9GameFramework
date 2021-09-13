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
	, grid_gizmo_(nullptr)
	, player_sandbox_gizmo_(nullptr)
	, effect_space_dust_(nullptr)
	, bgm_(nullptr)
	, progress_param_(nullptr)
	, progress_value_(0)
	, score_param_(nullptr)
	, score_value_(0)
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
	bgm_ = NEW AudioComponent(this);
	bgm_->SetSound(SoundType::WonderLand);
	bgm_->SetAudioVolume(0.1f);
	//bgm_->PlayLoop();

	// 値の作成
	{
		progress_param_ = NEW IntParameterComponent(this);
		progress_param_->SetParameterType(ParameterType::Progress);

		score_param_ = NEW IntParameterComponent(this);
		score_param_->SetParameterType(ParameterType::Score);
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
	UNREFERENCED_PARAMETER(deltaTime);

	// エネミーのファクトリの更新処理
	if (enemy_factory_ != nullptr)
	{
		enemy_factory_->Update(deltaTime);
	}

	ImGui::Begin("HUD");
	ImGui::SliderInt("##score_value_", &score_value_, 0, 999);
	ImGui::End();

	// 値の更新
	{
		// ゲームの進行度の値の更新
		progress_param_->SetInt(progress_value_);

		// スコアの値の更新
		score_param_->SetInt(score_value_);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/