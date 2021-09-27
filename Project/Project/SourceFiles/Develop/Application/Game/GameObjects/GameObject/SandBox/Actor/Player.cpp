/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Player.cpp] �v���C���[�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�v���C���[�̏������`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "Player.h"
#include "../Bullet/ChargeBullet.h"
#include "../../../../CheckCollision.h"
#include "Enemy.h"
#include "../../../../SandBoxManager/EnemieManager.h"
#include "../Bullet/NormalBullet.h"
#include "../../../../SandBoxManager/BulletManager.h"

// �`��R���|�[�l���g
#include "../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../../Component/RendererComponent/BillboardRendererComponent.h"

// ����R���|�[�l���g
#include "../../../Component/WeaponComponent/BlasterWeaponComponent.h"
#include "../../../Component/WeaponComponent/ChargeBlasterWeaponComponent.h"

// �ړ��R���|�[�l���g
#include "../../../Component/MoveComponent/PlayerMoveComponent.h"

// �Փ˔���R���|�[�l���g
#include "../../../Component/ColliderComponent/OBBColliderComponent.h"
#include "../../../Component/ColliderComponent/SphereColliderComponent.h"

// �����R���|�[�l���g
#include "../../../Component/AudioComponent.h"

// �M�Y���R���|�[�l���g
#include "../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

// �l�R���|�[�l���g
#include "../../../Component/ParameterComponent/FloatParameterComponent.h"

// ���̓`�F�b�N
#include "../../../../Input/InputCheck.h"

// ImGUI
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Player::Player(Game* game)
	: Actor(game)
	, player_move_(nullptr)
	, effect_after_burner_(nullptr)
	, effect_enemy_attack_hit_(nullptr)
	, near_reticle_(nullptr)
	, far_reticle_(nullptr)
	, lockon_reticle_(nullptr)
	, left_blaster_(nullptr)
	, right_blaster_(nullptr)
	, charge_blaster_(nullptr)
	, player_damege_sound_effect_(nullptr)
	, max_hp_param_(nullptr)
	, hp_param_(nullptr)
	, is_blaster_fire_(false)
	, is_received_damage_(false)
	, damage_recieve_interval_time_(0.f)
	, boss_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Player::~Player(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Player::Init(void)
{
	// �v���C���[�̈ړ��R���|�[�l���g�̐���
	player_move_ = NEW  PlayerMoveComponent(this);

	// �`��R���|�[�l���g
	{
		// ���@�̕\��
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::SpaceShip);
		actor_mesh_->SetEnableLighting(true);
		actor_mesh_->SetScale(0.5f);

		// �G�t�F�N�g�R���|�[�l���g
		{
			// �A�t�^�[�o�[�i�[�̕\��
			effect_after_burner_ = NEW EffectRendererComponent(this);
			effect_after_burner_->SetEffect(EffectType::AfterBurner);
			effect_after_burner_->Play();

			// �A�t�^�[�o�[�i�[�̕\��
			effect_enemy_attack_hit_ = NEW EffectRendererComponent(this);
			effect_enemy_attack_hit_->SetEffect(EffectType::HitEffect);
		}

		// ���e�B�N���̐ݒ�
		{
			// �����̃��e�B�N��
			{
				far_reticle_ = NEW BillboardRendererComponent(this, 290);
				far_reticle_->SetTexture(TextureType::FarReticle);
				far_reticle_->SetVertexColor(0, 255, 0, 255);
				far_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// ���e�B�N���̐����̒���
				far_reticle_->SetScale(1.2f);
				far_reticle_->SetTranslationZ(10.f);
			}

			//�@��O�̃��e�B�N��
			{
				near_reticle_ = NEW BillboardRendererComponent(this, 290);
				near_reticle_->SetTexture(TextureType::NearReticle);
				near_reticle_->SetVertexColor(0, 255, 0, 255);
				near_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// ���e�B�N���̐����̒���
				near_reticle_->SetScale(1.4f);
				near_reticle_->SetTranslationZ(9.f);
			}

			//�@���b�N�I���̃��e�B�N��
			{
				lockon_reticle_ = NEW BillboardRendererComponent(this, 290);
				lockon_reticle_->SetTexture(TextureType::NearReticle);
				lockon_reticle_->SetVertexColor(0, 255, 0, 255);
				lockon_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// ���e�B�N���̐����̒���
				lockon_reticle_->SetScale(1.4f);
				lockon_reticle_->SetTranslationZ(9.f);
			}
		}
	}

	// �����R���|�[�l���g
	{
		player_damege_sound_effect_ = NEW AudioComponent(this);
		player_damege_sound_effect_->SetSound(SoundType::DamagePlayer);
		player_damege_sound_effect_->SetAudioVolume(1.f);
	}

	// ����R���|�[�l���g
	{
		// ���̌����e
		left_blaster_ = NEW BlasterWeaponComponent(this);

		// �E�̌����e
		right_blaster_ = NEW BlasterWeaponComponent(this);

		// �`���[�W�e�p�̌����e
		charge_blaster_ = NEW ChargeBlasterWeaponComponent(this);
	}

	//�@�Փ˔���R���|�[�l���g
	{
		// OBB�̑傫��
		const float sphere_radius_scale = 0.5f;

		// ���̏Փ˔���
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(sphere_radius_scale);

		sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_gizmo_->SetScale(sphere_radius_scale);
		sphere_gizmo_->SetVertexColor(255, 255, 0, 255);


		// OBB�̑傫��
		const float box_scale = 0.5f;

		// OBB�̏Փ˔���
		obb_collider_ = NEW OBBColliderComponent(this);
		obb_collider_->SetDirLength(box_scale, AxisType::X);
		obb_collider_->SetDirLength(box_scale, AxisType::Y);
		obb_collider_->SetDirLength(box_scale, AxisType::Z);

		obb_collider_gizmo_ = NEW BoxGizmoRendererComponent(this);
		obb_collider_gizmo_->SetScale(box_scale);

		// ���b�N�I���̔��̏Փ˔���
		{
			const float lockon_langth = 10.f;
			const float lockon_scale = 0.5f;

			lockon_collider_ = NEW OBBColliderComponent(this);
			lockon_collider_->SetDirLength(lockon_scale, AxisType::X);
			lockon_collider_->SetDirLength(lockon_scale, AxisType::Y);
			lockon_collider_->SetDirLength(lockon_langth, AxisType::Z);

			lockon_gizmo_ = NEW BoxGizmoRendererComponent(this);
			lockon_gizmo_->SetVertexColor(0, 255, 255, 128);
			lockon_gizmo_->SetScaleX(lockon_scale);
			lockon_gizmo_->SetScaleY(lockon_scale);
			lockon_gizmo_->SetScaleZ(lockon_langth);
		}
	}

	// �l�R���|�[�l���g�̍쐬
	{
		// �ő�HP
		max_hp_param_ = NEW FloatParameterComponent(this);
		max_hp_param_->SetParameterType(ParameterType::MaxHP);
		max_hp_param_->SetFloat(max_hit_point_);

		// HP
		hp_param_ = NEW FloatParameterComponent(this);
		hp_param_->SetParameterType(ParameterType::HP);
		hp_param_->SetFloat(hit_point_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Player::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void Player::InputGameObject(void)
{
	// �`���[�W�e�̕���R���|�[�l���g�̊m�F
	if(charge_blaster_ == nullptr)
	{
		assert(!"Player::InputGameObject()�F�`���[�W�e�̕���R���|�[�l���g���Anullptr�ł����I");
	}

	// �e�𔭎˂��邩
	is_blaster_fire_ = InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A);

	// �{�^���𒷉���������
	if (charge_blaster_->IsCheckChargeBulletInstance() == false)
	{
		if (InputCheck::XInputRepeat(PadIndex::Pad1, XInputButton::XIB_A, 2.f))
		{
			charge_blaster_->CreateChargeBullet();
		}
	}

	if (charge_blaster_->IsCheckChargeBulletInstance() == true)
	{
		// �{�^���𗣂�����
		if (charge_blaster_->GetChargeBulletState() == ChargeBulletState::Hold)
		{
			if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_A) == false)
			{
				charge_blaster_->Fire();
			}
		}
	}
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Player::UpdateGameObject(float deltaTime)
{
	// �`���[�W�e�̕���R���|�[�l���g�̊m�F
	if (charge_blaster_ == nullptr)
	{
		assert(!"Player::UpdateWeapon():�`���[�W�e�̕���R���|�[�l���g���Anullptr�ł����I");
	}

	ImGui::Begin("PlayerTransform");
	ImGui::Text("Yaw:%f", transform_component_->GetAngleYaw());
	ImGui::Text("Pitch:%f", transform_component_->GetAnglePitch());
	ImGui::Text("Roll:%f", transform_component_->GetAngleRoll());

	auto pos = *transform_component_->GetPosition();
	ImGui::Text("PosX:%f", pos.x);
	ImGui::Text("PosY:%f", pos.y);
	ImGui::Text("PosZ:%f", pos.z);
	ImGui::End();

	// �l�R���|�[�l���g�̍X�V����
	this->UpdateParameter(deltaTime);

	// ����̍X�V����
	this->UpdateWeapon(deltaTime);

	// �G�t�F�N�g�̍X�V����
	this->UpdatePirticleEffect(deltaTime);

	// �����蔻��̍X�V
	this->UpdateCollision(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �l�R���|�[�l���g�̍X�V����
-----------------------------------------------------------------------------*/
void Player::UpdateParameter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const bool is_nullptr_max_hp_param	= (max_hp_param_ == nullptr);
	const bool is_nullptr_hp_param		= (hp_param_ == nullptr);

	// �ő�HP�̒l�R���|�[�l���g��null�`�F�b�N
	if (is_nullptr_max_hp_param)
	{
		assert(!"Player::UpdateParameter():�l�R���|�[�l���g:max_hp_param_ ���hnullptr�h�ł���");
		return;
	}

	// HP�̒l�R���|�[�l���g��null�`�F�b�N
	if (is_nullptr_hp_param)
	{
		assert(!"Player::UpdateParameter():�l�R���|�[�l���g:hp_param_ ���hnullptr�h�ł���");
		return;
	}

	// �ő�HP�̍X�V
	max_hp_param_->SetFloat(max_hit_point_);

	// ���݂�HP�̍X�V
	hp_param_->SetFloat(hit_point_);
}

/*-----------------------------------------------------------------------------
/* ����̍X�V����
-----------------------------------------------------------------------------*/
void Player::UpdateWeapon(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ����̈ʒu�𒲐�
	{
		left_blaster_->SetTranslation(-1.5f, 0.1f, 1.0f);
		right_blaster_->SetTranslation(1.5f, 0.1f, 1.0f);
		charge_blaster_->SetTranslation(0.f, 0.1f, 3.0f);
	}

	// �e�̔���
	if (is_blaster_fire_)
	{
		left_blaster_->Fire();
		right_blaster_->Fire();
		is_blaster_fire_ = false;
	}
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�̍X�V����
-----------------------------------------------------------------------------*/
void Player::UpdatePirticleEffect(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �G�t�F�N�g�̈ʒu�𒲐�
	{
		effect_after_burner_->SetTranslation(0.f, 0.1f, -1.1f);
	}
}


/*-----------------------------------------------------------------------------
/* �Փ˔���̍X�V����
-----------------------------------------------------------------------------*/
void Player::UpdateCollision(float deltaTime)
{
	if (InputCheck::KeyTrigger(DIK_O))
	{
		hit_point_ = 100.f;
	}

	// HP�̉�����ݒ�
	if (hit_point_ <= 0.f)
	{
		hit_point_ = 0.f;
	}

	// ���Ƀv���C���[���_���[�W���󂯂�܂ł̎��Ԃ��v�Z
	if (damage_recieve_interval_time_ >= MAX_DAMAGE_RECIEVE_INTERVAL_TIME_)
	{
		// ���l�𐳋K��
		damage_recieve_interval_time_ = MAX_DAMAGE_RECIEVE_INTERVAL_TIME_;

		// �_���[�W���󂯂���悤��
		is_received_damage_ = true;
	}
	else
	{
		damage_recieve_interval_time_ += deltaTime;
	}

	// �_���[�W���󂯕t���邩�H
	if (is_received_damage_ == false) { return; }

	// �Փ˔���
	{
		// �{�X�ւ̃|�C���^���擾
		if (boss_ == nullptr)
		{
			auto enemie_list = game_->GetEnemieManager()->GetEnemyGameObjectList();
			for (auto enemy : enemie_list)
			{
				// �{�X����Ȃ�������X�L�b�v
				auto actor_type = enemy->GetType();
				if (actor_type != GameObject::TypeID::Boss) { continue; }

				// �{�X�ւ̃|�C���^���擾
				boss_ = enemy;
			}
		}

		// �{�X����������Ă�����
		if (boss_ != nullptr)
		{
			// �o���b�g�̏Փ˔���
			auto bullets = game_->GetBulletManager()->GetBulletGameObjectList();
			for (auto bullet : bullets)
			{
				// Bullet�̏��L�҂�Player���𒲂ׂ�
				auto bullet_owner_game_object = bullet->GetParentGameObject();

				if (bullet_owner_game_object == nullptr) { continue; }

				// �o���b�g�̏��L�҂𒲂ׂ�
				const bool is_weak_enemy_shoot_bullet = (bullet_owner_game_object->GetType() == GameObject::TypeID::WeakEnemy);
				const bool is_strong_enemy_shoot_bullet = (bullet_owner_game_object->GetType() == GameObject::TypeID::StrongEnemy);
				const bool is_boss_shoot_bullet = (bullet_owner_game_object->GetType() == GameObject::TypeID::Boss);
				if (is_weak_enemy_shoot_bullet || is_strong_enemy_shoot_bullet || is_boss_shoot_bullet)
				{
					// �G�l�~�[�̃o���b�g�̏Փ˔�����擾
					if (CheckCollision::SphereVSSpghre(this->GetSphereCollider(), bullet->GetSphereCollider()))
					{
						// �_���[�W���󂯂����̃G�t�F�N�g���Đ�
						effect_enemy_attack_hit_->Play();

						// �_���[�W���󂯂�SE���Đ�
						player_damege_sound_effect_->Play();

						// �_���[�W�����󂯂�
						hit_point_ += -10.f;

						// �Փ˂����o���b�g��j������
						bullet->SetGameObjectState(State::Dead);
	
						// ���Ƀv���C���[���_���[�W���󂯂�܂ł̎��ԂƏ�Ԃ�������
						damage_recieve_interval_time_ = 0.f;
						is_received_damage_ = false;
						break;

					}
				}
			}

			// �{�X�̑̓�����̏Փ˔���
			if (CheckCollision::ObbVSObb(this->GetOBBCollider(), boss_->GetOBBCollider()))
			{
				// �_���[�W���󂯂����̃G�t�F�N�g���Đ�
				effect_enemy_attack_hit_->Play();

				// �_���[�W���󂯂�SE���Đ�
				player_damege_sound_effect_->Play();

				// �_���[�W�����󂯂�
				hit_point_ += -10.f;

				// ���Ƀv���C���[���_���[�W���󂯂�܂ł̎��ԂƏ�Ԃ�������
				damage_recieve_interval_time_ = 0.f;
				is_received_damage_ = false;
			}

			// �{�X�̑�^���[�U�[�̏Փ˔���
			{
				class Bullet* large_laser = nullptr;

				for (auto bullet : bullets)
				{
					// �o���b�g�̏��L�҂𒲂ׂ�
					const bool is_bullet_large_laser = (bullet->GetType() == GameObject::TypeID::LargeLaser);
					if (is_bullet_large_laser)
					{
						// ���僌�[�U�[���擾
						large_laser = bullet;
						break;
					}
				}

				// �{�X�̑�^���[�U�[�̏Փ˔���
				if (large_laser != nullptr)
				{
					if (CheckCollision::ObbVSObb(this->GetOBBCollider(), large_laser->GetOBBCollider()))
					{
						// �_���[�W���󂯂����̃G�t�F�N�g���Đ�
						effect_enemy_attack_hit_->Play();

						// �_���[�W���󂯂�SE���Đ�
						player_damege_sound_effect_->Play();

						// �_���[�W�����󂯂�
						hit_point_ += -10.f;

						// ���Ƀv���C���[���_���[�W���󂯂�܂ł̎��ԂƏ�Ԃ�������
						damage_recieve_interval_time_ = 0.f;
						is_received_damage_ = false;
					}
				}
			}
		}
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/