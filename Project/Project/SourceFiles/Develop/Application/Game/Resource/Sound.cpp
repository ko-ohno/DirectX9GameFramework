/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Sound.cpp] サウンドクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：サウンドクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "Sound.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Sound::Sound(SoundManager* manager, SoundType soundType)
	: sound_manager_(manager)
	, is_loading_complete_(false)
	, sound_type_id_(SoundType::None)
	, source_voice_(nullptr)
	, audio_data_(nullptr)
	, audio_data_size_(0UL)
{
	//テクスチャIDの設定
	sound_type_id_ = soundType;

	//テクスチャーの読み込み
	is_loading_complete_ = this->LoadSound(soundType);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Sound::~Sound(void)
{
}

/*-----------------------------------------------------------------------------
/* サウンドファイルの読み込み
-----------------------------------------------------------------------------*/
bool Sound::LoadSound(const SoundType soundType)
{
	// ルートパスとファイルパスを合成
	auto sound_filepath = sound_manager_->GetSoundRootpath() + sound_manager_->GetSoundFilepathList().at(soundType);
	{
		// 音声ファイル名を取得
		std::string sound_filename = SoundManager::SoundTypeNames[static_cast<int>(soundType)];

		// サウンドデータの確認
		{
			HANDLE file_handle	  = nullptr;
			DWORD dwChunkSize	  = 0UL;
			DWORD dwChunkPosition = 0UL;
			DWORD dwFiletype	  = 0UL;

			WAVEFORMATEXTENSIBLE wfx;
			XAUDIO2_BUFFER buffer;

			// バッファのクリア
			memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

			// サウンドデータファイルの生成
			file_handle = CreateFile(sound_filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (file_handle == INVALID_HANDLE_VALUE)
			{
				MessageBox(nullptr, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
				return false;
			}

			// ファイルポインタを先頭に移動
			if (SetFilePointer(file_handle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			{
				MessageBox(nullptr, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
				return false;
			}

			// WAVEファイルのチェック
			HRESULT hr;
			hr = CheckChunk(file_handle, 'FFIR', &dwChunkSize, &dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(nullptr, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
				return false;
			}

			hr = ReadChunkData(file_handle, &dwFiletype, sizeof(DWORD), dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(nullptr, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
				return false;
			}

			if (dwFiletype != 'EVAW')
			{
				MessageBox(nullptr, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
				return false;
			}

			// フォーマットチェック
			hr = CheckChunk(file_handle, ' tmf', &dwChunkSize, &dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(nullptr, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
				return false;
			}
			hr = ReadChunkData(file_handle, &wfx, dwChunkSize, dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(nullptr, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
				return false;
			}

			// オーディオデータ読み込み
			hr = CheckChunk(file_handle, 'atad', &audio_data_size_, &dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(nullptr, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
				return false;
			}

			audio_data_ = (BYTE*)malloc(audio_data_size_);
			hr = ReadChunkData(file_handle, audio_data_, audio_data_size_, dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(nullptr, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
				return false;
			}

			// ソースボイスの生成
			hr = sound_manager_->GetXAudio2Interface()->CreateSourceVoice(&source_voice_, &(wfx.Format));
			if (FAILED(hr))
			{
				MessageBox(nullptr, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
				return false;
			}

			// バッファの値設定
			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
			buffer.AudioBytes	= audio_data_size_;
			buffer.pAudioData	= audio_data_;
			buffer.Flags		= XAUDIO2_END_OF_STREAM;
			buffer.LoopCount	= 0;

			// オーディオバッファの登録
			source_voice_->SubmitSourceBuffer(&buffer);
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* チャンクデータの確認
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(fileHandle, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(fileHandle, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(fileHandle, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(fileHandle, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
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
/* チャンクデータの読み込み
-----------------------------------------------------------------------------*/
HRESULT Sound::ReadChunkData(HANDLE fileHandle, void* pBuffer, DWORD dwBufferSize, DWORD dwBufferOffset)
{
	DWORD dwRead;
	{
		// ファイルポインタを指定位置まで移動
		if (SetFilePointer(fileHandle, dwBufferOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// データの読み込み
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