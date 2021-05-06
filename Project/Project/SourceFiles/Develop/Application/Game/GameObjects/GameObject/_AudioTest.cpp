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

	audio_component_a_ = NEW AudioComponent(this);
	audio_component_a_->SetSound(SoundType::Sample);
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
	ImGui::Text("BGM_Volume:");
	ImGui::SameLine();
	ImGui::SliderFloat("", &volume, 0.000f, 1.000f);
	
	ImGui::Text("AllSounds:");
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		this->GetGame()->GetSoundManager()->SetPausedToAllSound(true);
	}

	ImGui::Text("AllSounds:");
	ImGui::SameLine();
	if (ImGui::Button("Replay"))
	{
		this->GetGame()->GetSoundManager()->SetPausedToAllSound(false);
	}

	ImGui::Text("SampleSound:");
	ImGui::SameLine();
	if (ImGui::Button("Play"))
	{
		audio_component_a_->Play();
	}

	ImGui::End();

	audio_component_->SetAudioVolume(volume);
}

/*=============================================================================
/*		End of File
=============================================================================*/