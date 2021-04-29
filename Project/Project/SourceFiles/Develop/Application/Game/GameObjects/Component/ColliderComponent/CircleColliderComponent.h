/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CircleColliderComponent.h] �T�[�N���R���C�_�̃R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�T�[�N���R���C�_�̃R���|�[�l���g
=============================================================================*/
#ifndef CIRCLE_COLLIDER_COMPONENT_H_
#define	CIRCLE_COLLIDER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ColliderComponent.h"

/*-------------------------------------
/* �T�[�N���R���C�_�̃R���|�[�l���g
-------------------------------------*/
class CircleColliderComponent : public ColliderComponent
{
public:
	Vector2 position_;
	float	radius_;

public:
	CircleColliderComponent(class GameObject* owner, int updateOrder = 100);
	~CircleColliderComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::CircleColliderComponent; };

	//
	// ���a�̐ݒ�
	//

	void SetRadius(float radius) { radius_ = radius; }
	float GetRadius(void) { return radius_; };

	//
	// ���W�̐ݒ� 
	//

	void SetPosition(D3DXVECTOR2& position) { position_ = position; }
	void SetPosition(Vector2& position) { position_ = position; }
	Vector2* GetPosition(void) { return &position_; }
};

#endif //CIRCLE_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/