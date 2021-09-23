/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossHUD.cpp] �{�X��HUD�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X��HUD�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "BossHUD.h"
#include "../../../Game.h"
#include "../../../../DX9Graphics.h"
#include "../SandBox/Actor/Enemy.h"

// �`��R���|�[�l���g
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/RendererComponent/BillboardRendererComponent.h"

// �����R���|�[�l���g
#include "../../Component/AudioComponent.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BossHUD::BossHUD(Game* game)
	: UI(game)
	, game_manager_(nullptr)
	, boss_(nullptr)
	, boss_state_(EnemyState::None)
	, health_bar_(nullptr)
	, health_bar_blank_(nullptr)
	, health_bar_bg_(nullptr)
	, hp_value_(0.f)
	, max_hp_value_(0.f)
	, hp_rate_(0.f)
	, weak_point_(nullptr)
	, is_alert_(false)
	, alert_execute_time_(0.f)
	, alert_time_(0.f)
	, alert_exclamation_(nullptr)
	, alert_bg_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
BossHUD::~BossHUD(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool BossHUD::Init(void)
{
	// �l�̏�����
	{
		hp_value_		= 100;
		max_hp_value_	= 100;
		hp_rate_ = 1.f;
	}

	// �̗͂̕\��
	{
		health_bar_ = NEW SpriteRendererComponent(this, 240);
		health_bar_->SetTexture(TextureType::Blank);
		health_bar_->SetVertexColor(0, 255, 0, 255); // ��
		health_bar_->IsSetDrawingPositionToCenter(true);

		health_bar_blank_ = NEW SpriteRendererComponent(this, 230);
		health_bar_blank_->SetTexture(TextureType::Blank);
		health_bar_blank_->SetVertexColor(0, 0, 0, 255); // ��
		health_bar_blank_->IsSetDrawingPositionToCenter(true);

		health_bar_bg_ = NEW SpriteRendererComponent(this);
		health_bar_bg_->SetTexture(TextureType::Blank);
		health_bar_bg_->SetVertexColor(255, 128, 128, 128); // �ԐF
		health_bar_bg_->IsSetDrawingPositionToCenter(true);
	}

	// ��_�̕\��
	{
		weak_point_ = NEW BillboardRendererComponent(this);
		weak_point_->SetTexture(TextureType::WeakPoint);
		weak_point_->SetScale(2.f);
		weak_point_->IsSetDrawable(false);
	}

	// �A���[�g�p�R���|�[�l���g�̐���
	{
		// �r�b�N���}�[�N
		alert_exclamation_ = NEW BillboardRendererComponent(this);
		alert_exclamation_->SetTexture(TextureType::Exclamation);
		alert_exclamation_->SetScale(2.f);

		// �w�i
		alert_bg_ = NEW BillboardRendererComponent(this);
		alert_bg_->SetTexture(TextureType::Blank);
	}

	// �����R���|�[�l���g�̐���
	{
		alert_se_ = NEW AudioComponent(this);
		alert_se_->SetSound(SoundType::DangerAlert);
	}

	boss_state_ = EnemyState::BodyPress;

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void BossHUD::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void BossHUD::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void BossHUD::UpdateGameObject(float deltaTime)
{
	// �̗̓o�[�̍X�V
	this->UpdateHealthBarHUD(deltaTime);

	// �A���[�g�̃X�e�[�g
	{
		switch (boss_state_)
		{
		case EnemyState::Idle:
			break;
		
		case EnemyState::BodyPress:
			// �����U���A���[�g�̍X�V
			this->UpdateHorizontalAlertHUD(deltaTime);
			break;
	
		case EnemyState::Shooting:
			// �ˌ��U���A���[�g�̍X�V
			this->UpdateAlertShootHUD(deltaTime);
			break;
	
		case EnemyState::LaserCannon:
			// �����U���A���[�g�̍X�V
			this->UpdateHorizontalAlertHUD(deltaTime);
			break;
	
		default:
			break;
		}
	} 
}

/*-----------------------------------------------------------------------------
/* �̗̓Q�[�W�̍X�V����
-----------------------------------------------------------------------------*/
void BossHUD::UpdateHealthBarHUD(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const float screen_width = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	const float offset_padding = 15.f;
	const float offset_padding_bg = 10.f;

	//�@�̗̓Q�[�W�̖{��
	{
		const float warning_value = (1.f / 3.f) * 2.f;
		const float danger_value = (1.f / 3.f);

		if (hp_rate_ >= warning_value)
		{
			health_bar_->SetVertexColor(0, 255, 0);
		}

		if (hp_rate_ <= warning_value)
		{
			health_bar_->SetVertexColor(255, 255, 0);
		}

		if (hp_rate_ <= danger_value)
		{
			health_bar_->SetVertexColor(255, 0, 0);
		}

		const float width = 500.f * hp_rate_;
		const float height = 60.f;

		//const float health_bar_width = health_bar_->GetScale()->x;
		const float health_bar_height = health_bar_->GetScale()->y;

		health_bar_->SetScaleX(width);
		health_bar_->SetScaleY(height);

		health_bar_->SetTranslationX(screen_width * 0.5f);
		health_bar_->SetTranslationY((health_bar_height * 0.5f) + offset_padding);
	}

	//�@�̗̓Q�[�W�̋󔒕���
	{
		const float width = 500.f;
		const float height = 60.f;

		//const float health_bar_width = health_bar_blank_->GetScale()->x;
		const float health_bar_height = health_bar_blank_->GetScale()->y;

		health_bar_blank_->SetScaleX(width);
		health_bar_blank_->SetScaleY(height);

		health_bar_blank_->SetTranslationX(screen_width * 0.5f);
		health_bar_blank_->SetTranslationY((health_bar_height * 0.5f) + offset_padding);
	}

	//�@�̗̓Q�[�W�̔w�i
	{
		const float width = 510.f;
		const float height = 70.f;

		//const float health_bar_width = health_bar_bg_->GetScale()->x;
		const float health_bar_height = health_bar_bg_->GetScale()->y;

		health_bar_bg_->SetScaleX(width);
		health_bar_bg_->SetScaleY(height);

		health_bar_bg_->SetTranslationX(screen_width * 0.5f);
		health_bar_bg_->SetTranslationY((health_bar_height * 0.5f) + offset_padding_bg);
	}
}

/*-----------------------------------------------------------------------------
/* �ˌ��̃A���[�gHUD�̍X�V����
-----------------------------------------------------------------------------*/
void BossHUD::UpdateAlertShootHUD(float deltaTime)
{
	// �A���[�g�����邩�H
	if (is_alert_ == false)
	{
		// �����̍Đ�
		alert_se_->Play();
		is_alert_ = true;
	}

	// �A���[�g�̑S�̂̎��s���Ԃ̌v�Z
	alert_execute_time_ += deltaTime;

	if (alert_execute_time_ >= MAX_ALERT_TIME)
	{
		boss_state_ = EnemyState::Idle;
		alert_execute_time_ = 0.f;
		is_alert_ = false;
	}

	// �_�ł̎��̐F
	int alert_color = 0;

	// �w�i��_�ł�����
	{	
		// �A���[�g�̋Ǐ��̎��s���Ԃ̌v�Z
		alert_time_ += (deltaTime * 2.f);
		{
			alert_color = static_cast<int>(Math::Lerp(255.f, 128.f, alert_time_));
			if (alert_time_ >= 1.f)
			{
				alert_time_ = 0.f;
			}
		}
	}

	// �r�b�N���}�[�N�̐ݒ�
	alert_exclamation_->IsSetDrawable(is_alert_);

	// �w�i�̐ݒ�
	alert_bg_->IsSetDrawable(is_alert_);
	alert_bg_->SetScaleX(12.f);
	alert_bg_->SetScaleY(8.f);
	alert_bg_->SetVertexColor(255, alert_color, alert_color, 128);
}

/*-----------------------------------------------------------------------------
/* ���僌�[�U�[�Ƒ̓�����U���̃A���[�gHUD�̍X�V����
-----------------------------------------------------------------------------*/
void BossHUD::UpdateHorizontalAlertHUD(float deltaTime)
{
	// �A���[�g�����邩�H
	if (is_alert_ == false)
	{
		// �����̍Đ�
		alert_se_->Play();
		is_alert_ = true;
	}

	// �A���[�g�̑S�̂̎��s���Ԃ̌v�Z
	alert_execute_time_ += deltaTime;

	if (alert_execute_time_ >= MAX_ALERT_TIME)
	{
		boss_state_ = EnemyState::Idle;
		alert_execute_time_ = 0.f;
		is_alert_ = false;
	}

	// �_�ł̎��̐F
	int alert_color = 0;

	// �w�i��_�ł�����
	{
		// �A���[�g�̋Ǐ��̎��s���Ԃ̌v�Z
		alert_time_ += (deltaTime * 2.f);
		{
			alert_color = static_cast<int>(Math::Lerp(255.f, 128.f, alert_time_));
			if (alert_time_ >= 1.f)
			{
				alert_time_ = 0.f;
			}
		}
	}

	// �r�b�N���}�[�N�̐ݒ�
	alert_exclamation_->IsSetDrawable(is_alert_);

	// �w�i�̐ݒ�
	alert_bg_->IsSetDrawable(is_alert_);
	alert_bg_->SetScaleX(12.f);
	alert_bg_->SetScaleY(2.f);
	alert_bg_->SetVertexColor(255, alert_color, alert_color, 128);
}

/*=============================================================================
/*		End of File
=============================================================================*/