/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossAIComponent.h]  �{�XAI�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�XAI�R���|�[�l���g
=============================================================================*/
#ifndef BOSS_AI_COMPONENT_H_
#define	BOSS_AI_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyAIComponent.h"

/*-------------------------------------------
/* �{�XAI�R���|�[�l���g�F�X�e�[�g�}�V���쐬
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

	void ChangeState(class BossStateMachine* bossStateMachine);

	void Wait(float deltaTime);
	void Enter(float deltaTime);
	void BodyPress(float deltaTime);
	void Shoot(float deltaTime);
	void LaserCannon(float deltaTime);

	virtual TypeID GetComponentType() const override { return TypeID::BossAIComponent; };
private:
	class Actor*			boss_actor_adress_;
	class BossStateMachine* boss_state_machine_;
};

/*-------------------------------------
/* �{�X�̃X�e�[�g�}�V�����`
-------------------------------------*/
class BossStateMachine
{
public:
	BossStateMachine(void) {}
	virtual ~BossStateMachine(void) {}

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(class BossAIComponent* stateMachineOwner, float deltaTime) = 0;
};

/*-------------------------------------
/* �{�X�̑ҋ@�s���N���X
-------------------------------------*/
class BossStateEnter : public BossStateMachine
{
public:
	BossStateEnter(void)
	{
		this->Init();
	}
	~BossStateEnter(void) override
	{
		this->Uninit();
	}

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
/* �{�X�̑ҋ@�s���N���X
-------------------------------------*/
class BossStateWait : public BossStateMachine
{
public:
	BossStateWait(void)
	{
		this->Init();
	}
	~BossStateWait(void) override
	{
		this->Uninit();
	}

	void Init(void) override
	{}
	void Uninit(void) override
	{}
	void Update(class BossAIComponent* stateMachineOwner, float deltaTime)  override
	{
		stateMachineOwner->Wait(deltaTime);
	}

private:
};



/*-------------------------------------
/* �{�X�̑̓�����U���N���X
-------------------------------------*/
class BossStateBodyblow : public BossStateMachine
{
public:
	BossStateBodyblow(void)
	{
		this->Init();
	}
	~BossStateBodyblow(void) override
	{
		this->Uninit();
	}

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
/* �{�X�̏e���s���N���X
-------------------------------------*/
class BossStateShoot : public BossStateMachine
{
public:
	BossStateShoot(void)
	{
		this->Init();
	}
	~BossStateShoot(void) override
	{
		this->Uninit();
	}

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
/* ���[�U�[�C�U�����x�N���X
-------------------------------------*/
class BossStateLaserCannon : public BossStateMachine
{
public:
	BossStateLaserCannon(void)
	{
		this->Init();
	}
	~BossStateLaserCannon(void) override
	{
		this->Uninit();
	}

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