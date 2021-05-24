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
#include "../TransformComponent.h"

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
private:
};

#endif //PLAYER_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/