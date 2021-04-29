/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioTest.cpp] �����e�X�g�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e�X�g�̃Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "_AudioTest.h"
#include "../Component/AudioComponent.h"

#include "../../../ImGui/ImGuiManager.h"
#include "../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
AudioTest::AudioTest(Game* game)
	: GameObject(game)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

	audio_component_ = NEW AudioComponent(this);
	audio_component_->SetSound(SoundType::WonderLand);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
AudioTest::~AudioTest(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
AudioTest* AudioTest::Create(Game* game)
{
	return NEW AudioTest(game);
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool AudioTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void AudioTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void AudioTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void AudioTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	static float time = 0;
	time += deltaTime;
	static bool a = false;
	if (a == false)
	{
		audio_component_->PlayLoop();
		a = true;
	}

	static float volume = 0.2f;

	ImGui::Begin("SoundTest");
	ImGui::SliderFloat("volume", &volume, 0.000f, 1.000f);
	ImGui::Text("Stop   :J");
	ImGui::Text("Replay :K");
	ImGui::End();

	audio_component_->SetAudioVolume(volume);

	if (InputCheck::KeyTrigger(DIK_J))
	{
		this->GetGame()->GetSoundManager()->SetPausedToAllSound(true);
	}

	if (InputCheck::KeyTrigger(DIK_K))
	{
		this->GetGame()->GetSoundManager()->SetPausedToAllSound(false);
	}

}

/*=============================================================================
/*		End of File
=============================================================================*/