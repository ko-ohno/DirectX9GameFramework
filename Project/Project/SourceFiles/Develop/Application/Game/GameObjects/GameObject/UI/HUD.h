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
#include "../UI.h"

/*-------------------------------------
/* ゲーム画面のHUDクラス
-------------------------------------*/
class HUD : public UI
{
public:
	HUD(class Game* game);
	~HUD(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::HUD; }

private:
};

#endif //HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/