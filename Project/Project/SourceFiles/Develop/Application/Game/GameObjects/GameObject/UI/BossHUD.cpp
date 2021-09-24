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
#include "../../../SandBoxManager/EnemieManager.h"

// �`��R���|�[�l���g
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/RendererComponent/BillboardRendererComponent.h"

// �����R���|�[�l���g
#include "../../Component/AudioComponent.h"

#include "../../../../ImGui/ImGuiManager.h"


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
	, is_execute_alert_(false)
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
	this->Uninit();
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

		health_bar_blank_ = NEW SpriteRendererComponent(this, 230);
		health_bar_blank_->SetTexture(TextureType::Blank);
		health_bar_blank_->SetVertexColor(0, 0, 0, 255); // ��

		health_bar_bg_ = NEW SpriteRendererComponent(this);
		health_bar_bg_->SetTexture(TextureType::Blank);
		health_bar_bg_->SetVertexColor(255, 128, 128, 128); // �ԐF
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
		alert_exclamation_->IsSetDrawable(false);

		// �w�i
		alert_bg_ = NEW BillboardRendererComponent(this);
		alert_bg_->SetTexture(TextureType::Blank);
		alert_bg_->IsSetDrawable(false);
	}

	// �����R���|�[�l���g�̐���
	{
		alert_se_ = NEW AudioComponent(this);
		alert_se_->SetSound(SoundType::DangerAlert);
	}
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
	// �Q�[���}�l�[�W����T��
	if (game_manager_ == nullptr)
	{
		game_manager_ = this->FindGameObject(TypeID::GameManager);
	}

	// �{�X�ւ̃|�C���^�擾
	if (boss_ == nullptr)
	{
		auto enemy_list = game_->GetEnemieManager()->GetEnemyGameObjectList();
		for(auto enemy : enemy_list)
		{
			auto enemy_type = enemy->GetType();
			if (enemy_type == GameObject::TypeID::Boss)
			{
				boss_ = enemy;
			}
		}
	}

	// HUD�̒l���X�V
	this->UpdateHUDValue(deltaTime);

	// �̗̓o�[�̍X�V
	this->UpdateHealthBarHUD(deltaTime);

	// �{�X�̏�Ԃ��擾
	if (boss_ != nullptr)
	{
		boss_state_ = boss_->GetEnemyState();
	}

	// �A���[�g�̃X�e�[�g�̍X�V
	{
		if (boss_state_ != boss_state_old_)
		{
			is_execute_alert_ = true;
		}

		if (is_execute_alert_)
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

	// 1�t���[���O�̏����X�V
	boss_state_old_ = boss_state_;
}

/*-----------------------------------------------------------------------------
/* HUD�̒l�̍X�V����
-----------------------------------------------------------------------------*/
void BossHUD::UpdateHUDValue(float deltaTime)
{
	auto a = boss_->GetHitPoint();

	//hp_rate_ = (1.f / 100.f) * a;

	ImGui::Begin("hp_rate");
	ImGui::SliderFloat("##hp_rate", &hp_rate_, 0.f, 1.f);
	ImGui::End();

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

		health_bar_->IsSetDrawingPositionToCenter(true);
		health_bar_->SetScaleX(width);
		health_bar_->SetScaleY(height);

		health_bar_->SetTranslationX((screen_width * 0.5f) - (width * 0.5f));
		health_bar_->SetTranslationY(offset_padding);
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
		// �A���[�g�����s���Ȃ���Ԃ�
		is_execute_alert_ = false;

		// �A���[�g���~
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
	alert_exclamation_->IsSetDrawable(false);

	// �w�i�̐ݒ�
	alert_bg_->IsSetDrawable(false);
	alert_bg_->SetScaleX(2.f);
	alert_bg_->SetScaleY(2.f);
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
		// �A���[�g�����s���Ȃ���Ԃ�
		is_execute_alert_ = false;

		// �A���[�g���~
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
	alert_bg_->SetScaleY(3.f);
	alert_bg_->SetVertexColor(255, alert_color, alert_color, 128);
}

/*=============================================================================
/*		End of File
=============================================================================*/