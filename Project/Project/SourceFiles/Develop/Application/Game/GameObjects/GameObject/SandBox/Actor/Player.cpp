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

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Player::Player(Game* game)
	: Actor(game)
	, mesh_space_ship_(nullptr)
	, effect_after_burner_(nullptr)
	, left_blaster_(nullptr)
	, right_blaster_(nullptr)
	, box_collider_(nullptr)
	, sphere_collider_(nullptr)
	, box_gizmo_(nullptr)
	, sphere_gizmo_(nullptr)
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
	// �`��R���|�[�l���g
	{
		// ���@�̕\��
		mesh_space_ship_ = NEW FFPMeshRendererComponent(this);
		mesh_space_ship_->SetMesh(XFileMeshType::SpaceShip);
		mesh_space_ship_->SetEnableLighting(true);
		mesh_space_ship_->SetScale(0.5f);

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
		box_collider_ = NEW OBBColliderComponent(this);
		sphere_collider_ = NEW SphereColliderComponent(this);

		box_gizmo_	= NEW BoxGizmoRendererComponent(this);
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
	}

	// �v���C���[�̈ړ��R���|�[�l���g
	move_component_ = NEW  PlayerMoveComponent(this);

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
}

/*=============================================================================
/*		End of File
=============================================================================*/