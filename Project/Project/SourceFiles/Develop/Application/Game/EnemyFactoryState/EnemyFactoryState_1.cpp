/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_1.cpp] �G�l�~�[�t�@�N�g���̑�1��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�1��ԃN���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "EnemyFactoryState_1.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactoryState_1::EnemyFactoryState_1(class Game* game)
	: EnemyFactoryState(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactoryState_1::~EnemyFactoryState_1(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool EnemyFactoryState_1::Init(void)
{
	//spawn_count = 5;
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void EnemyFactoryState_1::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void EnemyFactoryState_1::Update(float deltaTime)
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
	const float move_vector_diff   = 4.f;

	// �ړ��ւ̏��𐶐�
	const float start_position_x = 35.f;
	const float start_position_y =  5.f;
	const float start_position_z = 15.f;

	// �ړ��x�N�g���̒���
	const float move_vector_length = (start_position_x * 2.f) + (move_vector_diff * HALF_SPAWN_COUNT_);

	// �G�l�~�[�𐶐����鍷���̎��Ԃ����߂�
	const float spawn_time = (SPAWN_DIFF_TIME_ * spawn_count);

	// ���s���Ԃ��v�Z
	execute_time_ += deltaTime;

	// �G�l�~�[�̐������s�����H
	const bool is_execute_spawn = ((execute_time_ >= spawn_time ) && (is_spawn == false));
	if (is_execute_spawn)
	{
		if(!(spawn_count >= HALF_SPAWN_COUNT_))
		{
			// ����
			enemy = NEW WeakEnemy(game_);

			// �s���X�e�[�g��ݒ�
			enemy->SetEnemyState(EnemyState::MoveStraightWaitOneTime);

			// �J�n���W
			enemy->SetStartPosition(-start_position_x - ((move_vector_diff * spawn_count))
								   , start_position_y
								   , start_position_z);

			// �ő�s������
			enemy->SetMaxExecuteTime(8.f);

			// �ړ���������Ƌ���
			enemy->SetRotationMoveDirection(90.f, 0.f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// �ړ��A�N�V�����̐[��
			//enemy->SetMoveActionMagnitude(3.f);
		}
		else
		{
			// ����
			enemy = NEW WeakEnemy(game_);

			// �s���X�e�[�g��ݒ�
			enemy->SetEnemyState(EnemyState::MoveStraightWaitOneTime);

			// �J�n���W
			enemy->SetStartPosition(start_position_x + (move_vector_diff * (spawn_count - HALF_SPAWN_COUNT_))
								   , -start_position_y
								   ,  start_position_z);

			// �ő�s������
			enemy->SetMaxExecuteTime(8.f);

			// �ړ���������Ƌ���
			enemy->SetRotationMoveDirection(-90.f, 0.f, 0.f);
			enemy->SetMoveVectorLength(move_vector_length);

			// �ړ��A�N�V�����̐[��
			//enemy->SetMoveActionMagnitude(3.f);

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