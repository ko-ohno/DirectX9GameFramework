/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CameraComponent.h] �J�����̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�����R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef CAMERA_COMPONENT_H_
#define	CAMERA_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �J�����R���|�[�l���g�̃x�[�X�N���X
-------------------------------------*/
class CameraComponent : public Component
{
public:
	CameraComponent(class GameObject* owner, int updateOrder = 100);
	~CameraComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	void CallComponent() override;

	virtual TypeID GetComponentType() const override { return TypeID::CameraComponent; };

private:
protected:
};

#endif //CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/