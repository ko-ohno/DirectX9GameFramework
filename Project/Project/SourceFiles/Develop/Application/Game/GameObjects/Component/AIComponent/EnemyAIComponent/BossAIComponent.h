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

	void EnemyStateController(float deltaTime);

	void ChangeState(class BossEnemyStateMachine* bossStateMachine);

	void Idle(float deltaTime) override;
	void Enter(float deltaTime) override;
	void BodyPress(float deltaTime) override;
	void Shoot(float deltaTime) override;
	void LaserCannon(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BossAIComponent; };

private:
	// �ő�̃X�e�[�g�̐�
	static constexpr int MAX_STATE_ARRAY_SIZE = 3;

	// �G�̏�Ԃ̍s�����̔z��
	EnemyState enemy_state_array_[MAX_STATE_ARRAY_SIZE];
	int		   array_index_;
	bool	   is_state_change_;

	// �X�e�[�g�̎��s����
	float	   state_exe_time_;

private:
	class BossEnemyStateMachine* boss_state_machine_;
};

/*-------------------------------------
/* �{�X�̃X�e�[�g�}�V�����`
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
/* �{�X�̑ҋ@�s���N���X
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
/* �{�X�̑ҋ@�s���N���X
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
/* �{�X�̑̓�����U���N���X
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
/* �{�X�̏e���s���N���X
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
/* ���[�U�[�C�U�����x�N���X
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