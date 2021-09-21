/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_6.cpp] �G�l�~�[�t�@�N�g���̑�6��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�6��ԃN���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "EnemyFactoryState_6.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactoryState_6::EnemyFactoryState_6(class Game* game)
	: EnemyFactoryState(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactoryState_6::~EnemyFactoryState_6(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool EnemyFactoryState_6::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void EnemyFactoryState_6::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void EnemyFactoryState_6::Update(float deltaTime)
{
	//
	// �J�n���W�𓯂��ɂ��Đ������Ԃ����炷
	//

	if (spawn_count_ >= MAX_SPAWN_COUNT_) { return; }

	// �G�l�~�[�𐶐����邽�߂̏���������
	class WeakEnemy* enemy = nullptr;

	// ��������t���O��������
	is_spawn_ = false;

	// �ړ��x�N�g���̍���
	const float move_vector_diff = 4.f;

	// �ړ��ւ̏��𐶐�
	const float start_position_x =  30.f;
	const float start_position_y =  25.f;
	const float start_position_z = -15.f;

	// �ړ��x�N�g���̒���
	const float move_vector_length = 150.f;

	// �ړ��A�N�V�����̑傫��
	const float move_action_magnitude = 30.f;

	// �G�l�~�[�𐶐����鍷���̎��Ԃ����߂�
	const float spawn_time = ((SPAWN_DIFF_TIME_ * 0.5f) * spawn_count_);

	// ���s���Ԃ��v�Z
	execute_time_ += deltaTime;

	// �G�l�~�[�̐������s�����H
	const bool is_execute_spawn = ((execute_time_ >= spawn_time) && (is_spawn_ == false));
	if (is_execute_spawn)
	{
		// �������������ȉ���������
		if (!(spawn_count_ >= HALF_SPAWN_COUNT_))
		{
			// ����
			enemy = NEW WeakEnemy(game_);

			// �s���X�e�[�g��ݒ�
			enemy->SetEnemyState(EnemyState::MoveStraight);

			// �J�n���W
			enemy->SetStartPosition(-start_position_x
								   , start_position_y
								   , start_position_z);

			// �ő�s������
			enemy->SetMaxExecuteTime(10.f);

			// �ړ���������Ƌ���
			enemy->SetRotationMoveDirection(90.f * 0.3f, 90.f * 0.3f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// �ړ��A�N�V�����̐[��
			enemy->SetMoveActionMagnitude(move_action_magnitude);
		}
		else
		{
			// ����
			enemy = NEW WeakEnemy(game_);

			// �s���X�e�[�g��ݒ�
			enemy->SetEnemyState(EnemyState::MoveStraight);

			// �J�n���W
			enemy->SetStartPosition(start_position_x
								   , start_position_y
								   , start_position_z);

			// �ő�s������
			enemy->SetMaxExecuteTime(10.f);

			// �ړ���������Ƌ���
			enemy->SetRotationMoveDirection(-90.f * 0.3f, 90.f * 0.3f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// �ړ��A�N�V�����̐[��
			enemy->SetMoveActionMagnitude(move_action_magnitude);
		}

		// �����J�E���g�����Z
		spawn_count_++;

		// �����������Ƃ��L��
		is_spawn_ = true;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/