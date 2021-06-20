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

	// AI�̏��L�҂̐ݒ�
	void SetEnemyAIOwner(class Enemy* enemyAIOwner) { ai_owner_ = enemyAIOwner; }

	// AI�̏��L�҂̐ݒ�
	void SetOwnerMoveComponent(class EnemyMoveComponent* moveComponent) { enemy_move_ = moveComponent; }

	// ���L�҂̏�Ԃ�ݒ�

	EnemyState GetEnemyState(void) { return enemy_state_; }
	void SetEnemyState(EnemyState enemyState) { enemy_state_ = enemyState; }

	// �̗͂̐ݒ�

	void SetMaxHitPoint(float maxHitPoint) { max_hit_point_ = maxHitPoint; }
	void SetHitPoint(float hitPoint) { hit_point_ = hitPoint; }
	float GetHitPoint(void) { return hit_point_; }

protected:
	// AI�̏��L��
	class Enemy*			  ai_owner_;

	// ����AI�����삷��ړ��R���|�[�l���g
	class EnemyMoveComponent* enemy_move_;

	// �G�l�~�[�̃X�e�[�g
	EnemyState enemy_state_;

	// �̗͂̃p�����[�^

	float max_hit_point_;
	float hit_point_;
};

#endif //ENEMY_AI_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/