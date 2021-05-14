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
#include "../UI.h"

/*-------------------------------------
/* ポーズメニュー画面クラス
-------------------------------------*/
class PauseMenu : public UI
{
public:
	PauseMenu(class Game* game);
	~PauseMenu(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::PauseMenu; }

private:
};

#endif //PAUSE_MENU_H_
/*=============================================================================
/*		End of File
=============================================================================*/