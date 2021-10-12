/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyAIComponent.h]  強い敵のAIコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：強い敵のAIコンポーネント
=============================================================================*/
#ifndef STRONG_ENEMY_AI_COMPONENT_H_
#define	STRONG_ENEMY_AI_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../EnemyAIComponent.h"

/*-------------------------------------------
/* 強い敵のAIコンポーネント：ステートマシン作成
-------------------------------------------*/
class StrongEnemyAIComponent : public EnemyAIComponent
{
public:
	StrongEnemyAIComponent(class GameObject* owner, int updateOrder = 100);
	~StrongEnemyAIComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	void EnemyStateController(void);

	void ChangeState(class StrongEnemyStateMachine* strongEnemyStateMachine);

	void Idle(float deltaTime);
	void MoveStraight(float deltaTime);
	void MoveStraightWaitOneTime(float deltaTime);
	void MoveStraightWaitUpDown(float deltaTime);

	void MoveRoundVertical(float deltaTime);
	void MoveRoundHorizontal(float deltaTime);
	void MoveLoopUpDown(float deltaTime);
	void MoveLoopLeftRight(float deltaTime);
	void MoveShowOneTime(float deltaTime);

	virtual TypeID GetComponentType() const override { return TypeID::StrongEnemyAIComponent; };

private:
	class StrongEnemyStateMachine* strong_enemy_state_machine_;
};

/*-------------------------------------
/* ボスのステートマシンを定義
-------------------------------------*/
class StrongEnemyStateMachine
{
public:
	StrongEnemyStateMachine(void) {}
	virtual ~StrongEnemyStateMachine(void) {}

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime) = 0;
};

/*-------------------------------------
/* 強い敵の待機行動クラス
-------------------------------------*/
class StrongEnemyStateIdle : public StrongEnemyStateMachine
{
public:
	StrongEnemyStateIdle(void)
	{}
	~StrongEnemyStateIdle(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->Idle(deltaTime);
	}

private:
};

/*-------------------------------------
/* 強い敵の直線移動クラス
-------------------------------------*/
class StrongEnemyStateMoveStraight : public StrongEnemyStateMachine
{
public:
	StrongEnemyStateMoveStraight(void)
	{}
	~StrongEnemyStateMoveStraight(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveStraight(deltaTime);
	}

private:
};

/*----------------------------------------------
/* 強い敵の直線移動：一時待機：直線移動クラス
----------------------------------------------*/
class StrongEnemyStateMoveStraightWaitOneTime : public StrongEnemyStateMachine
{
public:
	StrongEnemyStateMoveStraightWaitOneTime(void)
	{}
	~StrongEnemyStateMoveStraightWaitOneTime(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveStraightWaitOneTime(deltaTime);
	}

private:
};

/*-------------------------------------
/* 強い敵の直線移動：複数回一時待機
-------------------------------------*/
class StrongEnemyStateMoveStraightWaitUpDown : public StrongEnemyStateMachine
{
public:
	StrongEnemyStateMoveStraightWaitUpDown(void)
	{}
	~StrongEnemyStateMoveStraightWaitUpDown(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveStraightWaitUpDown(deltaTime);
	}

private:
};

/*-------------------------------------
/* 強い敵が垂直に半円を描く移動クラス
-------------------------------------*/
class StrongEnemyStateMoveRoundVertical : public StrongEnemyStateMachine
{
public:
	StrongEnemyStateMoveRoundVertical(void)
	{}
	~StrongEnemyStateMoveRoundVertical(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveRoundVertical(deltaTime);
	}

private:
};

/*-------------------------------------
/* 強い敵が水平に半円を描く移動クラス
-------------------------------------*/
class StrongEnemyStateMoveRoundHorizontal : public StrongEnemyStateMachine
{
public:
	StrongEnemyStateMoveRoundHorizontal(void)
	{}
	~StrongEnemyStateMoveRoundHorizontal(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveRoundHorizontal(deltaTime);
	}

private:
};

/*-------------------------------------
/* 強い敵の上下移動クラス
-------------------------------------*/
class StrongEnemyStateMoveLoopUpDown : public StrongEnemyStateMachine
{
public:
	StrongEnemyStateMoveLoopUpDown(void)
	{}
	~StrongEnemyStateMoveLoopUpDown(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveLoopUpDown(deltaTime);
	}

private:
};

/*-------------------------------------
/* 強い敵の左右ループ移動クラス
-------------------------------------*/
class StrongEnemyStateMoveLoopLeftRight : public StrongEnemyStateMachine
{
public:
	StrongEnemyStateMoveLoopLeftRight(void)
	{}
	~StrongEnemyStateMoveLoopLeftRight(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveLoopLeftRight(deltaTime);
	}

private:
};

/*-------------------------------------
/* 画面の端からの顔出し移動クラス
-------------------------------------*/
class StrongEnemyStateMoveShowOneTime : public StrongEnemyStateMachine
{
public:
	StrongEnemyStateMoveShowOneTime(void)
	{}
	~StrongEnemyStateMoveShowOneTime(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->MoveShowOneTime(deltaTime);
	}

private:
};

#endif //STRONG_ENEMY_AI_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/