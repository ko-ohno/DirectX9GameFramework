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
	, StartUp	// �U���̗����オ��
	, Relay		// �U���ւ̈ڍs���
	, Attack	// ���ۂ̍U�����

	, FromRight	// �E����o��
	, FromLeft	// ������o��
	, FromTop	// �ォ��o��
	, FromUnder	// ������o��
	, Complete	// �������
	, End		// �I�����

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


	//
	// �GAI�̏�Ԃ�ݒ�
	//

	void SetEnemyState(EnemyState enemyState) { enemy_state_ = enemyState; }

	//
	// �ړ��A�N�V�������w��
	//

	void GetMotionState(EnemyMotionState enemyMotionState) { enemy_motion_state_ = enemyMotionState; }
	EnemyMotionState GetMotionState(void) const { return enemy_motion_state_; }

	virtual TypeID GetComponentType() const override { return TypeID::EnemyMoveComponent; };

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
};

#endif //ENEMY_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/