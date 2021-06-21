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
#include "../../../../Input/InputCheck.h"

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
	// �X�e�[�g�}�V�����폜
	SAFE_DELETE_(boss_state_machine_);
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

	// ����AI�̃X�e�[�g�}�V����nullptr���H
	if (boss_state_machine_ != nullptr)
	{
		boss_state_machine_->Update(this, deltaTime);
	}

	// �G�̃X�e�[�g�𑀍삷��
	this->EnemyStateController();
	{
		switch (enemy_state_)
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
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void BossAIComponent::EnemyStateController(void)
{
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
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̓o��s��
-----------------------------------------------------------------------------*/
void BossAIComponent::Enter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Wait;
	}
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̑̓�����s��
-----------------------------------------------------------------------------*/
void BossAIComponent::BodyPress(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Wait;
	}
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̎ˌ��U���s��
-----------------------------------------------------------------------------*/
void BossAIComponent::Shoot(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Wait;
	}
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̃��[�U�[�C�U���s��
-----------------------------------------------------------------------------*/
void BossAIComponent::LaserCannon(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Wait;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/