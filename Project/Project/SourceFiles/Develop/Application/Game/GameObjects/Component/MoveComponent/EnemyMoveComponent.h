/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyMoveComponent.h]  �G�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�̈ړ��R���|�[�l���g�̃N���X��`
=============================================================================*/
#ifndef ENEMY_MOVE_COMPONENT_H_
#define	ENEMY_MOVE_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../MoveComponent.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"

/*-------------------------------
/* �G�̃��[�V�������
-------------------------------*/
enum class EnemyMotionState
{
	None = -1
	, Idle			// �ҋ@���
	, StartUp		// �U���̗����オ��
	, Relay			// �U���ւ̈ڍs���
	, Attack		// ���ۂ̍U�����
	, MoveState_0	// �ړ��X�e�[�g_0
	, MoveState_1	// �ړ��X�e�[�g_1
	, MoveState_2	// �ړ��X�e�[�g_2
	, MoveState_3	// �ړ��X�e�[�g_3
	, MoveState_4	// �ړ��X�e�[�g_4
	, Complete		// �������
	, End			// �I�����

	, Max
};

/*-------------------------------------
/* �G�̈ړ��R���|�[�l���g
-------------------------------------*/
class EnemyMoveComponent : public MoveComponent
{
public:
	EnemyMoveComponent(class GameObject* owner, int updateOrder);
	~EnemyMoveComponent(void);

	// �����x�N�g���̌v�Z
	void ComputeMoveDirection(void);

	//
	// �GAI�̏�Ԃ�ݒ�
	//

	void SetEnemyState(EnemyState enemyState) { enemy_state_ = enemyState; }
	
	//
	// �ړ����W�̐ݒ�
	//

	// �n�_���W�̐ݒ�

	void SetStartPosition(const D3DXVECTOR3& startPosition ) { position_start_ = startPosition; }
	void SetStartPosition(float posX, float posY, float posZ) { position_start_ = { posX, posY, posZ }; }
	void SetStartPositionX(float posX) { position_start_.x = posX; }
	void SetStartPositionY(float posY) { position_start_.y = posY; }
	void SetStartPositionZ(float posZ) { position_start_.z = posZ; }

	// �����x�N�g���̉�]�̐ݒ�

	void SetRotationMoveDirection(float degreeYaw, float degreePitch, float degreeRoll)
	{
		angle_yaw_	 = degreeYaw;
		angle_pitch_ = degreePitch;
		angle_roll_  = degreeRoll;
	}

	void SetRotationMoveDirectionYaw(float degreeYaw)	  { angle_yaw_	 = degreeYaw; }
	void SetRotationMoveDirectionPitch(float degreePitch) { angle_pitch_ = degreePitch; }
	void SetRotationMoveDirectionRoll(float degreeRoll)   { angle_roll_  = degreeRoll; }


	// �ړ��x�N�g���̒���
	void SetMoveVectorLength(float moveVectorLength) { move_vector_length_ = moveVectorLength; }

	// �ő�̎��s����
	void SetMaxExecuteTime(float maxExecuteTime) { max_execute_time_ = maxExecuteTime; }

	// �ړ��A�N�V�����̐[���̐ݒ�
	void SetMoveActionMagnitude(float moveActionMagnitude) { move_action_magnitude_ = moveActionMagnitude; }

	//
	// �ړ����W�̌v�Z
	//
	void ComputeLerpPosition(void);

	//
	// ���[�V�����̏�Ԃ̐ݒ�E�擾
	//

	void GetMotionState(EnemyMotionState enemyMotionState) { enemy_motion_state_ = enemyMotionState; }
	EnemyMotionState GetMotionState(void) const { return enemy_motion_state_; }

	virtual TypeID GetComponentType() const override { return TypeID::EnemyMoveComponent; };

	// ���s���Ԃ̎擾
	float GetExecuteTime(void) { return execute_time_; }

	//
	// �G�̎��ۂ̋�����ݒ�
	//

	virtual void MoveActionIdle(float deltaTime);					// �ҋ@�s��
	virtual void MoveActionEnter(float deltaTime);					// �o��
	virtual void MoveActionBodyPress(float deltaTime);				// �̓�����
	virtual void MoveActionShoot(float deltaTime);					// �ˌ�
	virtual void MoveActionLaserCannon(float deltaTime);			// ���[�U�[�C	
	virtual void MoveActionStraight(float deltaTime);				// �����ړ�
	virtual void MoveActionStraightWaitOneTime(float deltaTime);	// �����ړ����҂�
	virtual void MoveActionStraightWaitUpDown(float deltaTime);		// �����ړ����ď㉺�^��������҂�
	virtual void MoveActionRoundVertical(float deltaTime);			// �����ɔ��~��`���F�b
	virtual void MoveActionRoundHorizontal(float deltaTime);		// �����ɔ��~��`���F��
	virtual void MoveActionLoopUpDown(float deltaTime);				// �㉺�s�������[�v
	virtual void MoveActionLoopLeftRight(float deltaTime);			// ���E�s�������[�v
	virtual void MoveActionShowOneTime(float deltaTime);			// ��x�����A�Ђ�������o������ 
	virtual void MoveActionSShapedCurve(float deltaTime);			// S���J�[�u�ړ�

protected:

	//
	// �G�̃��[�V�������
	//

	enum class EnemyMotionState  enemy_motion_state_;

	//
	// �G�̏��
	//

	enum class EnemyState		 enemy_state_;
	enum class EnemyState		 enemy_state_old_;

	//
	// �G�̍��W�֌W
	//

	// ���W�̌v�Z���K�v���H
	bool		is_need_compute_;

	// ���ݍ��W
	D3DXVECTOR3 position_;

	// ��Ԃ�����W
	D3DXVECTOR3 position_start_		//�@�n�_���W
			  , position_finish_;	//�@�I�_���W

	// 1�t���[���O�̎n�_���W
	D3DXVECTOR3 position_start_old_;

	// Y�����W�̈ꎞ�ۊǐ�
	float		position_y_start_	//�@�n�_���W
			  , position_y_finish_;	//�@�I�_���W

	// ���@�̉�]�p�x
	float		angle_yaw_;
	float		angle_pitch_;
	float		angle_roll_;

	// �E�x�N�g��
	D3DXVECTOR3 right_vector_;

	// �����x�N�g��
	D3DXVECTOR3 move_direction_;

	// �ړ��x�N�g���̒���
	float		move_vector_length_;

	// �ړ��A�N�V�����̐[��
	float		move_action_magnitude_;

	// �X�e�[�g���J��Ԃ�����
	int			state_loop_count_;

	// ���s����
	float		max_execute_time_;	// �ő�̎��s����
	float		execute_time_;		// ���݂̎��s����

	// ���@�̉�]�p�x
	float		yaw_;
	float		pitch_;
	float		roll_;
};

#endif //ENEMY_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/