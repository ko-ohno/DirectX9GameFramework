/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderComponent.h] AIビヘイビアのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：AIビヘイビアコンポーネントのベースになるクラス定義
=============================================================================*/
#ifndef COLLIDER_COMPONENT_H_
#define	COLLIDER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"
#include "../../../Math.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* AIビヘイビアコンポーネントのベースクラス
-------------------------------------*/
class ColliderComponent : public Component
{
public:
	Vector3 position_;
	Vector3 offset_position_;

public:
	ColliderComponent(class GameObject* owner, int updateOrder = 100);
	~ColliderComponent(void);

	virtual void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::ColliderComponent; };

	//
	// 座標の設定 
	//

	inline void SetOffsetTranslation(Vector3& position) { offset_position_ = position; }
	inline void SetOffsetTranslation(D3DXVECTOR3& position) { offset_position_ = position; }
	inline void SetOffsetTranslation(float posX, float posY, float posZ) { offset_position_ = { posX, posY, posZ }; }
	inline void SetOffsetTranslationX(float posX) { offset_position_.x_ = posX; }
	inline void SetOffsetTranslationY(float posY) { offset_position_.y_ = posY; }
	inline void SetOffsetTranslationZ(float posZ) { offset_position_.z_ = posZ; }

	// 位置座標の取得
	inline Vector3* GetPosition(void) { return &position_; }

private:
protected:
};

#endif //COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/