/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteTest.cpp] �X�v���C�g�e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "_SpriteTest.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../../Resource/Texture.h"

#include "../../../../ImGui/ImGuiManager.h"

#include "../../../Input/InputCheck.h"

#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SpriteTest::SpriteTest(Game* game)
	: GameObject(game)
	, sprite_(nullptr)
	, sprite_a_(nullptr)
	, sprite_b_(nullptr)
{
	//�Q�[�����C���[�ŕ`��
	this->renderer_layer_type_ = RendererLayerType::Game; 

	//�X�v���C�g�R���|�[�l���g�����L
	sprite_ = NEW SpriteRendererComponent(this);
	sprite_->SetDrawingPositionToCenter(true);
	sprite_->SetTexture(TextureType::Sample);


	//�X�v���C�g�R���|�[�l���g�����L
	sprite_a_ = NEW SpriteRendererComponent(this);
	sprite_a_->SetDrawingPositionToCenter(true);
	sprite_a_->SetTexture(TextureType::Planet);

	//�X�v���C�g�R���|�[�l���g�����L
	sprite_b_ = NEW SpriteRendererComponent(this);
	sprite_b_->SetDrawingPositionToCenter(true); 
	sprite_b_->SetTexture(TextureType::Planet);

}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SpriteTest::~SpriteTest(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SpriteTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SpriteTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void SpriteTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
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


	ImGui::Begin("SpriteTest");
	ImGui::Text(" DEGREE :%f", sprite_->GetDegree());
	ImGui::Text(" RADIAN :%f", sprite_->GetRadian());
	ImGui::End();

	static float val = 0.0f;

	//ImGuiWindowFlags wf = (ImGuiWindowFlags_NoDecoration);

	//bool b = true;

	ImGui::Begin("Progress Indicators");
	{
		const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
		const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

		const float div_num = 1000.f;
		ImGui::Spinner("##spinner", 15, 6, col);
		ImGui::BufferingBar("##buffer_bar", val / div_num, ImVec2(400, 6), bg, col);
		ImGui::SliderFloat("##buffer_bar", &val, 0.0f, div_num);
	}
	ImGui::End();


	ImGui::Begin("Progress bar");
	{
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
	}
	ImGui::End();

}

/*=============================================================================
/*		End of File
=============================================================================*/