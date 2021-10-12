/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Sound.h] サウンドクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：サウンドクラス
=============================================================================*/
#ifndef SOUND_H_
#define	SOUND_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "../ResourceManager/SoundManager.h"

/*-------------------------------------
/* サウンドクラス
-------------------------------------*/
class Sound
{
public:
	Sound(SoundManager* manager, SoundType soundType);
	~Sound(void);

	//サウンドの読み込み
	bool LoadSound(const SoundType soundType);

	//サウンドの読み込みができているか
	bool IsLoadCompleted(void) { return is_loading_complete_; }

private:
	HRESULT CheckChunk(HANDLE fileHandle, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE fileHandle, void* pBuffer, DWORD dwBufferSize, DWORD dwBufferOffset);

public:


	//
	// サウンドのデータ取得関数
	//

	SoundType			 GetSoundTypeID(void) { return sound_type_id_; }

	IXAudio2SourceVoice* GetXAudio2SourceVoice(void) { return source_voice_; }

	BYTE*				 GetAudioData(void) { return audio_data_; }

	DWORD				 GetAudioDataSize(void) { return audio_data_size_; }

private:
	// サウンドの所有者
	class SoundManager*  sound_manager_;

	//
	// サウンドのデータ
	//

	bool				 is_loading_complete_;

	SoundType			 sound_type_id_;

	IXAudio2SourceVoice* source_voice_;			// ソースボイス

	BYTE*				 audio_data_;			// オーディオデータ

	DWORD				 audio_data_size_;		// オーディオデータサイズ
};


#endif //SOUND_H_
/*=============================================================================
/*		End of File
=============================================================================*/