/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TransformComponent.h]  移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：移動コンポーネントのクラス定義
=============================================================================*/
#ifndef MOVE_COMPONENT_H_
#define	MOVE_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 移動のコンポーネント
-------------------------------------*/
class MoveComponent : public Component
{
public:
	MoveComponent(class GameObject* owner, int updateOrder);
	~MoveComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::MoveComponent; };

protected:
	class TransformComponent* transform_component_;
};


#endif //MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/