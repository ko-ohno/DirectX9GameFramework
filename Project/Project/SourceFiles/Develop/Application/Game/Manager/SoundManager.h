/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SoundManager.h] サウンド管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：サウンド管理クラス
=============================================================================*/
#ifndef SOUND_MANAGER_H_
#define	SOUND_MANAGER_H_

/*--- インクルードファイル ---*/
#include <XAudio2.h>


/*-------------------------------------
/* サウンドの種類
-------------------------------------*/
enum class SoundType
{
	None = -1
	, Sample
	, WonderLand

	, Max
};

/*-------------------------------------
/* サウンド管理クラス
-------------------------------------*/
class SoundManager
{
public:
	static const char* SoundTypeNames[static_cast<int>(SoundType::Max)];

public:
	SoundManager(class Game* game);
	~SoundManager(void);

	static SoundManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止

private:
	bool Init(void);	//初期化
	void Uninit(void);	//終了化

public:
	// すべてのサウンドを一時停止
	void SetPausedToAllSound(bool isPaused);

	//サウンドのルートパスの取得
	std::string GetSoundRootpath(void) const { return sound_root_path_; }

	//サウンドの読み込み
	class Sound* LoadSound(SoundType soundTypeID);

	//サウンドの解放
	void ReleaseSound(SoundType soundTypeID);

	//音声を検索する
	class Sound* FindSound(SoundType soundTypeID);

	//
	// サウンドの追加と削除
	//

	void AddSound(class Sound* sound);
	void RemoveSound(class Sound* sound);

	std::unordered_map<SoundType, std::string> GetSoundFilepathList(void) { return unmap_sound_path_list_; }

	class Game* GetGame(void) { return game_; }

	// XAudio2のインターフェイスを取得
	IXAudio2* GetXAudio2Interface(void) { return xaudio2_; }

private:
	IXAudio2*				xaudio2_;					// XAudio2へのインターフェイス

	IXAudio2MasteringVoice* xaudio2_mastering_voice_;	// マスターボイス

private:
	//マネージャの所有者
	class Game* game_;

	//サウンドのルートパス
	std::string sound_root_path_;

	//サウンドのパスリスト
	std::unordered_map<SoundType, std::string> unmap_sound_path_list_;

	//サウンドのコンテナ
	std::vector<class Sound*> sound_list_;

};

#endif //SOUND_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/