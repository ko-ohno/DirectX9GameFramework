/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AutomaticInputComponent.cpp] デモプレイの自動入力コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：デモプレイの自動入力コンポーネントの処理を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "AutomaticInputComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
AutomaticInputComponent::AutomaticInputComponent(GameObject* owner, int updateOrder)
	: InputComponent(owner, updateOrder)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
AutomaticInputComponent::~AutomaticInputComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool AutomaticInputComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void AutomaticInputComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void AutomaticInputComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void AutomaticInputComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/