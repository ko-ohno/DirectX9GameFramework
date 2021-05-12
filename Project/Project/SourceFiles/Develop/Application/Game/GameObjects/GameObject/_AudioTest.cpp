/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioTest.cpp] 音声テストのゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：音声テストのゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "_AudioTest.h"
#include "../Component/AudioComponent.h"

#include "../../../ImGui/ImGuiManager.h"
#include "../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
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
/* デストラクタ
-----------------------------------------------------------------------------*/
AudioTest::~AudioTest(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
AudioTest* AudioTest::Create(Game* game)
{
	return NEW AudioTest(game);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool AudioTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void AudioTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void AudioTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
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