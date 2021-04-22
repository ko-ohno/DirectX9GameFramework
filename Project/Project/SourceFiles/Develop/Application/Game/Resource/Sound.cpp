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
	, sound_type_id_(SoundType::None)
	, is_loading_complete_(false)
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
		HANDLE file_handle;
		DWORD  dwChunkSize		= 0UL;
		DWORD  dwChunkPosition	= 0UL;
		DWORD  dwFileType		= 0UL;

		WAVEFORMATEXTENSIBLE wave_format_extensible;
		XAUDIO2_BUFFER		 xaudio2_buffer;

		// バッファのクリア
		memset(&wave_format_extensible, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&xaudio2_buffer, 0, sizeof(XAUDIO2_BUFFER));

		// 音声ファイル名を取得
		std::string sound_filename = SoundManager::SoundTypeNames[static_cast<int>(soundType)];

		// サウンドデータの作成
		{
			// ファイルへのハンドルを取得
			file_handle = CreateFile(sound_filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (file_handle == INVALID_HANDLE_VALUE)
			{
				std::string err_msg = "Sound::LoadSound()：サウンドファイルが読み込めませんでした。\n";
				err_msg = err_msg + sound_filename + "：サウンドファイルへのハンドルが無効な値でした。";
				MessageBox(nullptr
						  , err_msg.c_str()
						  , "警告"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}

			// ファイルの先頭アドレスへ移動
			if (SetFilePointer(file_handle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			{
				std::string err_msg = "Sound::LoadSound()：サウンドファイルが読み込めませんでした。\n";
				err_msg = err_msg + sound_filename + "：サウンドファイルの先頭アドレスが無効な値でした。";
				MessageBox(nullptr
						  , err_msg.c_str()
						  , "警告"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}

		}

		// サウンドデータの確認
		HRESULT hr;
		{
			// RIFFヘッダの読み込み
			{
				hr = CheckChunk(file_handle, 'FFIR', &dwChunkSize, &dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()：サウンドファイルのデータが読み込めませんでした。\n";
					err_msg = err_msg + sound_filename + "：RIFFヘッダのチャンクデータの確認に失敗しました。";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "警告"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

				hr = ReadChunkData(file_handle, &dwFileType, sizeof(DWORD), dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()：サウンドファイルのデータが読み込めませんでした。\n";
					err_msg = err_msg + sound_filename + "：RIFFヘッダのチャンクデータの読み込みに失敗しました。";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "警告"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

				if (dwFileType != 'EVAW')
				{
					std::string err_msg = "Sound::LoadSound()：サウンドファイルのデータが読み込めませんでした。\n";
					err_msg = err_msg + sound_filename + "：拡張子(.wav)のみ対応。フォーマットされたデータ構造がWAVEフォーマットと一致しません。";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "警告"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}
			}

			// フォーマットチャンクの読み込み
			{
				hr = CheckChunk(file_handle, ' tmf', &dwChunkSize, &dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()：サウンドファイルのフォーマットチャンクデータが読み込めませんでした。\n";
					err_msg = err_msg + sound_filename + "：fmtチャンクデータの確認に失敗しました。";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "警告"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

				hr = ReadChunkData(file_handle, &wave_format_extensible, dwChunkSize, dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()：サウンドファイルのフォーマットチャンクデータが読み込めませんでした。\n";
					err_msg = err_msg + sound_filename + "：fmtチャンクデータの読み込みに失敗しました。";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "警告"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

			}

			// データチャンクの読み込み
			{
				hr = CheckChunk(file_handle, 'atad', &audio_data_size_, &dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()：サウンドファイルのデータチャンクが読み込めませんでした。\n";
					err_msg = err_msg + sound_filename + "：データチャンクの読み込みに失敗しました。";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "警告"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}

				//波形データの読み込み
				audio_data_ = (BYTE*)malloc(audio_data_size_);
				hr = ReadChunkData(file_handle, audio_data_, audio_data_size_, dwChunkPosition);
				if (FAILED(hr))
				{
					std::string err_msg = "Sound::LoadSound()：サウンドファイルのデータチャンクが読み込めませんでした。\n";
					err_msg = err_msg + sound_filename + "：波形データの読み込みに失敗しました。";
					MessageBox(nullptr
							  , err_msg.c_str()
							  , "警告"
							  , (MB_OK | MB_ICONWARNING));
					return false;
				}
			}

			// ソースボイスの生成
			hr = sound_manager_->GetXAudio2Interface()->CreateSourceVoice(&source_voice_, &(wave_format_extensible.Format));
			if (FAILED(hr))
			{
				std::string err_msg = "Sound::LoadSound()：ソースボイスの生成に失敗しました。\n";
				err_msg = err_msg + "SoundTypeID：" + sound_filename;
				MessageBox(nullptr
						  , err_msg.c_str()
						  , "警告"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}

			// バッファの値設定
			memset(&xaudio2_buffer, 0, sizeof(XAUDIO2_BUFFER));
			xaudio2_buffer.AudioBytes	= audio_data_size_;
			xaudio2_buffer.pAudioData	= audio_data_;
			xaudio2_buffer.Flags		= XAUDIO2_END_OF_STREAM;
			xaudio2_buffer.LoopCount	= 0U;

			// オーディオバッファの登録
			source_voice_->SubmitSourceBuffer(&xaudio2_buffer);
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* チャンクデータの確認
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

	// ファイルポインタを先頭に移動
	if (SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
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
/* チャンクデータの読み込み
-----------------------------------------------------------------------------*/
HRESULT Sound::ReadChunkData(HANDLE fileHandle, void* buffer, DWORD dwBufferSize, DWORD dwBufferOffset)
{
	DWORD dwRead;
	{
		// ファイルポインタを指定位置まで移動
		if (SetFilePointer(fileHandle, dwBufferOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// データの読み込み
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