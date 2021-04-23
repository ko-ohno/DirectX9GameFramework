/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioComponent.cpp] 音声コンポーネントのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：音声コンポーネントの共有のクラス定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "AudioComponent.h"
#include "../GameObject.h"
#include "../../Game.h"
#include "../../Manager/SoundManager.h"
#include "../../Resource/Sound.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
AudioComponent::AudioComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, sound_(nullptr)
	, audio_volume_(0.5f)
{
	// 自身の初期化
	this->Init();
}
/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
AudioComponent::~AudioComponent(void)
{
	// 自身の終了化
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool AudioComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void AudioComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理処理
-----------------------------------------------------------------------------*/
void AudioComponent::Update(float deltaTime)
{	
	const bool is_out_of_range = (audio_volume_ >= 1.001f || audio_volume_ <= -0.001f);
	if (is_out_of_range)
	{
		assert(!"AudioComponent::Update()：音量が範囲外の設定をされています。範囲：最小:0.f/最大1.f)");
		return;
	}

	if (sound_->GetXAudio2SourceVoice() == nullptr)
	{
		assert(!"AudioComponent::Update()：ソースボイスが無効な値です");
		return;
	}
	sound_->GetXAudio2SourceVoice()->SetVolume(audio_volume_);
}

/*-----------------------------------------------------------------------------
/* 音声情報の設定
-----------------------------------------------------------------------------*/
void AudioComponent::SetSound(SoundType soundType)
{
	//サウンドの読み込み
	this->sound_ = owner_->GetGame()->GetSoundManager()->LoadSound(soundType);
}

/*-----------------------------------------------------------------------------
/* 音声情報の取得
-----------------------------------------------------------------------------*/
Sound* AudioComponent::GetSound(void)
{
	//メッシュ情報の取得
	if (this->sound_ == nullptr)
	{
		assert(!"AudioComponent::GetSound():音声情報が設定されていません！");
	}
	return sound_;
}

/*-----------------------------------------------------------------------------
/* 再生処理
-----------------------------------------------------------------------------*/
void AudioComponent::Play(void)
{
	XAUDIO2_VOICE_STATE voice_state;
	XAUDIO2_BUFFER		xaudio2_buffer;

	// バッファの値設定
	memset(&xaudio2_buffer, 0, sizeof(XAUDIO2_BUFFER));
	xaudio2_buffer.AudioBytes	= sound_->GetAudioDataSize();
	xaudio2_buffer.pAudioData	= sound_->GetAudioData();
	xaudio2_buffer.Flags		= XAUDIO2_END_OF_STREAM;
	xaudio2_buffer.LoopCount	= 0U;

	// ソースボイスの取得
	auto source_voice = sound_->GetXAudio2SourceVoice();

	if (source_voice == nullptr)
	{
		MessageBox(nullptr
				  , "AudioComponent::Play()：ソースボイスが無効な値です。"
				  , "警告"
				  , (MB_OK | MB_ICONWARNING));
		return;
	}

	// 状態取得
	source_voice->GetState(&voice_state);

	// 再生中
	if (voice_state.BuffersQueued != 0)
	{
		// 一時停止
		source_voice->Stop(0);

		// オーディオバッファの削除
		source_voice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	source_voice->SubmitSourceBuffer(&xaudio2_buffer);

	// 再生
	source_voice->Start(0);
}

/*-----------------------------------------------------------------------------
/* ループ再生処理
-----------------------------------------------------------------------------*/
void AudioComponent::PlayLoop(void)
{
	XAUDIO2_VOICE_STATE voice_state;
	XAUDIO2_BUFFER		xaudio2_buffer;

	// バッファの値設定
	memset(&xaudio2_buffer, 0, sizeof(XAUDIO2_BUFFER));
	xaudio2_buffer.AudioBytes	= sound_->GetAudioDataSize();
	xaudio2_buffer.pAudioData	= sound_->GetAudioData();
	xaudio2_buffer.Flags		= XAUDIO2_END_OF_STREAM;
	xaudio2_buffer.LoopCount	= XAUDIO2_LOOP_INFINITE;

	// ソースボイスの取得
	auto source_voice = sound_->GetXAudio2SourceVoice();

	// 状態取得
	source_voice->GetState(&voice_state);

	// 再生中
	if (voice_state.BuffersQueued != 0)
	{
		// 一時停止
		source_voice->Stop(0);

		// オーディオバッファの削除
		source_voice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	source_voice->SubmitSourceBuffer(&xaudio2_buffer);

	// 再生
	source_voice->Start(0);
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
void AudioComponent::Stop(void)
{
	XAUDIO2_VOICE_STATE voice_state;

	// ソースボイスの取得
	auto source_voice = sound_->GetXAudio2SourceVoice();

	// 状態取得
	source_voice->GetState(&voice_state);

	// 再生中か
	if (voice_state.BuffersQueued != 0)
	{
		// 一時停止
		source_voice->Stop(0);

		// オーディオバッファの削除
		source_voice->FlushSourceBuffers();
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/