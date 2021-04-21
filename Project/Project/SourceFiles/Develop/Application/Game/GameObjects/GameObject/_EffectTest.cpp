/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectTest.cpp] �G�t�F�N�g�e�X�g�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�t�F�N�g�e�X�g�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "_EffectTest.h"
#include "../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Resource/Effect.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EffectTest::EffectTest(Game* game)
	: GameObject(game)
	, effect_renderer_comp_(nullptr)
	, effect_renderer_comp_a(nullptr)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

	effect_renderer_comp_ = NEW EffectRendererComponent(this);
	effect_renderer_comp_->SetEffect(EffectType::AfterBurner);
	effect_renderer_comp_->Play();

	effect_renderer_comp_a = NEW EffectRendererComponent(this);
	effect_renderer_comp_a->SetEffect(EffectType::YellowDust);
	effect_renderer_comp_a->Play();

	//effect_renderer_comp_b = NEW EffectRendererComponent(this);
	//effect_renderer_comp_b->SetEffect(EffectType::RedDust);
	//effect_renderer_comp_b->Play();


}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EffectTest::~EffectTest(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
EffectTest* EffectTest::Create(Game* game)
{
	return NEW EffectTest(game);
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool EffectTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void EffectTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void EffectTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void EffectTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	static float time = 0;

	//time += deltaTime;
	//if (time >= 3.0f)
	//{
	//	effect_renderer_comp_a->Stop();
	//	time = 0.f;
	//}
}

/*=============================================================================
/*		End of File
=============================================================================*/