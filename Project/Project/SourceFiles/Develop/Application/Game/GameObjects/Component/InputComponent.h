/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputComponent.h] 入力コンポーネントのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：入力コンポーネントのコンポーネントのベースになるクラス定義
=============================================================================*/
#ifndef INPUT_COMPONENT_H_
#define	INPUT_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"
#include "../GameObject.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 入力コンポーネントのベースクラス
-------------------------------------*/
class InputComponent : public Component
{
public:
	InputComponent(class GameObject* owner, int updateOrder = 100);
	~InputComponent(void);

	TypeID GetComponentType(void) const override { return TypeID::InputComponent; }

private:
protected:
	//入力部分のベース
	//class ButtonX* button_x_;
	//class ButtonY* button_y_;
	//class ButtonA* button_a_;
	//class ButtonB* button_b_;
};


#endif //INPUT_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/