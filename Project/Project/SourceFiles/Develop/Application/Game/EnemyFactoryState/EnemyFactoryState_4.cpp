/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_4.cpp] �G�l�~�[�t�@�N�g���̑�4��ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̑�4��ԃN���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "EnemyFactoryState_4.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactoryState_4::EnemyFactoryState_4(class Game* game)
	: EnemyFactoryState(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactoryState_4::~EnemyFactoryState_4(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool EnemyFactoryState_4::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void EnemyFactoryState_4::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void EnemyFactoryState_4::Update(float deltaTime)
{
	//
	// �J�n���W�𓯂��ɂ��Đ������Ԃ����炷
	//

	if (spawn_count_ >= MAX_SPAWN_COUNT_) { return; }

	// �G�l�~�[�𐶐����邽�߂̏���������
	class Enemy* enemy = nullptr;

	// ��������t���O��������
	is_spawn_ = false;

	// �ړ��x�N�g���̍���
	const float move_vector_diff = 4.f;

	// �ړ��ւ̏��𐶐�
	const float start_position_x = 25.f;
	const float start_position_y = 25.f;
	const float start_position_z = 20.f;

	// �ړ��x�N�g���̒���
	const float move_vector_length = start_position_y * 2.f;

	// �ړ��A�N�V�����̑傫��
	const float move_action_magnitude = 20.f;

	// �G�l�~�[�𐶐����鍷���̎��Ԃ����߂�
	const float spawn_time = (SPAWN_DIFF_TIME_ * spawn_count_);

	// ���s���Ԃ��v�Z
	execute_time_ += deltaTime;

	// �G�l�~�[�̐������s�����H
	const bool is_execute_spawn = ((execute_time_ >= spawn_time) && (is_spawn_ == false));
	if (is_execute_spawn)
	{
		// �������������ȉ���������
		if (!(spawn_count_ >= HALF_SPAWN_COUNT_))
		{
			// ��������2�Ŋ������]��̐����P�̂Ƃ�
			if ((spawn_count_%2) == 1)
			{
				// ����
				enemy = NEW StrongEnemy(game_);
			}
			else
			{
				// ����
				enemy = NEW WeakEnemy(game_);
			}

			// �s���X�e�[�g��ݒ�
			enemy->SetEnemyState(EnemyState::MoveRoundVertical);

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
			// ��������2�Ŋ������]��̐����P�̂Ƃ�
			if ((spawn_count_ % 2) == 1)
			{
				// ����
				enemy = NEW StrongEnemy(game_);
			}
			else
			{
				// ����
				enemy = NEW WeakEnemy(game_);
			}

			// �s���X�e�[�g��ݒ�
			enemy->SetEnemyState(EnemyState::MoveRoundVertical);

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
			enemy->SetMoveActionMagnitude(-move_action_magnitude);
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