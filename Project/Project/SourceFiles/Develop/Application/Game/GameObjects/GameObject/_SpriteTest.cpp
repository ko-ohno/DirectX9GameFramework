/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteTest.cpp] �X�v���C�g���e�X�g���邽�߂̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g���e�X�g���邽�߂̃Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "_SpriteTest.h"
#include "../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Resource/Texture.h"

#include "../../../ImGui/ImGuiManager.h"

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
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
SpriteTest* SpriteTest::Create(Game* game)
{
	return NEW SpriteTest(game);
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


	ImGui::Begin("DebugSprite");
	ImGui::Text(" DEGREE :%f", sprite_->GetDegree());
	ImGui::Text(" RADIAN :%f", sprite_->GetRadian());
	ImGui::End();
}

/*=============================================================================
/*		End of File
=============================================================================*/