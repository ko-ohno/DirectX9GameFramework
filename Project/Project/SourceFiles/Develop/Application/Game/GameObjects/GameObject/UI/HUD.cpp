/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[HUD.cpp] �Q�[����ʂ�HUD�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[����ʂ�HUD�̋������`�����N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "HUD.h"
#include "../../../Game.h"
#include "../../../../DX9Graphics.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/RendererComponent/SpriteDigitRendererComponent.h"

#include "../../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
HUD::HUD(class Game* game)
	: UI(game)
	, game_manager_(nullptr)
	, health_bar_(nullptr)
	, health_bar_blank_(nullptr)
	, health_bar_bg_(nullptr)
	, hp_value_(0)
	, max_hp_value_(0)
	, hp_rate_(0.f)
	, meter_center_bg_(nullptr)
	, meter_left_bg_(nullptr)
	, meter_right_bg_(nullptr)
	, distance_value_(0)
	, score_digit_(nullptr)
	, score_value_(0)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
HUD::~HUD(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool HUD::Init(void)
{
	// �l�̏�����
	{
		distance_value_ = 0;
		score_value_	= 0;
	}

	//float screen_width  = game_->GetGraphics()->GetScreenSize().x_;
	//float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	// �R���|�[�l���g�̃C���X�^���X�𐶐�
	{
		// �̗͂̕\��
		{
			health_bar_ = NEW SpriteRendererComponent(this, 240);
			health_bar_->SetTexture(TextureType::Blank);
			health_bar_->SetVertexColor(0, 255, 0, 255); // ��

			health_bar_blank_ = NEW SpriteRendererComponent(this, 230);
			health_bar_blank_->SetTexture(TextureType::Blank);
			health_bar_blank_->SetVertexColor(0, 0, 0, 255); // ��

			health_bar_bg_ = NEW SpriteRendererComponent(this);
			health_bar_bg_->SetTexture(TextureType::Blank);
			health_bar_bg_->SetVertexColor(0, 255, 255, 128); // ���F
		}

		// �S�[���܂ł̋�����\��
		{
			// �w�i
			{
				// ����
				meter_center_bg_ = NEW SpriteRendererComponent(this);
				meter_center_bg_->SetTexture(TextureType::Blank);
				meter_center_bg_->SetVertexColor(0, 255, 255, 240); // ���F
				meter_center_bg_->IsSetDrawingPositionToCenter(true);
		
				// ��
				meter_left_bg_ = NEW SpriteRendererComponent(this);
				meter_left_bg_->SetTexture(TextureType::Blank);
				meter_left_bg_->SetVertexColor(0, 255, 255, 128); // ���F
				meter_left_bg_->IsSetDrawingPositionToCenter(true);

				// �E
				meter_right_bg_	= NEW SpriteRendererComponent(this);
				meter_right_bg_->SetTexture(TextureType::Blank);
				meter_right_bg_->SetVertexColor(0, 255, 255, 128); // ���F
				meter_right_bg_->IsSetDrawingPositionToCenter(true);
			}

			// ������
			distance_digit_ = NEW SpriteDigitRendererComponent(this);
			distance_digit_->SetTexture(TextureType::ScoreFontOrigin_0);
			distance_digit_->SetDrawableDigitLength(2);
			distance_digit_->SetVertexColor(255, 255, 0);
		}

		// �X�R�A�̂̕\��
		{
			// ������
			score_digit_ = NEW SpriteDigitRendererComponent(this);
			score_digit_->SetTexture(TextureType::ScoreFontOrigin_0);
			score_digit_->SetDrawableDigitLength(3);
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void HUD::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void HUD::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void HUD::UpdateGameObject(float deltaTime)
{
	// �Q�[���}�l�[�W����T��
	if (game_manager_ == nullptr)
	{
		game_manager_ = this->FindGameObject(TypeID::GameManager);
	}

	// �̗̓Q�[�W�ɑ΂��銄�����v�Z
	hp_rate_ = (1.f / max_hp_value_) * hp_value_;

	// HUD�̒l���X�V
	this->UpdateHUDValue(deltaTime);

	// �̗̓Q�[�WHUD
	this->UpdateHealthBarHUD(deltaTime);

	// �S�[���܂ł̃��[�^�[HUD
	this->UpdateGoalMeterHUD(deltaTime);

	// �X�R�AHUD
	this->UpdateScoreHUD(deltaTime);
}

/*-----------------------------------------------------------------------------
/* HUD�̒l�̍X�V����
-----------------------------------------------------------------------------*/
void HUD::UpdateHUDValue(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (game_manager_ == nullptr) { return; }

	// �l�̍X�V
	auto parameter_compnents = game_manager_->GetParameterComponents();
	for (auto parameter_compnent : parameter_compnents)
	{
		// �l�R���|�[�l���g�̌^�𒲂ׂ�
		auto parameter_type = parameter_compnent->GetParameterType();

		// �v���C���[�̍ő�HP�̎擾
		if (parameter_type == ParameterType::MaxHP)
		{
			max_hp_value_ = parameter_compnent->GetInt();
		}

		// �v���C���[��HP�̎擾
		if (parameter_type == ParameterType::HP)
		{
			hp_value_ = parameter_compnent->GetInt();
		}

		// �Q�[���̐i�s�x
		if (parameter_type == ParameterType::GameProgress)
		{
			distance_value_ = parameter_compnent->GetInt();
		}

		// �X�R�A�̒l
		if (parameter_type == ParameterType::Score)
		{
			score_value_ = parameter_compnent->GetInt();
		}
	}
}

/*-----------------------------------------------------------------------------
/* �̗̓Q�[�W�̍X�V����
-----------------------------------------------------------------------------*/
void HUD::UpdateHealthBarHUD(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const float screen_width = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	const float offset_padding = 15.f;
	const float offset_padding_bg = 10.f;

	//�@�̗̓Q�[�W�̖{��
	{
		const float warning_value	= (1.f / 3.f) * 2.f;
		const float danger_value	= (1.f / 3.f);

		if (hp_rate_ >= warning_value)
		{
			health_bar_->SetVertexColor(  0, 255, 0);
		}

		if (hp_rate_ <= warning_value)
		{
			health_bar_->SetVertexColor(255, 255, 0);
		}

		if (hp_rate_ <= danger_value)
		{
			health_bar_->SetVertexColor(255,   0, 0);
		}

		const float width = 500.f * hp_rate_;
		const float height = 60.f;

		//const float health_bar_width = health_bar_->GetScale()->x;
		const float health_bar_height = health_bar_->GetScale()->y;

		health_bar_->SetScaleX(width);
		health_bar_->SetScaleY(height);

		health_bar_->SetTranslationX(offset_padding);
		health_bar_->SetTranslationY(screen_height - (health_bar_height + offset_padding));
	}

	//�@�̗̓Q�[�W�̋󔒕���
	{
		const float width = 500.f;
		const float height = 60.f;

		//const float health_bar_width = health_bar_blank_->GetScale()->x;
		const float health_bar_height = health_bar_blank_->GetScale()->y;

		health_bar_blank_->SetScaleX(width);
		health_bar_blank_->SetScaleY(height);

		health_bar_blank_->SetTranslationX(offset_padding);
		health_bar_blank_->SetTranslationY(screen_height - (health_bar_height + offset_padding));
	}

	//�@�̗̓Q�[�W�̔w�i
	{
		const float width = 510.f;
		const float height = 70.f;

		//const float health_bar_width = health_bar_bg_->GetScale()->x;
		const float health_bar_height = health_bar_bg_->GetScale()->y;

		health_bar_bg_->SetScaleX(width);
		health_bar_bg_->SetScaleY(height);

		health_bar_bg_->SetTranslationX(offset_padding_bg);
		health_bar_bg_->SetTranslationY(screen_height - (health_bar_height + offset_padding_bg));
	}
}

/*-----------------------------------------------------------------------------
/* �S�[���܂ł̋����̍X�V����
-----------------------------------------------------------------------------*/
void HUD::UpdateGoalMeterHUD(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ��ʃT�C�Y�̎擾
	const float screen_width = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	// �w�i�̐ݒ�
	{
		// ����
		{
			// �|���S���̕��ƍ���
			const float polygon_width = meter_center_bg_->GetScale()->x;
			const float polygon_height = meter_center_bg_->GetScale()->y;

			// �`����W
			const float draw_pos_x = (screen_width / 2.f);
			const float draw_pos_y = (screen_height - (polygon_height / 2.f));

			meter_center_bg_->SetScaleX(220.f);
			meter_center_bg_->SetScaleY(120.f);
			meter_center_bg_->SetTranslation(draw_pos_x, draw_pos_y);
		}
	
		// ��
		{
			// �|���S���̕��ƍ���
			const float polygon_width = meter_left_bg_->GetScale()->x;
			const float polygon_height = meter_left_bg_->GetScale()->y;

			// �`����W
			const float draw_pos_x = (screen_width / 2.f) - polygon_width;
			const float draw_pos_y = (screen_height - (polygon_height / 4.f));

			meter_left_bg_->SetScaleX(120.f);
			meter_left_bg_->SetScaleY(150.f);
			meter_left_bg_->SetRotate(45.f);
			meter_left_bg_->SetTranslationX(draw_pos_x);
			meter_left_bg_->SetTranslationY(draw_pos_y);

		}
	
		// �E
		{
			// �|���S���̕��ƍ���
			const float polygon_width = meter_right_bg_->GetScale()->x;
			const float polygon_height = meter_right_bg_->GetScale()->y;

			// �`����W
			const float draw_pos_x = (screen_width / 2.f) + polygon_width;
			const float draw_pos_y = (screen_height - (polygon_height / 4.f));

			meter_right_bg_->SetScaleX(120.f);
			meter_right_bg_->SetScaleY(150.f);
			meter_right_bg_->SetRotate(-45.f);
			meter_right_bg_->SetTranslationX(draw_pos_x);
			meter_right_bg_->SetTranslationY(draw_pos_y);

		}
	}

	// ���l�f�[�^�̐ݒ�
	{
		distance_digit_->SetIntData(static_cast<int>(distance_value_));

		// �`����W
		const float draw_pos_x = (screen_width / 2) - (distance_digit_->GetMaxDrawableDigitWidth()) - 15;
		const float draw_pos_y = (screen_height - distance_digit_->GetFontHeight());

		distance_digit_->SetTranslationX(draw_pos_x);
		distance_digit_->SetTranslationY(draw_pos_y);
	}

}

/*-----------------------------------------------------------------------------
/* �X�R�A�\���̍X�V����
-----------------------------------------------------------------------------*/
void HUD::UpdateScoreHUD(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ��ʃT�C�Y�̎擾
	const float screen_width = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	{
		score_digit_->SetIntData(score_value_);

		const float offset_value = 200;

		// �`����W
		const float draw_pos_x = (screen_width  - distance_digit_->GetMaxDrawableDigitWidth()) - offset_value;
		const float draw_pos_y = (screen_height - distance_digit_->GetFontHeight());

		score_digit_->SetTranslationX(draw_pos_x);
		score_digit_->SetTranslationY(draw_pos_y);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/