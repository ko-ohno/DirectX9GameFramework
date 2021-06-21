/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyAIComponent.h]  �GAI�̃R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�GAI�R���|�[�l���g�̃N���X��`
=============================================================================*/
#ifndef ENEMY_AI_COMPONENT_H_
#define	ENEMY_AI_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../AIComponent.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"
#include "../../Component/MoveComponent/EnemyMoveComponent.h"


/*-------------------------------------
/* �GAI�̃R���|�[�l���g
-------------------------------------*/
class EnemyAIComponent : public AIComponent
{
public:
	EnemyAIComponent(class GameObject* owner, int updateOrder = 100);
	~EnemyAIComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::EnemyAIComponent; };

	// ���L�҂̏�Ԃ̐ݒ�

	EnemyState GetEnemyState(void) { return enemy_state_; }
	void SetEnemyState(EnemyState enemyState) { enemy_state_ = enemyState; }

	// ���[�V�����̏�Ԃ̐ݒ�

	void SetMotionState(EnemyMotionState motionState_) { motion_state_ = motionState_; }

	// �̗͂̐ݒ�

	void SetMaxHitPoint(float maxHitPoint) { max_hit_point_ = maxHitPoint; }
	void SetHitPoint(float hitPoint) { hit_point_ = hitPoint; }
	float GetHitPoint(void) { return hit_point_; }

protected:	
	// �G�̏��
	EnemyState		 enemy_state_;

	// �G�̃��[�V�������
	EnemyMotionState motion_state_;

	// �̗͂̃p�����[�^

	float max_hit_point_;
	float hit_point_;
};

#endif //ENEMY_AI_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/