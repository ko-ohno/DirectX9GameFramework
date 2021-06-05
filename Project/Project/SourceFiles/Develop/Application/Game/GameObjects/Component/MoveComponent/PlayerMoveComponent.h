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

	void UpdateMovementState(class Vector2& padThumb);
	//void UpdateMovement(float deltaTime);


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