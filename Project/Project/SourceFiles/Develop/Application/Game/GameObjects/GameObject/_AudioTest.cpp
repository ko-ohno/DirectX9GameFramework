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