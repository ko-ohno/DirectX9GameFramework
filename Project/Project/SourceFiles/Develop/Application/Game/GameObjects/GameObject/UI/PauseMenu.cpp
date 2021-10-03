/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PauseMenu.cpp] �|�[�Y���j���[��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�|�[�Y���j���[��ʂ̋������`�����N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "PauseMenu.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/AudioComponent.h"
#include "../../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
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
	//UI�I�u�W�F�N�g�𐶐�������A
	//�����o�ϐ�state_��Closing�ɂȂ�܂ŕ\�����ꑱ����B
	//�T�u�N���X�͐����ƍ폜�Ɋւ��鏈�����L�q���邱�Ƃ�UI�̑�������邱��
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
PauseMenu::~PauseMenu(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool PauseMenu::Init(void)
{
	const int all_draw_order = 300;
	const int bg_offset_draw_order = -50;

	pause_select_state_old_ = pause_select_state_ = PauseMenuSelectState::Resume;

	// ���j���[�̐���
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

	// �����R���|�[�l���g�̐���
	{
		// SE�̐���
		se_select_ = NEW AudioComponent(this);
		se_select_->SetSound(SoundType::SelectSound);
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void PauseMenu::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
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
/* �X�V����
-----------------------------------------------------------------------------*/
void PauseMenu::UpdateGameObject(float deltaTime)
{
	auto game_state = game_->GetGameState();
	if (game_state != Game::GameState::Paused)
	{
		this->SetGameObjectState(GameObject::State::Dead);
		return;
	}

	// �|�[�Y���j���[�̍X�V
	this->UpdatePauseMenu(deltaTime);

	// �|�[�Y���j���[�̏�Ԃ��X�V
	this->UpdatePauseMenuState(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �|�[�Y���j���[�̍X�V����
-----------------------------------------------------------------------------*/
void PauseMenu::UpdatePauseMenu(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	float screen_width = game_->GetGraphics()->GetScreenSize().x_;
	float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	float texture_width = 0.f;
	float texture_height = 0.f;

	// �\��̃X�v���C�g
	{
		texture_width = static_cast<float>(pause_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(pause_->GetTextureImageInfo()->Height);

		pause_->SetScaleX(texture_width);
		pause_->SetScaleY(texture_height);

		pause_->SetTranslationX(screen_width / 2.f);
		pause_->SetTranslationY(screen_height / 4.f);
	}

	//�@�Q�[���ĊJ�̃X�v���C�g
	{
		texture_width = static_cast<float>(menu_game_resume_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_game_resume_->GetTextureImageInfo()->Height);

		menu_game_resume_->SetScaleX(texture_width);
		menu_game_resume_->SetScaleY(texture_height);

		menu_game_resume_->SetTranslationX(screen_width / 2.f);
		menu_game_resume_->SetTranslationY((screen_height / 2.f) - (texture_height / 2.f));
	}

	// �Q�[���I���̃X�v���C�g
	{
		texture_width = static_cast<float>(menu_game_quit_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_game_quit_->GetTextureImageInfo()->Height);

		menu_game_quit_->SetScaleX(texture_width);
		menu_game_quit_->SetScaleY(texture_height);

		menu_game_quit_->SetTranslationX(screen_width / 2.f);
		menu_game_quit_->SetTranslationY((screen_height / 2.f) + (texture_height / 2.f));
	}

	// ���ւ����ނ̃X�v���C�g
	{
		texture_width = static_cast<float>(go_next_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(go_next_->GetTextureImageInfo()->Height);

		go_next_->SetScaleX(texture_width);
		go_next_->SetScaleY(texture_height);

		go_next_->SetTranslationX(screen_width - texture_width);
		go_next_->SetTranslationY(screen_height - texture_height);
	}

	// �w�i�̃X�v���C�g
	{
		texture_width = static_cast<float>(menu_bg_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_bg_->GetTextureImageInfo()->Height);

		menu_bg_->SetScaleX(screen_width);
		menu_bg_->SetScaleY(screen_height);

		menu_bg_->SetTranslationX(0.f);
		menu_bg_->SetTranslationY(0.f);
	}

	// �����Đ�
	if (pause_select_state_ != pause_select_state_old_)
	{
		se_select_->Play();
	}

	// 1�t���[���O�̏����X�V
	pause_select_state_old_ = pause_select_state_;
}

/*-----------------------------------------------------------------------------
/* �|�[�Y���j���[�̏�ԍX�V����
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
		assert(!"PauseMenu::UpdatePauseMenuState():�|�[�Y���j���[�̏�Ԃ��s���ȏ�Ԃł�");
		break;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/