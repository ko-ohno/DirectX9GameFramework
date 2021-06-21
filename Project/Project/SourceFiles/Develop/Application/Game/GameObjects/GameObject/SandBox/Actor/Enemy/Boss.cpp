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
#include "../../../../Component/AIComponent/BossAIComponent/BossAIComponent.h"

// ���b�V���R���|�[�l���g
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"

// ���̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// �{�b�N�X�̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

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