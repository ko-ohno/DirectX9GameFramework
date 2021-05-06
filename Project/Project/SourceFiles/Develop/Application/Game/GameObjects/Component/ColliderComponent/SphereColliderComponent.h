/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereColliderComponent.h]  スフィアコライダのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スフィアコライダのコンポーネント
=============================================================================*/
#ifndef SPHERE_COLLIDER_COMPONENT_H_
#define	SPHERE_COLLIDER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../ColliderComponent.h"

/*-------------------------------------
/* スフィアコライダのコンポーネント
-------------------------------------*/
class SphereColliderComponent : public ColliderComponent
{
public:
	Vector3 position_;
	float	radius_;

public:
	SphereColliderComponent(class GameObject* owner, int updateOrder = 100);
	~SphereColliderComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::SphereColliderComponent; };

	//
	// 半径の設定
	//

	void SetRadius(float radius) { radius_ = radius; }
	float GetRadius(void) { return radius_; };

	//
	// 座標の設定 
	//

	void SetPosition(D3DXVECTOR3& position) { position_ = position; }
	void SetPosition(Vector3& position) { position_ = position; }
	Vector3* GetPosition(void) { return &position_; }
};

#endif //SPHERE_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/