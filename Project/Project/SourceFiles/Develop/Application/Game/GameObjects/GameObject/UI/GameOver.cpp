/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameOver.cpp] �Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "GameOver.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
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
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
GameOver::~GameOver(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool GameOver::Init(void)
{
	const int draw_order = 400;

	// ��ʃ^�C�g���̕\��
	{
		game_over_ = NEW SpriteRendererComponent(this, draw_order+10);
		game_over_->SetTexture(TextureType::GameOver);
	}

	// �w�i�̕\��
	{
		bg_ = NEW SpriteRendererComponent(this, draw_order);
		bg_->SetTexture(TextureType::Blank);
		bg_->SetVertexColor(0, 0, 0, 128);
	}

	// ������\��
	{
		text_go_to_next_ = NEW SpriteRendererComponent(this, draw_order +10);
		text_go_to_next_->SetTexture(TextureType::GoNext);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void GameOver::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void GameOver::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void GameOver::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ��ʃT�C�Y�̎擾
	const float screen_width_ = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height_ = game_->GetGraphics()->GetScreenSize().y_;

	// ��ʃA�j���[�V�����̎��Ԃ̌v�Z
	screen_animation_time_ += deltaTime;
	if (screen_animation_time_ >= MAX_SCREEN_ANIMATION_TIME_)
	{
		screen_animation_time_ = MAX_SCREEN_ANIMATION_TIME_;
	}

	// �Q�[����ʃ^�C�g���̐ݒ�
	{
		// �e�N�X�`���̃T�C�Y���擾
		const float texture_height = static_cast<float>(game_over_->GetTextureImageInfo()->Height);
		const float texture_width = static_cast<float>(game_over_->GetTextureImageInfo()->Width);

		// �|���S���̃T�C�Y���X�V
		game_over_->SetScaleX(texture_width * 2.f);
		game_over_->SetScaleY(texture_height * 2.f);

		// �`����W�̍X�V
		const float draw_pos_y = Math::Lerp(screen_height_ + (screen_height_ * 0.5f), (screen_height_ / 3.f), Easing::SineOut(screen_animation_time_));
		game_over_->IsSetDrawingPositionToCenter(true);
		game_over_->SetTranslationX(screen_width_ / 2.f);
		game_over_->SetTranslationY(draw_pos_y);
	}

	// �w�i�̐ݒ�
	{
		// �e�N�X�`���̃T�C�Y���擾
		//const float texture_height = static_cast<float>(game_over_->GetTextureImageInfo()->Height);
		//const float texture_width = static_cast<float>(game_over_->GetTextureImageInfo()->Width);

		// �|���S���̃T�C�Y���X�V
		bg_->SetScaleX(screen_width_);
		bg_->SetScaleY(screen_height_);
		bg_->SetVertexColor(0, 0, 0, static_cast<int>(128 * Easing::SineOut(screen_animation_time_)));
	}

	// �����̐ݒ�
	{
		// �e�N�X�`���̃T�C�Y���擾
		const float texture_height = static_cast<float>(game_over_->GetTextureImageInfo()->Height);
		const float texture_width = static_cast<float>(game_over_->GetTextureImageInfo()->Width);

		// �|���S���̃T�C�Y���X�V
		text_go_to_next_->SetScaleX(texture_width);
		text_go_to_next_->SetScaleY(texture_height);

		// �`����W�̍X�V
		text_go_to_next_->SetTranslationX(screen_width_ - texture_width);
		text_go_to_next_->SetTranslationY(screen_height_ - texture_height);
		text_go_to_next_->SetVertexColor(255, 255, 255, static_cast<int>(255 * Easing::SineOut(screen_animation_time_)));
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/