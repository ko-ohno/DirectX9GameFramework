/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossAIComponent.h]  ボスAIコンポーネント
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
class BossAIComponent : public EnemyAIComponent
{
public:
	BossAIComponent(class GameObject* owner, int updateOrder = 100);
	~BossAIComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	void EnemyStateController(float deltaTime);

	void ChangeState(class BossEnemyStateMachine* bossStateMachine);

	void Idle(float deltaTime) override;
	void Enter(float deltaTime) override;
	void BodyPress(float deltaTime) override;
	void Shoot(float deltaTime) override;
	void LaserCannon(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BossAIComponent; };

private:
	// 最大のステートの数
	static constexpr int MAX_STATE_ARRAY_SIZE = 3;

	// 敵の状態の行動順の配列
	EnemyState enemy_state_array_[MAX_STATE_ARRAY_SIZE];
	int		   array_index_;
	bool	   is_state_change_;

	// ステートの実行時間
	float	   state_exe_time_;

private:
	class BossEnemyStateMachine* boss_state_machine_;
};

/*-------------------------------------
/* ボスのステートマシンを定義
-------------------------------------*/
class BossEnemyStateMachine
{
public:
	BossEnemyStateMachine(void) {}
	virtual ~BossEnemyStateMachine(void) {}

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(class BossAIComponent* stateMachineOwner, float deltaTime) = 0;
};

/*-------------------------------------
/* ボスの待機行動クラス
-------------------------------------*/
class BossStateEnter : public BossEnemyStateMachine
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
	void Update(class BossAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->Enter(deltaTime);
	}

private:
};


/*-------------------------------------
/* ボスの待機行動クラス
-------------------------------------*/
class BossStateIdle : public BossEnemyStateMachine
{
public:
	BossStateIdle(void)
	{}
	~BossStateIdle(void) override
	{}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class BossAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->Idle(deltaTime);
	}

private:
};



/*-------------------------------------
/* ボスの体当たり攻撃クラス
-------------------------------------*/
class BossStateBodyPress : public BossEnemyStateMachine
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
	void Update(class BossAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->BodyPress(deltaTime);
	}

private:
};

/*-------------------------------------
/* ボスの銃撃行動クラス
-------------------------------------*/
class BossStateShooting : public BossEnemyStateMachine
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
	void Update(class BossAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->Shoot(deltaTime);
	}
private:
};

/*-------------------------------------
/* レーザー砲攻撃高度クラス
-------------------------------------*/
class BossStateLaserCannon : public BossEnemyStateMachine
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
	void Update(class BossAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->LaserCannon(deltaTime);
	}

private:
};



#endif //BOSS_AI_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/