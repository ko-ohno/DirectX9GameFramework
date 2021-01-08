/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereColliderComponent.h]  スフィアコライダのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スフィアコライダコンポーネントのクラス定義
=============================================================================*/
#ifndef SPHERE_COLLIDER_COMPONENT_H_
#define	SPHERE_COLLIDER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../ColliderComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* スフィアコライダのコンポーネント
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