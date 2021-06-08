/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Boss.h] �{�X�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F �{�X�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef BOSS_H_
#define	BOSS_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  �{�X
-------------------------------------*/
enum class BossState
{
	None = -1
	, Enter
	, BodyPress
	, Shooting
	, LaserCannone
	, Max
};

/*-------------------------------------
/*  �G�Q�[���I�u�W�F�N�g
-------------------------------------*/
class Boss : public Enemy
{
public:
	Boss(class Game* game);
	~Boss(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Boss; }

	//
	// �{�X�̍s���X�e�[�g�̐ݒ�
	//

	BossState GetState(void) { return boss_state_; }
	void SetState(BossState bossState) { boss_state_ = bossState; }

private:
	BossState boss_state_;
	class BossAIComponent* boss_ai_;
};

#endif //BOSS_H_
/*=============================================================================
/*		End of File
=============================================================================*/