/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputComponent.h] ���̓R���|�[�l���g�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���̓R���|�[�l���g�̃R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef INPUT_COMPONENT_H_
#define	INPUT_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"
#include "../GameObject.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* ���̓R���|�[�l���g�̃x�[�X�N���X
-------------------------------------*/
class InputComponent : public Component
{
public:
	InputComponent(class GameObject* owner, int updateOrder = 100);
	~InputComponent(void);

	TypeID GetComponentType(void) const override { return TypeID::InputComponent; }

private:
protected:
	//���͕����̃x�[�X
	//class ButtonX* button_x_;
	//class ButtonY* button_y_;
	//class ButtonA* button_a_;
	//class ButtonB* button_b_;
};


#endif //INPUT_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/