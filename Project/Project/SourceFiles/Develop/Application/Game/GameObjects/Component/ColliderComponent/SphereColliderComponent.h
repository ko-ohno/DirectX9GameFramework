/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereColliderComponent.h]  �X�t�B�A�R���C�_�̃R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�t�B�A�R���C�_�̃R���|�[�l���g
=============================================================================*/
#ifndef SPHERE_COLLIDER_COMPONENT_H_
#define	SPHERE_COLLIDER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ColliderComponent.h"

/*-------------------------------------
/* �X�t�B�A�R���C�_�̃R���|�[�l���g
-------------------------------------*/
class SphereColliderComponent : public ColliderComponent
{
public:
	float	radius_;

public:
	SphereColliderComponent(class GameObject* owner, int updateOrder = 100);
	~SphereColliderComponent(void);

	virtual void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::SphereColliderComponent; };

	//
	// ���a�̐ݒ�
	//

	inline void SetRadius(float radius) { radius_ = radius; }
	inline float GetRadius(void) { return radius_; };
};

#endif //SPHERE_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/