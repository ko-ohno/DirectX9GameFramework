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
		// AI�̏��L�҂�ʒm
		enemy_ai_->SetEnemyAIOwner(this);

		// �ړ��R���|�[�l���g��ʒm
		enemy_ai_->SetOwnerMoveComponent(this->enemy_move_);

		// �G�̏�Ԃ�������
		this->SetEnemyState(EnemyState::Enter);
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

	// AI�R���|�[�l���g����G�̍s����Ԃ��擾
	auto ai_state = enemy_ai_->GetEnemyState();
	{
		// AI�R���|�[�l���g�̏�񂩂�A���̈ړ����[�V���������肷��
	}



	// �ړ��R���|�[�l���g����ړ����[�V������Ԃ��擾
	auto move_motion_state = enemy_move_->GetEnemyMotionState();
	{
		// �ړ��R���|�[�l���g�̏�񂩂�A���̈ړ����[�V���������肷��
	}


	//boss_ai_->ChangeState(NEW BossStateEnter());
	//boss_ai_->ChangeState(NEW BossStateWait());
	//boss_ai_->ChangeState(NEW BossStateBodyblow());
	//boss_ai_->ChangeState(NEW BossStateShoot());
	//boss_ai_->ChangeState(NEW BossStateLaserCannon());

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_Y))
	{
		this->SetEnemyState(EnemyState::Enter);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_LEFT_SHOULDER))
	{
		this->SetEnemyState(EnemyState::Wait);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_LEFT_TRIGGER))
	{
		this->SetEnemyState(EnemyState::BodyPress);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_RIGHT_SHOULDER))
	{
		this->SetEnemyState(EnemyState::Shooting);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_RIGHT_TRIGGER))
	{
		this->SetEnemyState(EnemyState::LaserCannon);
	}

	//// �G�l�~�[�̏�ԃX�e�[�g
	//{
	//	switch (enemy_state_)
	//	{
	//	case EnemyState::Wait:
	//		enemy_move_->SetMoveActionState(EnemyState::Wait);
	//		break;
	//
	//	case EnemyState::Enter:
	//		enemy_move_->SetMoveActionState(EnemyState::Enter);
	//		break;

	//	case EnemyState::BodyPress:
	//		enemy_move_->SetMoveActionState(EnemyState::BodyPress);
	//		break;

	//	case EnemyState::Shooting:
	//		enemy_move_->SetMoveActionState(EnemyState::Shooting);
	//		break;

	//	case EnemyState::LaserCannon:
	//		enemy_move_->SetMoveActionState(EnemyState::LaserCannon);
	//		break;

	//	case EnemyState::Destroy:
	//		// �|���ꂽ�Ƃ��̃��[�V����
	//		enemy_move_->SetMoveActionState(EnemyState::Wait);
	//		break;

	//	default:
	//		assert(!"Boss::UpdateGameObject()�F�{�X���s���ȏ�Ԃ����Ă��܂��I");
	//		break;
	//	}
	//}

	//// ���g�̏�Ԃ�AI�ɒʒm
	//{
	//	if (enemy_move_->GetEnemyMotionState() == EnemyMotionState::End)
	//	{
	//		boss_ai_->SetEnemyState(EnemyState::Wait);
	//	}
	//	
	//	boss_ai_->SetHitPoint(this->GetHitPoint());
	//	this->SetEnemyState(boss_ai_->GetEnemyState());
	//}
}

/*=============================================================================
/*		End of File
=============================================================================*/