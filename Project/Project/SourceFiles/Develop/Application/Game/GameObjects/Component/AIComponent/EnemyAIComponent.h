/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyAIComponent.h]  敵AIのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：敵AIコンポーネントのクラス定義
=============================================================================*/
#ifndef ENEMY_AI_COMPONENT_H_
#define	ENEMY_AI_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../AIComponent.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"
#include "../../Component/MoveComponent/EnemyMoveComponent.h"


/*-------------------------------------
/* 敵AIのコンポーネント
-------------------------------------*/
class EnemyAIComponent : public AIComponent
{
public:
	EnemyAIComponent(class GameObject* owner, int updateOrder = 100);
	~EnemyAIComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::EnemyAIComponent; };

	// 所有者の状態の設定

	EnemyState GetEnemyState(void) { return enemy_state_; }
	void SetEnemyState(EnemyState enemyState) { enemy_state_ = enemyState; }

	// モーションの状態の設定

	void SetMotionState(EnemyMotionState motionState_) { motion_state_ = motionState_; }

	// 体力の設定

	void SetMaxHitPoint(float maxHitPoint) { max_hit_point_ = maxHitPoint; }
	void SetHitPoint(float hitPoint) { hit_point_ = hitPoint; }
	float GetHitPoint(void) { return hit_point_; }

protected:	
	// 敵の状態
	EnemyState		 enemy_state_;

	// 敵のモーション状態
	EnemyMotionState motion_state_;

	// 体力のパラメータ

	float max_hit_point_;
	float hit_point_;
};

#endif //ENEMY_AI_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/