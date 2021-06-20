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

	// AIの所有者の設定
	void SetEnemyAIOwner(class Enemy* enemyAIOwner) { ai_owner_ = enemyAIOwner; }

	// AIの所有者の設定
	void SetOwnerMoveComponent(class EnemyMoveComponent* moveComponent) { enemy_move_ = moveComponent; }

	// 所有者の状態を設定

	EnemyState GetEnemyState(void) { return enemy_state_; }
	void SetEnemyState(EnemyState enemyState) { enemy_state_ = enemyState; }

	// 体力の設定

	void SetMaxHitPoint(float maxHitPoint) { max_hit_point_ = maxHitPoint; }
	void SetHitPoint(float hitPoint) { hit_point_ = hitPoint; }
	float GetHitPoint(void) { return hit_point_; }

protected:
	// AIの所有者
	class Enemy*			  ai_owner_;

	// このAIが操作する移動コンポーネント
	class EnemyMoveComponent* enemy_move_;

	// エネミーのステート
	EnemyState enemy_state_;

	// 体力のパラメータ

	float max_hit_point_;
	float hit_point_;
};

#endif //ENEMY_AI_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/