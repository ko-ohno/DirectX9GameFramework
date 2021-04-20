/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioTest.cpp] 音声テストのゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：音声テストのゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "_AudioTest.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
AudioTest::AudioTest(Game* game)
	: GameObject(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
AudioTest::~AudioTest(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
AudioTest* AudioTest::Create(Game* game)
{
	return NEW AudioTest(game);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool AudioTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void AudioTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void AudioTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void AudioTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/