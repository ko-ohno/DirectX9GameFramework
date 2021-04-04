/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteTest.cpp] スプライトをテストするためのゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトをテストするためのゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "_SpriteTest.h"
#include "../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Resource/Texture.h"

#include "../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SpriteTest::SpriteTest(Game* game)
	: GameObject(game)
	, sprite_(nullptr)
	, sprite_a_(nullptr)
	, sprite_b_(nullptr)
{
	//ゲームレイヤーで描画
	this->renderer_layer_type_ = RendererLayerType::Game; 

	//スプライトコンポーネントを所有
	sprite_ = NEW SpriteRendererComponent(this);
	sprite_->SetDrawingPositionToCenter(true);
	sprite_->SetTexture(TextureType::Sample);


	//スプライトコンポーネントを所有
	sprite_a_ = NEW SpriteRendererComponent(this);
	sprite_a_->SetDrawingPositionToCenter(true);
	sprite_a_->SetTexture(TextureType::Planet);

	//スプライトコンポーネントを所有
	sprite_b_ = NEW SpriteRendererComponent(this);
	sprite_b_->SetDrawingPositionToCenter(true); 
	sprite_b_->SetTexture(TextureType::Planet);

}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SpriteTest::~SpriteTest(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
SpriteTest* SpriteTest::Create(Game* game)
{
	return NEW SpriteTest(game);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SpriteTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SpriteTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void SpriteTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void SpriteTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	auto info = sprite_->GetTextureImageInfo();
	int wid = info->Width;
	int het = info->Height;
	sprite_->SetScale(128, 128);
	{
		static float val = 0;
		val += deltaTime * 100;
		sprite_->SetUVAnimation(int(wid + val), int(het + val), wid, het);
		sprite_->SetTranslation(64, 64);
		sprite_->AddRotate(deltaTime * 10);
	}

	sprite_a_->SetTranslation(100, 200);
	sprite_a_->SetScale(128, 128);


	sprite_b_->SetTranslation(150, 200);
	sprite_b_->SetScale(128, 128);


	ImGui::Begin("DebugSprite");
	ImGui::Text(" DEGREE :%f", sprite_->GetDegree());
	ImGui::Text(" RADIAN :%f", sprite_->GetRadian());
	ImGui::End();
}

/*=============================================================================
/*		End of File
=============================================================================*/