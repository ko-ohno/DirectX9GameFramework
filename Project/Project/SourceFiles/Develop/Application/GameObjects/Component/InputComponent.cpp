/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputComponent.cpp] 入力コンポーネントのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：入力コンポーネントに共通する処理の定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "InputComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
InputComponent::InputComponent(GameObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
InputComponent::~InputComponent(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/