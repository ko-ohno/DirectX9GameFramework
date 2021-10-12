/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyMoveComponent.h]  ボスの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスの移動コンポーネント
=============================================================================*/
#ifndef WEAK_ENEMY_MOVE_COMPONENT_H_
#define	WEAK_ENEMY_MOVE_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../EnemyMoveComponent.h"

/*-------------------------------------
/* 弱い敵の移動コンポーネント
-------------------------------------*/
class WeakEnemyMoveComponent : public EnemyMoveComponent
{
public:
	WeakEnemyMoveComponent(class GameObject* owner, int updateOrder = 100);
	~WeakEnemyMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::WeakEnemyMoveComponent; };

	//
	// 弱い敵の実際の挙動を設定
	//

	virtual void MoveActionIdle(float deltaTime) override;					// 待機行動
	virtual void MoveActionStraight(float deltaTime) override;				// 直線移動
	virtual void MoveActionStraightWaitOneTime(float deltaTime) override;	// 直線移動一回待つ
	virtual void MoveActionStraightWaitUpDown(float deltaTime) override;	// 直線移動して一回待つ
	virtual void MoveActionRoundVertical(float deltaTime) override;			// 垂直に半円を描く：｜
	virtual void MoveActionRoundHorizontal(float deltaTime) override;		// 水平に半円を描く：─
	virtual void MoveActionLoopUpDown(float deltaTime) override;			// 上下行動をループ
	virtual void MoveActionLoopLeftRight(float deltaTime) override;			// 左右行動をループ
	virtual void MoveActionShowOneTime(float deltaTime) override;			// 一度だけ、ひょっこり顔出しする 

private:
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/