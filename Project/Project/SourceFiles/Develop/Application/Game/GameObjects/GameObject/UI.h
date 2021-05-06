/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[UI.h] UIのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：このクラスから継承・派生させてUIオブジェクトを作成する
=============================================================================*/
#ifndef UI_H_
#define	UI_H_

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "../GameObject.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* UIのベースクラス
-------------------------------------*/
class UI : public GameObject
{
public:
	enum class State
	{
		None = -1
		, Active	//活動するUIオブジェクトか？
		, Closing	//停止するUIオブジェクトか？

		, MAX		//状態の最大値
	};

public:
	UI(class Game* game);
	virtual ~UI(void);

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Input(void);
	virtual void Update(float deltaTime);

	void Close(void) { state_ = State::Closing; }

	void SetState(State state) { state_ = state; };
	State GetState(void) { return state_; }

	virtual TypeID GetType(void) const { return TypeID::UI; } //後でoverrideできるように

protected:
	//UIObjectの所有者
	class Game* game_;

	//UIの状態
	State		state_;
};

#endif //UI_H_
/*=============================================================================
/*		End of File
=============================================================================*/