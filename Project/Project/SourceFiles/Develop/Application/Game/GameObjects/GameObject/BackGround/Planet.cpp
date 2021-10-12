/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Planet.cpp] 惑星ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：惑星ゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "Planet.h"

#include "../../Component/RendererComponent/BillboardRendererComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Planet::Planet(Game* game)
	: BackGround(game)
	, planet_billboard_(nullptr)
	, planet_scaling_time_(0.f)
	, planet_offset_time_(0.f)
{	
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Planet::~Planet(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Planet::Init(void)
{
	// ビルボードの生成
	{
		planet_billboard_ = NEW BillboardRendererComponent(this);
		planet_billboard_->SetTexture(TextureType::Planet);
		planet_billboard_->SetTranslationY(-20.f);
		planet_billboard_->SetTranslationZ(150.f);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Planet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void Planet::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Planet::UpdateGameObject(float deltaTime)
{
	// 惑星のY軸の高さを計算
	{
		planet_offset_time_ += deltaTime;
		if (planet_offset_time_ >= MAX_PLANET_OFFSET_TIME_)
		{
			planet_offset_time_ = MAX_PLANET_OFFSET_TIME_;
		}

		// 惑星の高さを設定
		planet_billboard_->SetTranslationY(Math::Lerp(DEFAULT_PLANET_OFFSET_HEIGHT
										  , MAX_PLANET_OFFSET_HEIGHT
										  , Easing::Linear(planet_offset_time_, MAX_PLANET_OFFSET_TIME_)));
	}

	// 惑星の大きさを計算
	{
		planet_scaling_time_ += deltaTime;
		if (planet_scaling_time_ >= MAX_PLANET_SCALE_TIME_)
		{
			planet_scaling_time_ = MAX_PLANET_SCALE_TIME_;
		}

		// 惑星の大きさを設定
		planet_billboard_->SetScale(Math::Lerp(DEFAULT_PLANET_SIZE_
											  , MAX_PLANET_SIZE_
											  , Easing::Linear(planet_scaling_time_, MAX_PLANET_SCALE_TIME_)));
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/