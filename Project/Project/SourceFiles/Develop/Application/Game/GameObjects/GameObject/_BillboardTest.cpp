/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardTest.cpp] ビルボードをテストするためのゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ビルボードをテストするためのゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "_BillboardTest.h"

#include "../Component/RendererComponent/BillboardRendererComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BillboardTest::BillboardTest(Game* game)
	: GameObject(game)
	, billboard_(nullptr)
{
	//ゲームレイヤーで描画
	this->renderer_layer_type_ = RendererLayerType::Game;

	//スプライトコンポーネントを所有
	billboard_ = NEW BillboardRendererComponent(this, 30);
	billboard_->SetTexture(TextureType::Sample);

	billboard_a_ = NEW BillboardRendererComponent(this, 30);
	billboard_a_->SetTexture(TextureType::Sample);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
BillboardTest::~BillboardTest(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
BillboardTest* BillboardTest::Create(Game* game)
{
	return NEW BillboardTest(game);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BillboardTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void BillboardTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void BillboardTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void BillboardTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	billboard_->SetTranslationX(-3.f);
	auto info = billboard_->GetTextureImageInfo();
	int wid = info->Width;
	int het = info->Height;
	
	static float val = 0;
	val += deltaTime * 100;
	billboard_->SetUVAnimation(wid + val, het + val, wid, het);
	

	billboard_a_->SetTranslationX(3.f);
	billboard_a_->SetUVAnimation(wid - val, het - val, wid, het);

}

/*=============================================================================
/*		End of File
=============================================================================*/