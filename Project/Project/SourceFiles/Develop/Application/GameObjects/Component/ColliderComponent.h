/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderComponent.h] AI�r�w�C�r�A�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FAI�r�w�C�r�A�R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef COLLIDER_COMPONENT_H_
#define	COLLIDER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* AI�r�w�C�r�A�R���|�[�l���g�̃x�[�X�N���X
-------------------------------------*/
class ColliderComponent : public Component
{
public:
	ColliderComponent(class GameObject* owner, int updateOrder = 100);
	~ColliderComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::ColliderComponent; };

private:
protected:
};

#endif //COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/