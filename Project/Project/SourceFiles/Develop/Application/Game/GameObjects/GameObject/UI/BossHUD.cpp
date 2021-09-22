/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossHUD.cpp] �{�X��HUD�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X��HUD�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "BossHUD.h"

// �`��R���|�[�l���g
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/RendererComponent/BillboardRendererComponent.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BossHUD::BossHUD(Game* game)
	: UI(game)
	, health_bar_(nullptr)
	, health_bar_blank_(nullptr)
	, health_bar_bg_(nullptr)
	, hp_value_(0.f)
	, max_hp_value_(0.f)
	, hp_rate_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
BossHUD::~BossHUD(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool BossHUD::Init(void)
{
	// �l�̏�����
	{
		hp_value_		= 100;
		max_hp_value_	= 100;
	}

	// �̗͂̕\��
	{
		health_bar_ = NEW SpriteRendererComponent(this, 240);
		health_bar_->SetTexture(TextureType::Blank);
		health_bar_->SetVertexColor(0, 255, 0, 255); // ��

		health_bar_blank_ = NEW SpriteRendererComponent(this, 230);
		health_bar_blank_->SetTexture(TextureType::Blank);
		health_bar_blank_->SetVertexColor(0, 0, 0, 255); // ��

		health_bar_bg_ = NEW SpriteRendererComponent(this);
		health_bar_bg_->SetTexture(TextureType::Blank);
		health_bar_bg_->SetVertexColor(0, 255, 255, 128); // ���F
	}

	// �x��̕\��
	{

	}


	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void BossHUD::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void BossHUD::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void BossHUD::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/