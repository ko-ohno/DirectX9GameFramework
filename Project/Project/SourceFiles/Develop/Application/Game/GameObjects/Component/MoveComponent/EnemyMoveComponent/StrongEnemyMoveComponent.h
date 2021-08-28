/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyMoveComponent.h]  �����G�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����G�̈ړ��R���|�[�l���g
=============================================================================*/
#ifndef BOSS_MOVE_COMPONENT_H_
#define	BOSS_MOVE_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyMoveComponent.h"


/*-------------------------------------
/* �����G�̈ړ��R���|�[�l���g
-------------------------------------*/
class StrongEnemyMoveComponent : public EnemyMoveComponent
{
public:
	StrongEnemyMoveComponent(class GameObject* owner, int updateOrder = 100);
	~StrongEnemyMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::StrongEnemyMoveComponent; };

	//
	// �����G�̎��ۂ̋�����ݒ�
	//

	void MoveActionIdle(float deltaTime) override;					// �ҋ@�s��
	void MoveActionStraight(float deltaTime) override;				// �܂������i��
	void MoveActionStraightWaitOneTime(float deltaTime) override;	// �܂������i��ň��҂�
	void MoveActionStraightWaitUpDown(float deltaTime) override;	// �܂������i��ň��҂�
	void MoveActionRoundVertical(float deltaTime) override;			// �����ɔ��~��`���F�b
	void MoveActionRoundHorizontal(float deltaTime) override;		// �����ɔ��~��`���F��
	void MoveActionLoopUpDown(float deltaTime) override;			// �㉺�s�������[�v
	void MoveActionLoopLeftRight(float deltaTime) override;			// ���E�s�������[�v
	void MoveActionShowOneTime(float deltaTime) override;			// ��x�����A�Ђ�������o������ 
	void MoveActionSShapedCurve(float deltaTime) override;			// S���J�[�u�ړ�

private:
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/