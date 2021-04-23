/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioComponent.cpp] �����R���|�[�l���g�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����R���|�[�l���g�̋��L�̃N���X��`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "AudioComponent.h"
#include "../GameObject.h"
#include "../../Game.h"
#include "../../Manager/SoundManager.h"
#include "../../Resource/Sound.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
AudioComponent::AudioComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, sound_(nullptr)
	, audio_volume_(0.5f)
{
	// ���g�̏�����
	this->Init();
}
/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
AudioComponent::~AudioComponent(void)
{
	// ���g�̏I����
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool AudioComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void AudioComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V��������
-----------------------------------------------------------------------------*/
void AudioComponent::Update(float deltaTime)
{	
	const bool is_out_of_range = (audio_volume_ >= 1.001f || audio_volume_ <= -0.001f);
	if (is_out_of_range)
	{
		assert(!"AudioComponent::Update()�F���ʂ��͈͊O�̐ݒ������Ă��܂��B�͈́F�ŏ�:0.f/�ő�1.f)");
		return;
	}

	if (sound_->GetXAudio2SourceVoice() == nullptr)
	{
		assert(!"AudioComponent::Update()�F�\�[�X�{�C�X�������Ȓl�ł�");
		return;
	}
	sound_->GetXAudio2SourceVoice()->SetVolume(audio_volume_);
}

/*-----------------------------------------------------------------------------
/* �������̐ݒ�
-----------------------------------------------------------------------------*/
void AudioComponent::SetSound(SoundType soundType)
{
	//�T�E���h�̓ǂݍ���
	this->sound_ = owner_->GetGame()->GetSoundManager()->LoadSound(soundType);
}

/*-----------------------------------------------------------------------------
/* �������̎擾
-----------------------------------------------------------------------------*/
Sound* AudioComponent::GetSound(void)
{
	//���b�V�����̎擾
	if (this->sound_ == nullptr)
	{
		assert(!"AudioComponent::GetSound():������񂪐ݒ肳��Ă��܂���I");
	}
	return sound_;
}

/*-----------------------------------------------------------------------------
/* �Đ�����
-----------------------------------------------------------------------------*/
void AudioComponent::Play(void)
{
	XAUDIO2_VOICE_STATE voice_state;
	XAUDIO2_BUFFER		xaudio2_buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&xaudio2_buffer, 0, sizeof(XAUDIO2_BUFFER));
	xaudio2_buffer.AudioBytes	= sound_->GetAudioDataSize();
	xaudio2_buffer.pAudioData	= sound_->GetAudioData();
	xaudio2_buffer.Flags		= XAUDIO2_END_OF_STREAM;
	xaudio2_buffer.LoopCount	= 0U;

	// �\�[�X�{�C�X�̎擾
	auto source_voice = sound_->GetXAudio2SourceVoice();

	if (source_voice == nullptr)
	{
		MessageBox(nullptr
				  , "AudioComponent::Play()�F�\�[�X�{�C�X�������Ȓl�ł��B"
				  , "�x��"
				  , (MB_OK | MB_ICONWARNING));
		return;
	}

	// ��Ԏ擾
	source_voice->GetState(&voice_state);

	// �Đ���
	if (voice_state.BuffersQueued != 0)
	{
		// �ꎞ��~
		source_voice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		source_voice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	source_voice->SubmitSourceBuffer(&xaudio2_buffer);

	// �Đ�
	source_voice->Start(0);
}

/*-----------------------------------------------------------------------------
/* ���[�v�Đ�����
-----------------------------------------------------------------------------*/
void AudioComponent::PlayLoop(void)
{
	XAUDIO2_VOICE_STATE voice_state;
	XAUDIO2_BUFFER		xaudio2_buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&xaudio2_buffer, 0, sizeof(XAUDIO2_BUFFER));
	xaudio2_buffer.AudioBytes	= sound_->GetAudioDataSize();
	xaudio2_buffer.pAudioData	= sound_->GetAudioData();
	xaudio2_buffer.Flags		= XAUDIO2_END_OF_STREAM;
	xaudio2_buffer.LoopCount	= XAUDIO2_LOOP_INFINITE;

	// �\�[�X�{�C�X�̎擾
	auto source_voice = sound_->GetXAudio2SourceVoice();

	// ��Ԏ擾
	source_voice->GetState(&voice_state);

	// �Đ���
	if (voice_state.BuffersQueued != 0)
	{
		// �ꎞ��~
		source_voice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		source_voice->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	source_voice->SubmitSourceBuffer(&xaudio2_buffer);

	// �Đ�
	source_voice->Start(0);
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void AudioComponent::Stop(void)
{
	XAUDIO2_VOICE_STATE voice_state;

	// �\�[�X�{�C�X�̎擾
	auto source_voice = sound_->GetXAudio2SourceVoice();

	// ��Ԏ擾
	source_voice->GetState(&voice_state);

	// �Đ�����
	if (voice_state.BuffersQueued != 0)
	{
		// �ꎞ��~
		source_voice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		source_voice->FlushSourceBuffers();
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/