/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyMoveComponent.cpp] �{�X�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�̈ړ��R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "WeakEnemyMoveComponent.h"
#include "../../../GameObject.h"
#include "../../../../../Math.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
WeakEnemyMoveComponent::WeakEnemyMoveComponent(GameObject* owner, int updateOrder)
	: EnemyMoveComponent(owner, updateOrder)
	, position_(0.f, 0.f, 0.f)
	, yaw_(0.f)
	, pitch_(0.f)
	, roll_(0.f)
	, execute_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^ 
-----------------------------------------------------------------------------*/
WeakEnemyMoveComponent::~WeakEnemyMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool WeakEnemyMoveComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �e��]�l�̎擾
	yaw_   = owner_transform_->GetAngleYaw();
	pitch_ = owner_transform_->GetAnglePitch();
	roll_  = owner_transform_->GetAngleRoll();

	// ���`���ʕۊǂ��s���t���O��ON��
	{
		owner_transform_->IsSetExecuteSlerp(true);
	}

	// ���g�̏�Ԃ�\�L
	ImGui::Begin("boss_move_state");
	{
		switch (enemy_state_)
		{
		case EnemyState::Enter:
			ImGui::Text("enter");
			break;

		case EnemyState::Wait:
			ImGui::Text("wait");
			break;

		case EnemyState::BodyPress:
			ImGui::Text("body_press");
			break;

		case EnemyState::Shooting:
			ImGui::Text("shooting");
			break;

		case EnemyState::LaserCannon:
			ImGui::Text("laser_cannon");
			break;
		}
	}
	ImGui::End();

	//// �G�̏�ԍX�V
	//switch (enemy_state_)
	//{
	//case EnemyState::Enter:
	//	this->MoveActionEnter(deltaTime);
	//	break;
	//
	//case EnemyState::Wait:
	//	this->MoveActionWait(deltaTime);
	//	break;

	//case EnemyState::BodyPress:
	//	this->MoveActionBodyPress(deltaTime);
	//	break;

	//case EnemyState::Shooting:
	//	this->MoveActionShoot(deltaTime);
	//	break;
	//
	//case EnemyState::LaserCannon:
	//	this->MoveActionLaserCannon(deltaTime);
	//	break;

	//default:
	//	assert(!"WeakEnemyMoveComponent::Update()�F�{�X���s���ȍs���X�e�[�g�ɂ���܂��I");
	//	break;
	//}

	//�{�X�̃X�e�[�g�̍X�V
	enemy_state_old_ = enemy_state_;
}


/*=============================================================================
/*		End of File
=============================================================================*/