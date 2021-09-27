/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Title.cpp] �^�C�g����ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�^�C�g����ʂ̋������`�����N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "Title.h"
#include "../../../Game.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/AudioComponent.h"
#include "../../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
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
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Title::~Title(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Title::Init(void)
{
	// �^�C�g���̐���
	{
		title_ = NEW SpriteRendererComponent(this);
		title_->SetTexture(TextureType::Title);
	}

	// �w�i�̐���
	{
		bg_ = NEW SpriteRendererComponent(this, 150);
		bg_->SetTexture(TextureType::ScreenBG);
	}

	// ���j���[�̐���
	{
		// �Q�[���J�n�̃��j���[
		menu_game_start_ = NEW SpriteRendererComponent(this);
		menu_game_start_->SetTexture(TextureType::GameStart);

		// �Q�[���I���̃��j���[
		menu_game_quit_ = NEW SpriteRendererComponent(this);
		menu_game_quit_->SetTexture(TextureType::GameQuit);

		// ���j���[�̃J�[�\��
		menu_cursor_ = NEW SpriteRendererComponent(this);
		menu_cursor_->SetTexture(TextureType::NearReticle);

		// �����̕\��
		go_next_ = NEW SpriteRendererComponent(this);
		go_next_->SetTexture(TextureType::GoNext);
	}

	// ���j���[�̏�����
	select_state_old_ = select_state_ = TitleMenuState::GameStart;

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Title::Uninit(void)
{
	// BGM�̒�~
	{
		bgm_title_->Stop();
	}
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void Title::InputGameObject(void)
{
	// ���[�h������������͂��󂯕t���Ȃ�
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
/* �X�V����
-----------------------------------------------------------------------------*/
void Title::UpdateGameObject(float deltaTime)
{
	// �����R���|�[�l���g�̐���
	{
		// SE�̐���
		if (se_select_ == nullptr)
		{
			se_select_ = NEW AudioComponent(this);
			se_select_->SetSound(SoundType::SelectSound);
		}
	
		// BGM�̐���
		if (bgm_title_ == nullptr)
		{
			// BGM�̐���
			bgm_title_ = NEW AudioComponent(this);
			bgm_title_->SetSound(SoundType::JetPenguin);
			bgm_title_->PlayLoop();
		}
	}

	// ��ʃT�C�Y�̎擾
	screen_width_  = game_->GetGraphics()->GetScreenSize().x_;
	screen_height_ = game_->GetGraphics()->GetScreenSize().y_;

	// �\��̃X�v���C�g�̍X�V
	this->UpdateTitleSprite(deltaTime);

	// �w�i�̍X�V
	this->UpdateBackground(deltaTime);

	// ���j���[�̍X�V
	this->UpdateMenu(deltaTime);
	
	// ���͂��ꂽ���1�t���[���O�ƈ������
	if (select_state_ != select_state_old_)
	{
		if (se_select_ != nullptr)
		{
			se_select_->Play();
		}
	}
	
	// 1�t���[���O�̏����X�V
	select_state_old_ = select_state_;
}

/*-----------------------------------------------------------------------------
/* �^�C�g���̍X�V����
-----------------------------------------------------------------------------*/
void Title::UpdateTitleSprite(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �e�N�X�`���̃T�C�Y���擾
	float texture_width  = static_cast<float>(title_->GetTextureImageInfo()->Width);
	float texture_height = static_cast<float>(title_->GetTextureImageInfo()->Height);

	// �|���S���̃T�C�Y���X�V
	title_->SetScaleX(texture_width);
	title_->SetScaleY(texture_height);

	// �`����W�̍X�V
	title_->IsSetDrawingPositionToCenter(true);
	title_->SetTranslationX(screen_width_ / 2.f);
	title_->SetTranslationY(screen_height_ / 3.f);
}

/*-----------------------------------------------------------------------------
/* �w�i�̍X�V����
-----------------------------------------------------------------------------*/
void Title::UpdateBackground(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �w�i�|���S���̃T�C�Y���X�V
	bg_->SetScaleX(screen_width_);
	bg_->SetScaleY(screen_height_);

	// �e�N�X�`���̐؂���T�C�Y��ύX
	float texture_width  = static_cast<float>(bg_->GetTextureImageInfo()->Width);
	float texture_height = static_cast<float>(bg_->GetTextureImageInfo()->Height);

	// �e�N�X�`���̐؂�����W��������
	static float texture_cut_pos_x = 0.f;
	const float scroll_speed = 100.f;
	texture_cut_pos_x += scroll_speed * deltaTime;
	if (texture_cut_pos_x >= texture_width)
	{
		texture_cut_pos_x = 0.f;
	}

	// �w�i��UV�A�j���[�V����
	bg_->SetUVAnimation(static_cast<int>(texture_cut_pos_x)
					   , 0
					   , static_cast<int>(screen_width_)
					   , static_cast<int>(texture_height));
}


/*-----------------------------------------------------------------------------
/* ���j���[�̍X�V����
-----------------------------------------------------------------------------*/
void Title::UpdateMenu(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	float texture_width;
	float texture_height;

	// �Q�[���J�n�̃X�v���C�g
	{
		// �e�N�X�`���̃T�C�Y���擾
		texture_width  = static_cast<float>(menu_game_start_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_game_start_->GetTextureImageInfo()->Height);

		menu_game_start_->SetScaleX(texture_width);
		menu_game_start_->SetScaleY(texture_height);

		// �`����W�̍X�V
		menu_game_start_->IsSetDrawingPositionToCenter(true);
		menu_game_start_->SetTranslationX(screen_width_ / 2.f);
		menu_game_start_->SetTranslationY(((screen_height_ / 4.f) * 3.f) - (texture_height / 3.f));

	}

	// �Q�[���I���̃X�v���C�g
	{
		texture_width  = static_cast<float>(menu_game_quit_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(menu_game_quit_->GetTextureImageInfo()->Height);

		menu_game_quit_->SetScaleX(texture_width);
		menu_game_quit_->SetScaleY(texture_height);

		// �`����W�̍X�V
		menu_game_quit_->IsSetDrawingPositionToCenter(true);
		menu_game_quit_->SetTranslationX(screen_width_ / 2.f);
		menu_game_quit_->SetTranslationY(((screen_height_ / 4.f) * 3.f) + (texture_height / 3.f));
	}

	menu_cursor_->IsSetDrawingPositionToCenter(true);
	switch (select_state_)
	{
	case TitleMenuState::GameStart:

		// �e�k���̍X�V
		menu_cursor_->SetScaleX(menu_game_start_->GetScale()->x);
		menu_cursor_->SetScaleY(menu_game_start_->GetScale()->y);

		// �`����W�̍X�V
		menu_cursor_->SetTranslationX(menu_game_start_->GetPosition()->x);
		menu_cursor_->SetTranslationY(menu_game_start_->GetPosition()->y);
		break;

	case TitleMenuState::GameQuit:

		// �e�k���̍X�V
		menu_cursor_->SetScaleX(menu_game_quit_->GetScale()->x);
		menu_cursor_->SetScaleY(menu_game_quit_->GetScale()->y);

		// �`����W�̍X�V
		menu_cursor_->SetTranslationX(menu_game_quit_->GetPosition()->x);
		menu_cursor_->SetTranslationY(menu_game_quit_->GetPosition()->y);
		break;

	default:
		assert("Title::UpdateMenu():�^�C�g���̑I�����j���[���s���ȏ������N�����Ă��܂��I");
		break;
	}

	// �����̕\��
	{
		// �e�N�X�`���̃T�C�Y���擾
		texture_width  = static_cast<float>(go_next_->GetTextureImageInfo()->Width);
		texture_height = static_cast<float>(go_next_->GetTextureImageInfo()->Height);

		// �|���S���̃T�C�Y���X�V
		go_next_->SetScaleX(texture_width);
		go_next_->SetScaleY(texture_height);

		// �`����W�̍X�V
		go_next_->SetTranslationX(screen_width_ - texture_width);
		go_next_->SetTranslationY(screen_height_ - texture_height);
	}
	
}

/*=============================================================================
/*		End of File
=============================================================================*/