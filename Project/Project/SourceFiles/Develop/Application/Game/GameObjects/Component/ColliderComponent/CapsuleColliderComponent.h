/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CapsuleColliderComponent.h]  �J�v�Z���R���C�_�̃R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�v�Z���R���C�_�R���|�[�l���g�̃N���X��`
=============================================================================*/
#ifndef CAPSULE_COLLIDER_COMPONENT_H_
#define	CAPSULE_COLLIDER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ColliderComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �J�v�Z���R���C�_�̃R���|�[�l���g
-------------------------------------*/
class CapsuleColliderComponent : public ColliderComponent
{
public:
	CapsuleColliderComponent(class GameObject* owner, int updateOrder = 100);
	~CapsuleColliderComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::CapsuleColliderComponent; };


private:
};

#endif //CAPSULE_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/