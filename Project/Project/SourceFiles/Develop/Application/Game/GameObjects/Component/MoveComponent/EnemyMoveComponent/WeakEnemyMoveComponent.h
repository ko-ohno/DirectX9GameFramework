/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyMoveComponent.h]  �{�X�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�̈ړ��R���|�[�l���g
=============================================================================*/
#ifndef WEAK_ENEMY_MOVE_COMPONENT_H_
#define	WEAK_ENEMY_MOVE_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyMoveComponent.h"

/*-------------------------------------
/* �ア�G�̈ړ��R���|�[�l���g
-------------------------------------*/
class WeakEnemyMoveComponent : public EnemyMoveComponent
{
public:
	WeakEnemyMoveComponent(class GameObject* owner, int updateOrder = 100);
	~WeakEnemyMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::WeakEnemyMoveComponent; };

	//
	// �ア�G�̎��ۂ̋�����ݒ�
	//

	virtual void MoveActionIdle(float deltaTime) override;					// �ҋ@�s��
	virtual void MoveActionStraight(float deltaTime) override;				// �����ړ�
	virtual void MoveActionStraightWaitOneTime(float deltaTime) override;	// �����ړ����҂�
	virtual void MoveActionStraightWaitUpDown(float deltaTime) override;	// �����ړ����Ĉ��҂�
	virtual void MoveActionRoundVertical(float deltaTime) override;			// �����ɔ��~��`���F�b
	virtual void MoveActionRoundHorizontal(float deltaTime) override;		// �����ɔ��~��`���F��
	virtual void MoveActionLoopUpDown(float deltaTime) override;			// �㉺�s�������[�v
	virtual void MoveActionLoopLeftRight(float deltaTime) override;			// ���E�s�������[�v
	virtual void MoveActionShowOneTime(float deltaTime) override;			// ��x�����A�Ђ�������o������ 

private:
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/