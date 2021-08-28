/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyAIComponent.h]  �����G��AI�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����G��AI�R���|�[�l���g
=============================================================================*/
#ifndef STRONG_ENEMY_AI_COMPONENT_H_
#define	STRONG_ENEMY_AI_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyAIComponent.h"

/*-------------------------------------------
/* �����G��AI�R���|�[�l���g�F�X�e�[�g�}�V���쐬
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
/* �{�X�̃X�e�[�g�}�V�����`
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
/* �����G�̑ҋ@�s���N���X
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
/* �����G�̒����ړ��N���X
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
/* �����G�̒����ړ��F�ꎞ�ҋ@�F�����ړ��N���X
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
/* �����G�̒����ړ��F������ꎞ�ҋ@
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
/* �����G�������ɔ��~��`���ړ��N���X
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
/* �����G�������ɔ��~��`���ړ��N���X
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
/* �����G�̏㉺�ړ��N���X
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
/* �����G�̍��E���[�v�ړ��N���X
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
/* ��ʂ̒[����̊�o���ړ��N���X
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