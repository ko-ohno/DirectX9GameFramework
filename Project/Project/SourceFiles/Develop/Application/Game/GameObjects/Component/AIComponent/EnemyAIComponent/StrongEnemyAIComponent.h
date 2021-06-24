/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyAIComponent.h]  ボスAIコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスAIコンポーネント
=============================================================================*/
#ifndef BOSS_AI_COMPONENT_H_
#define	BOSS_AI_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../EnemyAIComponent.h"

/*-------------------------------------------
/* ボスAIコンポーネント：ステートマシン作成
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

	void ChangeState(class BossStateMachine* bossStateMachine);

	void Wait(float deltaTime);
	void Enter(float deltaTime);
	void BodyPress(float deltaTime);
	void Shoot(float deltaTime);
	void LaserCannon(float deltaTime);

	virtual TypeID GetComponentType() const override { return TypeID::StrongEnemyAIComponent; };

private:
	class BossStateMachine* boss_state_machine_;
};

/*-------------------------------------
/* ボスのステートマシンを定義
-------------------------------------*/
class BossStateMachine
{
public:
	BossStateMachine(void) {}
	virtual ~BossStateMachine(void) {}

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime) = 0;
};

/*-------------------------------------
/* ボスの待機行動クラス
-------------------------------------*/
class BossStateEnter : public BossStateMachine
{
public:
	BossStateEnter(void)
	{}
	~BossStateEnter(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->Enter(deltaTime);
	}

private:
};


/*-------------------------------------
/* ボスの待機行動クラス
-------------------------------------*/
class BossStateWait : public BossStateMachine
{
public:
	BossStateWait(void)
	{}
	~BossStateWait(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->Wait(deltaTime);
	}

private:
};



/*-------------------------------------
/* ボスの体当たり攻撃クラス
-------------------------------------*/
class BossStateBodyPress : public BossStateMachine
{
public:
	BossStateBodyPress(void)
	{}
	~BossStateBodyPress(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->BodyPress(deltaTime);
	}

private:
};

/*-------------------------------------
/* ボスの銃撃行動クラス
-------------------------------------*/
class BossStateShooting : public BossStateMachine
{
public:
	BossStateShooting(void)
	{}
	~BossStateShooting(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->Shoot(deltaTime);
	}
private:
};

/*-------------------------------------
/* レーザー砲攻撃高度クラス
-------------------------------------*/
class BossStateLaserCannon : public BossStateMachine
{
public:
	BossStateLaserCannon(void)
	{}
	~BossStateLaserCannon(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class StrongEnemyAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->LaserCannon(deltaTime);
	}

private:
};

#endif //BOSS_AI_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/