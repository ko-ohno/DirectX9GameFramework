/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Enemy.h] �G�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F �G�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef ENEMY_H_
#define	ENEMY_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Actor.h"

/*-------------------------------------
/*  �G�l�~�[�̃X�e�[�g
-------------------------------------*/
enum class EnemyState
{
	None = -1
	, Idle				// �ҋ@
	, Enter				// �o��
	, BodyPress			// �̓�����
	, Shooting			// �ˌ�
	, LaserCannon		// ���[�U�[�C

	, MoveStraight				// �����ړ�
	, MoveStraightWaitOneTime	// �����ړ��F�ꎞ�ҋ@�F�����ړ�
	, MoveStraightWaitUpDown	// �����ړ��F�㉺�^���ƈꎞ�ҋ@���J��Ԃ�
	, MoveRoundVertical			// �����ɔ��~��`���ړ�
	, MoveRoundHorizontal		// �����ɔ��~��`���ړ�
	, MoveLoopUpDown			// �㉺���[�v�ړ�
	, MoveLoopLeftRight			// ���E���[�v�ړ�
	, MoveShowOneTime			// ��ʂ̒[�����o��

	, Destroy			// ���j���ꂽ���
	, End				// ��ڂ��I�������

	, Max
};

/*-------------------------------------
/*  �G�Q�[���I�u�W�F�N�g
-------------------------------------*/
class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	~Enemy(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Enemy; }

	//
	// ���g�̏�Ԃ̐ݒ�
	//

	void SetEnemyState(EnemyState enemyState);
	EnemyState GetEnemyState(void);

	//
	// �ړ����W�̐ݒ�
	//

	// �n�_���W�̐ݒ�

	void SetStartPosition(const D3DXVECTOR3& startPosition) { position_start_ = startPosition; }
	void SetStartPosition(float posX, float posY, float posZ) { position_start_ = { posX, posY, posZ }; }
	void SetStartPositionX(float posX) { position_start_.x = posX; }
	void SetStartPositionY(float posY) { position_start_.y = posY; }
	void SetStartPositionZ(float posZ) { position_start_.z = posZ; }

	// �����x�N�g���̉�]�̐ݒ�

	void SetRotationMoveDirection(float degreeYaw, float degreePitch, float degreeRoll)
	{
		angle_yaw_   = degreeYaw;
		angle_pitch_ = degreePitch;
		angle_roll_  = degreeRoll;
	}

	void SetRotationMoveDirectionYaw(float degreeYaw)     { angle_yaw_   = degreeYaw; }
	void SetRotationMoveDirectionPitch(float degreePitch) { angle_pitch_ = degreePitch; }
	void SetRotationMoveDirectionRoll(float degreeRoll)	  { angle_roll_  = degreeRoll; }


	// �ړ��x�N�g���̒���
	void SetMoveVectorLength(float moveVectorLength) { move_vector_length_ = moveVectorLength; }

	// �ő�̎��s����
	void SetMaxExecuteTime(float maxExecuteTime) { max_execute_time_ = maxExecuteTime; }

	// �ړ��A�N�V�����̐[���̐ݒ�
	void SetMoveActionMagnitude(float moveActionMagnitude) { move_action_magnitude_ = moveActionMagnitude; }


protected:
	// �G��AI�R���|�[�l���g
	class EnemyAIComponent*   enemy_ai_;

	// �ړ��R���|�[�l���g
	class EnemyMoveComponent* enemy_move_;

protected:

	//
	// ���W�̐ݒ�
	//

	// �n�_���W
	D3DXVECTOR3 position_start_;	

	// �ړ��x�N�g���̌������
	float		angle_yaw_;		// �ړ��x�N�g���̌����Fyaw
	float		angle_pitch_;	// �ړ��x�N�g���̌����Fpitch
	float		angle_roll_;	// �ړ��x�N�g���̌����Froll

	// �ړ��x�N�g���̒���
	float		move_vector_length_;

	// �ړ��A�N�V�����̐[��
	float		move_action_magnitude_;

	// �ő�̎��s����
	float		max_execute_time_;	
};

#endif //ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/