/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PlayerMoveComponent.h]  �v���C���[�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�v���C���[�̈ړ��R���|�[�l���g
=============================================================================*/
#ifndef PLAYER_MOVE_COMPONENT_H_
#define	PLAYER_MOVE_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../MoveComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/

/*-------------------------------------
/* �v���C���[�̈ړ��R���|�[�l���g
-------------------------------------*/
class PlayerMoveComponent : public MoveComponent
{
public:
	PlayerMoveComponent(class GameObject* owner, int updateOrder = 100);
	~PlayerMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::PlayerMoveComponent; };

	// �A�j���[�V�����̏�ʂ������ꍇ�̍X�V����
	void UpdateAnimationScene(float deltaTime);

	// �ړ��̏�ԍX�V����
	void UpdateMovementState(class Vector2& padThumb);

private:
	//�@�A�j���[�V�����̍ő���s����
	static constexpr float	MAX_ANIMATION_TIME  = 3.f;

	// ���݂̈ʒu���W
	D3DXVECTOR3				position_;

	// �A�j���[�V�����J�n�ʒu���W
	D3DXVECTOR3				position_animation_start_;
	
	// �A�j���[�V�����I���ʒu���W
	D3DXVECTOR3				position_animation_finish_;

	// �A�j���[�V�����̎��s����
	float					move_animation_time_;


private:
	// �v���C���[�̗V�я�
	class OBBColliderComponent* player_sandbox_;

	//�@�ǂ��ֈړ����邩
	bool is_move_top_;
	bool is_move_bottom_;
	bool is_move_left_;
	bool is_move_right_;

	//�@�ړ����x
	float move_speed_;
};

#endif //PLAYER_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/