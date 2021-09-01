/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyMoveComponent.cpp] �{�X�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�̈ړ��R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "StrongEnemyMoveComponent.h"
#include "../../../GameObject.h"
#include "../../../../../Math.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemyMoveComponent::StrongEnemyMoveComponent(GameObject* owner, int updateOrder)
	: EnemyMoveComponent(owner, updateOrder)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemyMoveComponent::~StrongEnemyMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool StrongEnemyMoveComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ���@�̊e��]�l�̎擾
	yaw_	= owner_transform_->GetAngleYaw();
	pitch_	= owner_transform_->GetAnglePitch();
	roll_	= owner_transform_->GetAngleRoll();

	// ��]�̕�Ԃ��s���t���O��ON��
	{
		owner_transform_->IsSetExecuteSlerpRotation(true);
	}

	// ���g�̏�Ԃ�\�L
	ImGui::Begin("strong_enemy_move_state");
	{
		switch (enemy_state_)
		{
		case EnemyState::Idle:
			ImGui::Text("idle");
			break;

		case EnemyState::MoveStraight:
			ImGui::Text("move_straight");
			break;

		case EnemyState::MoveStraightWaitOneTime:
			ImGui::Text("move_straight_wait_one_time");
			break;

		case EnemyState::MoveStraightWaitUpDown:
			ImGui::Text("move_straight_wait_up_down");
			break;

		case EnemyState::MoveRoundVertical:
			ImGui::Text("move_round_vertical");
			break;

		case EnemyState::MoveRoundHorizontal:
			ImGui::Text("move_round_horizontal");
			break;

		case EnemyState::MoveLoopUpDown:
			ImGui::Text("move_loop_up_down");
			break;

		case EnemyState::MoveLoopLeftRight:
			ImGui::Text("move_loop_left_right");
			break;

		case EnemyState::MoveShowOneTime:
			ImGui::Text("move_show_one_time");
			break;

		case EnemyState::Destroy:
			ImGui::Text("destroy");
			break;

		default:
			assert(!"StrongEnemyMoveComponent::Update()�F�����G���s���ȍs���X�e�[�g�ɂ���܂��I");
			break;
		}
	}
	ImGui::End();

	// �G�̏�ԍX�V
	switch (enemy_state_)
	{	
	case EnemyState::Idle:
		this->MoveActionIdle(deltaTime);
		break;

	case EnemyState::MoveStraight:
		this->MoveActionStraight(deltaTime);
		break;

	case EnemyState::MoveStraightWaitOneTime:
		this->MoveActionStraightWaitOneTime(deltaTime);
		break;

	case EnemyState::MoveStraightWaitUpDown:
		this->MoveActionStraightWaitUpDown(deltaTime);
		break;

	case EnemyState::MoveRoundVertical:
		this->MoveActionRoundVertical(deltaTime);
		break;

	case EnemyState::MoveRoundHorizontal:
		this->MoveActionRoundHorizontal(deltaTime);
		break;

	case EnemyState::MoveLoopUpDown:
		this->MoveActionLoopUpDown(deltaTime);
		break;

	case EnemyState::MoveLoopLeftRight:
		this->MoveActionLoopLeftRight(deltaTime);
		break;

	case EnemyState::MoveShowOneTime:
		this->MoveActionShowOneTime(deltaTime);
		break;

	case EnemyState::Destroy:
		break;

	default:
		assert(!"StrongEnemyMoveComponent::Update()�F�����G���s���ȍs���X�e�[�g�ɂ���܂��I");
		break;
	}

	//�{�X�̃X�e�[�g�̍X�V
	enemy_state_old_ = enemy_state_;
}

/*-----------------------------------------------------------------------------
/* �����G�̑ҋ@�s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionIdle(float deltaTime)
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
/* �����G�̒����ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionStraight(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// ���L�҂̏�Ԃ��A1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::MoveState_0;
		execute_time_ = 0.f;
	}

	// �A�j���[�V�����̎��s���Ԃ��ő���s���Ԃ���������
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// ���ۂ̋������`
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::MoveState_0:
		// ���W����
		D3DXVec3Lerp(&position_												// ���ݍ��W
			, &position_start_										// �n�_���W
			, &position_finish_										// �I�_���W
			, Easing::Linear(execute_time_, max_execute_time_));	// ��Ԃ̎d��

		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::MoveState_0;
		execute_time_ = 0.f;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionStraight()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	// �ړ�
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* �����G�̒����ړ����Ĉ��҂s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionStraightWaitOneTime(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// ���L�҂̏�Ԃ��A1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// �A�j���[�V�����̎��s���Ԃ��ő���s���Ԃ���������
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// ���ۂ̋������`
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// ���W����
		D3DXVec3Lerp(&position_
			, &position_start_
			, &position_finish_
			, Easing::SineInOut(execute_time_, max_execute_time_));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * 0.5f))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::MoveState_0:

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			execute_time_ = (max_execute_time_ * 0.5f);
		}
		break;

	case EnemyMotionState::MoveState_1:
		// ���W����
		D3DXVec3Lerp(&position_
			, &position_start_
			, &position_finish_
			, Easing::SineInOut(execute_time_, max_execute_time_));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
		}
		break;


	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp; // �ŏ��ɖ߂�
		break;


	default:
		assert(!"EnemyMoveComponent::MoveActionStraightWaitOneTime()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	// �ړ�
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* �����G�̒����ړ����ď㉺�^���ƕ�����҂s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionStraightWaitUpDown(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// ���L�҂̏�Ԃ��A1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// �A�j���[�V�����̎��s���Ԃ��ő���s���Ԃ���������
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// X�EZ����́A�ʏ�ǂ���ړ�
	{
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	static bool	is_finish_position = false;	// �I�_���W�ɓ��B���Ă��邩�H
	const int	max_state_loop_count = 6;		// �X�e�[�g���ő�ŌJ��Ԃ�����
	const float max_state_div_value = 0.166f;	// 1��6����

	// ���ۂ̋������`
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// �o��
	{
		position_.x = Math::Lerp(position_start_.x
			, position_finish_.x
			, Easing::Linear(execute_time_, max_execute_time_));

		position_.y = Math::Lerp(position_start_.y
			, position_finish_.y
			, Easing::Linear(execute_time_, max_execute_time_));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * 0.5f))
		{
			// �n�_���W�̌v�Z
			position_y_start_ = position_.y;

			// �I�_���W�̌v�Z
			position_y_finish_ = Math::Lerp(position_y_start_
				, position_y_start_ + move_action_magnitude_ * -1.f
				, 1.f);

			// ���̃X�e�[�g��
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			execute_time_ = 0.f;
		}
	}
	break;

	case EnemyMotionState::MoveState_1:
		// Y���̏I�_��
	{
		position_.y = Math::Lerp(position_y_start_
			, position_y_finish_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// �����𖞂�������I���X�e�[�g��
		if (state_loop_count_ >= max_state_loop_count)
		{
			execute_time_ = (max_execute_time_ * 0.5f);
			enemy_motion_state_ = EnemyMotionState::End;
			break;
		}

		// �ҋ@���[�V������
		if (execute_time_ >= (max_execute_time_ * max_state_div_value))
		{
			is_finish_position = true;
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::MoveState_3;
			break;
		}
	}
	break;

	case EnemyMotionState::MoveState_2:
		// Y���̎n�_��
	{
		position_.y = Math::Lerp(position_y_finish_
			, position_y_start_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));


		// �����𖞂�������I���X�e�[�g��
		if (state_loop_count_ >= max_state_loop_count)
		{
			execute_time_ = (max_execute_time_ * 0.5f);
			enemy_motion_state_ = EnemyMotionState::End;
			break;
		}

		// �ҋ@���[�V������
		if (execute_time_ >= (max_execute_time_ * max_state_div_value))
		{
			is_finish_position = false;
			execute_time_ = 0.f;
			enemy_motion_state_ = EnemyMotionState::MoveState_3;
			break;
		}
	}
	break;

	case EnemyMotionState::MoveState_3:
		//�ҋ@

		if (execute_time_ >= (max_execute_time_ * max_state_div_value))
		{
			// �X�e�[�g�̃��[�v���։��Z
			state_loop_count_++;

			if (is_finish_position)
			{
				enemy_motion_state_ = EnemyMotionState::MoveState_2; // �n�_���W��
				execute_time_ = 0.f;
				break;
			}
			else
			{
				enemy_motion_state_ = EnemyMotionState::MoveState_1; // �I�_���W��
				execute_time_ = 0.f;
				break;
			}
		}
		break;

	case EnemyMotionState::End:
		// �ޏ�
	{
		position_.x = Math::Lerp(position_start_.x
			, position_finish_.x
			, Easing::Linear(execute_time_, max_execute_time_));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::StartUp; // �ŏ��ɖ߂�
			execute_time_ = 0.f;
			state_loop_count_ = 0;
		}
	}
	break;

	default:
		assert(!"EnemyMoveComponent::MoveActionStraightWaitUpDown()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	// �ړ�
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* �����G�̐����ɔ��~��`���ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionRoundVertical(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// ���L�҂̏�Ԃ��A1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// �A�j���[�V�����̎��s���Ԃ��ő���s���Ԃ���������
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// Y�EZ����́A�ʏ�ǂ���ړ�
	{
		position_.y = Math::Lerp(position_start_.y, position_finish_.y, Easing::SineInOut(execute_time_, max_execute_time_));
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	right_vector_;

	// ���ۂ̋������`
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// ���W����
		position_.x = Math::Lerp(position_start_.x
			, position_finish_.x + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * 0.5f)));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * 0.5f))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			//execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::MoveState_0:

		// ���W����
		position_.x = Math::Lerp(position_finish_.x
			, position_finish_.x + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * 0.5f)));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= (max_execute_time_))
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionRoundVertical()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	// �ړ�
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* �����G�̐����ɔ��~��`���ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionRoundHorizontal(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// ���L�҂̏�Ԃ��A1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// �A�j���[�V�����̎��s���Ԃ��ő���s���Ԃ���������
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// X�EZ����́A�ʏ�ǂ���ړ�
	{
		position_.x = Math::Lerp(position_start_.x, position_finish_.x, Easing::SineInOut(execute_time_, max_execute_time_));
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	// ���ۂ̋������`
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// ���W����
		position_.y = Math::Lerp(position_finish_.y
			, position_finish_.y + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * 0.5f)));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * 0.5f))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
		}
		break;

	case EnemyMotionState::MoveState_0:
		// ���W����
		position_.y = Math::Lerp(position_finish_.y
			, position_finish_.y + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * 0.5f)));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= (max_execute_time_))
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionRoundHorizontal()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	// �ړ�
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* �����G�̏㉺�^�����[�v�ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionLoopUpDown(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// ���L�҂̏�Ԃ��A1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// �A�j���[�V�����̎��s���Ԃ��ő���s���Ԃ���������
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// X�EZ����́A�ʏ�ǂ���ړ�
	{
		position_.x = Math::Lerp(position_start_.x, position_finish_.x, Easing::SineInOut(execute_time_, max_execute_time_));
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	// �e�X�e�[�g�̎��Ԃ𕪊������{��
	const float max_state_div_value = 0.143f; // 1��7����

	// ���ۂ̋������`
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// ���� 
		position_.y = Math::Lerp(position_start_.y
			, position_finish_.y + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
		}
		break;

	case EnemyMotionState::MoveState_0:
		// �㏸
		position_.y = Math::Lerp(position_finish_.y + move_action_magnitude_ * -1.f
			, position_finish_.y + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// �����𖞂�������I���X�e�[�g��
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
			state_loop_count_ = 0;
			break;
		}

		// ���̃X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::MoveState_1:
		// ���~
		position_.y = Math::Lerp((position_finish_.y + move_action_magnitude_) * -1.f
			, position_finish_.y + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// �����𖞂�������I���X�e�[�g��
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
			state_loop_count_ = 0;
			break;
		}

		// �ЂƂO�̃X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionLoopUpDown()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	// �ړ�
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* �����G�̍��E�^�����[�v�ړ��s��
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionLoopLeftRight(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// ���L�҂̏�Ԃ��A1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// �A�j���[�V�����̎��s���Ԃ��ő���s���Ԃ���������
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// Y�EZ����́A�ʏ�ǂ���ړ�
	{
		position_.y = Math::Lerp(position_start_.y, position_finish_.y, Easing::SineInOut(execute_time_, max_execute_time_));
		position_.z = Math::Lerp(position_start_.z, position_finish_.z, Easing::SineInOut(execute_time_, max_execute_time_));
	}

	// �e�X�e�[�g�̎��Ԃ𕪊������{��
	const float max_state_div_value = 0.143f;  // 1��7����

	// ���ۂ̋������`
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// ���� 
		position_.x = Math::Lerp(position_start_.x
			, position_finish_.x + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
		}
		break;

	case EnemyMotionState::MoveState_0:
		// ����
		position_.x = Math::Lerp((position_finish_.x + move_action_magnitude_) * -1.f
			, position_finish_.x + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// �����𖞂�������I���X�e�[�g��
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
			state_loop_count_ = 0;
			break;
		}

		// ���̃X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::MoveState_1:
		// �E��
		position_.x = Math::Lerp((position_finish_.x + move_action_magnitude_) * -1.f
			, position_finish_.x + move_action_magnitude_
			, Easing::SineInOut(execute_time_, (max_execute_time_ * max_state_div_value)));

		// �����𖞂�������I���X�e�[�g��
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
			state_loop_count_ = 0;
			break;
		}

		// �ЂƂO�̃X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * (max_state_div_value * state_loop_count_)))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			state_loop_count_++;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp;
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionLoopLeftRight()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	// �ړ�
	owner_transform_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* �����G�̉�ʂ̒[����Ђ������������
-----------------------------------------------------------------------------*/
void StrongEnemyMoveComponent::MoveActionShowOneTime(float deltaTime)
{
	// ��]�̍X�V
	owner_transform_->SetSlerpSpeed(5.f);
	owner_transform_->SetRotation(yaw_, 8.f, 0);
	owner_transform_->AddRotationYaw(4);

	// ���L�҂̏�Ԃ��A1�t���[���O�ƍ��ق��������ꍇ
	if (enemy_state_ != enemy_state_old_)
	{
		//�U����Ԃ̏�����
		enemy_motion_state_ = EnemyMotionState::StartUp;
		execute_time_ = 0.f;
	}

	// �A�j���[�V�����̎��s���Ԃ��ő���s���Ԃ���������
	if (execute_time_ >= max_execute_time_)
	{
		execute_time_ = max_execute_time_;
	}
	else
	{
		execute_time_ += deltaTime;
	}

	// ���ۂ̋������`
	switch (enemy_motion_state_)
	{
	case EnemyMotionState::StartUp:
		// ���W����
		D3DXVec3Lerp(&position_
			, &position_start_
			, &position_finish_
			, Easing::SineInOut(execute_time_, max_execute_time_));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= (max_execute_time_ * 0.5f))
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_0;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::MoveState_0:

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= max_execute_time_ * 0.5f)
		{
			enemy_motion_state_ = EnemyMotionState::MoveState_1;
			execute_time_ = (max_execute_time_ * 0.5f);
		}
		break;

	case EnemyMotionState::MoveState_1:
		// ���W����
		D3DXVec3Lerp(&position_
			, &position_finish_
			, &position_start_
			, Easing::SineInOut(execute_time_, max_execute_time_));

		// �����𖞂������玟�̃��[�V�����X�e�[�g��
		if (execute_time_ >= max_execute_time_)
		{
			enemy_motion_state_ = EnemyMotionState::End;
			execute_time_ = 0.f;
		}
		break;

	case EnemyMotionState::End:
		enemy_motion_state_ = EnemyMotionState::StartUp; // �ŏ��ɖ߂�
		break;

	default:
		assert(!"EnemyMoveComponent::MoveActionStraightWaitOneTime()�F�s���ȃ��[�V�����̏�ԁI");
		break;
	}

	// �ړ�
	owner_transform_->SetTranslation(position_);
}

/*=============================================================================
/*		End of File
=============================================================================*/