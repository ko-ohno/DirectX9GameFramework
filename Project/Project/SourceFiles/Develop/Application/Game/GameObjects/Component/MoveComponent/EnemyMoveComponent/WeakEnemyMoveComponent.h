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

private:

	// 現在座標
	D3DXVECTOR3 position_;

	// 回転角度
	float yaw_;
	float pitch_;
	float roll_;

	// 実行時間
	float execute_time_;
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/