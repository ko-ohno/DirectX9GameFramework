/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossMoveComponent.h]  ボスの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスの移動コンポーネント
=============================================================================*/
#ifndef BOSS_MOVE_COMPONENT_H_
#define	BOSS_MOVE_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../MoveComponent.h"

/*-------------------------------
/* ボスの移動状態
-------------------------------*/
enum class BossState
{
	NONE = -1
	, ENTER
	, WAIT
	, BODY_BLOW
	, SHOOT
	, LASER_CANNON
};

/*-------------------------------
/* ボスの攻撃モーション状態
-------------------------------*/
enum class AttackAnimState
{
	NONE = -1
	, START_UP	//攻撃の立ち上がり
	, RELAY		//攻撃への移行状態
	, ATTACK	//実際の攻撃状態
	, END		//初期状態へ戻る
};

/*-------------------------------
/* ボスの登場モーションの状態
-------------------------------*/
enum class EnterAnimState
{
	NONE = -1
	, FROM_RIGHT	//右から左へ
	, FLOM_LEFT		//左から右へ
	, FLOM_TOP		//上からババーン！！する。
	, END			//待機行動へ移行　
};


/*-------------------------------------
/* ボスの移動コンポーネント
-------------------------------------*/
class BossMoveComponent : public MoveComponent
{
public:
	BossMoveComponent(class GameObject* owner, int updateOrder = 100);
	~BossMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BossMoveComponent; };

	void UpdateMovementState(class Vector2& padThumb);
	//void UpdateMovement(float deltaTime);


private:

	//　移動速度
	float move_speed_;
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/