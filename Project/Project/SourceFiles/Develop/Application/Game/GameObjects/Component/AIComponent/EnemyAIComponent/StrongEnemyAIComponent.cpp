/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyAIComponent.cpp] �{�XAI�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�XAI�R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "StrongEnemyAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemyAIComponent::StrongEnemyAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, boss_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemyAIComponent::~StrongEnemyAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool StrongEnemyAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Uninit(void)
{
	// �X�e�[�g�}�V�����폜
	SAFE_DELETE_(boss_state_machine_);
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �G�̃X�e�[�g�𑀍삷��
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
	//		assert(!"StrongEnemyAIComponent::Update()�F�{�X��AI���s���ȏ�Ԃł��I");
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
	//	assert(!"StrongEnemyAIComponent::Update()�F�{�X��AI���s���ȏ�Ԃł��I");
	//	break;
	//}

	// ����AI�̃X�e�[�g�}�V����nullptr���H
	//if (boss_state_machine_ != nullptr)
	//{
	//	boss_state_machine_->Update(this, deltaTime);
	//}
}

/*=============================================================================
/*		End of File
=============================================================================*/