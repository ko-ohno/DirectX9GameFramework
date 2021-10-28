/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemy.h] �ア�G�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F �ア�G�̃Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef STRONG_ENEMY_H_
#define	STRONG_ENEMY_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  �G�Q�[���I�u�W�F�N�g
-------------------------------------*/
class StrongEnemy : public Enemy
{
public:
	StrongEnemy(class Game* game);
	~StrongEnemy(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::StrongEnemy; }

	// �����e�̍X�V
	void UpdateBlaster(float deltaTime, enum class EnemyState enemyState, enum class EnemyMotionState motionState);

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
	//
	// �G�t�F�N�g�R���|�[�l���g
	//
	class EffectRendererComponent*		effect_enemy_action_shoot_;

private:
	static constexpr float				ATTACK_VALUE_SHOOT		= 5.f;

	// �G�̕���R���|�[�l���g
	class EnemyBlasterWeaponComponent*	enemy_blaster_;

	// �u���X�^�[�𔭎˂���܂ł̎���
	float								blaster_execute_time_;

	// ����̔��˗p
	bool								is_ready_;
	bool								is_fire_;
};

#endif //STRONG_ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/