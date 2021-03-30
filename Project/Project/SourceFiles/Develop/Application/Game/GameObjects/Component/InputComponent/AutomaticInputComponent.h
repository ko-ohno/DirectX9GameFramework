/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AutomaticInputComponent.h]  デモプレイの自動入力コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：デモプレイの自動入力コンポーネントのクラス定義
=============================================================================*/
#ifndef AUTOMATIC_INPUT_COMPONENT_H_
#define	AUTOMATIC_INPUT_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../InputComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* デモプレイの自動入力コンポーネント
-------------------------------------*/
class AutomaticInputComponent : public InputComponent
{
public:
	AutomaticInputComponent(class GameObject* owner, int updateOrder = 100);
	~AutomaticInputComponent(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::AutomaticInputComponent; };

private:

};


#endif //AUTOMATIC_INPUT_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/