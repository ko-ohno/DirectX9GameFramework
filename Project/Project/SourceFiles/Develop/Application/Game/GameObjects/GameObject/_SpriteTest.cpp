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

#pragma warning(disable:4996)

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


	ImGui::Begin("Progress Indicators");

	const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
	const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

	ImGui::Spinner("##spinner", 15, 6, col);
	ImGui::BufferingBar("##buffer_bar", 0.7f, ImVec2(400, 6), bg, col);

	ImGui::End();


	ImGui::Begin("Progress bar");

	// Animate a simple progress bar
	static float progress = 0.0f, progress_dir = 1.0f;
	if (true)
	{
		progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
		if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
		if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }
	}

	// Typically we would use ImVec2(-1.0f,0.0f) to use all available width, or ImVec2(width,0.0f) for a specified width. ImVec2(0.0f,0.0f) uses ItemWidth.
	ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
	ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
	ImGui::Text("Progress Bar");

	float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;
	char buf[32];
	sprintf(buf, "%d/%d", (int)(progress_saturated * 1753), 1753);
	ImGui::ProgressBar(progress, ImVec2(0.f, 0.f), buf);

	ImGui::End();
}

/*=============================================================================
/*		End of File
=============================================================================*/