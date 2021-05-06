/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Sound.cpp] �T�E���h�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�T�E���h�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "Sound.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Sound::Sound(SoundManager* manager, SoundType soundType)
	: sound_manager_(manager)
	, is_loading_complete_(false)
	, sound_type_id_(SoundType::None)
	, source_voice_(nullptr)
	, audio_data_(nullptr)
	, audio_data_size_(0UL)
{
	//�e�N�X�`��ID�̐ݒ�
	sound_type_id_ = soundType;

	//�e�N�X�`���[�̓ǂݍ���
	is_loading_complete_ = this->LoadSound(soundType);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Sound::~Sound(void)
{
	//�\�[�X�{�C�X�̍폜
	source_voice_->DestroyVoice();
	source_voice_ = nullptr;

	//�����f�[�^�̍폜
	SAFE_DELETE_(audio_data_);
}

/*-----------------------------------------------------------------------------
/* �T�E���h�t�@�C���̓ǂݍ���
-----------------------------------------------------------------------------*/
bool Sound::LoadSound(const SoundType soundType)
{
	// ���[�g�p�X�ƃt�@�C���p�X������
	auto sound_filepath = sound_manager_->GetSoundRootpath() + sound_manager_->GetSoundFilepathList().at(soundType);
	{
		// �����t�@�C�������擾
		std::string sound_filename = SoundManager::SoundTypeNames[static_cast<int>(soundType)];

		// �T�E���h�f�[�^�̊m�F
		{
			HANDLE file_handle	  = nullptr;
			DWORD dwChunkSize	  = 0UL;
			DWORD dwChunkPosition = 0UL;
			DWORD dwFiletype	  = 0UL;

			WAVEFORMATEXTENSIBLE wfx;
			XAUDIO2_BUFFER buffer;

			// �o�b�t�@�̃N���A
			memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

			//�G���[���b�Z�[�W�̊i�[��
			std::string err_msg = "�����t�@�C���̏��̓ǂݍ��݂Ɏ��s���܂���\nError�F";

			// �T�E���h�f�[�^�t�@�C���̐���
			file_handle = CreateFile(sound_filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (file_handle == INVALID_HANDLE_VALUE)
			{
				err_msg =  err_msg  + "�����t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}

			// �t�@�C���|�C���^��擪�Ɉړ�
			if (SetFilePointer(file_handle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			{
				err_msg =  err_msg  + "�����f�[�^�̐擪�A�h���X�̎擾�Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}

			// WAVE�t�@�C���̃`�F�b�N
			HRESULT hr;
			hr = CheckChunk(file_handle, 'FFIR', &dwChunkSize, &dwChunkPosition);
			if (FAILED(hr))
			{
				err_msg = err_msg + "RIFF�w�b�_�̏��̓ǂݍ��݂Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}

			hr = ReadChunkData(file_handle, &dwFiletype, sizeof(DWORD), dwChunkPosition);
			if (FAILED(hr))
			{
				err_msg = err_msg + "RIFF�w�b�_�̖{�̏��̓ǂݍ��݂Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}

			if (dwFiletype != 'EVAW')
			{
				err_msg = err_msg + "WAVE�t�@�C���ł͂Ȃ����߁A�����t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}

			// �t�H�[�}�b�g�`�F�b�N
			hr = CheckChunk(file_handle, ' tmf', &dwChunkSize, &dwChunkPosition);
			if (FAILED(hr))
			{
				err_msg = err_msg + "�t�H�[�}�b�g�f�[�^�̓ǂݍ��݂Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}
			hr = ReadChunkData(file_handle, &wfx, dwChunkSize, dwChunkPosition);
			if (FAILED(hr))
			{
				err_msg = err_msg + "�t�H�[�}�b�g�f�[�^�̖{�̏��̓ǂݍ��݂Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}

			// �I�[�f�B�I�f�[�^�ǂݍ���
			hr = CheckChunk(file_handle, 'atad', &audio_data_size_, &dwChunkPosition);
			if (FAILED(hr))
			{
				err_msg = err_msg + "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}

			audio_data_ = (BYTE*)malloc(audio_data_size_);
			hr = ReadChunkData(file_handle, audio_data_, audio_data_size_, dwChunkPosition);
			if (FAILED(hr))
			{
				err_msg = err_msg + "�I�[�f�B�I�f�[�^�̔g�`���̓ǂݍ��݂Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}

			// �\�[�X�{�C�X�̐���
			hr = sound_manager_->GetXAudio2Interface()->CreateSourceVoice(&source_voice_, &(wfx.Format));
			if (FAILED(hr))
			{
				err_msg = err_msg + "�\�[�X�{�C�X�̐����Ɏ��s���܂���";
				MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK|MB_ICONWARNING));
				return false;
			}

			// �o�b�t�@�̒l�ݒ�
			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
			buffer.AudioBytes	= audio_data_size_;
			buffer.pAudioData	= audio_data_;
			buffer.Flags		= XAUDIO2_END_OF_STREAM;
			buffer.LoopCount	= 0;

			// �I�[�f�B�I�o�b�t�@�̓o�^
			source_voice_->SubmitSourceBuffer(&buffer);
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �`�����N�f�[�^�̊m�F
-----------------------------------------------------------------------------*/
HRESULT Sound::CheckChunk(HANDLE fileHandle, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD	dwRead			= 0UL;
	DWORD	dwChunkType		= 0UL;
	DWORD	dwChunkDataSize	= 0UL;
	DWORD	dwRIFFDataSize	= 0UL;
	DWORD	dwFileType		= 0UL;
	DWORD	dwBytesRead		= 0UL;
	DWORD	dwOffset		= 0UL;

	if (SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(fileHandle, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(fileHandle, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(fileHandle, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(fileHandle, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	return S_OK;
}

/*-----------------------------------------------------------------------------
/* �`�����N�f�[�^�̓ǂݍ���
-----------------------------------------------------------------------------*/
HRESULT Sound::ReadChunkData(HANDLE fileHandle, void* pBuffer, DWORD dwBufferSize, DWORD dwBufferOffset)
{
	DWORD dwRead;
	{
		// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		if (SetFilePointer(fileHandle, dwBufferOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// �f�[�^�̓ǂݍ���
		if (ReadFile(fileHandle, pBuffer, dwBufferSize, &dwRead, NULL) == 0)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}
	}
	return S_OK;
}

/*=============================================================================
/*		End of File
=============================================================================*/