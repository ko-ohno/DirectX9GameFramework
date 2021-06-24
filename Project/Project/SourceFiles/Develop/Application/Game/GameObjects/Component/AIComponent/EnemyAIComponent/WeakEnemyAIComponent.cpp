/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyAIComponent.cpp] �{�XAI�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�XAI�R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "WeakEnemyAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
WeakEnemyAIComponent::WeakEnemyAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, boss_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
WeakEnemyAIComponent::~WeakEnemyAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool WeakEnemyAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Uninit(void)
{
	// �X�e�[�g�}�V�����폜
	SAFE_DELETE_(boss_state_machine_);
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//// �G�̃X�e�[�g�𑀍삷��
	//this->EnemyStateController();
	//
	//ImGui::Begin("boss_ai_state");

	//{
	//	switch (enemy_state_)
	//	{
	//	case EnemyState::Wait:
	//		ImGui::Text("wait");
	//		this->ChangeState(NEW BossStateWait());
	//		break;

	//	case EnemyState::Enter:
	//		ImGui::Text("enter");
	//		this->ChangeState(NEW BossStateEnter());
	//		break;

	//	case EnemyState::BodyPress:
	//		ImGui::Text("body_press");
	//		this->ChangeState(NEW BossStateBodyPress());
	//		break;

	//	case EnemyState::Shooting:
	//		ImGui::Text("shooting");
	//		this->ChangeState(NEW BossStateShooting());
	//		break;

	//	case EnemyState::LaserCannon:
	//		ImGui::Text("laser_cannon");
	//		this->ChangeState(NEW BossStateLaserCannon());
	//		break;

	//	case EnemyState::Destroy:
	//		break;

	//	default:
	//		assert(!"WeakEnemyAIComponent::Update()�F�{�X��AI���s���ȏ�Ԃł��I");
	//		break;
	//	}
	//}
	//ImGui::End();

	//switch (enemy_state_)
	//{
	//case EnemyState::Wait:
	//	this->ChangeState(NEW BossStateWait());
	//	break;

	//case EnemyState::Enter:
	//	this->ChangeState(NEW BossStateEnter());
	//	break;

	//case EnemyState::BodyPress:
	//	this->ChangeState(NEW BossStateBodyPress());
	//	break;

	//case EnemyState::Shooting:
	//	this->ChangeState(NEW BossStateShooting());
	//	break;

	//case EnemyState::LaserCannon:
	//	this->ChangeState(NEW BossStateLaserCannon());
	//	break;

	//case EnemyState::Destroy:
	//	break;

	//default:
	//	assert(!"WeakEnemyAIComponent::Update()�F�{�X��AI���s���ȏ�Ԃł��I");
	//	break;
	//}

	//// ����AI�̃X�e�[�g�}�V����nullptr���H
	//if (boss_state_machine_ != nullptr)
	//{
	//	boss_state_machine_->Update(this, deltaTime);
	//}
}

///*-----------------------------------------------------------------------------
///*�@�X�V����
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::EnemyStateController(void)
//{
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_Y))
//	{
//		this->SetEnemyState(EnemyState::Enter);
//	}
//
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_LEFT_SHOULDER))
//	{
//		this->SetEnemyState(EnemyState::Wait);
//	}
//
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_LEFT_TRIGGER))
//	{
//		this->SetEnemyState(EnemyState::BodyPress);
//	}
//
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_RIGHT_SHOULDER))
//	{
//		this->SetEnemyState(EnemyState::Shooting);
//	}
//
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_RIGHT_TRIGGER))
//	{
//		this->SetEnemyState(EnemyState::LaserCannon);
//	}
//}
//
///*-----------------------------------------------------------------------------
///*�@�{�X�̃X�e�[�g�}�V���̕ύX
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::ChangeState(BossStateMachine* bossStateMachine)
//{
//	if (boss_state_machine_ != nullptr)
//		delete boss_state_machine_;
//
//	boss_state_machine_ = bossStateMachine;
//
//	if (boss_state_machine_ != nullptr)
//		boss_state_machine_->Init();
//}
//
///*-----------------------------------------------------------------------------
///*�@�{�X�̑ҋ@�s��
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::Wait(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//}
//
///*-----------------------------------------------------------------------------
///*�@�{�X�̓o��s��
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::Enter(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//
//	if (motion_state_ == EnemyMotionState::End)
//	{
//		enemy_state_ = EnemyState::Wait;
//	}
//}
//
///*-----------------------------------------------------------------------------
///*�@�{�X�̑̓�����s��
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::BodyPress(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//
//	if (motion_state_ == EnemyMotionState::End)
//	{
//		enemy_state_ = EnemyState::Wait;
//	}
//}
//
///*-----------------------------------------------------------------------------
///*�@�{�X�̎ˌ��U���s��
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::Shoot(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//
//	if (motion_state_ == EnemyMotionState::End)
//	{
//		enemy_state_ = EnemyState::Wait;
//	}
//}
//
///*-----------------------------------------------------------------------------
///*�@�{�X�̃��[�U�[�C�U���s��
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::LaserCannon(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//
//	if (motion_state_ == EnemyMotionState::End)
//	{
//		enemy_state_ = EnemyState::Wait;
//	}
//}

/*=============================================================================
/*		End of File
=============================================================================*/