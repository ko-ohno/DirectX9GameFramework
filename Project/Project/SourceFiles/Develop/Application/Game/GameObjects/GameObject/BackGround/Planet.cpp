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
	, game_manager_(nullptr)
	, planet_scale_(0.f)
	, planet_offset_height_(0.f)
	, game_progress_value_(0.f)
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
	// 惑星の大きさを設定
	planet_scale_ = 50.f;

	// 惑星の高さを設定
	planet_offset_height_ = -20.f;

	// ビルボードの生成
	{
		planet_billboard_ = NEW BillboardRendererComponent(this);
		planet_billboard_->SetTexture(TextureType::Planet);
		planet_billboard_->SetTranslationY(-20.f);
		planet_billboard_->SetTranslationZ(150.f);
		planet_billboard_->SetScale(planet_scale_);
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
	UNREFERENCED_PARAMETER(deltaTime);

	// nullptrだったらゲームマネージャーを探す
	if (game_manager_ == nullptr)
	{
		game_manager_ = this->FindGameObject(GameObject::TypeID::GameManager);
	}

	// 検索した結果が”nullptr”だったらリターン
	if (game_manager_ == nullptr) { return; }

	//　ゲームマネージャから値コンポーネントを取得
	auto parameter_components = game_manager_->GetParameterComponents();
	for (auto parameter_component : parameter_components)
	{
		// 値コンポーネントの型を調べる
		auto parameter_component_type = parameter_component->GetParameterType();

		// ゲームの進行度を取得
		if (parameter_component_type == ParameterType::GameProgress)
		{
			game_progress_value_ = parameter_component->GetInt();
			break;
		}
	}

	//　惑星の高さを設定
	{
		planet_offset_height_ -= (deltaTime * 0.01f);

		if (planet_offset_height_ <= MAX_PLANET_OFFSET_HEIGHT)
		{
			planet_offset_height_ = MAX_PLANET_OFFSET_HEIGHT;
		}
	}

	// 惑星の大きさを設定
	{
		planet_scale_ += (deltaTime * 0.6f);

		if (planet_scale_ >= MAX_PLANET_SCALE)
		{
			planet_scale_ = MAX_PLANET_SCALE;
		}
	}

	//　惑星の高さを設定
	planet_billboard_->SetTranslationY(planet_offset_height_);

	// 惑星の大きさを設定
	planet_billboard_->SetScale(planet_scale_);

}

/*=============================================================================
/*		End of File
=============================================================================*/