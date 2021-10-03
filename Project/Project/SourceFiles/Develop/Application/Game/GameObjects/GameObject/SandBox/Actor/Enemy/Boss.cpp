/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Boss.cpp] �{�X�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../../StdAfx.h"
#include "Boss.h"

// �ړ��R���|�[�l���g
#include "../../../../Component/MoveComponent/EnemyMoveComponent/BossMoveComponent.h"

// �{�XAI�R���|�[�l���g
#include "../../../../Component/AIComponent/EnemyAIComponent/BossAIComponent.h"

// �`��R���|�[�l���g
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../../Component/RendererComponent/EffectRendererComponent.h"

// �����R���|�[�l���g
#include "../../../../Component/AudioComponent.h"

// ���̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// �{�b�N�X�̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

// �G�̕���R���|�[�l���g
#include "../../../../Component/WeaponComponent/EnemyBlasterWeaponComponent.h"
#include "../../../../Component/WeaponComponent/LaserCannonWeaponComponent.h"

// �l�R���|�[�l���g
#include "../../../../Component/ParameterComponent/FloatParameterComponent.h"

// ���̓`�F�b�N
#include "../../../../../Input/InputCheck.h"

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"


#include "../../../../../Game.h"
#include "../../Bullet/NormalBullet.h"
#include "../../../../../SandBoxManager/ActorManager.h"
#include "../../../../../SandBoxManager/BulletManager.h"
#include "../../../../../CheckCollision.h"



/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Boss::Boss(Game* game)
	: Enemy(game)
	, enemy_state_old_(EnemyState::None)
	, motion_state_old_(EnemyMotionState::None)
	, effect_enemy_action_shoot_(nullptr)
	, effect_player_attack_hit_(nullptr)
	, enemy_damage_sound_effect_(nullptr)
	, max_hp_param_(nullptr)
	, hp_param_(nullptr)
	, is_fire_(false)
	, blaster_index_(0)
	, switch_time_(0.f)
	, laser_cannon_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Boss::~Boss(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Boss::Init(void)
{
	// �{�X��AI�𐶐� 
	enemy_ai_ = NEW BossAIComponent(this);

	// �{�X�̈ړ��R���|�[�l���g�𐶐�
	enemy_move_ = NEW BossMoveComponent(this);

	// �������W��������
	{
		this->transform_component_->SetTranslationY(-100.f);
		this->enemy_move_->SetStartPositionY(-100.f);

		// �e�X�g�p�������W
		//this->transform_component_->SetTranslationZ(15.f);
	}

	// ���b�V���̐���
	{
		// �{�X�̃��b�V������
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyBoss);
		//actor_mesh_->IsSetDrawable(false);
		actor_mesh_->SetEnableLighting(true);			// ���C�e�B���O��L���ɂ���
	}

	// �G�t�F�N�g�R���|�[�l���g�̐���
	{
		// �ˌ��s���ʒm�G�t�F�N�g
		effect_enemy_action_shoot_ = NEW EffectRendererComponent(this);
		effect_enemy_action_shoot_->SetEffect(EffectType::EnemyActionGuide_Red);
		effect_enemy_action_shoot_->SetTranslationY(3.f);

		// �q�b�g�G�t�F�N�g
		effect_player_attack_hit_ = NEW EffectRendererComponent(this);
		effect_player_attack_hit_->SetEffect(EffectType::HitEffect);
		effect_player_attack_hit_->SetTranslationY(3.f);

		// �����G�t�F�N�g
		effect_explosion_ = NEW EffectRendererComponent(this);
		effect_explosion_->SetEffect(EffectType::ExplosionBoss);
		effect_explosion_->SetTranslationY(3.f);
	}

	// �����R���|�[�l���g�̐���
	{
		enemy_damage_sound_effect_ = NEW AudioComponent(this);
		enemy_damage_sound_effect_->SetSound(SoundType::DamageBoss);
		enemy_damage_sound_effect_->SetAudioVolume(1.f);
	}

	// �Q�[���}�l�[�W���ւ̃|�C���^�̎擾
	{
		game_manager_ = this->FindGameObject(GameObject::TypeID::GameManager);
		if (game_manager_ == nullptr)
		{
			assert(!"StrongEnemy::Init()�F�Q�[���}�l�[�W���ւ̃|�C���^���擾�ł��܂���ł���");
		}
	}

	// �{�X�̏�Ԃ�������
	{
		auto init_boss_state = EnemyState::Enter;

		// �G�̏�Ԃ�������
		enemy_ai_->SetEnemyState(init_boss_state);
		enemy_move_->SetEnemyState(init_boss_state);
	}

	// ����̐���
	{
		for (int i = 0; i < MAX_WEAPON_COUNT; i++)
		{
			enemy_blaster_[i] = nullptr;
			enemy_blaster_[i] = NEW EnemyBlasterWeaponComponent(this);
		}
	
		laser_cannon_ = NEW LaserCannonWeaponComponent(this);
		laser_cannon_->SetTranslationY(-0.5f);
	}


	// �Փ˔���֌W
	{
		// ��
		{
			// ���̔��a
			const float sphere_radius_size = 3.f;

			// �Փ˔���
			sphere_collider_ = NEW SphereColliderComponent(this);
			sphere_collider_->SetOffsetTranslationY(COLLIDER_OFFSET_HEIGHT_POS);
			sphere_collider_->SetRadius(sphere_radius_size);

			// �M�Y��
			sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
			sphere_gizmo_->SetTranslationY(COLLIDER_OFFSET_HEIGHT_POS);
			sphere_gizmo_->SetScale(sphere_radius_size);
			//sphere_gizmo_->IsSetDrawable(false);
		}

		// ��
		{
			// ���̍���
			const float box_height_size = 1.f;

			// ���̐������̑傫��
			const float box_size = 7.f;

			// �Փ˔���
			obb_collider_ = NEW OBBColliderComponent(this);
			obb_collider_->SetOffsetTranslationY(COLLIDER_OFFSET_HEIGHT_POS);
			obb_collider_->SetDirLength(box_size, AxisType::X);
			obb_collider_->SetDirLength(box_height_size, AxisType::Y);
			obb_collider_->SetDirLength(box_size, AxisType::Z);

			// �M�Y��
			obb_collider_gizmo_ = NEW BoxGizmoRendererComponent(this);
			obb_collider_gizmo_->SetTranslationY(COLLIDER_OFFSET_HEIGHT_POS);
			obb_collider_gizmo_->SetScaleX(box_size);
			obb_collider_gizmo_->SetScaleY(box_height_size);
			obb_collider_gizmo_->SetScaleZ(box_size);
			//obb_collider_gizmo_->IsSetDrawable(false);
		}
	}

	// �l�R���|�[�l���g�̍쐬
	{
		// �ő�HP
		max_hp_param_ = NEW FloatParameterComponent(this);
		max_hp_param_->SetParameterType(ParameterType::BossMaxHP);
		max_hp_param_->SetFloat(max_hit_point_);

		// HP
		hp_param_ = NEW FloatParameterComponent(this);
		hp_param_->SetParameterType(ParameterType::BossHP);
		hp_param_->SetFloat(hit_point_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Boss::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̓��͏���
-----------------------------------------------------------------------------*/
void Boss::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* override�Ŏ������g���X�V
-----------------------------------------------------------------------------*/
void Boss::UpdateGameObject(float deltaTime)
{

	// AI�R���|�[�l���g�Ƀ{�X��HP��ʒm����
	{
		enemy_ai_->SetHitPoint(this->GetHitPoint());
	}

	/*
	*			��		EnemyState		��
	* 
	����������������������������������������������������
	���@�@Move�@�@��  ���@�@Boss �@ ���@���@�@AI�@�@�@��
	����������������������������������������������������
	*
	*			��		MotionState		��
	*/

	// AI�R���|�[�l���g����GAI�̍s���X�e�[�g���擾
	auto ai_state = enemy_ai_->GetEnemyState();
	{
		// �ړ��R���|�[�l���g�ցA�GAI�̍s���X�e�[�g��ʒm
		enemy_move_->SetEnemyState(ai_state);
	}

	// �ړ��R���|�[�l���g����ړ����[�V������Ԃ��擾
	auto move_motion_state = enemy_move_->GetMotionState();
	{
		// AI�R���|�[�l���g�ֈړ����[�V������Ԃ�ʒm
		enemy_ai_->SetMotionState(move_motion_state);
	}

	// �ˌ��s���ɓ��邱�Ƃ�ʒm����
	if (ai_state == EnemyState::Shooting)
	{
		if (ai_state != enemy_state_old_)
		{
			effect_enemy_action_shoot_->Play();
		}
	}

	//�@���g��AI�̃X�e�[�g����U���͂��X�V����
	switch (ai_state)
	{
	case EnemyState::BodyPress:
		attack_ = ATTACK_VALUE_BODY_PRESS;
		break;

	case EnemyState::Shooting:
		attack_ = ATTACK_VALUE_SHOOT;
		break;

	case EnemyState::LaserCannon:
		attack_ = ATTACK_VALUE_LASER_CANNON;
		break;

	case EnemyState::Destroy:
		attack_ = 0.f;
		break;

	default:
		break;
	}

	// �l�R���|�[�l���g�̍X�V
	this->UpdateParameter(deltaTime);

	// ����R���|�[�l���g�̍X�V
	{
		this->UpdateBlaster(deltaTime, ai_state, move_motion_state);

		// ���[�U�[�C�̍X�V
		this->UpdateLaserCannon(ai_state, move_motion_state);
	}

	// �Փ˔���̍X�V
	this->UpdateCollision(deltaTime);

	// 1�t���[���O�̏����X�V
	enemy_state_old_ = ai_state;
	motion_state_old_ = move_motion_state;


	// ���g��j�󂳂ꂽ��
	if (this->GetGameObjectState() == State::Destroy)
	{
		// �j���Ԃł̏��������s��
		if (is_destroy_ == false)
		{
			// �j�󂳂���ԂƂ��ċL�����s��
			is_destroy_ = true;

			// �����G�t�F�N�g���Đ�
			effect_explosion_->Play();

			// �X�R�A�։��Z����
			auto parameter_components = game_manager_->GetParameterComponents();
			for (auto parameter_component : parameter_components)
			{
				// �X�R�A�ւ̒l�R���|�[�l���g�ւ̃|�C���^���擾
				auto parameter_component_type = parameter_component->GetParameterType();
				if (parameter_component_type == ParameterType::Score)
				{
					parameter_component->AddInt(100);
					break;
				}
			}

			sphere_gizmo_->IsSetDrawable(false);
		}

		// �j��܂ł̎���
		destroy_interval_time_ += deltaTime;

		// ���g��j������
		const float MAX_DESTROY_INTERVAL_TIME = 6.f;

		// ���b�V���̕`��𖳌���
		if (destroy_interval_time_ >= (MAX_DESTROY_INTERVAL_TIME * 0.6f))
		{
			actor_mesh_->IsSetDrawable(false);
		}

		// ���g��j��
		if (destroy_interval_time_ >= MAX_DESTROY_INTERVAL_TIME)
		{
			// �v���C���[���j�󂳂ꂽ�̂ŃQ�[���I�[�o�[�ɂ���
			game_->SetGameState(Game::GameState::GameFinishScene);

			this->SetGameObjectState(State::Dead);
		}
		return;
	}
}

/*-----------------------------------------------------------------------------
/* �l�R���|�[�l���g�̍X�V����
-----------------------------------------------------------------------------*/
void Boss::UpdateParameter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const bool is_nullptr_max_hp_param = (max_hp_param_ == nullptr);
	const bool is_nullptr_hp_param = (hp_param_ == nullptr);

	// �ő�HP�̒l�R���|�[�l���g��null�`�F�b�N
	if (is_nullptr_max_hp_param)
	{
		assert(!"Boss::UpdateParameter():�l�R���|�[�l���g:max_hp_param_ ���hnullptr�h�ł���");
		return;
	}

	// HP�̒l�R���|�[�l���g��null�`�F�b�N
	if (is_nullptr_hp_param)
	{
		assert(!"Boss::UpdateParameter():�l�R���|�[�l���g:hp_param_ ���hnullptr�h�ł���");
		return;
	}

	// �ő�HP�̍X�V
	max_hp_param_->SetFloat(max_hit_point_);

	// ���݂�HP�̍X�V
	hp_param_->SetFloat(hit_point_);
}

/*-----------------------------------------------------------------------------
/* �����e�̍X�V����
-----------------------------------------------------------------------------*/
void Boss::UpdateBlaster(float deltaTime, EnemyState enemyState, EnemyMotionState motionState)
{
	// �Q�[���̏�Ԃ��؂�ւ������
	if (this->GetGameObjectState() == GameObject::State::Destroy) { return; }

	// ���W�̍X�V
	{
		// ���ꂼ��̍��W�̈ꎞ�ۊǐ�
		D3DXVECTOR3 pos;

		// �p�x���O����
		const float degree = 360.f / 3.f;

		// ���a
		const float radius = 5.0f;

		for (int i = 0; i < MAX_WEAPON_COUNT; i++)
		{
			// �p�x��radian �ɕϊ�
			const float radian = Math::ToRadian(degree * i);
			pos.x = cosf(radian) * radius;
			pos.y = 1.0f;
			pos.z = sinf(radian) * radius;

			// ���W�̌v�Z
			enemy_blaster_[i]->SetTranslation(pos);
		}
	}

	// �U�����s�����̔���
	if (enemyState != EnemyState::Shooting) { return; }
	if (motionState != EnemyMotionState::Attack) { return; }

	if (blaster_index_ >= MAX_WEAPON_COUNT)
	{
		blaster_index_ = 0;
	}

	// �؂�ւ�莞�Ԃ��v�Z
	switch_time_ += deltaTime;

	const float SWITCH_TIME_LIMIT = 0.3f;
	if (switch_time_ >= SWITCH_TIME_LIMIT)
	{
		switch_time_ = 0.f;
		is_fire_ = true;
	}

	if (is_fire_ == true)
	{
		enemy_blaster_[blaster_index_]->Fire();
		blaster_index_++;
		is_fire_ = false;
	}
}

/*-----------------------------------------------------------------------------
/* ���[�U�[�C�̍X�V����
-----------------------------------------------------------------------------*/
void Boss::UpdateLaserCannon(EnemyState enemyState, EnemyMotionState motionState)
{
	if (enemyState != EnemyState::LaserCannon) { return; }

	// �{�X�̃��[�V������Ԃ�ʒm
	laser_cannon_->SetEnemyMotionState(motionState);

	// �X�e�[�g���؂�ւ�����u�ԂƂ�
	if (enemy_state_old_ != enemyState)
	{
		is_fire_ = true;
	}

	if ((is_fire_ == true)
		&& (motionState == EnemyMotionState::Relay))
	{
		// ���[�U�[��C�̔���
		laser_cannon_->Shoot();
		is_fire_ = false;
	}
}

/*-----------------------------------------------------------------------------
/* �Փ˔���̍X�V����
-----------------------------------------------------------------------------*/
void Boss::UpdateCollision(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (InputCheck::KeyTrigger(DIK_I))
	{
		hit_point_ = 100.f;
	}

	// HP�̉�����ݒ�
	if (hit_point_ <= 0.f)
	{
		// �G�l�~�[���j�󂳂���Ԃ�
		this->SetGameObjectState(State::Destroy);
		hit_point_ = 0.f;
	}

	auto boss_state_ = this->enemy_ai_->GetEnemyState();
	auto boss_motion_state_ = this->enemy_move_->GetMotionState();

	const bool is_weakpoint_ready = ((boss_state_ == EnemyState::LaserCannon) || (boss_state_ == EnemyState::Shooting));
	const bool is_weakpoint_enable = ((boss_motion_state_ == EnemyMotionState::Attack) && is_weakpoint_ready);

	// ��_���L���ł͂Ȃ������ꍇ
	if (is_weakpoint_enable == false) { return; }

	// �o���b�g�̏Փ˔���
	auto bullets = game_->GetBulletManager()->GetBulletGameObjectList();
	for (auto bullet : bullets)
	{
		// Bullet�̐e�I�u�W�F�N�g��Player���𒲂ׂ�
		auto bullet_parent_game_object_type = bullet->GetParentGameObjectType();

		if (bullet_parent_game_object_type != GameObject::TypeID::Player)
		{
			continue;
		}

		// �G�l�~�[�̃o���b�g�̏Փ˔�����擾
		if (CheckCollision::SphereVSSpghre(this->GetSphereCollider(), bullet->GetSphereCollider()))
		{
			// �_���[�W���󂯂����̃G�t�F�N�g���Đ�
			effect_player_attack_hit_->Play();

			// �_���[�W���󂯂�SE���Đ�
			enemy_damage_sound_effect_->Play();

			// �_���[�W�����󂯂�
			const float DAMAGE = -5.f;
			hit_point_ += DAMAGE;

			// �Փ˂����o���b�g��j������
			bullet->SetGameObjectState(State::Dead);
			break;
		}

	}
}

/*=============================================================================
/*		End of File
=============================================================================*/