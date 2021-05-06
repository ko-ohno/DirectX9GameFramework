/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CapsuleColliderComponent.h]  カプセルコライダのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カプセルコライダコンポーネントのクラス定義
=============================================================================*/
#ifndef CAPSULE_COLLIDER_COMPONENT_H_
#define	CAPSULE_COLLIDER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../ColliderComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* カプセルコライダのコンポーネント
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