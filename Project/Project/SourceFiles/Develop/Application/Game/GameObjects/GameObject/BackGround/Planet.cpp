/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Planet.cpp] �f���Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�f���Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "Planet.h"

#include "../../Component/RendererComponent/BillboardRendererComponent.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
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
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Planet::~Planet(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Planet::Init(void)
{
	// �r���{�[�h�̐���
	{
		planet_billboard_ = NEW BillboardRendererComponent(this);
		planet_billboard_->SetTexture(TextureType::Planet);
		planet_billboard_->SetTranslationY(-20.f);
		planet_billboard_->SetTranslationZ(150.f);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Planet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void Planet::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Planet::UpdateGameObject(float deltaTime)
{
	// �f����Y���̍������v�Z
	{
		planet_offset_time_ += deltaTime;
		if (planet_offset_time_ >= MAX_PLANET_OFFSET_TIME_)
		{
			planet_offset_time_ = MAX_PLANET_OFFSET_TIME_;
		}

		// �f���̍�����ݒ�
		planet_billboard_->SetTranslationY(Math::Lerp(DEFAULT_PLANET_OFFSET_HEIGHT
										  , MAX_PLANET_OFFSET_HEIGHT
										  , Easing::Linear(planet_offset_time_, MAX_PLANET_OFFSET_TIME_)));
	}

	// �f���̑傫�����v�Z
	{
		planet_scaling_time_ += deltaTime;
		if (planet_scaling_time_ >= MAX_PLANET_SCALE_TIME_)
		{
			planet_scaling_time_ = MAX_PLANET_SCALE_TIME_;
		}

		// �f���̑傫����ݒ�
		planet_billboard_->SetScale(Math::Lerp(DEFAULT_PLANET_SIZE_
											  , MAX_PLANET_SIZE_
											  , Easing::Linear(planet_scaling_time_, MAX_PLANET_SCALE_TIME_)));
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/