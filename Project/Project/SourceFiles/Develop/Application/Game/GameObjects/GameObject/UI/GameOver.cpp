/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameOver.cpp] ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "GameOver.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
GameOver::GameOver(Game* game)
	: UI(game)
	, game_over_(nullptr)
	, bg_(nullptr)
	, text_go_to_next_(nullptr)
	, screen_animation_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
GameOver::~GameOver(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool GameOver::Init(void)
{
	const int draw_order = 400;

	// 画面タイトルの表示
	{
		game_over_ = NEW SpriteRendererComponent(this, draw_order+10);
		game_over_->SetTexture(TextureType::GameOver);
	}

	// 背景の表示
	{
		bg_ = NEW SpriteRendererComponent(this, draw_order);
		bg_->SetTexture(TextureType::Blank);
		bg_->SetVertexColor(0, 0, 0, 128);
	}

	// 説明を表示
	{
		text_go_to_next_ = NEW SpriteRendererComponent(this, draw_order +10);
		text_go_to_next_->SetTexture(TextureType::GoNext);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void GameOver::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void GameOver::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void GameOver::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 画面サイズの取得
	const float screen_width_ = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height_ = game_->GetGraphics()->GetScreenSize().y_;

	// 画面アニメーションの時間の計算
	screen_animation_time_ += deltaTime;
	if (screen_animation_time_ >= MAX_SCREEN_ANIMATION_TIME_)
	{
		screen_animation_time_ = MAX_SCREEN_ANIMATION_TIME_;
	}

	// ゲーム画面タイトルの設定
	{
		// テクスチャのサイズを取得
		const float texture_height = static_cast<float>(game_over_->GetTextureImageInfo()->Height);
		const float texture_width = static_cast<float>(game_over_->GetTextureImageInfo()->Width);

		// ポリゴンのサイズを更新
		game_over_->SetScaleX(texture_width * 2.f);
		game_over_->SetScaleY(texture_height * 2.f);

		// 描画座標の更新
		const float draw_pos_y = Math::Lerp(screen_height_ + (screen_height_ * 0.5f), (screen_height_ / 3.f), Easing::SineOut(screen_animation_time_));
		game_over_->IsSetDrawingPositionToCenter(true);
		game_over_->SetTranslationX(screen_width_ / 2.f);
		game_over_->SetTranslationY(draw_pos_y);
	}

	// 背景の設定
	{
		// テクスチャのサイズを取得
		//const float texture_height = static_cast<float>(game_over_->GetTextureImageInfo()->Height);
		//const float texture_width = static_cast<float>(game_over_->GetTextureImageInfo()->Width);

		// ポリゴンのサイズを更新
		bg_->SetScaleX(screen_width_);
		bg_->SetScaleY(screen_height_);
		bg_->SetVertexColor(0, 0, 0, static_cast<int>(128 * Easing::SineOut(screen_animation_time_)));
	}

	// 説明の設定
	{
		// テクスチャのサイズを取得
		const float texture_height = static_cast<float>(game_over_->GetTextureImageInfo()->Height);
		const float texture_width = static_cast<float>(game_over_->GetTextureImageInfo()->Width);

		// ポリゴンのサイズを更新
		text_go_to_next_->SetScaleX(texture_width);
		text_go_to_next_->SetScaleY(texture_height);

		// 描画座標の更新
		text_go_to_next_->SetTranslationX(screen_width_ - texture_width);
		text_go_to_next_->SetTranslationY(screen_height_ - texture_height);
		text_go_to_next_->SetVertexColor(255, 255, 255, static_cast<int>(255 * Easing::SineOut(screen_animation_time_)));
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/