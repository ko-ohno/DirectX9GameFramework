/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossMoveComponent.h]  �{�X�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�̈ړ��R���|�[�l���g
=============================================================================*/
#ifndef BOSS_MOVE_COMPONENT_H_
#define	BOSS_MOVE_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../MoveComponent.h"

/*-------------------------------
/* �{�X�̈ړ����
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
/* �{�X�̍U�����[�V�������
-------------------------------*/
enum class AttackAnimState
{
	NONE = -1
	, START_UP	//�U���̗����オ��
	, RELAY		//�U���ւ̈ڍs���
	, ATTACK	//���ۂ̍U�����
	, END		//������Ԃ֖߂�
};

/*-------------------------------
/* �{�X�̓o�ꃂ�[�V�����̏��
-------------------------------*/
enum class EnterAnimState
{
	NONE = -1
	, FROM_RIGHT	//�E���獶��
	, FLOM_LEFT		//������E��
	, FLOM_TOP		//�ォ��o�o�[���I�I����B
	, END			//�ҋ@�s���ֈڍs�@
};


/*-------------------------------------
/* �{�X�̈ړ��R���|�[�l���g
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

	//�@�ړ����x
	float move_speed_;
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/