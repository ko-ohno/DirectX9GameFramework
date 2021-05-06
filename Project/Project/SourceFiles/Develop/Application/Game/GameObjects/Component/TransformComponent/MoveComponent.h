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
#include "../TransformComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 移動のコンポーネント
-------------------------------------*/
class MoveComponent : public TransformComponent
{
public:
	MoveComponent(class GameObject* owner, int updateOrder);
	~MoveComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::MoveComponent; };

private:

};


#endif //MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/