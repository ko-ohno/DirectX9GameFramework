/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PlayerInputComponent.h]  �v���C���[�̓��̓R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�v���C���[�̓��̓R���|�[�l���g�̃N���X��`
=============================================================================*/
#ifndef PLAYER_INPUT_COMPONENT_H_
#define	PLAYER_INPUT_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../InputComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �v���C���[�̓��̓R���|�[�l���g
-------------------------------------*/
class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent(class GameObject* owner, int updateOrder = 100);
	~PlayerInputComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::PlayerInputComponent; };

private:

};

#endif //PLAYER_INPUT_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/