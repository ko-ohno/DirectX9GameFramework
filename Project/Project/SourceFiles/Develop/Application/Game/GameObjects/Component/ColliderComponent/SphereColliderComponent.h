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
	float	radius_;

public:
	SphereColliderComponent(class GameObject* owner, int updateOrder = 100);
	~SphereColliderComponent(void);

	virtual void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::SphereColliderComponent; };

	//
	// 半径の設定
	//

	inline void SetRadius(float radius) { radius_ = radius; }
	inline float GetRadius(void) { return radius_; };
};

#endif //SPHERE_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/