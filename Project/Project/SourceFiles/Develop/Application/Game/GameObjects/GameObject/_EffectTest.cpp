/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectTest.cpp] エフェクトテストゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エフェクトテストゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "_EffectTest.h"
#include "../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Resource/Effect.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EffectTest::EffectTest(Game* game)
	: GameObject(game)
	, effect_renderer_comp_(nullptr)
	, effect_renderer_comp_a(nullptr)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

	effect_renderer_comp_ = NEW EffectRendererComponent(this);
	effect_renderer_comp_->SetEffect(EffectType::AfterBurner);
	effect_renderer_comp_->Play();

	effect_renderer_comp_a = NEW EffectRendererComponent(this);
	effect_renderer_comp_a->SetEffect(EffectType::YellowDust);
	effect_renderer_comp_a->Play();

	//effect_renderer_comp_b = NEW EffectRendererComponent(this);
	//effect_renderer_comp_b->SetEffect(EffectType::RedDust);
	//effect_renderer_comp_b->Play();


}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EffectTest::~EffectTest(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
EffectTest* EffectTest::Create(Game* game)
{
	return NEW EffectTest(game);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool EffectTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void EffectTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void EffectTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void EffectTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	static float time = 0;

	effect_renderer_comp_->SetTranslationZ(3.f);

	//time += deltaTime;
	//if (time >= 3.0f)
	//{
	//	effect_renderer_comp_a->Stop();
	//	time = 0.f;
	//}
}

/*=============================================================================
/*		End of File
=============================================================================*/