/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Title.h] タイトル画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：タイトル画面の挙動を定義したクラス
=============================================================================*/
#ifndef TITLE_H_
#define	TITLE_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* タイトル画面クラス
-------------------------------------*/
class Title : public UI
{
public:
	Title(class Game* game);
	~Title(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Title; } 

private:
};

#endif //TITLE_H_
/*=============================================================================
/*		End of File
=============================================================================*/