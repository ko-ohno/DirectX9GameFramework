/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PlayerInputComponent.h]  プレイヤーの入力コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：プレイヤーの入力コンポーネントのクラス定義
=============================================================================*/
#ifndef PLAYER_INPUT_COMPONENT_H_
#define	PLAYER_INPUT_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../InputComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* プレイヤーの入力コンポーネント
-------------------------------------*/
class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent(class GameObject* owner, int updateOrder = 100);
	~PlayerInputComponent(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::PlayerInputComponent; };

private:

};

#endif //PLAYER_INPUT_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/