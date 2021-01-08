/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AutomaticInputComponent.h]  �f���v���C�̎������̓R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�f���v���C�̎������̓R���|�[�l���g�̃N���X��`
=============================================================================*/
#ifndef AUTOMATIC_INPUT_COMPONENT_H_
#define	AUTOMATIC_INPUT_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../InputComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �f���v���C�̎������̓R���|�[�l���g
-------------------------------------*/
class AutomaticInputComponent : public InputComponent
{
public:
	AutomaticInputComponent(class GameObject* owner, int updateOrder = 100);
	~AutomaticInputComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::AutomaticInputComponent; };

private:

};


#endif //AUTOMATIC_INPUT_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/