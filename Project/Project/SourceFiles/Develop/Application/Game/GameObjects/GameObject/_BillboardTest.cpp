/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardTest.cpp] �r���{�[�h���e�X�g���邽�߂̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�r���{�[�h���e�X�g���邽�߂̃Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "_BillboardTest.h"

#include "../Component/RendererComponent/BillboardRendererComponent.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BillboardTest::BillboardTest(Game* game)
	: GameObject(game)
	, billboard_(nullptr)
{
	//�Q�[�����C���[�ŕ`��
	this->renderer_layer_type_ = RendererLayerType::Game;

	//�X�v���C�g�R���|�[�l���g�����L
	billboard_ = NEW BillboardRendererComponent(this, 30);
	billboard_->SetTexture(TextureType::Sample);

	billboard_a_ = NEW BillboardRendererComponent(this, 30);
	billboard_a_->SetTexture(TextureType::Sample);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
BillboardTest::~BillboardTest(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
BillboardTest* BillboardTest::Create(Game* game)
{
	return NEW BillboardTest(game);
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool BillboardTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void BillboardTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void BillboardTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
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