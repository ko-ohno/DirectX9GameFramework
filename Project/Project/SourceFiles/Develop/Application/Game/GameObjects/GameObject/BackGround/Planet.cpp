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
	, game_manager_(nullptr)
	, planet_scale_(0.f)
	, planet_offset_height_(0.f)
	, game_progress_value_(0.f)
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
	// �f���̑傫����ݒ�
	planet_scale_ = 50.f;

	// �f���̍�����ݒ�
	planet_offset_height_ = -20.f;

	// �r���{�[�h�̐���
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
	UNREFERENCED_PARAMETER(deltaTime);

	// nullptr��������Q�[���}�l�[�W���[��T��
	if (game_manager_ == nullptr)
	{
		game_manager_ = this->FindGameObject(GameObject::TypeID::GameManager);
	}

	// �����������ʂ��hnullptr�h�������烊�^�[��
	if (game_manager_ == nullptr) { return; }

	//�@�Q�[���}�l�[�W������l�R���|�[�l���g���擾
	auto parameter_components = game_manager_->GetParameterComponents();
	for (auto parameter_component : parameter_components)
	{
		// �l�R���|�[�l���g�̌^�𒲂ׂ�
		auto parameter_component_type = parameter_component->GetParameterType();

		// �Q�[���̐i�s�x���擾
		if (parameter_component_type == ParameterType::GameProgress)
		{
			game_progress_value_ = parameter_component->GetInt();
			break;
		}
	}

	//�@�f���̍�����ݒ�
	{
		planet_offset_height_ -= (deltaTime * 0.01f);

		if (planet_offset_height_ <= MAX_PLANET_OFFSET_HEIGHT)
		{
			planet_offset_height_ = MAX_PLANET_OFFSET_HEIGHT;
		}
	}

	// �f���̑傫����ݒ�
	{
		planet_scale_ += (deltaTime * 0.6f);

		if (planet_scale_ >= MAX_PLANET_SCALE)
		{
			planet_scale_ = MAX_PLANET_SCALE;
		}
	}

	//�@�f���̍�����ݒ�
	planet_billboard_->SetTranslationY(planet_offset_height_);

	// �f���̑傫����ݒ�
	planet_billboard_->SetScale(planet_scale_);

}

/*=============================================================================
/*		End of File
=============================================================================*/