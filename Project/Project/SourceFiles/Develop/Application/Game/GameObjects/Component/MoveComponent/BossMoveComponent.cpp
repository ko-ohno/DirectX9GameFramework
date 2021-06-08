/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossMoveComponent.cpp] �{�X�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�̈ړ��R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "BossMoveComponent.h"
#include "../../GameObject.h"
#include "../../../../Math.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BossMoveComponent::BossMoveComponent(GameObject* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
	, boss_ai_(nullptr)
	, enter_motion_state_(EnterMotionState::NONE)
	, attack_motion_state_(AttackMotionState::NONE)
	, boss_motion_state_(BossMotionState::NONE)
	, boss_motion_state_old_(BossMotionState::NONE)
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
	if (this->boss_ai_ == nullptr)
	{
		auto owner_component_list = owner_->GetComponents();

		//�@�������茟��������
		for (auto owner_component : owner_component_list)
		{
			//
			auto type_id = owner_component->GetComponentType();
			if (type_id == Component::TypeID::BossAIComponent)
			{
				auto ai = owner_component;

				//ai->ge
				break;
			}
		}
	}

	// �e��]�l�̎擾
	yaw_   = owner_transform_->GetAngleYaw();
	pitch_ = owner_transform_->GetAnglePitch();
	roll_  = owner_transform_->GetAngleRoll();

	// ���`���ʕۊǂ��s���t���O��ON��
	{
		owner_transform_->IsSetExecuteSlerp(true);
	}

	//owner_transform_->SetTranslation();

	//�{�X�̃X�e�[�g�̍X�V
	boss_motion_state_old_ = boss_motion_state_;
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
	if (boss_motion_state_ != boss_motion_state_old_)
	{
		//�U����Ԃ̏�����
		enter_motion_state_ = EnterMotionState::FROM_RIGHT;
		execute_time_ = 0.f;
	}

	//�A�j���[�V�����̎���
	const float MAX_EXE_TIME = 2.f;
	execute_time_ += deltaTime;

	switch (enter_motion_state_)
	{
	case EnterMotionState::FROM_RIGHT:
		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &enter_from_right_wait_position_
					, &enter_from_left_wait_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enter_motion_state_ = EnterMotionState::FLOM_LEFT;
		}
		break;

	case EnterMotionState::FLOM_LEFT:
		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &enter_from_left_wait_position_
					, &enter_from_right_wait_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enter_motion_state_ = EnterMotionState::FLOM_UNDER;
		}
		break;

	case EnterMotionState::FLOM_UNDER:
		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &enter_from_under_wait_position_
					, &wait_position_
					, Easing::SineInOut(execute_time_, MAX_EXE_TIME));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			enter_motion_state_ = EnterMotionState::END;
		}
		break;

	case EnterMotionState::END:
		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			boss_motion_state_ = BossMotionState::WAIT;
		}
		break;

	default:
		assert("�s���ȃA�j���[�V�����J�ځI�I");
		break;
	}

	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/*�@�{�X�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void BossMoveComponent::MoveActionWait(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 0, 0);
	owner_transform_->AddRotationYaw(4);

	// �A�j���[�V�����̎���
	const float MAX_STATE_TIME = 5.f;
	execute_time_ += deltaTime;

	// ���[�V�����̎��s���Ԃ��ő�𒴂�����
	if (execute_time_ >= MAX_STATE_TIME)
	{
		execute_time_ = 0.f;
		boss_motion_state_ = BossMotionState::WAIT;
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
	if (boss_motion_state_ != boss_motion_state_old_)
	{
		//�U����Ԃ̏�����
		attack_motion_state_ = AttackMotionState::START_UP;
		execute_time_ = 0.f;
	}

	switch (attack_motion_state_)
	{
	case AttackMotionState::START_UP:	//�������񉺂�����
		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &wait_position_
					, &body_press_startup_position_
					, Easing::SineIn(execute_time_));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::RELAY;
		}
		break;

	case AttackMotionState::RELAY:	//�������W�ɖ߂��Ă���

		// �ړ����x���{��
		execute_time_ += deltaTime;

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &body_press_startup_position_
					, &wait_position_
					, Easing::SineIn(execute_time_));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::ATTACK;
		}
		break;

	case AttackMotionState::ATTACK:	//�U��

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &wait_position_
					, &body_press_position_
					, Easing::SineIn(execute_time_));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::END;
		}
		break;

	case AttackMotionState::END:	//�]�C���c���đҋ@�s����

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &body_press_position_
					, &wait_position_
					, Easing::SineIn(execute_time_));

		// ���[�V�����̎��s���Ԃ��ő�𒴂�����
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			boss_motion_state_ = BossMotionState::WAIT;
		}
		break;

	default:
		assert("�{�X���s���ȍU����ԁI�I");
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
	if (boss_motion_state_ != boss_motion_state_old_)
	{
		//�U����Ԃ̏�����
		execute_time_ = 0.f;
		attack_motion_state_ = AttackMotionState::START_UP;
	}

	//�A�j���[�V�����̎���
	const float MAX_STATE_TIME = 7.f;
	const float MAX_EXE_TIME = 1.f;
	execute_time_ += deltaTime;


	switch (attack_motion_state_)
	{
	case AttackMotionState::START_UP:

		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &wait_position_
					, &shoot_position_
					, Easing::SineIn(execute_time_));

		//��Ԃ̑J��
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::ATTACK;
		}
		break;

	case AttackMotionState::ATTACK:
		//��]�̍X�V
		owner_transform_->SetSlerpSpeed(3.0f);
		owner_transform_->SetRotation(0, 90, roll_);
		owner_transform_->AddRotationRoll(4);

		//��Ԃ̑J��
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::END;
		}
		break;

	case AttackMotionState::END:
		//��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &shoot_position_
					, &wait_position_
					, Easing::SineIn(execute_time_));

		//��Ԃ̑J��
		if (execute_time_ >= MAX_EXE_TIME)
		{
			execute_time_ = 0.f;
			boss_motion_state_ = BossMotionState::WAIT;
		}
		break;

	default:
		assert("�{�X�̕s���ȍU����ԁI�I");
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
	if (boss_motion_state_ != boss_motion_state_old_)
	{
		//�U����Ԃ̏�����
		execute_time_ = 0.f;
		attack_motion_state_ = AttackMotionState::START_UP;

		//�G�t�F�N�g�̍Đ�

	}

	//�A�j���[�V�����̎���
	const float MAX_STATE_TIME = 7.f;
	execute_time_ += deltaTime;

	switch (attack_motion_state_)
	{
	case AttackMotionState::START_UP:
		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &wait_position_
					, &shoot_position_
					, Easing::SineIn(execute_time_));


		// ��]�̍X�V
		if (execute_time_ >= 1.f)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::ATTACK;
		}
		break;

	case AttackMotionState::ATTACK:
		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(3.0f);

		// �v���C���[�̈ʒu�ɍ��킹�Ċp�x�𒲐�����
		owner_transform_->SetRotation(yaw_, 90, 0);
		owner_transform_->SetRotationYaw(45);

		// ��]�̍X�V
		if (execute_time_ >= MAX_STATE_TIME)
		{
			execute_time_ = 0.f;
			attack_motion_state_ = AttackMotionState::END;
		}
		break;

	case AttackMotionState::END:
		// ��]�̍X�V
		owner_transform_->SetSlerpSpeed(5.f);
		owner_transform_->SetRotation(yaw_, 0, 0);
		owner_transform_->AddRotationYaw(4);

		// ���W�̕��
		D3DXVec3Lerp(&position_
					, &shoot_position_
					, &wait_position_
					, Easing::SineIn(execute_time_));

		// ��]�̍X�V
		if (execute_time_ >= 1.f)
		{
			execute_time_ = 0.f;
			boss_motion_state_ = BossMotionState::WAIT;
		}
		break;

	default:
		assert("�{�X�̕s���ȍU����ԁI�I");
		break;
	}

	//�ړ�
	owner_transform_->SetTranslation(position_);
}

/*=============================================================================
/*		End of File
=============================================================================*/