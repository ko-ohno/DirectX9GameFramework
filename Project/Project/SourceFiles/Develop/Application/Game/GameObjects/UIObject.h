/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[UIObject.h] UIオブジェクトのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：このクラスから継承・派生させてUIオブジェクトを作成する
=============================================================================*/
#ifndef UI_OBJECT_H_
#define	UI_OBJECT_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* UIオブジェクトのベースクラス
-------------------------------------*/
class UIObject
{
public:
	enum class TypeID
	{
		None = -1
		//自分自身
		, UIObject

		//UIObject
		, HUD
		, PauseMenu
		, Result
		, Title

		, MAX		//UIオブジェクトのIDの最大値
	};

	//ゲームオブオブジェクトが所有する型のID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	//活動するUIオブジェクトか？
		, Closing	//停止するUIオブジェクトか？

		, MAX		//状態の最大値
	};

public:
	UIObject(class GameManager* gameManager);
	virtual ~UIObject(void);

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Input(void);
	virtual void Update(float deltaTime);
	virtual void Draw(void);

	void Close(void) { state_ = State::Closing; }

	void SetState(State state) { state_ = state; };
	State GetState(void) { return state_; }

	virtual TypeID GetType(void) const { return TypeID::UIObject; } //後でoverrideできるように

protected:
	//UIObjectの所有者
	class GameManager*				game_manager_;

	//UIObjectの状態
	State							state_;
};

#endif //UI_OBJECT_H_
/*=============================================================================
/*		End of File
=============================================================================*/