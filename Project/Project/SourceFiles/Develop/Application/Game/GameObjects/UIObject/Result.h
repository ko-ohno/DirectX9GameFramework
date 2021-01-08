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
#include "../UIObject.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* リザルト画面クラス
-------------------------------------*/
class Result : public UIObject
{
public:
	Result(class GameManager* gameManager);
	~Result(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void Draw(void) override;

	virtual TypeID GetType(void) const { return TypeID::Result; }

private:

};


#endif //RESULT_H_
/*=============================================================================
/*		End of File
=============================================================================*/