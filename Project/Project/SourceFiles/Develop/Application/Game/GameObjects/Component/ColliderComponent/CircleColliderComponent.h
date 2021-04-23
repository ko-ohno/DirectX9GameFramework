/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CircleColliderComponent.h] サークルコライダのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：サークルコライダのコンポーネント
=============================================================================*/
#ifndef CIRCLE_COLLIDER_COMPONENT_H_
#define	CIRCLE_COLLIDER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../ColliderComponent.h"

/*-------------------------------------
/* サークルコライダのコンポーネント
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
	// 半径の設定
	//

	void SetRadius(float radius) { radius_ = radius; }
	float GetRadius(void) { return radius_; };

	//
	// 座標の設定 
	//

	void SetPosition(D3DXVECTOR2& position) { position_ = position; }
	void SetPosition(Vector2& position) { position_ = position; }
	Vector2* GetPosition(void) { return &position_; }
};

#endif //CIRCLE_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/