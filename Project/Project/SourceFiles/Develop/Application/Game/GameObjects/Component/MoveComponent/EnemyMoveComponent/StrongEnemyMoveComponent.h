/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyMoveComponent.h]  強い敵の移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：強い敵の移動コンポーネント
=============================================================================*/
#ifndef BOSS_MOVE_COMPONENT_H_
#define	BOSS_MOVE_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../EnemyMoveComponent.h"


/*-------------------------------------
/* 強い敵の移動コンポーネント
-------------------------------------*/
class StrongEnemyMoveComponent : public EnemyMoveComponent
{
public:
	StrongEnemyMoveComponent(class GameObject* owner, int updateOrder = 100);
	~StrongEnemyMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::StrongEnemyMoveComponent; };

	//
	// 強い敵の実際の挙動を設定
	//

	void MoveActionIdle(float deltaTime) override;					// 待機行動
	void MoveActionStraight(float deltaTime) override;				// まっすぐ進む
	void MoveActionStraightWaitOneTime(float deltaTime) override;	// まっすぐ進んで一回待つ
	void MoveActionStraightWaitUpDown(float deltaTime) override;	// まっすぐ進んで一回待つ
	void MoveActionRoundVertical(float deltaTime) override;			// 垂直に半円を描く：｜
	void MoveActionRoundHorizontal(float deltaTime) override;		// 水平に半円を描く：─
	void MoveActionLoopUpDown(float deltaTime) override;			// 上下行動をループ
	void MoveActionLoopLeftRight(float deltaTime) override;			// 左右行動をループ
	void MoveActionShowOneTime(float deltaTime) override;			// 一度だけ、ひょっこり顔出しする 
	void MoveActionSShapedCurve(float deltaTime) override;			// S字カーブ移動

private:
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/