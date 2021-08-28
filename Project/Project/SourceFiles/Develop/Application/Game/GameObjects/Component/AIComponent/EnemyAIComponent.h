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

	virtual void Idle(float deltaTime);							// 待機行動
	virtual void Enter(float deltaTime);						// 登場
	virtual void BodyPress(float deltaTime);					// 体当たり
	virtual void Shoot(float deltaTime);						// 射撃
	virtual void LaserCannon(float deltaTime);					// レーザー砲	
	virtual void MoveStraight(float deltaTime);					// 直線移動
	virtual void MoveStraightWaitOneTime(float deltaTime);		// 直線移動して一回待つ
	virtual void MoveStraightWaitUpDown(float deltaTime);		// 直線移動して上下運動して一回待つ
	virtual void MoveRoundVertical(float deltaTime);			// 垂直に半円を描く：｜
	virtual void MoveRoundHorizontal(float deltaTime);			// 水平に半円を描く：─
	virtual void MoveLoopUpDown(float deltaTime);				// 上下行動をループ
	virtual void MoveLoopLeftRight(float deltaTime);			// 左右行動をループ
	virtual void MoveShowOneTime(float deltaTime);				// 一度だけ、ひょっこり顔出しする
	virtual void MoveSShapedCurve(float deltaTime);				// S字カーブ移動

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