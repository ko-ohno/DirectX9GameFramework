/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameOver.h] ゲームオーバー画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームオーバー画面クラス
=============================================================================*/
#ifndef GAME_OVER_H_
#define	GAME_OVER_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* ゲームオーバー画面クラス
-------------------------------------*/
class GameOver : public UI
{
public:
	GameOver(class Game* game);
	~GameOver(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::GameOver; }

private:
};

#endif //GAME_OVER_H_
/*=============================================================================
/*		End of File
=============================================================================*/