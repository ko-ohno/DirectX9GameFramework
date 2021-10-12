/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyAIComponent.h]  �{�XAI�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�XAI�R���|�[�l���g
=============================================================================*/
#ifndef WEAK_ENEMY_AI_COMPONENT_H_
#define	WEAK_ENEMY_AI_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyAIComponent.h"

/*-------------------------------------------
/* �{�XAI�R���|�[�l���g�F�X�e�[�g�}�V���쐬
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
/* �{�X�̃X�e�[�g�}�V�����`
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
/* �ア�G�̑ҋ@�s���N���X
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
/* �ア�G�̒����ړ��N���X
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
/* �ア�G�̒����ړ��N���X
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
/* �ア�G�������ɔ��~��`���ړ��N���X
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
/* �ア�G�������ɔ��~��`���ړ��N���X
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
/* �ア�G�̏㉺�ړ��N���X
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
/* �ア�G�̍��E���[�v�ړ��N���X
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
/* ��ʂ̒[����̊�o���ړ��N���X
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
/* S���J�[�u�ړ��N���X
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