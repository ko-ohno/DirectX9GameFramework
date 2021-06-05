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

#include "../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"

// ����R���|�[�l���g
#include "../../../Component/WeaponComponent/BlasterComponent.h"

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
	, left_blaster_(nullptr)
	, right_blaster_(nullptr)
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
	actor_move_ = NEW  PlayerMoveComponent(this);

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
	}

	// ����R���|�[�l���g
	{
		// ���̌����e
		left_blaster_ = NEW BlasterComponent(this);

		// �E�̌����e
		right_blaster_ = NEW BlasterComponent(this);
	}

	//�@�Փ˔���R���|�[�l���g
	{
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_gizmo_->SetVertexColor(255, 255, 0, 255);

		obb_collider_ = NEW OBBColliderComponent(this);
		box_gizmo_ = NEW BoxGizmoRendererComponent(this);
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
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Player::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �G�t�F�N�g�̈ʒu�𒲐�
	effect_after_burner_->SetTranslation(0.f, 0.1f, -1.1f);

	// ����̈ʒu�𒲐�
	{
		left_blaster_->SetTranslation(-1.5f, 0.1f, 1.0f);
		right_blaster_->SetTranslation(1.5f, 0.1f, 1.0f);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
	{
		left_blaster_->Fire();
		right_blaster_->Fire();
	}


	ImGui::Begin("PlayerTransform");
	ImGui::Text("Yaw:%f", transform_component_->GetAngleYaw());
	ImGui::Text("Pitch:%f", transform_component_->GetAnglePitch());
	ImGui::Text("Roll:%f", transform_component_->GetAngleRoll());
	ImGui::End();
}

/*=============================================================================
/*		End of File
=============================================================================*/