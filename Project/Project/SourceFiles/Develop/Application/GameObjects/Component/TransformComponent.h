/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TransformComponent.h]  姿勢制御コンポーネントのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：姿勢制御コンポーネントのベースになるクラス定義
=============================================================================*/
#ifndef TRANSFORM_COMPONENT_H_
#define	TRANSFORM_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 姿勢制御のコンポーネント
-------------------------------------*/
class TransformComponent : public Component
{
public:
	TransformComponent(class GameObject* owner, int updateOrder = 100);
	~TransformComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	void CallTransform(void);

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; };
private:
};

#endif //TRANSFORM_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/