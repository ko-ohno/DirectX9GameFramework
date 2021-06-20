/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossAIComponent.cpp] �{�XAI�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�XAI�R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "BossAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BossAIComponent::BossAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, boss_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
BossAIComponent::~BossAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool BossAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void BossAIComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void BossAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void BossAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ����AI�̏��L�҂�nullptr���H
	if (ai_owner_ != nullptr)
	{
		// �{�X�̏�Ԃ�J��
		auto enemy_state = ai_owner_->GetEnemyState();
		{
			switch (enemy_state)
			{
			case EnemyState::Wait:
				this->ChangeState(NEW BossStateWait());
				break;

			case EnemyState::Enter:
				this->ChangeState(NEW BossStateEnter());
				break;

			case EnemyState::BodyPress:
				this->ChangeState(NEW BossStateBodyPress());
				break;

			case EnemyState::Shooting:
				this->ChangeState(NEW BossStateShooting());
				break;

			case EnemyState::LaserCannon:
				this->ChangeState(NEW BossStateLaserCannon());
				break;

			case EnemyState::Destroy:
				break;

			default:
				assert(!"BossAIComponent::Update()�F�{�X��AI���s���ȏ�Ԃł��I");
				break;
			}
		}

		// ����AI�̏��L�҂��ړ��R���|�[�l���g��nullptr���H
		if (enemy_move_ != nullptr)
		{
			if (enemy_move_->GetEnemyMotionState() == EnemyMotionState::End)
			{
				ai_owner_->SetEnemyState(EnemyState::Wait);
			}
			enemy_move_->SetEnemyState(enemy_state);
		}
	}

	// ����AI�̃X�e�[�g�}�V����nullptr���H
	if (boss_state_machine_ != nullptr)
	{
		boss_state_machine_->Update(this, deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̃X�e�[�g�}�V���̕ύX
-----------------------------------------------------------------------------*/
void BossAIComponent::ChangeState(BossStateMachine* bossStateMachine)
{
	if (boss_state_machine_ != nullptr)
		delete boss_state_machine_;

	boss_state_machine_ = bossStateMachine;

	if (boss_state_machine_ != nullptr)
		boss_state_machine_->Init();
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void BossAIComponent::Wait(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	enemy_move_->SetEnemyState(EnemyState::Wait);
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̓o��s��
-----------------------------------------------------------------------------*/
void BossAIComponent::Enter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	enemy_move_->SetEnemyState(EnemyState::Enter);
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̑̓�����s��
-----------------------------------------------------------------------------*/
void BossAIComponent::BodyPress(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	enemy_move_->SetEnemyState(EnemyState::BodyPress);
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̎ˌ��U���s��
-----------------------------------------------------------------------------*/
void BossAIComponent::Shoot(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	enemy_move_->SetEnemyState(EnemyState::Shooting);
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̃��[�U�[�C�U���s��
-----------------------------------------------------------------------------*/
void BossAIComponent::LaserCannon(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	enemy_move_->SetEnemyState(EnemyState::LaserCannon);
}

/*=============================================================================
/*		End of File
=============================================================================*/