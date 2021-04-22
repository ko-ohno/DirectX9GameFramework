/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SoundManager.cpp] サウンド管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：サウンド管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "SoundManager.h"
#include "../Resource/Sound.h"

//サウンドのリスト
const char* SoundManager::SoundTypeNames[static_cast<int>(SoundType::Max)] = {
	//自分自身
	"Sample"
	, "WonderLand"
};

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SoundManager::SoundManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SoundManager::~SoundManager(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
SoundManager* SoundManager::Create(Game* game)
{
	return NEW SoundManager(game);
}

/*-----------------------------------------------------------------------------
/* 起動処理
-----------------------------------------------------------------------------*/
bool SoundManager::StartUp(void)
{
	//自身の初期化
	const bool sound_manager_init = this->Init();
	if (sound_manager_init == false)
	{
		assert(!"SoundManager::StartUp()：サウンドマネージャの初期化に失敗しました。");
		return false;
	}

	//サウンドの読み込み
	{
		//this->LoadSound(SoundType::Sample);

	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
void SoundManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SoundManager::Init(void)
{
	// サウンドのルートパスを指定
	sound_root_path_ = "Assets/Sounds/";

	// リストの初期化
	unmap_sound_path_list_.clear();
	{
		//unmap_sound_path_list_[SoundType::Sample] = "BGM/samaple.wav";

		//unmap_sound_path_list_[SoundType::Sample] = "SE/samaple.wav";

		unmap_sound_path_list_[SoundType::WonderLand] = "BGM/wonderland.wav";
	}

	HRESULT hr;

	// XAudio2へのインターフェイスを作成
	hr = XAudio2Create(&xaudio2_);
	if (FAILED(hr))
	{
		assert(!"SoundManager::Init()：XAudio2のインターフェイスの作成に失敗しました。");
		return false;
	}

	// XAudio2のマスターボイスを作成
	hr = xaudio2_->CreateMasteringVoice(&xaudio2_mastering_voice_);
	if (FAILED(hr))
	{
		assert(!"SoundManager::Init()：XAudio2のマスターボイスの作成に失敗しました。");
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SoundManager::Uninit(void)
{
	while (!sound_list_.empty())
	{
		delete sound_list_.back();
		sound_list_.pop_back();
	}

	// XAudio2のマスターボイスを破棄
	xaudio2_mastering_voice_->DestroyVoice();
	xaudio2_mastering_voice_ = nullptr;

	// XAudio2へのインターフェイスを破棄
	if (xaudio2_ != nullptr)
	{
		SAFE_RELEASE_(xaudio2_);
	}
}

/*-----------------------------------------------------------------------------
/* すべての音声を一時停止
-----------------------------------------------------------------------------*/
void SoundManager::SetPausedToAllSound(bool isPaused)
{
	for (auto sound : sound_list_)
	{
		//ソースボイスの取得
		auto source_voice = sound->GetXAudio2SourceVoice();
		if (source_voice)
		{
			//一時停止
			source_voice->Stop(0);
		}
	}
}

/*-----------------------------------------------------------------------------
/* 音声の読み込み処理
-----------------------------------------------------------------------------*/
Sound* SoundManager::LoadSound(SoundType soundTypeID)
{
	//サウンドがあったら
	auto sound = this->FindSound(soundTypeID);
	if (sound != nullptr)
	{
		return sound;
	}
	else
	{
		//サウンドがなかったら
		const bool is_sound_list_out_of_range = ((soundTypeID <= SoundType::None)
												|| (soundTypeID >= SoundType::Max));
		if (is_sound_list_out_of_range)
		{
			assert(!"範囲外のサウンドIDを参照しようとしています！");
			return nullptr;
		}
		this->AddSound(NEW Sound(this, soundTypeID));
	}
	return this->FindSound(soundTypeID);
}

/*-----------------------------------------------------------------------------
/* 音声の解放処理
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
/* 音声の検索処理
-----------------------------------------------------------------------------*/
Sound* SoundManager::FindSound(SoundType soundTypeID)
{
	//テクスチャリストの検索
	for (auto sound : sound_list_)
	{
		//現在の調査対象からIDを取得
		auto id = sound->GetSoundTypeID();

		//取得したIDとsoundTypeID
		if (id == soundTypeID)
		{
			return sound;
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* 音声の追加処理
-----------------------------------------------------------------------------*/
void SoundManager::AddSound(Sound* sound)
{
	sound_list_.emplace_back(sound);
}

/*-----------------------------------------------------------------------------
/* 音声の削除処理
-----------------------------------------------------------------------------*/
void SoundManager::RemoveSound(Sound* sound)
{
	auto iter = std::find(sound_list_.begin()	//範囲0～
						 , sound_list_.end()	//範囲最大まで
						 , sound);				//探す対象

	if (iter != sound_list_.end())
	{
		sound_list_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/