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

/*-------------------------------------
/* UIの状態クラス
-------------------------------------*/
enum class UIState
{
	None = -1
	, Active	//活動するUIオブジェクトか？
	, Closing	//停止するUIオブジェクトか？

	, MAX		//状態の最大値
};

/*-------------------------------------
/* UIのベースクラス
-------------------------------------*/
class UI : public GameObject
{
public:
	UI(class Game* game);
	virtual ~UI(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	void Close(void) { state_ = UIState::Closing; }

	void SetState(UIState state) { state_ = state; };
	UIState GetState(void) { return state_; }
	 
	virtual TypeID GetType(void) const { return TypeID::UI; } //後でoverrideできるように

protected:
	//UIの所有者
	class Game* game_;

	//UIの状態
	UIState		state_;
};

#endif //UI_H_
/*=============================================================================
/*		End of File
=============================================================================*/