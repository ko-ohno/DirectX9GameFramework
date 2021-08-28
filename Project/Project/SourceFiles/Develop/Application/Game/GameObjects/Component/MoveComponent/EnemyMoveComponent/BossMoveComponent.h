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
#include "../EnemyMoveComponent.h"


/*-------------------------------------
/* �{�X�̈ړ��R���|�[�l���g
-------------------------------------*/
class BossMoveComponent : public EnemyMoveComponent
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

	//
	// �{�X�̎��ۂ̋�����ݒ�
	//

	void MoveActionEnter(float deltaTime) override;
	void MoveActionIdle(float deltaTime) override; 
	void MoveActionBodyPress(float deltaTime) override;
	void MoveActionShoot(float deltaTime) override;
	void MoveActionLaserCannon(float deltaTime) override;

private:

	// ���ꂼ��̏������W
	static constexpr float offset_height_ = -3.0f;

	//
	// �o��Ɏg�����[�V�����̍��W
	//

	const D3DXVECTOR3 enter_from_right_idle_position_ = {  40.f,   0.f + offset_height_, 13.f };
	const D3DXVECTOR3 enter_from_left_idle_position_  = { -40.f,   0.f + offset_height_, 13.f };
	const D3DXVECTOR3 enter_from_under_idle_position_ = {   0.f, -30.f + offset_height_, 13.f };

	//
	// �U���Ɏg�����[�V�����̍��W
	//

	const D3DXVECTOR3 idle_position_				  = {   0.f,   0.f + offset_height_, 13.f };
	const D3DXVECTOR3 shoot_position_				  = {   0.f,   3.f + offset_height_, 20.f };
	const D3DXVECTOR3 body_press_startup_position_	  = {   0.f,   3.f + offset_height_, 16.f };
	const D3DXVECTOR3 body_press_position_			  = {   0.f,   0.f + offset_height_,  3.f };
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/