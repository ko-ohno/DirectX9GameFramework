/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_5.cpp] エネミーファクトリの第5状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第5状態クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "EnemyFactoryState_5.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EnemyFactoryState_5::EnemyFactoryState_5(class Game* game)
	: EnemyFactoryState(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EnemyFactoryState_5::~EnemyFactoryState_5(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool EnemyFactoryState_5::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void EnemyFactoryState_5::Uninit(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/