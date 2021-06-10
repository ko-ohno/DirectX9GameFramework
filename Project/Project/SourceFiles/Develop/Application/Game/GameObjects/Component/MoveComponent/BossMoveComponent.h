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
enum class BossMotionState
{
	NONE = -1
	, ENTER
	, WAIT
	, BODY_PRESS
	, SHOOT
	, LASER_CANNON
};

/*-------------------------------
/* �{�X�̍U�����[�V�������
-------------------------------*/
enum class AttackMotionState
{
	NONE = -1
	, START_UP	// �U���̗����オ��
	, RELAY		// �U���ւ̈ڍs���
	, ATTACK	// ���ۂ̍U�����
	, END		// ������Ԃ֖߂�
};

/*-------------------------------
/* �{�X�̓o�ꃂ�[�V�����̏��
-------------------------------*/
enum class EnterMotionState
{
	NONE = -1
	, FROM_RIGHT	// �E���獶��
	, FLOM_LEFT		// ������E��
	, FLOM_UNDER	// ������o�o�[���I�I����B
	, END			// �ҋ@�s���ֈڍs�@
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

	void MoveActionEnter(float deltaTime);
	void MoveActionWait(float deltaTime);
	void MoveActionBodyPress(float deltaTime);
	void MoveActionShoot(float deltaTime);
	void MoveActionLaserCannon(float deltaTime);

	//
	// �{�X�̏�Ԃ�ݒ�
	//
	BossMotionState GetBossMotionState(void) { return boss_motion_state_; }
	void SetBossMotionState(BossMotionState bossState) { boss_motion_state_ = bossState; }

private:
	// ���L�҂̃{�X�A�N�^�[
	class Actor* owner_boss_actor_;

	//
	// �{�X�̍s�����
	//

	EnterMotionState  enter_motion_state_;		// �{�X�̓o��̍s�����
	AttackMotionState attack_motion_state_;		// �{�X�̍U���̍s�����
	BossMotionState	  boss_motion_state_;		// �{�X�̍s�����
	BossMotionState	  boss_motion_state_old_;	// �{�X�̂P�t���[���O�̍s�����


	// ���ꂼ��̏������W
	static constexpr float offset_height_ = -3.0f;

	//
	// �o��Ɏg�����[�V�����̍��W
	//

	const D3DXVECTOR3 enter_from_right_wait_position_ = {  40.f,   0.f + offset_height_, 13.f };
	const D3DXVECTOR3 enter_from_left_wait_position_  = { -40.f,   0.f + offset_height_, 13.f };
	const D3DXVECTOR3 enter_from_under_wait_position_ = {   0.f, -30.f + offset_height_, 13.f };

	//
	// �U���Ɏg�����[�V�����̍��W
	//

	const D3DXVECTOR3 wait_position_				  = {   0.f,   0.f + offset_height_, 13.f };
	const D3DXVECTOR3 shoot_position_				  = {   0.f,   2.f + offset_height_, 20.f };
	const D3DXVECTOR3 body_press_startup_position_	  = {   0.f,   2.f + offset_height_, 16.f };
	const D3DXVECTOR3 body_press_position_			  = {   0.f,   0.f + offset_height_,  3.f };

	// ���ݍ��W
	D3DXVECTOR3 position_;

	// ��]�p�x
	float yaw_;
	float pitch_;
	float roll_;

	// ���s����
	float execute_time_;
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/