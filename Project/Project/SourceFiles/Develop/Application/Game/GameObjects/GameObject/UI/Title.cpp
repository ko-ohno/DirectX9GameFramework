/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Title.cpp] タイトル画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：タイトル画面の挙動を定義したクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "Title.h"
#include "../../../Game.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/AudioComponent.h"
#include "../../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Title::Title(class Game* game)
	: UI(game)
	, menu_game_start_(nullptr)
	, menu_game_quit_(nullptr)
	, menu_cursor_(nullptr)
	, title_(nullptr)
	, bg_(nullptr)
	, bgm_title_(nullptr)
	, se_select_(nullptr)
	, select_state_(TitleMenuState::None)
	, select_state_old_(TitleMenuState::None)
	, screen_width_(0)
	, screen_height_(0)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Title::~Title(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Title::Init(void)
{
	// タイトルの生成
	{
		title_ = NEW SpriteRendererComponent(this);
		title_->SetTexture(TextureType::Title);
	}

	// 背景の生成
	{
		bg_ = NEW SpriteRendererComponent(this, 150);
		bg_->SetTexture(TextureType::ScreenBG);
	}

	// メニューの生成
	{
		// ゲーム開始のメニュー
		menu_game_start_ = NEW SpriteRendererComponent(this);
		menu_game_start_->SetTexture(TextureType::GameStart);

		// ゲーム終了のメニュー
		menu_game_quit_ = NEW SpriteRendererComponent(this);
		menu_game_quit_->SetTexture(TextureType::GameQuit);

		// メニューのカーソル
		menu_cursor_ = NEW SpriteRendererComponent(this);
		menu_cursor_->SetTexture(TextureType::NearReticle);

		// 説明の表示
		go_next_ = NEW SpriteRendererComponent(this);
		go_next_->SetTexture(TextureType::GoNext);
	}

	// メニューの初期化
	select_state_old_ = select_state_ = TitleMenuState::GameStart;

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Title::Uninit(void)
{
	// BGMの停止
	{
		bgm_title_->Stop();
	}
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void Title::InputGameObject(void)
{
	// ロード中だったら入力を受け付けない
	auto game_state = game_->GetGameState();
	if (game_state == Game::GameState::Loading) { return; }
	
	const float InputDeadZone = 0.1f;

	const bool is_up = ((InputCheck::XInputThumbLeft(PadIndex::Pad1).y_ >= InputDeadZone)
						|| InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_UP));
	if (is_up)
	{
		select_state_ = TitleMenuState::GameStart;
	}

	const bool is_down = ((InputCheck::XInputThumbLeft(PadIndex::Pad1).y_ <= -InputDeadZone)
						  || InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_DOWN));
	if (is_down)
	{
		select_state_ = TitleMenuState::GameQuit;
	}
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Title::UpdateGameObject(float deltaTime)
{
	// 音声コンポーネントの生成
	{
		// SEの生成
		if (se_select_ == nullptr)
		{
			se_select_ = NEW AudioComponent(this);
			se_select_->SetSound(SoundType::SelectSound);
		}
	
		// BGMの生成
		if (bgm_title_ == nullptr)
		{
			// BGMの生成
			bgm_title_ = NEW AudioComponent(this);
			bgm_title_->SetSound(SoundType::JetPenguin);
			bgm_title_->PlayLoop();
		}
	}

	// 画面サイズの取得
	screen_width_  = game_->GetGraphics()->GetScreenSize().x_;
	screen_height_ = game_->GetGraphics()->GetScreenSize().y_;

	// 表題のスプライトの更新
	this->UpdateTitleSprite(deltaTime);

	// 背景の更新
	this->UpdateBackground(deltaTime);

	// メニューの更新
	this->UpdateMenu(deltaTime);
	
	// 入力された情報が1フレーム前と違ったら
	if (select_state_ != select_state_old_)
	{
		if (se_select_ != nullptr)
		{
			se_select_->Play();
		}
	}
	
	// 1フレーム前の情報を更新
	select_state_old_ = select_state_;
}

/*-----------------------------------------------------------------------------
/* タイトルの更新処理
-----------------------------------------------------------------------------*/
void Title::UpdateTitleSprite(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// テクスチャのサイズを取得
	float texture_width  = static_cast<float>(title_->GetTextureImageInfo()->Width);
	float texture_height = static_cast<float>(title_->GetTextureImageInfo()->Height);

	// ポリゴンのサイズを更新
	title_->SetScaleX(texture_width);
	title_->SetScaleY(texture_height);

	// 描画座標の更新
	title_->IsSetDrawingPositionToCenter(true);
	title_->SetTranslationX(screen_width_ / 2.f);
	title_->SetTranslationY(screen_height_ / 3.f);
}

/*-----------------------------------------------------------------------------
/* 背景の更新処理
-----------------------------------------------------------------------------*/
void Title::UpdateBackground(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 背景ポリゴンのサイズを更新
	bg_->SetScaleX(screen_width_);
	bg_->SetScaleY(screen_height_);

	// テクスチャの切り取りサイズを変更
	float texture_width  = static_cast<float>(bg_->GetTextureImageInfo()->Width);
	float texture_height = static_cast<float>(bg_->GetTextureImageInfo()->Height);

	// テクスチャの切り取り座標を初期化
	static float texture_cut_pos_x = 0.f;
	const float scroll_speed = 100.f;
	texture_cut_pos_x += scroll_speed * deltaTime;
	if (texture_cut_pos_x >= texture_width)
	{
		texture_cut_pos_x = 0.f;
	}

	// 背景をUVアニメーション
	bg_->SetUVAnimation(static_cast<int>(texture_cut_pos_x)
					   , 0
					   , static_cast<int>(screen_width_)
					   , static_cast<int>(texture_height));
}


/*-----------------------------------------------------------------------------
/* メニューの更新処理
-----------------------------------------------------------------------------*/
void Title::UpdateMenu(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	float texture_width;
	float texture_height;

	// ゲーム開始のスプライト
	{
		// テクスチャのサイズを取得
		texture_width  = static_cast<float>(menu_game_start_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_game_start_->GetTextureImageInfo()->Height);

		menu_game_start_->SetScaleX(texture_width);
		menu_game_start_->SetScaleY(texture_height);

		// 描画座標の更新
		menu_game_start_->IsSetDrawingPositionToCenter(true);
		menu_game_start_->SetTranslationX(screen_width_ / 2.f);
		menu_game_start_->SetTranslationY(((screen_height_ / 4.f) * 3.f) - (texture_height / 3.f));

	}

	// ゲーム終了のスプライト
	{
		texture_width  = static_cast<float>(menu_game_quit_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_game_quit_->GetTextureImageInfo()->Height);

		menu_game_quit_->SetScaleX(texture_width);
		menu_game_quit_->SetScaleY(texture_height);

		// 描画座標の更新
		menu_game_quit_->IsSetDrawingPositionToCenter(true);
		menu_game_quit_->SetTranslationX(screen_width_ / 2.f);
		menu_game_quit_->SetTranslationY(((screen_height_ / 4.f) * 3.f) + (texture_height / 3.f));
	}

	menu_cursor_->IsSetDrawingPositionToCenter(true);
	switch (select_state_)
	{
	case TitleMenuState::GameStart:

		// 各縮率の更新
		menu_cursor_->SetScaleX(menu_game_start_->GetScale()->x);
		menu_cursor_->SetScaleY(menu_game_start_->GetScale()->y);

		// 描画座標の更新
		menu_cursor_->SetTranslationX(menu_game_start_->GetPosition()->x);
		menu_cursor_->SetTranslationY(menu_game_start_->GetPosition()->y);
		break;

	case TitleMenuState::GameQuit:

		// 各縮率の更新
		menu_cursor_->SetScaleX(menu_game_quit_->GetScale()->x);
		menu_cursor_->SetScaleY(menu_game_quit_->GetScale()->y);

		// 描画座標の更新
		menu_cursor_->SetTranslationX(menu_game_quit_->GetPosition()->x);
		menu_cursor_->SetTranslationY(menu_game_quit_->GetPosition()->y);
		break;

	default:
		assert("Title::UpdateMenu():タイトルの選択メニューが不正な処理を起こしています！");
		break;
	}

	// 説明の表示
	{
		// テクスチャのサイズを取得
		texture_width  = static_cast<float>(go_next_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(go_next_->GetTextureImageInfo()->Height);

		// ポリゴンのサイズを更新
		go_next_->SetScaleX(texture_width);
		go_next_->SetScaleY(texture_height);

		// 描画座標の更新
		go_next_->SetTranslationX(screen_width_ - texture_width);
		go_next_->SetTranslationY(screen_height_ - texture_height);
	}
	
}

/*=============================================================================
/*		End of File
=============================================================================*/