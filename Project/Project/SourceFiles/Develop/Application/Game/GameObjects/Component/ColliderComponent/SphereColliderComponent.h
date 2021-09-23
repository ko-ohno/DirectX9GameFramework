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

	virtual void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::SphereColliderComponent; };

	//
	// 半径の設定
	//

	inline void SetRadius(float radius) { radius_ = radius; }
	inline float GetRadius(void) { return radius_; };

	//
	// 座標の設定 
	//

	inline void SetTranslation(Vector3& position) { position_ = position; }
	inline void SetTranslation(D3DXVECTOR3& position) { position_ = position; }
	inline void SetTranslation(float posX, float posY, float posZ) { position_ = { posX, posY, posZ }; }
	inline void SetTranslationX(float posX) { position_.x_ = posX; }
	inline void SetTranslationY(float posY) { position_.y_ = posY; }
	inline void SetTranslationZ(float posZ) { position_.z_ = posZ; }

	inline Vector3* GetPosition(void) { return &position_; }
};

#endif //SPHERE_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/