/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[RenderComponent.h] ���̓R���|�[�l���g�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���̓R���|�[�l���g�̃R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef RENDER_COMPONENT_H_
#define	RENDER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* ���̓R���|�[�l���g�̃x�[�X�N���X
-------------------------------------*/
class RenderComponent : public Component
{
public:
	RenderComponent(class GameObject* owner, int drawOrder = 100);
	~RenderComponent(void);

	TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

private:
protected:
};


#endif //RENDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/