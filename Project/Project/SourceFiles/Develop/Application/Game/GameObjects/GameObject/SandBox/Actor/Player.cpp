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
#include "../ChargeBullet.h"

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

// �M�Y���R���|�[�l���g
#include "../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

// ���̓R���|�[�l���g 
#include "../../../../Input/InputCheck.h"

// ImGUI
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Player::Player(Game* game)
	: Actor(game)
	, effect_after_burner_(nullptr)
	, near_reticle_(nullptr)
	, far_reticle_(nullptr)
	, lockon_reticle_(nullptr)
	, left_blaster_(nullptr)
	, right_blaster_(nullptr)
	, charge_blaster_(nullptr)
	, is_blaster_fire_(false)
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

		// �A�t�^�[�o�[�i�[�̕\��
		effect_after_burner_ = NEW EffectRendererComponent(this);
		effect_after_burner_->SetEffect(EffectType::AfterBurner);
		effect_after_burner_->Play();

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
				//near_reticle_->GetPosition();
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
		// ���̏Փ˔���
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_gizmo_->SetVertexColor(255, 255, 0, 255);

		// OBB�̏Փ˔���
		obb_collider_ = NEW OBBColliderComponent(this);
		box_gizmo_ = NEW BoxGizmoRendererComponent(this);

		// ���b�N�I���̔��̏Փ˔���
		{
			const float lockon_langth_ = 20.f;

			lockon_collider_ = NEW OBBColliderComponent(this);
			lockon_collider_->SetDirLength(1.1f, AxisType::X);
			lockon_collider_->SetDirLength(1.1f, AxisType::Y);
			lockon_collider_->SetDirLength(lockon_langth_, AxisType::Z);

			lockon_gizmo_ = NEW BoxGizmoRendererComponent(this);
			lockon_gizmo_->SetVertexColor(0, 255, 255, 128);
			lockon_gizmo_->SetScaleX(1.1f);
			lockon_gizmo_->SetScaleY(1.1f);
			lockon_gizmo_->SetScaleZ(lockon_langth_);
		}
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

	// ����̍X�V����
	this->UpdateWeapon(deltaTime);

	// �G�t�F�N�g�̍X�V����
	this->UpdatePirticleEffect(deltaTime);

	ImGui::Begin("PlayerTransform");
	ImGui::Text("Yaw:%f", transform_component_->GetAngleYaw());
	ImGui::Text("Pitch:%f", transform_component_->GetAnglePitch());
	ImGui::Text("Roll:%f", transform_component_->GetAngleRoll());

	auto pos = *transform_component_->GetPosition();
	ImGui::Text("PosX:%f", pos.x);
	ImGui::Text("PosY:%f", pos.y);
	ImGui::Text("PosZ:%f", pos.z);

	ImGui::End();
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

/*=============================================================================
/*		End of File
=============================================================================*/