/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AIComponent.h] AI�r�w�C�r�A�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FAI�r�w�C�r�A�R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef AI_COMPONENT_H_
#define	AI_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* AI�r�w�C�r�A�R���|�[�l���g�̃x�[�X�N���X
-------------------------------------*/
class AIComponent : public Component
{
public:
	AIComponent(class GameObject* owner, int updateOrder = 100);
	~AIComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::AIComponent; };

private:
protected:
};

#endif //AI_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/