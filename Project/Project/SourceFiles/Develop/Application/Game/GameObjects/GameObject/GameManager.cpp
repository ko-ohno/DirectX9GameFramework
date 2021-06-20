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

// 描画コンポーネント
#include "../Component/RendererComponent/EffectRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/GridGizmoRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"

// 音声コンポーネント
#include "../Component/AudioComponent.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
GameManager::GameManager(Game* game)
	: GameObject(game)
	, grid_gizmo_(nullptr)
	, player_sandbox_gizmo_(nullptr)
	, effect_space_dust_(nullptr)
	, bgm_(nullptr)
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

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void GameManager::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void GameManager::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void GameManager::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/