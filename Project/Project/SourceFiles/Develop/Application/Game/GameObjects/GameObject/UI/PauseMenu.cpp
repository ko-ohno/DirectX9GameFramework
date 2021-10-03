/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PauseMenu.cpp] ポーズメニュー画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ポーズメニュー画面の挙動を定義したクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "PauseMenu.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/AudioComponent.h"
#include "../../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
PauseMenu::PauseMenu(class Game* game)
	: UI(game)
	, pause_(nullptr)
	, menu_game_resume_(nullptr)
	, menu_game_quit_(nullptr)
	, menu_cursor_(nullptr)
	, go_next_(nullptr)
	, menu_bg_(nullptr)
	, pause_select_state_(PauseMenuSelectState::None)
	, pause_select_state_old_(PauseMenuSelectState::None)
{
	//UIオブジェクトを生成したら、
	//メンバ変数state_がClosingになるまで表示され続ける。
	//サブクラスは生成と削除に関する処理を記述することでUIの操作をすること
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
PauseMenu::~PauseMenu(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool PauseMenu::Init(void)
{
	const int all_draw_order = 300;
	const int bg_offset_draw_order = -50;

	pause_select_state_old_ = pause_select_state_ = PauseMenuSelectState::Resume;

	// メニューの生成
	{
		pause_ = NEW SpriteRendererComponent(this, all_draw_order);
		pause_->SetTexture(TextureType::Pause);
		pause_->IsSetDrawingPositionToCenter(true);

		menu_game_resume_ = NEW SpriteRendererComponent(this, all_draw_order);
		menu_game_resume_->SetTexture(TextureType::Resume);
		menu_game_resume_->IsSetDrawingPositionToCenter(true);

		menu_game_quit_ = NEW SpriteRendererComponent(this, all_draw_order);
		menu_game_quit_->SetTexture(TextureType::GameQuit);
		menu_game_quit_->IsSetDrawingPositionToCenter(true);

		menu_bg_ = NEW SpriteRendererComponent(this, all_draw_order + bg_offset_draw_order);
		menu_bg_->SetTexture(TextureType::Blank);
		menu_bg_->SetVertexColor(0, 0, 0, 128);

		menu_cursor_ = NEW SpriteRendererComponent(this, all_draw_order);
		menu_cursor_->SetTexture(TextureType::NearReticle);
		menu_cursor_->IsSetDrawingPositionToCenter(true);

		go_next_ = NEW SpriteRendererComponent(this, all_draw_order);
		go_next_->SetTexture(TextureType::GoNext);
	}

	// 音声コンポーネントの生成
	{
		// SEの生成
		se_select_ = NEW AudioComponent(this);
		se_select_->SetSound(SoundType::SelectSound);
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void PauseMenu::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void PauseMenu::InputGameObject(void)
{
	const float InputDeadZone = 0.1f;

	const bool is_up = ((InputCheck::XInputThumbLeft(PadIndex::Pad1).y_ >= InputDeadZone)
						|| InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_UP));
	if (is_up)
	{
		pause_select_state_ = PauseMenuSelectState::Resume;
	}

	const bool is_down = ((InputCheck::XInputThumbLeft(PadIndex::Pad1).y_ <= -InputDeadZone)
						  || InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_DOWN));
	if (is_down)
	{
		pause_select_state_ = PauseMenuSelectState::Quit;
	}
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void PauseMenu::UpdateGameObject(float deltaTime)
{
	auto game_state = game_->GetGameState();
	if (game_state != Game::GameState::Paused)
	{
		this->SetGameObjectState(GameObject::State::Dead);
		return;
	}

	// ポーズメニューの更新
	this->UpdatePauseMenu(deltaTime);

	// ポーズメニューの状態を更新
	this->UpdatePauseMenuState(deltaTime);
}

/*-----------------------------------------------------------------------------
/* ポーズメニューの更新処理
-----------------------------------------------------------------------------*/
void PauseMenu::UpdatePauseMenu(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	float screen_width = game_->GetGraphics()->GetScreenSize().x_;
	float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	float texture_width = 0.f;
	float texture_height = 0.f;

	// 表題のスプライト
	{
		texture_width = static_cast<float>(pause_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(pause_->GetTextureImageInfo()->Height);

		pause_->SetScaleX(texture_width);
		pause_->SetScaleY(texture_height);

		pause_->SetTranslationX(screen_width / 2.f);
		pause_->SetTranslationY(screen_height / 4.f);
	}

	//　ゲーム再開のスプライト
	{
		texture_width = static_cast<float>(menu_game_resume_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_game_resume_->GetTextureImageInfo()->Height);

		menu_game_resume_->SetScaleX(texture_width);
		menu_game_resume_->SetScaleY(texture_height);

		menu_game_resume_->SetTranslationX(screen_width / 2.f);
		menu_game_resume_->SetTranslationY((screen_height / 2.f) - (texture_height / 2.f));
	}

	// ゲーム終了のスプライト
	{
		texture_width = static_cast<float>(menu_game_quit_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_game_quit_->GetTextureImageInfo()->Height);

		menu_game_quit_->SetScaleX(texture_width);
		menu_game_quit_->SetScaleY(texture_height);

		menu_game_quit_->SetTranslationX(screen_width / 2.f);
		menu_game_quit_->SetTranslationY((screen_height / 2.f) + (texture_height / 2.f));
	}

	// 次へすすむのスプライト
	{
		texture_width = static_cast<float>(go_next_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(go_next_->GetTextureImageInfo()->Height);

		go_next_->SetScaleX(texture_width);
		go_next_->SetScaleY(texture_height);

		go_next_->SetTranslationX(screen_width - texture_width);
		go_next_->SetTranslationY(screen_height - texture_height);
	}

	// 背景のスプライト
	{
		texture_width = static_cast<float>(menu_bg_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_bg_->GetTextureImageInfo()->Height);

		menu_bg_->SetScaleX(screen_width);
		menu_bg_->SetScaleY(screen_height);

		menu_bg_->SetTranslationX(0.f);
		menu_bg_->SetTranslationY(0.f);
	}

	// 音声再生
	if (pause_select_state_ != pause_select_state_old_)
	{
		se_select_->Play();
	}

	// 1フレーム前の情報を更新
	pause_select_state_old_ = pause_select_state_;
}

/*-----------------------------------------------------------------------------
/* ポーズメニューの状態更新処理
-----------------------------------------------------------------------------*/
void PauseMenu::UpdatePauseMenuState(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	switch (pause_select_state_)
	{
	case PauseMenuSelectState::Resume:
		menu_cursor_->SetScaleX(menu_game_resume_->GetScale()->x);
		menu_cursor_->SetScaleY(menu_game_resume_->GetScale()->y);

		menu_cursor_->SetTranslationX(menu_game_resume_->GetPosition()->x);
		menu_cursor_->SetTranslationY(menu_game_resume_->GetPosition()->y);

		if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
		{
			game_->SetGameState(Game::GameState::Gameplay);
		}
		break;

	case PauseMenuSelectState::Quit:
		menu_cursor_->SetScaleX(menu_game_quit_->GetScale()->x);
		menu_cursor_->SetScaleY(menu_game_quit_->GetScale()->y);

		menu_cursor_->SetTranslationX(menu_game_quit_->GetPosition()->x);
		menu_cursor_->SetTranslationY(menu_game_quit_->GetPosition()->y);
		if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
		{
			game_->SetGameState(Game::GameState::BackToTitle);
		}
		break;
	
	default:
		assert(!"PauseMenu::UpdatePauseMenuState():ポーズメニューの状態が不正な状態です");
		break;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/