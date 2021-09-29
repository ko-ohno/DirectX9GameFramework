/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemy.h] �ア�G�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F �ア�G�̃Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef WEAK_ENEMY_H_
#define	WEAK_ENEMY_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  �G�Q�[���I�u�W�F�N�g
-------------------------------------*/
class WeakEnemy : public Enemy
{
public:
	WeakEnemy(class Game* game);
	~WeakEnemy(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::WeakEnemy; }

	// �Փ˔���̍X�V
	void UpdateCollision(float deltaTime);

	void TestMoveStraight();
	void TestMoveStraightWaitOneTime();
	void TestMoveRoundVertical();
	void TestMoveRoundHorizontal();
	void TestMoveLoopUpDown();
	void TestMoveLoopLeftRight();
	void TestMoveShowOneTime();
	void TestMoveStraightWaitUpDown();

private:
};

#endif //WeakEnemy_H_
/*=============================================================================
/*		End of File
=============================================================================*/