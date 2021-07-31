/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBullet.cpp] �`���[�W�e�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�`���[�W�e�̃Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "ChargeBullet.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../Component/ColliderComponent/SphereColliderComponent.h"
#include "../../../../Math.h"
#include "../../../Input/InputCheck.h"
#include "../SandBox/Actor/Enemy.h"
#include "../../../SandBoxManager/EnemieManager.h"
#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ChargeBullet::ChargeBullet(Game* game)
	: SandBox(game)
	, sphere_collider_(nullptr)
	, sphere_collider_gizmo_(nullptr)
	, charge_bullet_state_(ChargeBulletState::None)
	, charge_bullet_state_old_(ChargeBulletState::None)
	, is_fire_(false)
	, is_hit_(false)
	, is_lockon_(false)
	, is_next_state_(false)
	, parent_front_vector_(0.f, 0.f, 1.f)
	, move_speed_(15.f)
	, position_(0.f, 0.f, -100.f)
	, src_position_(0.f, 0.f, 0.f)
	, dst_position_(0.f, 0.f, 0.f)
	, lerp_execute_time_(0.f)
	, kill_timer_(2.f)
	, alive_time_(0.f)
	, state_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ChargeBullet::~ChargeBullet(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool ChargeBullet::Init(void)
{
	// �z��̏�����
	{
		// �G�t�F�N�g�ԍ��̓o�^
		effect_type_[0] = EffectType::ChargeBulletState1Charge;
		effect_type_[1] = EffectType::ChargeBulletState2Hold;
		effect_type_[2] = EffectType::ChargeBulletState4Bullet;
		effect_type_[3] = EffectType::ChargeBulletState5Explosion;

		for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
		{
			effect_[i] = nullptr;
		}
	}

	// �e�ۂ̐���
	{
		for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
		{
			effect_[i] = nullptr;
			effect_[i] = NEW EffectRendererComponent(this);
			effect_[i]->SetEffect(effect_type_[i]);
			effect_[i]->SetScale(0.5f);
			effect_[i]->SetTranslationY(-100.f);
		}
	}

	// �Փ˔���̍쐬
	{
		const float scale = 1.f;

		// ���̏Փ˔���
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);
		sphere_collider_->SetTranslationY(-100.f);

		// �M�Y���̕`��R���|�[�l���g
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
		sphere_collider_gizmo_->SetTranslationY(-100.f);
		//sphere_collider_gizmo_->IsSetDrawable(false);
	}

	// �`���[�W�e�̋N��
	{
		charge_bullet_state_ = ChargeBulletState::Charge;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void ChargeBullet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void ChargeBullet::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateGameObject(float deltaTime)
{
	if ((charge_bullet_state_ == ChargeBulletState::Fire) && (is_fire_ == false))
	{
		// �v���C���[�̑O�x�N�g���ֈړ�����
		if (game_object_parent_ == nullptr)
		{
			assert(!"ChargeBullet::UpdateChargeBullet():���̃Q�[���I�u�W�F�N�g�̏��L�҂��s���ł��I");
		}

		// ���˂��Ă��邱�Ƃ��ؖ�
		is_fire_ = true;

		// �e�̃Q�[���I�u�W�F�N�g�̑O�x�N�g�����擾
		parent_front_vector_ = *game_object_parent_->GetTransform()->GetFrontVector();

		// ���ˍ��W���L�^
		src_position_ = position_;
	}

	if (charge_bullet_state_ == ChargeBulletState::Bullet)
	{
		// �ړ��̍X�V
		this->UpdateMovement(deltaTime);

		// �������Ԃ̌v�Z
		alive_time_ += deltaTime;

		//// �������Ԃ��������Ԃ𒴂�����
		if (alive_time_ >= kill_timer_)
		{
			this->SetChargeBulletState(ChargeBulletState::End);
			alive_time_ = 0.f;
		}
	}

	// �`���[�W�e�̍X�V
	this->UpdateChargeBulletState(deltaTime);

	// Particle�G�t�F�N�g�̍X�V
	this->UpdateParticleEffect();

	// �Փ˔���̍X�V
	this->UpdateColilision(charge_bullet_state_);

	// 1�t���[���O�̏����X�V
	charge_bullet_state_old_ = charge_bullet_state_;
}

/*-----------------------------------------------------------------------------
/* �`���[�W�e�̈ړ��̍X�V����
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateMovement(float deltaTime)
{
	if (is_lockon_ == true)
	{
		// �ړ�
		lerp_execute_time_ += deltaTime;

		// ���b�N�I����������܂Ŕ��ł���
		const Vector3 src_pos(src_position_);
		const Vector3 dst_pos(dst_position_);

		// Lerp��Easing�ō��W�̕��
		auto bullet_pos = Vector3::Vector3lerp(src_pos, dst_pos, Easing::Linear(lerp_execute_time_));

		position_ = { bullet_pos.x_, bullet_pos.y_, bullet_pos.z_ };
	}
	else
	{
		// �v���C���[�̑O�x�N�g���ֈړ�
		position_ += (parent_front_vector_ * move_speed_) * deltaTime;
	}
}

/*-----------------------------------------------------------------------------
/* �`���[�W�e�̏�Ԃ̍X�V����
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateChargeBulletState(float deltaTime)
{
	const float MAX_STATE_TIME_CHARGE		= 3.0f;
	const float MAX_STATE_TIME_FIRE			= 0.05f;
	const float MAX_STATE_TIME_EXPLOSION	= 1.5f;

	// �`���[�W�e�̐�������
	state_time_ += deltaTime;

	if (is_next_state_)
	{
		charge_bullet_state_ = ChargeBulletState::Hold;
		is_next_state_ = false;
	}

	ImGui::Begin("BulletState");

	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		ImGui::Text("Charge"); // �{�^���𒷉������Ă����
		if (state_time_ >= MAX_STATE_TIME_CHARGE)
		{
			is_next_state_ = true;
			state_time_ = 0;
		}
		break;

	case ChargeBulletState::Hold:
		ImGui::Text("Hold");
		state_time_ = 0;
		break;

	case ChargeBulletState::Fire:
		ImGui::Text("Fire");
		if (state_time_ >= MAX_STATE_TIME_FIRE)
		{
			charge_bullet_state_ = ChargeBulletState::Bullet;
			state_time_ = 0;
		}
		break;
	
	case ChargeBulletState::Bullet:
		ImGui::Text("Bullet");
		if (is_hit_)
		{
			charge_bullet_state_ = ChargeBulletState::Explosion;
			state_time_ = 0;
		}
		break;
	
	case ChargeBulletState::Explosion:
		ImGui::Text("Explosion");
		if (state_time_ >= MAX_STATE_TIME_EXPLOSION)
		{
			charge_bullet_state_ = ChargeBulletState::End;
			state_time_ = 0;
		}
		break;

	case ChargeBulletState::End:
		ImGui::Text("End");
		break;

	default:
		assert(!"ChargeBullet::UpdateChargeBullet():�`���[�W�e�̃Q�[���I�u�W�F�N�g���s���ȏ������N�����Ă��܂��I");
		break;
	}

	ImGui::End();
	
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�̍X�V����
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateParticleEffect(void)
{
	// �X�e�[�g���؂�ւ�����u�Ԃ����Đ������悤��
	if (charge_bullet_state_ != charge_bullet_state_old_)
	{
		this->UpdateParticleEffectPlayState(charge_bullet_state_);
	}

	// �G�t�F�N�g�̈ʒu���X�V
	for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
	{
		effect_[i]->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�̍Đ��󋵂̍X�V����
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateParticleEffectPlayState(ChargeBulletState chargeBulletState)
{
	const int EFFECT_CHARGE		= 0;
	const int EFFECT_HOLD		= 1;
	const int EFFECT_BULLET		= 2;
	const int EFFECT_EXPLOSION	= 3;

	switch (chargeBulletState)
	{
	case ChargeBulletState::Charge:
		effect_[EFFECT_CHARGE]->Play();		// �G�t�F�N�g�Đ��F�`���[�W���J�n����G�t�F�N�g
		break;

	case ChargeBulletState::Hold:
		effect_[EFFECT_HOLD]->Play();		// �G�t�F�N�g�Đ��F�`���[�W�𑱂���G�t�F�N�g
		break;

	case ChargeBulletState::Fire:
		effect_[EFFECT_HOLD]->Stop();		// �G�t�F�N�g��~�F�`���[�W�𑱂���G�t�F�N�g
		effect_[EFFECT_BULLET]->Play();		// �G�t�F�N�g�Đ��F�`���[�W�e�̃G�t�F�N�g
		break;

	case ChargeBulletState::Explosion:
		effect_[EFFECT_BULLET]->Stop();		// �G�t�F�N�g��~�F�`���[�W�e�̃G�t�F�N�g
		effect_[EFFECT_EXPLOSION]->Play();	// �G�t�F�N�g�Đ��F�����̃G�t�F�N�g
		break;

	default:
		break;
	}
}

/*-----------------------------------------------------------------------------
/* �Փ˔���̍X�V
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateColilision(ChargeBulletState chargeBulletState)
{
	const float colider_scale_ = 1.f;

	switch (chargeBulletState)
	{
	case ChargeBulletState::Bullet:
		// �e�̔���̑傫����1�{
		sphere_collider_->SetRadius(colider_scale_);
		sphere_collider_gizmo_->SetScale(colider_scale_);
		break;

	case ChargeBulletState::Explosion:
		// ���������画��̑傫����4�{�ɐݒ�
		sphere_collider_->SetRadius(colider_scale_ * 4.f);
		sphere_collider_gizmo_->SetScale(colider_scale_ * 4.f);
		break;

	default:
		break;
	}

	// �Փ˔���̈ʒu�̍X�V
	{
		sphere_collider_gizmo_->SetTranslation(position_);
		sphere_collider_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/* �e�̔���
-----------------------------------------------------------------------------*/
void ChargeBullet::Fire(void)
{
	charge_bullet_state_ = ChargeBulletState::Fire;
}

/*=============================================================================
/*		End of File
=============================================================================*/