/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState_2.cpp] エネミーファクトリの第2状態クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーファクトリの第2状態クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "EnemyFactoryState_2.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EnemyFactoryState_2::EnemyFactoryState_2(class Game* game)
	: EnemyFactoryState(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EnemyFactoryState_2::~EnemyFactoryState_2(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool EnemyFactoryState_2::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void EnemyFactoryState_2::Uninit(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/