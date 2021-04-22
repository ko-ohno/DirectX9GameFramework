/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SoundManager.cpp] �T�E���h�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�T�E���h�Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "SoundManager.h"
#include "../Resource/Sound.h"

//�T�E���h�̃��X�g
const char* SoundManager::SoundTypeNames[static_cast<int>(SoundType::Max)] = {
	//�������g
	"Sample"
	, "WonderLand"
};

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SoundManager::SoundManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SoundManager::~SoundManager(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
SoundManager* SoundManager::Create(Game* game)
{
	return NEW SoundManager(game);
}

/*-----------------------------------------------------------------------------
/* �N������
-----------------------------------------------------------------------------*/
bool SoundManager::StartUp(void)
{
	//���g�̏�����
	const bool sound_manager_init = this->Init();
	if (sound_manager_init == false)
	{
		assert(!"SoundManager::StartUp()�F�T�E���h�}�l�[�W���̏������Ɏ��s���܂����B");
		return false;
	}

	//�T�E���h�̓ǂݍ���
	{
		//this->LoadSound(SoundType::Sample);

	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void SoundManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SoundManager::Init(void)
{
	// �T�E���h�̃��[�g�p�X���w��
	sound_root_path_ = "Assets/Sounds/";

	// ���X�g�̏�����
	unmap_sound_path_list_.clear();
	{
		//unmap_sound_path_list_[SoundType::Sample] = "BGM/samaple.wav";

		//unmap_sound_path_list_[SoundType::Sample] = "SE/samaple.wav";

		unmap_sound_path_list_[SoundType::WonderLand] = "BGM/wonderland.wav";
	}

	HRESULT hr;

	// XAudio2�ւ̃C���^�[�t�F�C�X���쐬
	hr = XAudio2Create(&xaudio2_);
	if (FAILED(hr))
	{
		assert(!"SoundManager::Init()�FXAudio2�̃C���^�[�t�F�C�X�̍쐬�Ɏ��s���܂����B");
		return false;
	}

	// XAudio2�̃}�X�^�[�{�C�X���쐬
	hr = xaudio2_->CreateMasteringVoice(&xaudio2_mastering_voice_);
	if (FAILED(hr))
	{
		assert(!"SoundManager::Init()�FXAudio2�̃}�X�^�[�{�C�X�̍쐬�Ɏ��s���܂����B");
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SoundManager::Uninit(void)
{
	while (!sound_list_.empty())
	{
		delete sound_list_.back();
		sound_list_.pop_back();
	}

	// XAudio2�̃}�X�^�[�{�C�X��j��
	xaudio2_mastering_voice_->DestroyVoice();
	xaudio2_mastering_voice_ = nullptr;

	// XAudio2�ւ̃C���^�[�t�F�C�X��j��
	if (xaudio2_ != nullptr)
	{
		SAFE_RELEASE_(xaudio2_);
	}
}

/*-----------------------------------------------------------------------------
/* ���ׂẲ������ꎞ��~
-----------------------------------------------------------------------------*/
void SoundManager::SetPausedToAllSound(bool isPaused)
{
	for (auto sound : sound_list_)
	{
		//�\�[�X�{�C�X�̎擾
		auto source_voice = sound->GetXAudio2SourceVoice();
		if (source_voice)
		{
			//�ꎞ��~
			source_voice->Stop(0);
		}
	}
}

/*-----------------------------------------------------------------------------
/* �����̓ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
Sound* SoundManager::LoadSound(SoundType soundTypeID)
{
	//�T�E���h����������
	auto sound = this->FindSound(soundTypeID);
	if (sound != nullptr)
	{
		return sound;
	}
	else
	{
		//�T�E���h���Ȃ�������
		const bool is_sound_list_out_of_range = ((soundTypeID <= SoundType::None)
												|| (soundTypeID >= SoundType::Max));
		if (is_sound_list_out_of_range)
		{
			assert(!"�͈͊O�̃T�E���hID���Q�Ƃ��悤�Ƃ��Ă��܂��I");
			return nullptr;
		}
		this->AddSound(NEW Sound(this, soundTypeID));
	}
	return this->FindSound(soundTypeID);
}

/*-----------------------------------------------------------------------------
/* �����̉������
-----------------------------------------------------------------------------*/
void SoundManager::ReleaseSound(SoundType soundTypeID)
{
	for (auto sound : sound_list_)
	{
		auto id = sound->GetSoundTypeID();

		if (id == soundTypeID)
		{
			delete sound;
		}
	}
}

/*-----------------------------------------------------------------------------
/* �����̌�������
-----------------------------------------------------------------------------*/
Sound* SoundManager::FindSound(SoundType soundTypeID)
{
	//�e�N�X�`�����X�g�̌���
	for (auto sound : sound_list_)
	{
		//���݂̒����Ώۂ���ID���擾
		auto id = sound->GetSoundTypeID();

		//�擾����ID��soundTypeID
		if (id == soundTypeID)
		{
			return sound;
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* �����̒ǉ�����
-----------------------------------------------------------------------------*/
void SoundManager::AddSound(Sound* sound)
{
	sound_list_.emplace_back(sound);
}

/*-----------------------------------------------------------------------------
/* �����̍폜����
-----------------------------------------------------------------------------*/
void SoundManager::RemoveSound(Sound* sound)
{
	auto iter = std::find(sound_list_.begin()	//�͈�0�`
						 , sound_list_.end()	//�͈͍ő�܂�
						 , sound);				//�T���Ώ�

	if (iter != sound_list_.end())
	{
		sound_list_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/