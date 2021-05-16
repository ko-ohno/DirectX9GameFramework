/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SandBox.cpp] ゲームを構成するゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームを構成するゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "SandBox.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SandBox::SandBox(Game* game)
	: GameObject(game)
{
	this->renderer_layer_type_ = RendererLayerType::Game;
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SandBox::~SandBox(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SandBox::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SandBox::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void SandBox::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void SandBox::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/