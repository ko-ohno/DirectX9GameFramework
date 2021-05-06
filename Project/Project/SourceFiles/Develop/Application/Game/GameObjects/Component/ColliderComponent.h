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
	ColliderComponent(class GameObject* owner, int updateOrder = 100);
	~ColliderComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::ColliderComponent; };

private:
protected:
};

#endif //COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/