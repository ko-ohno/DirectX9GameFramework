/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TransformComponent.h]  �p������R���|�[�l���g�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�p������R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef TRANSFORM_COMPONENT_H_
#define	TRANSFORM_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �p������̃R���|�[�l���g
-------------------------------------*/
class TransformComponent : public Component
{
public:
	TransformComponent(class GameObject* owner, int updateOrder = 100);
	~TransformComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	void CallTransform(void);

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; };
private:
};

#endif //TRANSFORM_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/