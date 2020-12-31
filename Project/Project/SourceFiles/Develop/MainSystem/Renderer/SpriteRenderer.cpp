/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteRenderer.cpp] スプライトレンダラークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトレンダラークラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "SpriteRenderer.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SpriteRenderer::SpriteRenderer(void)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SpriteRenderer::~SpriteRenderer(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
SpriteRenderer* SpriteRenderer::Create(void)
{
	return NEW SpriteRenderer();
}


/*=============================================================================
/*		End of File
=============================================================================*/