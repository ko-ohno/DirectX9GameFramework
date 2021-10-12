/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBlasterWeaponComponent.cpp] �����e����R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e����R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "ChargeBlasterWeaponComponent.h"
#include "../../../Game.h"

// �`��R���|�[�l���g
#include "../../Component/RendererComponent/BillboardRendererComponent.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"

// �Փ˔���R���|�[�l���g
#include "../../Component/AudioComponent.h"

// �Փ˔���R���|�[�l���g
#include "../../Component/ColliderComponent/OBBColliderComponent.h"

// �M�Y���R���|�[�l���g
#include "../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

// �Q�[���I�u�W�F�N�g�֘A
#include "../../GameObject.h"
#include "../../GameObject/SandBox/Bullet/ChargeBullet.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../SandBoxManager/EnemieManager.h"

//�Փ˔���n
#include "../../../CheckCollision.h"

// ���͌n
#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ChargeBlasterWeaponComponent::ChargeBlasterWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, is_bullet_created_(false)
	, is_fire_(false)
	, target_enemy_(nullptr)
	, is_enable_lockon_(false)
	, lockon_release_time_(0.f)
	, lockon_reticle_animation_time_(0.f)
	, lockon_reticle_hud_animation_time_(0.f)
	, lockon_reticle_src_pos_(0.f, 0.f, 0.f)
	, lockon_reticle_dst_pos_(0.f, 0.f, 0.f)
	, charge_bullet_(nullptr)
	, muzzle_flash_(nullptr)
	, lockon_reticle_(nullptr)
	, lockon_reticle_owner_transform_order_(nullptr)
	, lockon_alert_se_(nullptr)
	, lockon_collider_(nullptr)
	, lockon_gizmo_(nullptr)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ChargeBlasterWeaponComponent::~ChargeBlasterWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool ChargeBlasterWeaponComponent::Init(void)
{
	// �`��R���|�[�l���g�̐���
	{
		
		// �e�̔��ˌ��̐���
		{
			muzzle_flash_ = NEW EffectRendererComponent(owner_);
			muzzle_flash_->SetEffect(EffectType::ChargeBulletState3Fire);
			muzzle_flash_->SetScale(0.5f);
		}

		//�@���b�N�I���̃��e�B�N���̐���
		{
			lockon_reticle_ = NEW BillboardRendererComponent(owner_, 290);
			lockon_reticle_->SetTexture(TextureType::NearReticle);
			lockon_reticle_->SetVertexColor(0, 255, 0, 255);
			lockon_reticle_->SetRendererLayerType(RendererLayerType::UI);
			lockon_reticle_->IsSetDrawable(false);

			// ���e�B�N���̐����̒���
			lockon_reticle_->SetScaleX(1.4f);
			lockon_reticle_->SetScaleY(1.4f);
			lockon_reticle_->SetTranslationZ(9.f);
		}

		// ���L�҂̎p���̉e�����󂯂郍�b�N�I���̃��e�B�N���̐���
		{
			// �����Ƃ��ĕ`�悷��
			lockon_reticle_owner_transform_order_ = NEW BillboardRendererComponent(owner_, 290);
			lockon_reticle_owner_transform_order_->SetTexture(TextureType::NearReticle);
			lockon_reticle_->SetVertexColor(0, 0, 0, 0);
			lockon_reticle_owner_transform_order_->SetRendererLayerType(RendererLayerType::UI);

			// ���e�B�N���̐����̒���
			lockon_reticle_owner_transform_order_->SetScale(1.4f);
			lockon_reticle_owner_transform_order_->SetTranslationZ(9.f);

			// �`�悵�Ȃ��悤�ɐݒ�
			lockon_reticle_owner_transform_order_->IsSetDrawable(false);
		}
	}

	// �����R���|�[�l���g�̐���
	{
		lockon_alert_se_ = NEW AudioComponent(owner_);
		lockon_alert_se_->SetSound(SoundType::LockonAlert);
	}

	// ���b�N�I���̔��̏Փ˔���
	{
		const float lockon_langth = 20.f;
		const float lockon_scale = 0.5f;

		lockon_collider_ = NEW OBBColliderComponent(owner_);
		lockon_collider_->SetDirLength(lockon_scale, AxisType::X);
		lockon_collider_->SetDirLength(lockon_scale, AxisType::Y);
		lockon_collider_->SetDirLength(lockon_langth, AxisType::Z);

		lockon_gizmo_ = NEW BoxGizmoRendererComponent(owner_);
		lockon_gizmo_->SetVertexColor(0, 255, 255, 128);
		lockon_gizmo_->SetScaleX(lockon_scale);
		lockon_gizmo_->SetScaleY(lockon_scale);
		lockon_gizmo_->SetScaleZ(lockon_langth);
	}

	// �M�Y���̐���
	{
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(owner_);
		sphere_gizmo_->SetScale(0.5f);
		sphere_gizmo_->SetVertexColor(0, 255, 255);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//�@���e�B�N����`�悷�邩�H
	{
		bool is_draw_reticle = false;

		auto game_state = owner_->GetGame()->GetGameState();
		if (game_state == Game::GameState::Gameplay)
		{
			is_draw_reticle = true;
		}
		lockon_reticle_->IsSetDrawable(is_draw_reticle);
	}


	if (charge_bullet_ != nullptr)
	{
		// ���s�ړ����̍쐬
		D3DXMATRIX translation_matrix;
		D3DXMatrixIdentity(&translation_matrix);
		{
			translation_matrix._41 = position_.x;
			translation_matrix._42 = position_.y;
			translation_matrix._43 = position_.z;

			// ���L�҂̎p�����ƍ�������
			translation_matrix = translation_matrix * *owner_transform_->GetWorldMatrix();
		}


#ifdef DEBUG_MODE_
		ImGui::Begin("BulletCreatePos");
		ImGui::Text("posX:%f", translation_matrix._41);
		ImGui::Text("posY:%f", translation_matrix._42);
		ImGui::Text("posZ:%f", translation_matrix._43);
		ImGui::End();
#endif

		if (charge_bullet_->GetChargeBulletState() <= ChargeBulletState::Hold)
		{
			// �e�̍��W���X�V
			charge_bullet_->SetTranslation(translation_matrix._41, translation_matrix._42, translation_matrix._43);
		}

		if (charge_bullet_->GetChargeBulletState() == ChargeBulletState::Fire)
		{
			if (is_fire_ == false)
			{	
				// �G�t�F�N�g�Đ����X�V
				muzzle_flash_->Play();
				is_fire_ = true;
			}
		}

		// �`���[�W�e�̏�Ԃ��m�F
		if (charge_bullet_->GetChargeBulletState() == ChargeBulletState::End)
		{
			charge_bullet_->SetGameObjectState(GameObject::State::Dead);

			// �o���b�g�𐶐������L����������
			is_bullet_created_ = false;

			// �o���b�g�̃|�C���^��������
			charge_bullet_ = nullptr;

			// �o���b�g�𔭎˂����L����������
			is_fire_ = false;
		}
	}

	// ���b�N�I���̕W�I���X�V
	this->UpdateLockonTarget(deltaTime);

	// �M�Y���̍X�V
	{
		sphere_gizmo_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/*�@�`���[�W�e�̔��ˏ���
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::CreateChargeBullet(void)
{
	//// ���s�ړ����̍쐬
	D3DXMATRIX translation_matrix;
	D3DXMatrixIdentity(&translation_matrix);
	{
		translation_matrix._41 = position_.x;
		translation_matrix._42 = position_.y;
		translation_matrix._43 = position_.z;

		// ���L�҂̎p�����ƍ�������
		translation_matrix = translation_matrix * *owner_transform_->GetWorldMatrix();
	}

	// �e�ۂ̐���
	{
		if (is_bullet_created_ == true) { return; }
		
		// �o���b�g�̐�������
		charge_bullet_ = NEW ChargeBullet(owner_->GetGame());
		charge_bullet_->SetParentGameObject(owner_);
		charge_bullet_->SetTranslation(translation_matrix._41, translation_matrix._42, translation_matrix._43);

		// �o���b�g�𐶐��������Ƃ��L��
		is_bullet_created_ = true;
	}
}

/*-----------------------------------------------------------------------------
/*�@���ˏ���
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Fire(void)
{	
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::ChargeBulletFire()�F�`���[�W�e�̃C���X�^���X����������Ă��܂���I");
	}
	charge_bullet_->Fire();	// �`���[�W�e�̔���
}

/*-----------------------------------------------------------------------------
/*�@���b�N�I���̕W�I���X�V
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::UpdateLockonTarget(float deltaTime)
{
	//�@�W�I�̏�Ԃ��m�F
	if (target_enemy_ != nullptr)
	{
		// �j�󂳂ꂽ�Q�[���I�u�W�F�N�g�����m�F
		auto target_enemy_game_object_state = target_enemy_->GetGameObjectState();
		const bool is_destroyed = ((target_enemy_game_object_state == GameObject::State::Destroy)
								  || (target_enemy_game_object_state == GameObject::State::Dead));

		if (is_destroyed == true)
		{
			// �^�[�Q�b�g����O��
			target_enemy_ = nullptr;
		}
	}

	// ���b�N�I���̏Փ˔���
	{
		// �`���[�W�e�̃C���X�^���X�����邩�H
		if (charge_bullet_ != nullptr)
		{
			// �`���[�W�e�𔭎˂�����ق��̃^�[�Q�b�g�����b�N�I�����Ȃ�
			auto charge_bullet_state = charge_bullet_->GetChargeBulletState();
			if (charge_bullet_state >= ChargeBulletState::Bullet)
			{
				// ���˂����烌�e�B�N���̐F��ԂɎw��
				lockon_reticle_->SetVertexColor(255, 0, 0);
				lockon_reticle_->SetScale(1.f);
				return;
			}

			// �G�l�~�[�̃��X�g���擾
			auto enemy_list = owner_->GetGame()->GetEnemieManager()->GetEnemyGameObjectList();
			for (auto enemy : enemy_list)
			{
				// �G�l�~�[�̏�Ԃ��擾
				auto enemy_game_object_state = enemy->GetGameObjectState();

				// �j�󒆂⎀�S����������Փ˔�������Ȃ�
				if (enemy_game_object_state == GameObject::State::Destroy) { continue; }
				if (enemy_game_object_state == GameObject::State::Dead) { continue; }

				// ���b�N�I���̏Փ˔���
				if (CheckCollision::ObbVSObb(this->lockon_collider_, enemy->GetOBBCollider()))
				{
					// ���b�N�I������������܂ł̎��Ԃ����Z�b�g
					lockon_release_time_ = 0.f;

					// ���b�N�I���L����
					is_enable_lockon_ = true;

					// ���b�N�I�������^�[�Q�b�g�̃C���X�^���X�����݂̕W�I�ƈႤ�ꍇ
					if (target_enemy_ != enemy)
					{
						lockon_alert_se_->Play();
					}

					// �W�I�ւ̃|�C���^���擾
					target_enemy_ = enemy;
					break;
				}
				else
				{
					// ���b�N�I������������܂ł̎��Ԃ��v�Z
					lockon_release_time_ += deltaTime;
					if (lockon_release_time_ >= MAX_LOCKON_RELEASE_TIME_)
					{
						// ���݂̃C���^�[�o���̏����ݒ�
						lockon_release_time_ = MAX_LOCKON_RELEASE_TIME_;

						// ���b�N�I��������
						is_enable_lockon_ = false;
					}
				}
			}
		}
		else
		{
			// ���b�N�I��������
			is_enable_lockon_ = false;
		}
	}

	// ���b�N�I�������H
	if (is_enable_lockon_)
	{
		 // �v���C���[�̎p���̉e�����펞�󂯂Ă��郌�e�B�N������A��Ԃ̎n�_���W���擾
		lockon_reticle_src_pos_ = *lockon_reticle_owner_transform_order_->GetPosition() + *owner_->GetTransform()->GetPosition();

		// ��Ԃ̏I�_���W�̍X�V
		if (target_enemy_ != nullptr)
		{
			auto enemy_game_object_state = target_enemy_->GetGameObjectState();
			const bool is_not_state_destroy = (enemy_game_object_state != GameObject::State::Destroy);
			const bool is_not_state_dead	= (enemy_game_object_state != GameObject::State::Dead);
			if (is_not_state_destroy || is_not_state_dead)
			{
				auto game_object_type = target_enemy_->GetType();;
				if (game_object_type == GameObject::TypeID::Boss)
				{
					// �{�X�̃��f�������_�Y�����N�����Ă��邽�߁A�ړI�n���W���I�t�Z�b�g���Đݒ�
					lockon_reticle_dst_pos_ = *target_enemy_->GetTransform()->GetPosition();

					// Y���W���I�t�Z�b�g
					lockon_reticle_dst_pos_.y += 1.f;
				}
				else
				{
					// �ړI�n���W��ݒ�
					lockon_reticle_dst_pos_ = *target_enemy_->GetTransform()->GetPosition();
				}
			}
		}
		else
		{
			lockon_reticle_dst_pos_ = { 0.f, 0.f, 0.f };
		}

		// ���e�B�N���̏�Ԃ�ݒ�
		{
			// ���e�B�N���̈ʒu����
			D3DXVECTOR3 reticle_position = { 0.f, 0.f, 0.f };
			D3DXVec3Lerp(&reticle_position, &lockon_reticle_src_pos_, &lockon_reticle_dst_pos_, Easing::SineInOut(lockon_reticle_animation_time_, MAX_LOCKON_RETICLE_ANIMATION_TIME_));

			// ���b�N�I���̃A�j���[�V�������Ԃ̌v�Z
			lockon_reticle_animation_time_ += deltaTime;
			if (lockon_reticle_animation_time_ >= MAX_LOCKON_RETICLE_ANIMATION_TIME_)
			{
				lockon_reticle_animation_time_ = MAX_LOCKON_RETICLE_ANIMATION_TIME_;
			}

			// ���b�N�I����HUD�̃A�j���[�V�������Ԃ̌v�Z
			lockon_reticle_hud_animation_time_ += deltaTime;
			if (lockon_reticle_hud_animation_time_ >= MAX_LOCKON_RETICLE_HUD_ANIMATION_TIME_)
			{
				lockon_reticle_hud_animation_time_ = 0.f;
			}

			// ���b�N�I����HUD���g�k����A�j���[�V����
			float scale = Math::Lerp(1.9f, 1.4f, lockon_reticle_hud_animation_time_);
			lockon_reticle_->SetScale(scale);

			// ���b�N�I���̃��e�B�N���̐F���X�V
			const int red   = static_cast<int>(Math::Lerp(255.f, 255.f, Easing::SineInOut(lockon_reticle_hud_animation_time_)));
			const int green = static_cast<int>(Math::Lerp(255.f,   0.f, Easing::SineInOut(lockon_reticle_hud_animation_time_)));
			const int bule  = static_cast<int>(Math::Lerp(  0.f,   0.f, Easing::SineInOut(lockon_reticle_hud_animation_time_)));
			lockon_reticle_->SetVertexColor(red, green, bule);															  

			// �R���|�[�l���g�̏��L�҂̎p������̉e�����󂯂Ȃ��悤�ɐݒ�
			lockon_reticle_->IsSetOwnerTransfromOrder(false);

			// ���b�N�I���̃��e�B�N���̈ʒu�����X�V
			lockon_reticle_->SetTranslation(reticle_position);
		}

		// �`���[�W�e�̏�Ԃ�ݒ�
		if (charge_bullet_ != nullptr)
		{
			// ���b�N�I���̃^�[�Q�b�g���`���[�W�e�ɒʒm
			charge_bullet_->SetLockonTargetEnemy(target_enemy_);

			// ���b�N�I���������Ƃ�ʒm
			charge_bullet_->IsSetLockon(true);
		}
	}
	else
	{
		// ���e�B�N���̏�Ԃ�ݒ�
		{
			// ���b�N�I���̃��e�B�N���̐F���X�V
			lockon_reticle_->SetVertexColor(0, 255, 0);
		
			// �R���|�[�l���g�̏��L�҂̎p������̉e�����󂯂�悤�ɐݒ�
			lockon_reticle_->IsSetOwnerTransfromOrder(true);

			// �g�k�l��������
			lockon_reticle_->SetScale(1.4f);

			// ���b�N�I���̃��e�B�N���̈ʒu�����X�V
			lockon_reticle_->SetTranslation(0.f, 0.f, 9.f);

			// ���e�B�N���̃A�j���[�V�������Ԃ��ď�����
			lockon_reticle_animation_time_ = 0.f;
		}

		// �`���[�W�e�̏�Ԃ�ݒ�
		if (charge_bullet_ != nullptr)
		{
			// ���b�N�I���������Ƃ�ʒm
			charge_bullet_->IsSetLockon(false);
		}
	}
}

/*-----------------------------------------------------------------------------
/*�@�`���[�W�e�̃C���X�^���X�����邩�m�F
-----------------------------------------------------------------------------*/
bool ChargeBlasterWeaponComponent::IsCheckChargeBulletInstance(void)
{
	if (charge_bullet_ == nullptr) { return false; }
	return true;
}

/*-----------------------------------------------------------------------------
/*�@�`���[�W�e�̏�Ԃ̎擾����
-----------------------------------------------------------------------------*/
ChargeBulletState ChargeBlasterWeaponComponent::GetChargeBulletState(void)
{
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::GetChargeBulletState()�F�`���[�W�e�̃C���X�^���X����������Ă��܂���I");
	}
	return charge_bullet_->GetChargeBulletState();
}

/*-----------------------------------------------------------------------------
/*�@�`���[�W�e�̏�Ԃ̐ݒ菈��
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::SetChargeBulletState(ChargeBulletState chargeBulletState)
{
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::SetChargeBulletState()�F�`���[�W�e�̃C���X�^���X����������Ă��܂���I");
	}
	charge_bullet_->SetChargeBulletState(chargeBulletState);
}

/*=============================================================================
/*		End of File
=============================================================================*/