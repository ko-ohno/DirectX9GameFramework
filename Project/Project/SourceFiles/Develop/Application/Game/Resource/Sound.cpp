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
	, sound_type_id_(SoundType::None)
	, is_loading_complete_(false)
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
}

/*-----------------------------------------------------------------------------
/* �T�E���h�t�@�C���̓ǂݍ���
-----------------------------------------------------------------------------*/
bool Sound::LoadSound(const SoundType soundType)
{
	// ���[�g�p�X�ƃt�@�C���p�X������
	auto sound_filepath = sound_manager_->GetSoundRootpath() + sound_manager_->GetSoundFilepathList().at(soundType);
	{
		HANDLE file_handle;
		DWORD  dwChunkSize		= 0UL;
		DWORD  dwChunkPosition	= 0UL;
		DWORD  dwFileType		= 0UL;

		WAVEFORMATEXTENSIBLE wave_format_extensible;
		XAUDIO2_BUFFER		 xaudio2_buffer;

		// �o�b�t�@�̃N���A
		memset(&wave_format_extensible, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&xaudio2_buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �����t�@�C�������擾
		std::string sound_filename = SoundManager::SoundTypeNames[static_cast<int>(soundType)];

		// �T�E���h�f�[�^�̍쐬
		{
			// �t�@�C���ւ̃n���h�����擾
			file_handle = CreateFile(sound_filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (file_handle == INVALID_HANDLE_VALUE)
			{
				std::string err_msg = "Sound::LoadSound()�F�T�E���h�t�@�C�����ǂݍ��߂܂���ł����B\n";
				err_msg = err_msg + sound_filename + "�F�T�E���h�t�@�C���ւ̃n���h���������Ȓl�ł����B";
				MessageBox(nullptr
						  , err_msg.c_str()
						  , "�x��"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}

			// �t�@�C���̐擪�A�h���X�ֈړ�
			if (SetFilePointer(file_handle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			{
				std::string err_msg = "Sound::LoadSound()�F�T�E���h�t�@�C�����ǂݍ��߂܂���ł����B\n";
				err_msg = err_msg + sound_filename + "�F�T�E���h�t�@�C���̐擪�A�h���X�������Ȓl�ł����B";
				MessageBox(nullptr
						  , err_msg.c_str()
						  , "�x��"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}

		}

		// �T�E���h�f�[�^�̊m�F
		HRESULT hr;
		{
			// RIFF�w�b�_�̓ǂݍ���
			{
				hr = CheckChunk(file_handle, 'FFIR', &dwChunkSize, &dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()�F�T�E���h�t�@�C���̃f�[�^���ǂݍ��߂܂���ł����B\n";
					err_msg = err_msg + sound_filename + "�FRIFF�w�b�_�̃`�����N�f�[�^�̊m�F�Ɏ��s���܂����B";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "�x��"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

				hr = ReadChunkData(file_handle, &dwFileType, sizeof(DWORD), dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()�F�T�E���h�t�@�C���̃f�[�^���ǂݍ��߂܂���ł����B\n";
					err_msg = err_msg + sound_filename + "�FRIFF�w�b�_�̃`�����N�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "�x��"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

				if (dwFileType != 'EVAW')
				{
					std::string err_msg = "Sound::LoadSound()�F�T�E���h�t�@�C���̃f�[�^���ǂݍ��߂܂���ł����B\n";
					err_msg = err_msg + sound_filename + "�F�g���q(.wav)�̂ݑΉ��B�t�H�[�}�b�g���ꂽ�f�[�^�\����WAVE�t�H�[�}�b�g�ƈ�v���܂���B";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "�x��"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}
			}

			// �t�H�[�}�b�g�`�����N�̓ǂݍ���
			{
				hr = CheckChunk(file_handle, ' tmf', &dwChunkSize, &dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()�F�T�E���h�t�@�C���̃t�H�[�}�b�g�`�����N�f�[�^���ǂݍ��߂܂���ł����B\n";
					err_msg = err_msg + sound_filename + "�Ffmt�`�����N�f�[�^�̊m�F�Ɏ��s���܂����B";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "�x��"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

				hr = ReadChunkData(file_handle, &wave_format_extensible, dwChunkSize, dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()�F�T�E���h�t�@�C���̃t�H�[�}�b�g�`�����N�f�[�^���ǂݍ��߂܂���ł����B\n";
					err_msg = err_msg + sound_filename + "�Ffmt�`�����N�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "�x��"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

			}

			// �f�[�^�`�����N�̓ǂݍ���
			{
				hr = CheckChunk(file_handle, 'atad', &audio_data_size_, &dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()�F�T�E���h�t�@�C���̃f�[�^�`�����N���ǂݍ��߂܂���ł����B\n";
					err_msg = err_msg + sound_filename + "�F�f�[�^�`�����N�̓ǂݍ��݂Ɏ��s���܂����B";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "�x��"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

				//�g�`�f�[�^�̓ǂݍ���
				audio_data_ = (BYTE*)malloc(audio_data_size_);
				hr = ReadChunkData(file_handle, audio_data_, audio_data_size_, dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()�F�T�E���h�t�@�C���̃f�[�^�`�����N���ǂݍ��߂܂���ł����B\n";
					err_msg = err_msg + sound_filename + "�F�g�`�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "�x��"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}
			}

			// �\�[�X�{�C�X�̐���
			hr = sound_manager_->GetXAudio2Interface()->CreateSourceVoice(&source_voice_, &(wave_format_extensible.Format));
			if (FAILED(hr))
			{
				std::string err_msg = "Sound::LoadSound()�F�\�[�X�{�C�X�̐����Ɏ��s���܂����B\n";
				err_msg = err_msg + "SoundTypeID�F" + sound_filename;
				MessageBox(nullptr
						  , err_msg.c_str()
						  , "�x��"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}

			// �o�b�t�@�̒l�ݒ�
			memset(&xaudio2_buffer, 0, sizeof(XAUDIO2_BUFFER));
			xaudio2_buffer.AudioBytes	= audio_data_size_;
			xaudio2_buffer.pAudioData	= audio_data_;
			xaudio2_buffer.Flags		= XAUDIO2_END_OF_STREAM;
			xaudio2_buffer.LoopCount	= 0U;

			// �I�[�f�B�I�o�b�t�@�̓o�^
			source_voice_->SubmitSourceBuffer(&xaudio2_buffer);
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �`�����N�f�[�^�̊m�F
-----------------------------------------------------------------------------*/
HRESULT Sound::CheckChunk(HANDLE fileHandle, DWORD format, DWORD* chunkSize, DWORD* chunkDataPosition)
{
	HRESULT hr				= E_FAIL;
	DWORD	dwRead			= 0UL;
	DWORD	dwChunkType		= 0UL;
	DWORD	dwChunkDataSize	= 0UL;
	DWORD	dwRIFFDataSize	= 0UL;
	DWORD	dwFileType		= 0UL;
	DWORD	dwBytesRead		= 0UL;
	DWORD	dwOffset		= 0UL;

	// �t�@�C���|�C���^��擪�Ɉړ�
	if (SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
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
			*chunkSize = dwChunkDataSize;
			*chunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

/*-----------------------------------------------------------------------------
/* �`�����N�f�[�^�̓ǂݍ���
-----------------------------------------------------------------------------*/
HRESULT Sound::ReadChunkData(HANDLE fileHandle, void* buffer, DWORD dwBufferSize, DWORD dwBufferOffset)
{
	DWORD dwRead;
	{
		// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		if (SetFilePointer(fileHandle, dwBufferOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// �f�[�^�̓ǂݍ���
		if (ReadFile(fileHandle, buffer, dwBufferSize, &dwRead, NULL) == 0)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}
	}
	return S_OK;
}

/*=============================================================================
/*		End of File
=============================================================================*/