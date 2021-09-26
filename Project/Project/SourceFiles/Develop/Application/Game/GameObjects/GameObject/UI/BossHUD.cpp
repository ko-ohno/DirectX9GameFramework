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

// �ړ��R���|�[�l���g
#include "../../Component/MoveComponent/EnemyMoveComponent.h"

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
	, max_hp_value_(0.f)
	, hp_value_(0.f)
	, hp_rate_(0.f)
	, weak_point_hud_(nullptr)
	, hud_animation_time_(0.f)
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
		health_bar_blank_->IsSetDrawingPositionToCenter(true);

		health_bar_bg_ = NEW SpriteRendererComponent(this);
		health_bar_bg_->SetTexture(TextureType::Blank);
		health_bar_bg_->SetVertexColor(255, 128, 128, 128); // �ԐF
		health_bar_bg_->IsSetDrawingPositionToCenter(true);
	}

	// ��_�̕\��
	{
		weak_point_hud_ = NEW BillboardRendererComponent(this);
		weak_point_hud_->SetTexture(TextureType::WeakPoint);
		weak_point_hud_->SetScale(3.f);
		weak_point_hud_->SetTranslationY(-100.f);	// �������W�̏�����
		weak_point_hud_->IsSetDrawable(false);
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

	// �̗̓Q�[�W�ɑ΂��銄�����v�Z
	hp_rate_ = (1.f / max_hp_value_) * hp_value_;

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

	// �{�X�̏�Ԃ��擾
	if (boss_ != nullptr)
	{
		boss_state_			= boss_->GetEnemyState();
		boss_motion_state_	= boss_->GetEnemyMotionState();
	}

	// HUD�̒l���X�V
	this->UpdateHUDValue(deltaTime);

	// �̗̓o�[�̍X�V
	this->UpdateHealthBarHUD(deltaTime);

	// ��_�̕\���̍X�V
	this->UpdateWeakPointHUD(deltaTime);

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
				this->weak_point_hud_->IsSetDrawable(false);
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
	UNREFERENCED_PARAMETER(deltaTime);

	if (game_manager_ == nullptr) { return; }

	// �l�̍X�V
	auto parameter_compnents = game_manager_->GetParameterComponents();
	for (auto parameter_compnent : parameter_compnents)
	{
		// �l�R���|�[�l���g�̌^�𒲂ׂ�
		auto parameter_type = parameter_compnent->GetParameterType();

		// �v���C���[�̍ő�HP�̎擾
		if (parameter_type == ParameterType::BossMaxHP)
		{
			max_hp_value_ = parameter_compnent->GetFloat();
		}

		// �v���C���[��HP�̎擾
		if (parameter_type == ParameterType::BossHP)
		{
			hp_value_ = parameter_compnent->GetFloat();
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

		const float width = 500.f;
		const float height = 60.f;

		// ���ۂ�HP�̕�
		const float true_width = width * hp_rate_;

		//const float health_bar_width = health_bar_->GetScale()->x;
		const float health_bar_height = health_bar_->GetScale()->y;

		health_bar_->SetScaleX(true_width);
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
/* �{�X�̎�_��HUD�̍X�V����
-----------------------------------------------------------------------------*/
void BossHUD::UpdateWeakPointHUD(float deltaTime)
{
	if (boss_ == nullptr) { return; }

	const bool is_weakpoint_ready = ((boss_state_ == EnemyState::LaserCannon) || (boss_state_ == EnemyState::Shooting));
	const bool is_weakpoint_show  = ((boss_motion_state_ == EnemyMotionState::Attack) && is_weakpoint_ready);

	if (is_weakpoint_ready == false)
	{
		weak_point_hud_->SetTranslationY(-100.f);
		hud_animation_time_  = 0.f;
		return;
	}

	// �{�X�̎p�������擾
	D3DXMATRIX boss_matrix = *boss_->GetTransform()->GetWorldMatrix();

	// HUD��\������p�����̍쐬
	D3DXMATRIX weak_point_hud_matrix;
	D3DXMatrixIdentity(&weak_point_hud_matrix);

	// �I�t�Z�b�g���W���AHUD��\������p�����ɍ쐬
	D3DXVECTOR3 offset_hud_position = { 0.f, 0.f, 0.f };

	// ���`��Ԃ�HUD���A�j���[�V����
	offset_hud_position.y = Math::Lerp(-100.f, 0.f, Easing::SineIn(hud_animation_time_));
	{
		weak_point_hud_matrix._41 = offset_hud_position.x;
		weak_point_hud_matrix._42 = offset_hud_position.y;
		weak_point_hud_matrix._43 = offset_hud_position.z;
	}

	// �p�����̌v�Z
	weak_point_hud_matrix = weak_point_hud_matrix * boss_matrix;

	// ���������p�����̍��W���I�t�Z�b�g���W�Ƃ��Đݒ�
	offset_hud_position.x = weak_point_hud_matrix._41;
	offset_hud_position.y = weak_point_hud_matrix._42;
	offset_hud_position.z = weak_point_hud_matrix._43;


	// ��_��\�����邩
	if (is_weakpoint_show)
	{
		//�@�A�j���[�V�����̎��Ԃ��v�Z
		hud_animation_time_ += deltaTime;
		if (hud_animation_time_ >= MAX_HUD_ANIMATION_TIME_)
		{
			hud_animation_time_ = MAX_HUD_ANIMATION_TIME_;
		}

		// HUD�𕽍s�ړ�������
		weak_point_hud_->SetTranslation(offset_hud_position);
		weak_point_hud_->IsSetDrawable(true);
	}
	else
	{
		// �A�j���[�V���������Ȃ�
		hud_animation_time_ = 0.f;
		weak_point_hud_->IsSetDrawable(false);
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

	if (alert_execute_time_ >= MAX_ALERT_TIME_)
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
		const float MAX_COLOR_ANIMATION_TIME = 1.f;

		// �A���[�g�̋Ǐ��̎��s���Ԃ̌v�Z
		alert_time_ += (deltaTime * 2.f);
		{
			alert_color = static_cast<int>(Math::Lerp(255.f, 128.f, alert_time_));
			if (alert_time_ >= MAX_COLOR_ANIMATION_TIME)
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

	if (alert_execute_time_ >= MAX_ALERT_TIME_)
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
		const float MAX_COLOR_ANIMATION_TIME = 1.f;

		// �A���[�g�̋Ǐ��̎��s���Ԃ̌v�Z
		alert_time_ += (deltaTime * 2.f);
		{
			alert_color = static_cast<int>(Math::Lerp(255.f, 128.f, alert_time_));
			if (alert_time_ >= MAX_COLOR_ANIMATION_TIME)
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