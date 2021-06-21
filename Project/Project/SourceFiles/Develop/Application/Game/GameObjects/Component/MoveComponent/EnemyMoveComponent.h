/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyMoveComponent.h]  敵の移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：敵の移動コンポーネントのクラス定義
=============================================================================*/
#ifndef ENEMY_MOVE_COMPONENT_H_
#define	ENEMY_MOVE_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../MoveComponent.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"

/*-------------------------------
/* 敵のモーション状態
-------------------------------*/
enum class EnemyMotionState
{
	None = -1
	, StartUp	// 攻撃の立ち上がり
	, Relay		// 攻撃への移行状態
	, Attack	// 実際の攻撃状態

	, FromRight	// 右から登場
	, FromLeft	// 左から登場
	, FromTop	// 上から登場
	, FromUnder	// 下から登場
	, Complete	// 完了状態
	, End		// 終了状態

	, Max
};

/*-------------------------------------
/* 敵の移動コンポーネント
-------------------------------------*/
class EnemyMoveComponent : public MoveComponent
{
public:
	EnemyMoveComponent(class GameObject* owner, int updateOrder);
	~EnemyMoveComponent(void);


	//
	// 敵AIの状態を設定
	//

	void SetEnemyState(EnemyState enemyState) { enemy_state_ = enemyState; }

	//
	// 移動アクションを指定
	//

	void GetMotionState(EnemyMotionState enemyMotionState) { enemy_motion_state_ = enemyMotionState; }
	EnemyMotionState GetMotionState(void) const { return enemy_motion_state_; }

	virtual TypeID GetComponentType() const override { return TypeID::EnemyMoveComponent; };

protected:
	//
	// 敵のモーション状態
	//

	enum class EnemyMotionState  enemy_motion_state_;

	//
	// 敵の状態
	//

	enum class EnemyState		 enemy_state_;
	enum class EnemyState		 enemy_state_old_;
};

#endif //ENEMY_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/