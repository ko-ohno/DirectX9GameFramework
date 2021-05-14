/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Result.h] リザルト画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：リザルト画面の挙動を定義したクラス
=============================================================================*/
#ifndef RESULT_H_
#define	RESULT_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* リザルト画面クラス
-------------------------------------*/
class Result : public UI
{
public:
	Result(class Game* game);
	~Result(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Result; }

private:
};

#endif //RESULT_H_
/*=============================================================================
/*		End of File
=============================================================================*/