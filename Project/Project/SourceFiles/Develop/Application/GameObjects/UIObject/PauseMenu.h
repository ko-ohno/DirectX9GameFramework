/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PauseMenu.h] ポーズメニュー画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ポーズメニュー画面の挙動を定義したクラス
=============================================================================*/
#ifndef PAUSE_MENU_H_
#define	PAUSE_MENU_H_

/*--- インクルードファイル ---*/
#include "../UIObject.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* ポーズメニュー画面クラス
-------------------------------------*/
class PauseMenu : public UIObject
{
public:
	PauseMenu(class GameManager* gameManager);
	~PauseMenu(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void Draw(void) override;

	virtual TypeID GetType(void) const { return TypeID::PauseMenu; }

private:

};


#endif //PAUSE_MENU_H_
/*=============================================================================
/*		End of File
=============================================================================*/