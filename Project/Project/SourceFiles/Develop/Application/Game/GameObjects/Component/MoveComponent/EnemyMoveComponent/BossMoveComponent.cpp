/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossMoveComponent.cpp] �{�X�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�̈ړ��R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "BossMoveComponent.h"
#include "../../../GameObject.h"
#include "../../../../../Math.h"
#include "../../../../SandBoxManager/ActorManager.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BossMoveComponent::BossMoveComponent(GameObject* owner, int updateOrder)
	: EnemyMoveComponent(owner, updateOrder)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^ 
-----------------------------------------------------------------------------*/
BossMoveComponent::~BossMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool BossMoveComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void BossMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void BossMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void BossMoveComponent::Update(float deltaTime)
{
	// �e��]�l�̎擾
	yaw_   = owner_transform_->GetAngleYaw();
	pitch_ = owner_transform_->GetAnglePitch();
	roll_  = owner_transform_->GetAngleRoll();

	// ��]�̕�Ԃ��s���t���O��ON��
	{
		owner_transform_->IsSetExecuteSlerpRotation(true);
	}

	// ���g�̏�Ԃ�\�L
	ImGui::Begin("boss_move_state");
	{
		switch (enemy_state_)
		{
		case EnemyState::Enter:
			ImGui::Text("enter");
			break;

		case EnemyState::Idle:
			ImGui::Text("idle");
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

	// �G�̏�ԍX�V
	switch (enemy_state_)
	{
	case EnemyState::Enter:
		this->MoveActionEnter(deltaTime);
		break;
	
	case EnemyState::Idle:
		this->MoveActionIdle(deltaTime);
		break;

	case EnemyState::BodyPress:
		this->MoveActionBodyPress(deltaTime);
		break;

	case EnemyState::Shooting:
		this->MoveActionShoot(deltaTime);
		break;
	
	case EnemyState::LaserCannon:
		this->MoveActionLaserCannon(deltaTime);
		break;

	default:
		assert(!"BossMoveComponent::Update()�F�{�X���s���ȍs���X�e�[�g�ɂ���܂��I");
		break;
	}

	//�{�X�̃X�e�[�g�̍X�V
	enemy_state_old_ = enemy_state_;
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̓o��s��
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionEnter(float deltaTime)
{
	//��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotationPitch(10);
	owner_transform_->AddRotationYaw(4);

	//1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::MoveState_0;
		execute_time_ = 0.f;
	}

	//�A�j���[�V�����̎���
	const float MAX_EXE_TIME = 2.f;
	execute_time_ += deltaTime;

	switch (enemy_motion_state_)
	{
	case EnemyMotionState::MoveState_0:
		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &enter_from_right_idle_position_
					, &enter_from_left_idle_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
		}
		break;

	case EnemyMotionState::MoveState_1:
		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &enter_from_left_idle_position_
					, &enter_from_right_idle_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::MoveState_2;
		}
		break;

	case EnemyMotionState::MoveState_2:
		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &enter_from_under_idle_position_
					, &idle_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Complete;
		}
		break;

	case EnemyMotionState::Complete:
		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		break;

	default:
		assert(!"BossMoveComponent::MoveActionEnter()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionIdle(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 2.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;
	}
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̃{�f�B�v���X�U���s��
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionBodyPress(float deltaTime)
{
	//��]�̏���
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->AddRotationYaw(4);

	//�A�j���[�V�����̎���
	const float MAX_STATE_TIME = 1.0f;
	const float MAX_EXE_TIME = 1.0f;
	execute_time_ += deltaTime;

	//1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:	//�������񉺂�����
		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &idle_position_
					, &body_press_startup_position_
					, Easing::SineIn(execute_time_));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Relay;
		}
		break;

	case EnemyMotionState::Relay:	//�������W�ɖ߂��Ă���

		// �ړ����x���{��
		execute_time_ += deltaTime;

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &body_press_startup_position_
					, &idle_position_
					, Easing::SineIn(execute_time_));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Attack;
		}
		break;

	case EnemyMotionState::Attack:	//�U��

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &idle_position_
					, &body_press_position_
					, Easing::SineIn(execute_time_));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Complete;
		}
		break;

	case EnemyMotionState::Complete:	//�]�C���c���đҋ@�s����

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &body_press_position_
					, &idle_position_
					, Easing::SineIn(execute_time_));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		break;

	default:
		assert(!"BossMoveComponent::MoveActionBodyPress()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	// �ړ�
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̎ˌ��U���s��
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionShoot(float deltaTime)
{
	//1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	//�A�j���[�V�����̎���
	const float MAX_START_UP_TIME = 1.f;
	const float MAX_RELAY_TIME = 2.f;
	const float MAX_STATE_TIME = 7.f;
	const float MAX_EXE_TIME = 1.f;
	execute_time_ += deltaTime;

	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:

		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &idle_position_
					, &shoot_position_
					, Easing::SineIn(execute_time_));

		//��Ԃ̑J��
		if (execute_time_ >= MAX_START_UP_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Relay;
		}
		break;

	case EnemyMotionState::Relay:
		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.0f);

		// �v���C���[�̈ʒu�ɍ��킹�Ċp�x�𒲐�����
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(90.f, pitch_, 90.f);
		owner_transform_->AddRotationPitch(4);

		if (execute_time_ >= MAX_RELAY_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Attack;
		}
		break;

	case EnemyMotionState::Attack:

		//��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(90.f, pitch_, 90.f);
		owner_transform_->AddRotationPitch(4);

		//��Ԃ̑J��
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Complete;
		}
		break;

	case EnemyMotionState::Complete:
		//��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &shoot_position_
					, &idle_position_
					, Easing::SineIn(execute_time_));

		//��Ԃ̑J��
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		break;

	default:
		assert(!"BossMoveComponent::MoveActionShoot()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	//�ړ�
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̃��[�U�[�C�U���s��
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionLaserCannon(float deltaTime)
{
	//1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		execute_time_ = 0.f;
		enemy_motion_state_ = EnemyMotionState::StartUp;

		//�G�t�F�N�g�̍Đ�

	}
	static float angle = 45.f;


	//�A�j���[�V�����̎���
	const float MAX_STATE_TIME	= 1.f;
	const float MAX_ATTACK_TIME = 7.f;
	const float MAX_RELAY_TIME	= 1.f;

	execute_time_ += deltaTime;

	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &idle_position_
					, &shoot_position_
					, Easing::SineIn(execute_time_));


		// ��]�̍X�V
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Relay;
		}
		break;

	case EnemyMotionState::Relay:
		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(3.0f);

		// �v���C���[�̈ʒu�ɍ��킹�Ċp�x�𒲐�����
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(45, 90, 0);

		if (execute_time_ >= MAX_RELAY_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Attack;
		}
		break;

	case EnemyMotionState::Attack:
		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(3.0f);

		// �v���C���[�̈ʒu�ɍ��킹�Ċp�x�𒲐�����
		owner_transform_->SetRotation(yaw_, 90, 0);
		yaw_ = Math::Lerp(45.f, -45.f, Easing::CubicInOut(execute_time_ / 7.f));
		owner_transform_->SetRotationYaw(yaw_);

		// ��]�̍X�V
		if (execute_time_ >= MAX_ATTACK_TIME)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::Complete;
		}
		break;

	case EnemyMotionState::Complete:
		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &shoot_position_
					, &idle_position_
					, Easing::SineIn(execute_time_));

		// ��]�̍X�V
		if (execute_time_ >= 1.f)
		{
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		break;

	default:
		assert(!"BossMoveComponent::MoveActionLaserCannon()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	//�ړ�
	owner_transform_->SetTranslation(position_);
}

/*=============================================================================
/*		End of File
=============================================================================*/