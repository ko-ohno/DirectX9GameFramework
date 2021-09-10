/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Fade.cpp] �Q�[����ʂ�Fade�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[����ʂ�Fade�̋������`�����N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "Fade.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../../Game.h"

#include "../../../Input/InputCheck.h"

#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Fade::Fade(class Game* game)
	: UI(game)
	, fade_(nullptr)
	, fade_state_(FadeState::None)
	, is_execute_fade_(false)
	, is_fade_completed(false)
	, fade_alpha_(0.f)
	, execute_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Fade::~Fade(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Fade::Init(void)
{
	// �t�F�[�h�p�X�v���C�g�̐���
	fade_ = NEW SpriteRendererComponent(this, 300);
	fade_->SetVertexColor(0, 0, 0);

	// �l�̏�����
	{
		fade_state_		= FadeState::Idle;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Fade::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void Fade::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Fade::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const float screen_width  = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	// �t�F�[�h�̉�ʃT�C�Y�̐ݒ�
	fade_->SetScaleX(screen_width);
	fade_->SetScaleY(screen_height);
	
	// �t�F�[�h�̊J�n���߂𔭍s
	if (InputCheck::KeyTrigger(DIK_P))
	{
		is_execute_fade_ = true;
		is_fade_completed = false;
		execute_time_ = 0.f;
	}

	// �t�F�[�h�̍ő���s���Ԃɓ��B������
	if (execute_time_ >= (MAX_EXECUTE_TIME_ - 0.01f))
	{
		fade_state_ = FadeState::Idle;	// �X�e�[�g��ҋ@��Ԃֈڍs
		is_execute_fade_ = false;		// �t�F�[�h�̎��s��Ԃ��I��
		is_fade_completed = true;		// �t�F�[�h����
	}

	// ���ۂ̋������`
	switch (fade_state_)
	{
	case FadeState::Idle:
		if (is_execute_fade_ == true)	// �t�F�[�h�����s���邩?
		{
			// �t�F�[�h�̃X�e�[�g�X�V����
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
		assert(!"Fade::UpdateGameObject():�t�F�[�h���s���ȏ�Ԃł��I");
		break;
	}

	// �t�F�[�h�̃A���t�@�l��ݒ�
	fade_->SetVertexColor(0, 0, 0, static_cast<int>(fade_alpha_));
}

/*-----------------------------------------------------------------------------
/* �t�F�[�h��Ԃ̍X�V����
-----------------------------------------------------------------------------*/
void Fade::UpdateFadeState(void)
{
	// �t�F�[�h�C�����邩�H
	const bool is_fadein = (fade_alpha_ >= (MAX_FADE_ALPHA_VALUE_ - 0.01f));
	if (is_fadein)
	{
		fade_state_ = FadeState::FadeIn;
		return;
	}

	// �t�F�[�h�A�E�g���邩�H
	const bool is_fadeout = (fade_alpha_ <= 0.1f);
	if (is_fadeout)
	{
	 	fade_state_ = FadeState::FadeOut;
		return;
	}
}

/*-----------------------------------------------------------------------------
/* ��ʂ��Â��t�F�[�h�A�E�g
-----------------------------------------------------------------------------*/
void Fade::FadeOut(float deltaTime)
{
	if (execute_time_ >= MAX_EXECUTE_TIME_) { return; }

	// ���s���Ԃ։��Z����
	execute_time_ += deltaTime;

	// 255 * 1.f �̔{���̊|���Z������
	const float scale = Easing::SineOut(execute_time_);
	fade_alpha_ = MAX_FADE_ALPHA_VALUE_ * scale;
}

/*-----------------------------------------------------------------------------
/* ��ʂ𖾂邭�t�F�[�h�C��
-----------------------------------------------------------------------------*/
void Fade::FadeIn(float deltaTime)
{
	if (execute_time_ >= MAX_EXECUTE_TIME_) { return; }

	// ���s���Ԃ։��Z����
	execute_time_ += deltaTime;

	// 255 ���猸�Z����l�� 255 * 1.f �̔{���̊|���Z�̌��ʂ��狁�߂�
	const float scale = Easing::SineOut(execute_time_);
	fade_alpha_ = MAX_FADE_ALPHA_VALUE_ - (MAX_FADE_ALPHA_VALUE_ * scale);
}

/*=============================================================================
/*		End of File
=============================================================================*/