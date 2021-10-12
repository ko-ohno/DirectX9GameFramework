/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyAIComponent.h]  ボスAIコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスAIコンポーネント
=============================================================================*/
#ifndef WEAK_ENEMY_AI_COMPONENT_H_
#define	WEAK_ENEMY_AI_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../EnemyAIComponent.h"

/*-------------------------------------------
/* ボスAIコンポーネント：ステートマシン作成
-------------------------------------------*/
class WeakEnemyAIComponent : public EnemyAIComponent
{
public:
	WeakEnemyAIComponent(class GameObject* owner, int updateOrder = 100);
	~WeakEnemyAIComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	void EnemyStateController(void);

	void ChangeState(class WeakEnemyStateMachine* weakEnemyStateMachine);

	void Idle(float deltaTime) override;
	void MoveStraight(float deltaTime) override;
	void MoveStraightWaitOneTime(float deltaTime) override;
	void MoveStraightWaitUpDown(float deltaTime) override;
	void MoveRoundVertical(float deltaTime) override;
	void MoveRoundHorizontal(float deltaTime) override;
	void MoveLoopUpDown(float deltaTime) override;
	void MoveLoopLeftRight(float deltaTime) override;
	void MoveShowOneTime(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::WeakEnemyAIComponent; };

private:
	class WeakEnemyStateMachine* weak_enemy_state_machine_;
};

/*-------------------------------------
/* ボスのステートマシンを定義
-------------------------------------*/
class WeakEnemyStateMachine
{
public:
	WeakEnemyStateMachine(void) {}
	virtual ~WeakEnemyStateMachine(void) {}

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime) = 0;
};

/*-------------------------------------
/* 弱い敵の待機行動クラス
-------------------------------------*/
class WeakEnemyStateIdle : public WeakEnemyStateMachine
{
public:
	WeakEnemyStateIdle(void)
	{}
	~WeakEnemyStateIdle(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->Idle(deltaTime);
	}

private:
};

/*-------------------------------------
/* 弱い敵の直線移動クラス
-------------------------------------*/
class WeakEnemyStateMoveStraight : public WeakEnemyStateMachine
{
public:
	WeakEnemyStateMoveStraight(void)
	{}
	~WeakEnemyStateMoveStraight(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveStraight(deltaTime);
	}

private:
};

/*-------------------------------------
/* 弱い敵の直線移動クラス
-------------------------------------*/
class WeakEnemyStateMoveStraightWaitOneTime : public WeakEnemyStateMachine
{
public:
	WeakEnemyStateMoveStraightWaitOneTime(void)
	{}
	~WeakEnemyStateMoveStraightWaitOneTime(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveStraightWaitOneTime(deltaTime);
	}

private:
};

/*-------------------------------------
/* 弱い敵が垂直に半円を描く移動クラス
-------------------------------------*/
class WeakEnemyStateMoveRoundVertical : public WeakEnemyStateMachine
{
public:
	WeakEnemyStateMoveRoundVertical(void)
	{}
	~WeakEnemyStateMoveRoundVertical(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveRoundVertical(deltaTime);
	}

private:
};

/*-------------------------------------
/* 弱い敵が水平に半円を描く移動クラス
-------------------------------------*/
class WeakEnemyStateMoveRoundHorizontal : public WeakEnemyStateMachine
{
public:
	WeakEnemyStateMoveRoundHorizontal(void)
	{}
	~WeakEnemyStateMoveRoundHorizontal(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveRoundHorizontal(deltaTime);
	}

private:
};

/*-------------------------------------
/* 弱い敵の上下移動クラス
-------------------------------------*/
class WeakEnemyStateMoveLoopUpDown : public WeakEnemyStateMachine
{
public:
	WeakEnemyStateMoveLoopUpDown(void)
	{}
	~WeakEnemyStateMoveLoopUpDown(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveLoopUpDown(deltaTime);
	}

private:
};

/*-------------------------------------
/* 弱い敵の左右ループ移動クラス
-------------------------------------*/
class WeakEnemyStateMoveLoopLeftRight : public WeakEnemyStateMachine
{
public:
	WeakEnemyStateMoveLoopLeftRight(void)
	{}
	~WeakEnemyStateMoveLoopLeftRight(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveLoopLeftRight(deltaTime);
	}

private:
};

/*-------------------------------------
/* 画面の端からの顔出し移動クラス
-------------------------------------*/
class WeakEnemyStateMoveShowOneTime : public WeakEnemyStateMachine
{
public:
	WeakEnemyStateMoveShowOneTime(void)
	{}
	~WeakEnemyStateMoveShowOneTime(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveShowOneTime(deltaTime);
	}

private:
};

/*-------------------------------------
/* S字カーブ移動クラス
-------------------------------------*/
class WeakEnemyStateMoveStraightWaitUpDown : public WeakEnemyStateMachine
{
public:
	WeakEnemyStateMoveStraightWaitUpDown(void)
	{}
	~WeakEnemyStateMoveStraightWaitUpDown(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class WeakEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveSShapedCurve(deltaTime);
	}

private:
};

#endif //WEAK_ENEMY_AI_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/