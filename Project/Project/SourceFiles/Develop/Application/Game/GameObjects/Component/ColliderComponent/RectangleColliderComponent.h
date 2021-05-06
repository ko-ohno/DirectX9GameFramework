/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[RectangleColliderComponent.h] レクタングルコライダのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：レクタングルコライダのコンポーネント
=============================================================================*/
#ifndef RECTANGLE_COLLIDER_COMPONENT_H_
#define	RECTANGLE_COLLIDER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../ColliderComponent.h"

/*-------------------------------------
/* レクタングルコライダのコンポーネント
-------------------------------------*/
class RectangleColliderComponent : public ColliderComponent
{
public:
	Vector2 position_;
	float width_;
	float height_; 

public:
	RectangleColliderComponent(class GameObject* owner, int updateOrder = 100);
	~RectangleColliderComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::RectangleColliderComponent; };

	Vector2* GetPosition(void) { return &position_; }
	void	 SetPosition(Vector2& position) { position_ = position; }
	void	 SetPosition(D3DXVECTOR2& position) { position_ = position; }

	//
	//　幅の設定
	//

	void  SetWidth(float width) { width_ = width; }
	float GetWidth(void) { return width_; }

	//
	//　高さの設定
	//

	void  SetHeight(float height) { height_ = height; }
	float GetHeight(void) { return height_; }

};


#endif //RECTANGLE_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/