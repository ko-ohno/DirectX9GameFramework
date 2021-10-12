/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBullet.cpp] �`���[�W�e�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�`���[�W�e�̃Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "ChargeBullet.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../Component/ColliderComponent/SphereColliderComponent.h"
#include "../../../Component/AudioComponent.h"
#include "../../../../../Math.h"
#include "../../SandBox/Actor/Enemy.h"
#include "../../../../SandBoxManager/EnemieManager.h"
#include "../../../../CheckCollision.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ChargeBullet::ChargeBullet(Game* game)
	: Bullet(game)
	, bullet_charge_se_(nullptr)
	, bullet_fire_se_(nullptr)
	, bullet_explosion_se_(nullptr)
	, charge_bullet_state_(ChargeBulletState::None)
	, charge_bullet_state_old_(ChargeBulletState::None)
	, is_fire_(false)
	, is_hit_(false)
	, is_lockon_(false)
	, is_next_state_(false)
	, parent_front_vector_(0.f, 0.f, 1.f)
	, move_speed_(0.f)
	, position_(0.f, 0.f, 0.f)
	, src_position_(0.f, 0.f, 0.f)
	, dst_position_(0.f, 0.f, 0.f)
	, lerp_execute_time_(0.f)
	, kill_timer_(0.f)
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
	// �l�̐ݒ�
	move_speed_ = 15.f;
	kill_timer_ = 2.f;


	// �z��̏�����
	{
		// �G�t�F�N�g�ԍ��̓o�^
		effect_type_[0] = EffectType::ChargeBulletState1Charge;
		effect_type_[1] = EffectType::ChargeBulletState2Hold;
		effect_type_[2] = EffectType::ChargeBulletState4Bullet;
		effect_type_[3] = EffectType::ChargeBulletState5Explosion;

		for (int i = 0; i < MAX_CHARGE_BULLET_STATE_; i++)
		{
			effect_[i] = nullptr;
		}
	}

	const float init_axis_y_pos = -100.f;

	// �e�ۂ̐���
	{
		for (int i = 0; i < MAX_CHARGE_BULLET_STATE_; i++)
		{
			effect_[i] = nullptr;
			effect_[i] = NEW EffectRendererComponent(this);
			effect_[i]->SetEffect(effect_type_[i]);
			//effect_[i]->SetScale(0.5f);
			effect_[i]->SetTranslationY(init_axis_y_pos);
		}
	}

	// �����R���|�[�l���g�̐���
	{
		bullet_charge_se_ = NEW AudioComponent(this);
		bullet_charge_se_->SetSound(SoundType::ChargeBulletCharge);
		bullet_charge_se_->SetAudioVolume(0.8f);

		bullet_fire_se_ = NEW AudioComponent(this);
		bullet_fire_se_->SetSound(SoundType::ChargeBulletFire);
		bullet_fire_se_->SetAudioVolume(0.8f);

		bullet_explosion_se_ = NEW AudioComponent(this);
		bullet_explosion_se_->SetSound(SoundType::ChargeBulletExplosion);
		bullet_explosion_se_->SetAudioVolume(0.8f);
	}

	// �Փ˔���̍쐬
	{
		const float scale = 1.f;

		// ���̏Փ˔���
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);

		// �M�Y���̕`��R���|�[�l���g
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
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
	//���L�҂��s���������ꍇ
	const bool is_owner_type_unkown = (parent_game_object_type_ == GameObject::TypeID::None);
	if (is_owner_type_unkown)
	{
		// �e�Q�[���I�u�W�F�N�g�̎�ނ��L��
		parent_game_object_type_ = this->GetParentGameObject()->GetType();
	}

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
		// ���W���Ԃ��āA���b�N�I����������܂Ŕ��ł���
		D3DXVec3Lerp(&position_, &src_position_, &dst_position_, Easing::Linear(lerp_execute_time_, MAX_LERP_EXECUTE_TIME_));

		// �ړ�
		lerp_execute_time_ += deltaTime;
		if (lerp_execute_time_ >= MAX_LERP_EXECUTE_TIME_)
		{
			lerp_execute_time_ = MAX_LERP_EXECUTE_TIME_;
		}
	}
	else
	{
		// �v���C���[�̑O�x�N�g���ֈړ�
		position_ += (parent_front_vector_ * move_speed_) * deltaTime;
	}

	// ���W�̍X�V
	this->transform_component_->SetTranslation(position_);
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

#ifdef DEBUG_MODE_
	ImGui::Begin("BulletState");
	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		ImGui::Text("Charge"); // �{�^���𒷉������Ă����
		break;

	case ChargeBulletState::Hold:
		ImGui::Text("Hold");
		break;

	case ChargeBulletState::Fire:
		ImGui::Text("Fire");
		break;

	case ChargeBulletState::Bullet:
		ImGui::Text("Bullet");
		break;

	case ChargeBulletState::Explosion:
		ImGui::Text("Explosion");
		break;

	case ChargeBulletState::End:
		ImGui::Text("End");
		break;

	default:
		break;
	}
	ImGui::End();
#endif

	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		if (state_time_ >= MAX_STATE_TIME_CHARGE)
		{
			is_next_state_ = true;
			state_time_ = 0;
		}
		break;

	case ChargeBulletState::Hold:
		state_time_ = 0;
		break;

	case ChargeBulletState::Fire:
		if (state_time_ >= MAX_STATE_TIME_FIRE)
		{
			charge_bullet_state_ = ChargeBulletState::Bullet;
			state_time_ = 0;
		}
		break;
	
	case ChargeBulletState::Bullet:
		if (is_hit_)
		{
			charge_bullet_state_ = ChargeBulletState::Explosion;
			state_time_ = 0;
		}
		break;
	
	case ChargeBulletState::Explosion:
		if (state_time_ >= MAX_STATE_TIME_EXPLOSION)
		{
			charge_bullet_state_ = ChargeBulletState::End;
			state_time_ = 0;
		}
		break;

	case ChargeBulletState::End:
		break;

	default:
		assert(!"ChargeBullet::UpdateChargeBullet():�`���[�W�e�̃Q�[���I�u�W�F�N�g���s���ȏ������N�����Ă��܂��I");
		break;
	}
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

	// �o���b�g�̏�Ԃ��X�V
	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		effect_[0]->SetTranslation(position_);
		break;

	case ChargeBulletState::Hold:
		effect_[1]->SetTranslation(position_);
		break;

	case ChargeBulletState::Bullet:
		effect_[2]->IsSetOwnerTransfromOrder(false);
		effect_[2]->SetTranslation(position_);
		break;

	case ChargeBulletState::Explosion:
		effect_[3]->IsSetOwnerTransfromOrder(false);
		effect_[3]->SetTranslation(position_);
		break;

	default:
		break;
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
		bullet_charge_se_->Play();			// �����Đ�:�`���[�W����
		break;

	case ChargeBulletState::Hold:
		effect_[EFFECT_HOLD]->Play();		// �G�t�F�N�g�Đ��F�`���[�W�𑱂���G�t�F�N�g
		break;

	case ChargeBulletState::Fire:
		effect_[EFFECT_HOLD]->Stop();		// �G�t�F�N�g��~�F�`���[�W�𑱂���G�t�F�N�g
		effect_[EFFECT_BULLET]->Play();		// �G�t�F�N�g�Đ��F�`���[�W�e�̃G�t�F�N�g
		bullet_fire_se_->Play();			// �����Đ�:���ˉ���
		break;

	case ChargeBulletState::Explosion:
		effect_[EFFECT_BULLET]->Stop();		// �G�t�F�N�g��~�F�`���[�W�e�̃G�t�F�N�g
		effect_[EFFECT_EXPLOSION]->Play();	// �G�t�F�N�g�Đ��F�����̃G�t�F�N�g
		bullet_explosion_se_->Play();		// �����Đ�:��������
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
	// �Փ˔���̑傫�����X�V
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
	}

	// �G�̏Փ˔�����擾
	auto enemy_list_ = game_->GetEnemieManager()->GetEnemyGameObjectList();
	for (auto enemy : enemy_list_)
	{
		auto game_object_state = enemy->GetGameObjectState();
		if (game_object_state == GameObject::State::Destroy) { continue; }
		if (game_object_state == GameObject::State::Dead) { continue; }

		if (CheckCollision::SphereVSSpghre(this->GetSphereCollider(), enemy->GetSphereCollider()))
		{
			// �Q�[���I�u�W�F�N�g�̌^�𒲂ׂ�
			auto enemy_game_object_type = enemy->GetType();
			if (enemy_game_object_type != GameObject::TypeID::Boss)
			{
				// �{�X����Ȃ�������G�l�~�[��j�󂷂�
				enemy->SetGameObjectState(GameObject::State::Destroy);
			}

			// �Փ˂������Ƃ��L��
			is_hit_ = true;

			// �`���[�W�e�̏�Ԃ𔚔���Ԃ�
			chargeBulletState = ChargeBulletState::Explosion;
			break;
		}
	}
}

/*-----------------------------------------------------------------------------
/* �e�̔���
-----------------------------------------------------------------------------*/
void ChargeBullet::Fire(void)
{
	charge_bullet_state_ = ChargeBulletState::Fire;
}

/*-----------------------------------------------------------------------------
/* �^�[�Q�b�g�̓G�ւ̃|�C���^��ݒ�
-----------------------------------------------------------------------------*/
void ChargeBullet::SetLockonTargetEnemy(Enemy* enemy)
{
	if (enemy == nullptr) { return; }

	auto game_object_type = enemy->GetType();
	if (game_object_type == GameObject::TypeID::Boss)
	{
		// �{�X�̃��f�������_�Y�����N�����Ă��邽�߁A�ړI�n���W���I�t�Z�b�g���Đݒ�
		dst_position_ = *enemy->GetTransform()->GetPosition();

		// Y���W���I�t�Z�b�g
		dst_position_.y += 1.f;
	}
	else
	{
		// �ړI�n���W��ݒ�
		dst_position_ = *enemy->GetTransform()->GetPosition();
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/