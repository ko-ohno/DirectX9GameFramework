/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Result.cpp] ���U���g��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���U���g��ʂ̋������`�����N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "Result.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/RendererComponent/SpriteDigitRendererComponent.h"
#include "../../Component/AudioComponent.h"
#include "../../../ResourceManager/SaveDataManager.h"
#include "../../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Result::Result(class Game* game)
	: UI(game)
	, result_(nullptr)
	, bg_(nullptr)
	, bgm_result_(nullptr)
	, se_(nullptr)
	, result_state_(ResultMenuState::None)
	, result_state_old_(ResultMenuState::None)
	, screen_width_(0)
	, screen_height_(0)
	, hud_animation_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Result::~Result(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Result::Init(void)
{
	// ��Ԃ�������
	result_state_old_ = result_state_ = ResultMenuState::Wait;

	// �Z�[�u�f�[�^�}�l�[�W���ւ̃|�C���^���擾
	auto save_data_manager = game_->GetSaveDataManager();

	// �Z�[�u�f�[�^�̃��X�g�̎擾
	auto save_data_list = save_data_manager->GetSaveDataList();

	// �����̗]���ȃZ�[�u�f�[�^�̍폜
	if (save_data_list.size() >= MAX_SCORE_DATA +1)
	{
		save_data_manager->RemoveSaveData(save_data_list.back());
	}

	// ���U���g��ʂ̃f�[�^���쐬
	{
		// �����̕\��
		go_next_ = NEW SpriteRendererComponent(this);
		go_next_->SetTexture(TextureType::GoNext);

		// �^�C�g���̕\��
		result_ = NEW SpriteRendererComponent(this);
		result_->SetTexture(TextureType::Result);
		result_->IsSetDrawingPositionToCenter(true);

		// �w�i�̕\��
		bg_ = NEW SpriteRendererComponent(this, 150);
		bg_->SetTexture(TextureType::ScreenBG); 

		// �X�R�A�\���p�f�[�^�̐���
		for (int i = 0; i < MAX_SCORE_DATA; i++)
		{
			ranking_bg_[i] = nullptr;
			ranking_double_point_[i] = nullptr;
			ranking_new_[i] = nullptr;
			ranking_num_[i] = nullptr;
			ranking_score_digit_[i] = nullptr;

			// �w�i�̐���
			ranking_bg_[i] = NEW SpriteRendererComponent(this);
			ranking_bg_[i]->SetTexture(TextureType::Blank);
			ranking_bg_[i]->SetVertexColor(0, 255, 255, 128);
			ranking_bg_[i]->IsSetDrawingPositionToCenter(true);

			// �_�u���R�����̃X�v���C�g����
			ranking_double_point_[i] = NEW SpriteRendererComponent(this);
			ranking_double_point_[i]->SetTexture(TextureType::ScoreDoublePoint);
			ranking_double_point_[i]->IsSetDrawingPositionToCenter(true);

			// NEW�̃X�v���C�g����(�V�����_���f�[�^���̖���)
			ranking_new_[i] = NEW SpriteRendererComponent(this, 250);
			ranking_new_[i]->SetTexture(TextureType::New);
			ranking_new_[i]->SetVertexColor(230, 180, 34);		// ���F��
			ranking_new_[i]->IsSetDrawingPositionToCenter(true);

			// �����L���O�̏���
			ranking_num_[i] = NEW SpriteDigitRendererComponent(this);
			ranking_num_[i]->SetTexture(TextureType::ScoreFontOrigin_0);
			ranking_num_[i]->IsSetDrawingPositionToCenter(true);
			ranking_num_[i]->SetDrawableDigitLength(1);
			ranking_num_[i]->SetIntData(i + 1);

			switch (i)
			{
			case 0:
				ranking_num_[i]->SetVertexColor(230, 180, 34);	// ���F��
				break;

			case 1:
				ranking_num_[i]->SetVertexColor(212, 212, 212); // ��F��
				break;

			case 2:
				ranking_num_[i]->SetVertexColor(179,  140, 93);	// ���F��
				break;

			default:
				break;
			}

			ranking_score_digit_[i] = NEW SpriteDigitRendererComponent(this);
			ranking_score_digit_[i]->SetTexture(TextureType::ScoreFontOrigin_0);
			ranking_score_digit_[i]->IsSetDrawingPositionToCenter(true);
			ranking_score_digit_[i]->SetDrawableDigitLength(3);
			ranking_score_digit_[i]->SetOffestWidth(30);

			// �_���̐ݒ�
			ranking_score_digit_[i]->SetIntData(save_data_list.at(i)->GetScore());
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Result::Uninit(void)
{
	// BGM�̒�~
	{
		bgm_result_->Stop();
	}

	// �Z�[�u�f�[�^�̏�Ԃ��X�V
	{
		auto save_data_list = game_->GetSaveDataManager()->GetSaveDataList();
		for (auto save_data : save_data_list)
		{
			// �V�����f�[�^�Ƃ��Ă̌o�����폜
			save_data->IsSetNewData(false);
		}
	}
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void Result::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Result::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �����f�[�^�̐���
	{
		// BGM�̐���
		if (bgm_result_ == nullptr)
		{
			bgm_result_ = NEW AudioComponent(this);
			bgm_result_->SetSound(SoundType::Kemono);
			bgm_result_->PlayLoop();
		}
		
		// SE�̐���
		if (se_ == nullptr)
		{
			se_ = NEW AudioComponent(this);
			se_->SetSound(SoundType::SelectSound);
		}
	}

	// ��ʃT�C�Y�̎擾
	screen_width_  = game_->GetGraphics()->GetScreenSize().x_;
	screen_height_ = game_->GetGraphics()->GetScreenSize().y_;

	// ���j���[�̍X�V
	this->UpdateMenu(deltaTime);

	// �\��̃X�v���C�g�̍X�V
	this->UpdateResultSprite(deltaTime);

	// �w�i�̍X�V
	this->UpdateBackground(deltaTime);

	// �����L���O�f�[�^�̍X�V
	this->UpdateRankingData(deltaTime);

	// ���͂��ꂽ���1�t���[���O�ƈ������
	if (result_state_ != result_state_old_)
	{
		se_->Play();
	}

	// 1�t���[���O�̏����X�V
	result_state_old_ = result_state_;
}

/*-----------------------------------------------------------------------------
/* ���j���[�̍X�V����
-----------------------------------------------------------------------------*/
void Result::UpdateMenu(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �e�N�X�`���̃T�C�Y���擾
	float texture_width  = static_cast<float>(go_next_->GetTextureImageInfo()->Width);
	float texture_height = static_cast<float>(go_next_->GetTextureImageInfo()->Height);

	// �|���S���̃T�C�Y���X�V
	go_next_->SetScaleX(texture_width);
	go_next_->SetScaleY(texture_height);

	// �`����W�̍X�V
	go_next_->SetTranslationX(screen_width_ - texture_width);
	go_next_->SetTranslationY(screen_height_ - texture_height);

}

/*-----------------------------------------------------------------------------
/* ���U���g�̕\��̍X�V����
-----------------------------------------------------------------------------*/
void Result::UpdateResultSprite(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ��ʂ̊g�k�l�̎擾
	float screen_scaler = game_->GetGraphics()->GetScreenScaler();

	// �e�N�X�`���̃T�C�Y���擾
	float texture_width  = static_cast<float>(result_->GetTextureImageInfo()->Width);
	float texture_height = static_cast<float>(result_->GetTextureImageInfo()->Height);

	// �|���S���̃T�C�Y���X�V
	result_->SetScaleX(texture_width * screen_scaler);
	result_->SetScaleY(texture_height * screen_scaler);

	// �`����W�̍X�V
	result_->SetTranslationX(screen_width_ / 2.f);
	result_->SetTranslationY(screen_height_ / 8.f);
}

/*-----------------------------------------------------------------------------
/* �w�i�̍X�V����
-----------------------------------------------------------------------------*/
void Result::UpdateBackground(float deltaTime)
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
/* �����L���O�̍X�V����
-----------------------------------------------------------------------------*/
void Result::UpdateRankingData(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ��ʂ̊g�k�l�̎擾
	float screen_scaler = game_->GetGraphics()->GetScreenScaler();

	// �Z�[�u�f�[�^�̃��X�g���擾
	auto save_data_list = game_->GetSaveDataManager()->GetSaveDataList();

	// �e�N�X�`���̃T�C�Y���擾
	float digit_texture_width  = static_cast<float>(ranking_score_digit_[0]->GetFontWidth());
	float digit_texture_height = static_cast<float>(ranking_score_digit_[0]->GetFontHeight());

	for (int i = 0; i < MAX_SCORE_DATA; i++)
	{
		// �����L���O�̔w�i���X�V
		{
			ranking_bg_[i]->SetScaleX((screen_width_ / 2.f));
			ranking_bg_[i]->SetScaleY((digit_texture_height));

			ranking_bg_[i]->SetTranslationX(screen_width_ / 2.f);
			ranking_bg_[i]->SetTranslationY((screen_height_ / 4.f) + ((digit_texture_height * 1.5f) * i));
		}
	
		// �����L���O�̏��ʂ��X�V
		{
			ranking_num_[i]->SetScaleX(screen_scaler);
			ranking_num_[i]->SetScaleY(screen_scaler);

			ranking_num_[i]->SetTranslationX(screen_width_ / 3.5f);
			ranking_num_[i]->SetTranslationY((screen_height_ / 4.f) + ((digit_texture_height * 1.5f) * i));

			// �E�B���h�E�T�C�Y�ɍ��킹�Ċg�k
			ranking_double_point_[i]->SetScaleX((digit_texture_width  * 1.5f) * screen_scaler);
			ranking_double_point_[i]->SetScaleY((digit_texture_height * 1.5f) * screen_scaler);

			ranking_double_point_[i]->SetTranslationX(ranking_num_[i]->GetPosition()->x + digit_texture_width);
			ranking_double_point_[i]->SetTranslationY(ranking_num_[i]->GetPosition()->y);
		}

		// �����L���O�̐V�����f�[�^����\������
		{
			if (save_data_list.at(i)->IsGetNewData())
			{
				ranking_new_[i]->IsSetDrawable(true);
			}
			else
			{
				ranking_new_[i]->IsSetDrawable(false);
			}

			float new_texture_width = static_cast<float>(ranking_new_[0]->GetTextureImageInfo()->Width);
			float new_texture_height = static_cast<float>(ranking_new_[0]->GetTextureImageInfo()->Height);


			// HUD�A�j���[�V�����̎��Ԃ��v�Z
			hud_animation_time_ += deltaTime;
			if (hud_animation_time_ >= MAX_HUD_ANIMATION_TIME_)
			{
				hud_animation_time_ = 0.f;
			}

			// hud�̃J���[�A�j���[�V����(���F������F�ւ�)
			int red		= static_cast<int>(Math::Lerp(255, 230, hud_animation_time_));
			int green	= static_cast<int>(Math::Lerp(255, 180, hud_animation_time_));
			int blue	= static_cast<int>(Math::Lerp(255,  34, hud_animation_time_));

			// �F�̍X�V
			ranking_new_[i]->SetVertexColor(red, green, blue);

			// �|���S���̑傫�����e�N�X�`���T�C�Y��
			ranking_new_[i]->SetScaleX((new_texture_width * 2.f) * screen_scaler);
			ranking_new_[i]->SetScaleY((new_texture_height * 2.f) * screen_scaler);

			ranking_new_[i]->SetTranslationX(screen_width_ * 0.65f);
			ranking_new_[i]->SetTranslationY((screen_height_ / 4.f) + ((digit_texture_height * 1.5f) * i));
		}

		// �����L���O�̃X�R�A���X�V
		{
			auto digit_width = ranking_score_digit_[0]->GetMaxDrawableDigitWidth();

			ranking_score_digit_[i]->SetScaleX(screen_scaler);
			ranking_score_digit_[i]->SetScaleY(screen_scaler);

			ranking_score_digit_[i]->SetTranslationX((screen_width_ / 2.f)  - (((digit_width / 3.f) * 2.f)));
			ranking_score_digit_[i]->SetTranslationY((screen_height_ / 4.f) + (((digit_texture_height * 1.5f)))  * i);
		}
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/