/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Sound.h] �T�E���h�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�T�E���h�N���X
=============================================================================*/
#ifndef SOUND_H_
#define	SOUND_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "../ResourceManager/SoundManager.h"

/*-------------------------------------
/* �T�E���h�N���X
-------------------------------------*/
class Sound
{
public:
	Sound(SoundManager* manager, SoundType soundType);
	~Sound(void);

	//�T�E���h�̓ǂݍ���
	bool LoadSound(const SoundType soundType);

	//�T�E���h�̓ǂݍ��݂��ł��Ă��邩
	bool IsLoadCompleted(void) { return is_loading_complete_; }

private:
	HRESULT CheckChunk(HANDLE fileHandle, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE fileHandle, void* pBuffer, DWORD dwBufferSize, DWORD dwBufferOffset);

public:


	//
	// �T�E���h�̃f�[�^�擾�֐�
	//

	SoundType			 GetSoundTypeID(void) { return sound_type_id_; }

	IXAudio2SourceVoice* GetXAudio2SourceVoice(void) { return source_voice_; }

	BYTE*				 GetAudioData(void) { return audio_data_; }

	DWORD				 GetAudioDataSize(void) { return audio_data_size_; }

private:
	// �T�E���h�̏��L��
	class SoundManager*  sound_manager_;

	//
	// �T�E���h�̃f�[�^
	//

	bool				 is_loading_complete_;

	SoundType			 sound_type_id_;

	IXAudio2SourceVoice* source_voice_;			// �\�[�X�{�C�X

	BYTE*				 audio_data_;			// �I�[�f�B�I�f�[�^

	DWORD				 audio_data_size_;		// �I�[�f�B�I�f�[�^�T�C�Y
};


#endif //SOUND_H_
/*=============================================================================
/*		End of File
=============================================================================*/