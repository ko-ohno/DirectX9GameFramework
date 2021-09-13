/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Fade.cpp] ゲーム画面のFadeクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲーム画面のFadeの挙動を定義したクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "Fade.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../../Game.h"

// 値コンポーネント
#include "../../Component/ParameterComponent/BoolParameterComponent.h"

// 入力
#include "../../../Input/InputCheck.h"

// ImGui
#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Fade::Fade(class Game* game)
	: UI(game)
	, fade_(nullptr)
	, parameter_is_fade_execute_(nullptr)
	, parameter_is_fade_completed_(nullptr)
	, fade_state_(FadeState::None)
	, fade_alpha_(0.f)
	, execute_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Fade::~Fade(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Fade::Init(void)
{
	// フェード用スプライトの生成
	fade_ = NEW SpriteRendererComponent(this, 300);
	fade_->SetRendererLayerType(RendererLayerType::Fade);
	fade_->SetVertexColor(0, 0, 0);

	// 値コンポーネントの生成
	{
		// フェードを実行するか？
		parameter_is_fade_execute_ = NEW BoolParameterComponent(this);
		parameter_is_fade_execute_->SetParameterType(ParameterType::IsFadeExecute);
  
		// フェードが完了したか？
		parameter_is_fade_completed_ = NEW BoolParameterComponent(this);
		parameter_is_fade_completed_->SetParameterType(ParameterType::IsFadeCompleted);
	}

	// 値の初期化
	{
		fade_state_	= FadeState::Idle;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Fade::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void Fade::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Fade::UpdateGameObject(float deltaTime)
{
	// 値コンポーネントのnullチェック
	{
		if (parameter_is_fade_execute_ == nullptr)
		{
			assert(!"Fade::UpdateGameObject():値コンポーネント:parameter_is_fade_execute_ が”nullptr”でした。");
			return;
		}
	
		if (parameter_is_fade_completed_ == nullptr)
		{
			assert(!"Fade::UpdateGameObject():値コンポーネント:parameter_is_fade_completed_ が、nullptrでした。");
			return;
		}
	}

	// 画面サイズの取得
	const float screen_width  = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	// フェードの画面サイズの設定
	fade_->SetScaleX(screen_width);
	fade_->SetScaleY(screen_height);
	
	// フェードの開始命令を発行
	const bool is_execute_fade = parameter_is_fade_execute_->GetBool();
	if (is_execute_fade == true)
	{
		// フェードが実行状態を初期化
		parameter_is_fade_execute_->SetBool(false);

		// フェードが未完了の状態を通知
		parameter_is_fade_completed_->SetBool(false);

		// フェードの実行時間を初期化
		execute_time_ = 0.f;
	}

	// フェードの最大実行時間に到達したら
	if (execute_time_ >= (MAX_EXECUTE_TIME_ - 0.01f))
	{
		if (fade_state_ == FadeState::FadeOut)
		{
			// フェードが完了したことを通知
			parameter_is_fade_completed_->SetBool(true);
		}

		// ステートを待機状態へ移行
		fade_state_ = FadeState::Idle;
	}

	// 実際の挙動を定義
	switch (fade_state_)
	{
	case FadeState::Idle:
		if (is_execute_fade == true)	// フェードを実行するか?
		{
			// フェードのステート更新処理
			this->UpdateFadeState();
		}
		break;

	case FadeState::FadeOut:
		this->FadeOut(deltaTime); 
		break;

	case FadeState::FadeIn:
		this->FadeIn(deltaTime);  
		break;

	default:
		assert(!"Fade::UpdateGameObject():フェードが不正な状態です！");
		break;
	}

	// フェードのアルファ値を設定
	fade_->SetVertexColor(0, 0, 0, static_cast<int>(fade_alpha_));
}

/*-----------------------------------------------------------------------------
/* フェード状態の更新処理
-----------------------------------------------------------------------------*/
void Fade::UpdateFadeState(void)
{
	// フェードインするか？
	const bool is_fadein = (fade_alpha_ >= (MAX_FADE_ALPHA_VALUE_ - 0.01f));
	if (is_fadein)
	{
		fade_state_ = FadeState::FadeIn;
		return;
	}

	// フェードアウトするか？
	const bool is_fadeout = (fade_alpha_ <= 0.1f);
	if (is_fadeout)
	{
	 	fade_state_ = FadeState::FadeOut;
		return;
	}
}

/*-----------------------------------------------------------------------------
/* 画面を暗くフェードアウト
-----------------------------------------------------------------------------*/
void Fade::FadeOut(float deltaTime)
{
	if (execute_time_ >= MAX_EXECUTE_TIME_) { return; }

	// 実行時間へ加算する
	execute_time_ += deltaTime;

	// 255 * 1.f の倍率の掛け算をする
	const float scale = Easing::SineOut(execute_time_);
	fade_alpha_ = MAX_FADE_ALPHA_VALUE_ * scale;
}

/*-----------------------------------------------------------------------------
/* 画面を明るくフェードイン
-----------------------------------------------------------------------------*/
void Fade::FadeIn(float deltaTime)
{
	if (execute_time_ >= MAX_EXECUTE_TIME_) { return; }

	// 実行時間へ加算する
	execute_time_ += deltaTime;

	// 255 から減算する値を 255 * 1.f の倍率の掛け算の結果から求める
	const float scale = Easing::SineOut(execute_time_);
	fade_alpha_ = MAX_FADE_ALPHA_VALUE_ - (MAX_FADE_ALPHA_VALUE_ * scale);
}

/*=============================================================================
/*		End of File
=============================================================================*/