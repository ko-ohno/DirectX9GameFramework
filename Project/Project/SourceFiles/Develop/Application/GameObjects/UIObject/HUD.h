/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[HUD.h] ゲーム画面のHUDクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲーム画面のHUDの挙動を定義したクラス
=============================================================================*/
#ifndef HUD_H_
#define	HUD_H_

/*--- インクルードファイル ---*/
#include "../UIObject.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* ゲーム画面のHUDクラス
-------------------------------------*/
class HUD : public UIObject
{
public:
	HUD(class GameManager* gameManager);
	~HUD(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void Draw(void) override;

	virtual TypeID GetType(void) const { return TypeID::HUD; }

private:

};


#endif //HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/