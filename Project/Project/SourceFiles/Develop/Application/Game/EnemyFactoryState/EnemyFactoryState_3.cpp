/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_3.cpp] �G�l�~�[�t�@�N�g���̑�3��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�3��ԃN���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "EnemyFactoryState_3.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactoryState_3::EnemyFactoryState_3(class Game* game)
	: EnemyFactoryState(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactoryState_3::~EnemyFactoryState_3(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool EnemyFactoryState_3::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void EnemyFactoryState_3::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void EnemyFactoryState_3::Update(float deltaTime)
{
	//
	// �J�n���W�𓯂��ɂ��Đ������Ԃ����炷
	//

	if (spawn_count >= MAX_SPAWN_COUNT_) { return; }

	// �G�l�~�[�𐶐����邽�߂̏���������
	class WeakEnemy* enemy = nullptr;

	// ��������t���O��������
	is_spawn = false;

	// �ړ��x�N�g���̍���
	const float move_vector_diff = 4.f;

	// �ړ��ւ̏��𐶐�
	const float start_position_x = 15.f;
	const float start_position_y = 25.f;
	const float start_position_z = 20.f;

	// �ړ��x�N�g���̒���
	const float move_vector_length = start_position_y * 2.f;

	// �ړ��A�N�V�����̑傫��
	const float move_action_magnitude = 0.5f;

	// �G�l�~�[�𐶐����鍷���̎��Ԃ����߂�
	const float spawn_time = ((SPAWN_DIFF_TIME_ * 0.5f) * spawn_count);

	// ���s���Ԃ��v�Z
	execute_time_ += deltaTime;

	// �G�l�~�[�̐������s�����H
	const bool is_execute_spawn = ((execute_time_ >= spawn_time) && (is_spawn == false));
	if (is_execute_spawn)
	{
		// �������������ȉ���������
		if (!(spawn_count >= HALF_SPAWN_COUNT_))
		{
			// ����
			enemy = NEW WeakEnemy(game_);

			// �s���X�e�[�g��ݒ�
			enemy->SetEnemyState(EnemyState::MoveLoopLeftRight);

			// �J�n���W
			enemy->SetStartPosition(-start_position_x
								   , start_position_y
								   , start_position_z);

			// �ő�s������
			enemy->SetMaxExecuteTime(10.f);

			// �ړ���������Ƌ���
			enemy->SetRotationMoveDirection(0.f, 90.f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// �ړ��A�N�V�����̐[��
			enemy->SetMoveActionMagnitude(move_action_magnitude);
		}
		else
		{
			// ����
			enemy = NEW WeakEnemy(game_);

			// �s���X�e�[�g��ݒ�
			enemy->SetEnemyState(EnemyState::MoveLoopLeftRight);

			// �J�n���W
			enemy->SetStartPosition(start_position_x
								   , -start_position_y
								   , start_position_z);

			// �ő�s������
			enemy->SetMaxExecuteTime(10.f);

			// �ړ���������Ƌ���
			enemy->SetRotationMoveDirection(0.f, -90.f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// �ړ��A�N�V�����̐[��
			enemy->SetMoveActionMagnitude(move_action_magnitude);
		}

		// �����J�E���g�����Z
		spawn_count++;

		// �����������Ƃ��L��
		is_spawn = true;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/