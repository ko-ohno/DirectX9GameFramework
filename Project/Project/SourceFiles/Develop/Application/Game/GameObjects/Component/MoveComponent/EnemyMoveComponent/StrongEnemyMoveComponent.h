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