/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Hoge.h] ロード画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ロード画面クラス
=============================================================================*/
#ifndef LOADING_SCREEN_H_
#define	LOADING_SCREEN_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* ロード画面クラス
-------------------------------------*/
class LoadingScreen : public UI
{
public:
	LoadingScreen(class Game* game);
	~LoadingScreen(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
};


#endif //HOGE_H_
/*=============================================================================
/*		End of File
=============================================================================*/