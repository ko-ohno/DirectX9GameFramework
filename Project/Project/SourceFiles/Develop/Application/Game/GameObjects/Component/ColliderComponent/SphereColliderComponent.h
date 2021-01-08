/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereColliderComponent.h]  �X�t�B�A�R���C�_�̃R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�t�B�A�R���C�_�R���|�[�l���g�̃N���X��`
=============================================================================*/
#ifndef SPHERE_COLLIDER_COMPONENT_H_
#define	SPHERE_COLLIDER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ColliderComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �X�t�B�A�R���C�_�̃R���|�[�l���g
-------------------------------------*/
class SphereColliderComponent : public ColliderComponent
{
public:
	SphereColliderComponent(class GameObject* owner, int updateOrder = 100);
	~SphereColliderComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::SphereColliderComponent; };


private:
};

#endif //SPHERE_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/