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

// ���b�V���R���|�[�l���g
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"

// ���̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// �{�b�N�X�̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

#include "../../../../Component/WeaponComponent/BlasterWeaponComponent.h"

// ���̓`�F�b�N
#include "../../../../../Input/InputCheck.h"

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"


#include "../../../../../Game.h"
#include "../../../../../SandBoxManager/ActorManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Boss::Boss(Game* game)
	: Enemy(game)
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

	{
		// �{�X�̃��b�V������
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyBoss);
		actor_mesh_->SetEnableLighting(true);			// ���C�e�B���O��L���ɂ���

		// �������W�𒲐�
		this->transform_component_->SetTranslationZ(15.f);
	}

	// �{�X�̏�Ԃ�������
	{
		auto init_boss_state = EnemyState::Enter;

		// �G�̏�Ԃ�������
		enemy_ai_->SetEnemyState(init_boss_state);
		enemy_move_->SetEnemyState(init_boss_state);
	}

	// �Փ˔���֌W
	{
		// �Փ˔���̍����@�I�t�Z�b�g���W
		const float collider_height_pos = 3.f;

		// ��
		{
			// ���̔��a
			const float sphere_radius_size = 6.f;

			// �Փ˔���
			sphere_collider_ = NEW SphereColliderComponent(this);
			sphere_collider_->SetTranslationY(collider_height_pos);
			sphere_collider_->SetRadius(sphere_radius_size);

			// �M�Y��
			sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
			sphere_gizmo_->SetTranslationY(collider_height_pos);
			sphere_gizmo_->SetScale(sphere_radius_size);
		}

		// ��
		{
			// ���̍���
			const float box_height_size = 1.5f;

			// ���̐������̑傫��
			const float box_size = 16.f;

			// �Փ˔���
			obb_collider_ = NEW OBBColliderComponent(this);
			obb_collider_->SetTranslationY(collider_height_pos);
			obb_collider_->SetDirLength(box_size	   , AxisType::X);
			obb_collider_->SetDirLength(box_height_size, AxisType::Y);
			obb_collider_->SetDirLength(box_size	   , AxisType::Z);

			// �M�Y��
			box_gizmo_ = NEW BoxGizmoRendererComponent(this);
			box_gizmo_->SetTranslationY(collider_height_pos);
			box_gizmo_->AddScaleX(box_size);
			box_gizmo_->AddScaleY(box_height_size);
			box_gizmo_->AddScaleZ(box_size);
		}
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
	UNREFERENCED_PARAMETER(deltaTime);

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

}

/*=============================================================================
/*		End of File
=============================================================================*/