/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectManager.h] メッシュ管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エフェクトの管理クラス
=============================================================================*/
#ifndef EFFECT_MANAGER_H_
#define	EFFECT_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../../../../External/Effekseer/include/Effekseer.h"
#include "../../../../External/Effekseer/include/EffekseerRendererDX9.h"
#include "../../../../External/Effekseer/include/EffekseerSoundXAudio2.h"

// 音再生用ライブラリの呼び出し
#include <X3DAudio.h>

// 音再生
#pragma comment(lib, "X3DAudio.lib")

//ライブラリのリンク
#if defined(_DEBUG)||(DEBUG)
#pragma comment(lib, "Effekseer/Debug/Effekseer.Debug.lib")
#pragma comment(lib, "Effekseer/Debug/EffekseerRendererDX9.Debug.lib")
#pragma comment(lib, "Effekseer/Debug/EffekseerSoundXAudio2.Debug.lib")
#else			
#pragma comment(lib, "Effekseer/Release/Effekseer.Release.lib")
#pragma comment(lib, "Effekseer/Release/EffekseerRendererDX9.Release.lib")
#pragma comment(lib, "Effekseer/Release/EffekseerSoundXAudio2.Release.lib")
#endif


/*-------------------------------------
/* エフェクトの種類
-------------------------------------*/
enum class EffectType
{
	None = -1
	, Sample
	, SpaceDustBlue
	, SpaceDustYellow
	, SpaceDustRed

	, MuzzluFrashBlue
	, MuzzluFrashGreen
	, MuzzluFrashOrange

	, ChargeBulletState1Charge
	, ChargeBulletState2Hold
	, ChargeBulletState3Fire
	, ChargeBulletState4Bullet
	, ChargeBulletState5Explosion

	, AfterBurner
	, Max
};

/*-------------------------------------
/* エフェクトの管理クラス
-------------------------------------*/
class EffectManager
{
public:
	static const char* EffectTypeNames[static_cast<int>(EffectType::Max)];

public:
	EffectManager(class Game* game);
	~EffectManager(void);

	static EffectManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止	

private:
	bool Init(void);
	void Uninit(void);

public:
	// すべてのエフェクトを一時停止
	void SetPausedToAllEffect(bool isPaused);

	// エフェクト用の43行列へ変換
	const Effekseer::Matrix43 Convert43Matrix(const D3DXMATRIX& d3dxMatrix);

	// エフェクト用の44行列へ変換
	const Effekseer::Matrix44 Convert44Matrix(const D3DXMATRIX& d3dxMatrix);

	//テクスチャのルートパスの取得
	std::string GetEffectRootpath(void) const { return effect_root_path_; }

	//メッシュの読み込み
	class GameEffect* LoadEffect(EffectType effectTypeID);

	//メッシュの解放
	void ReleaseEffect(EffectType effectTypeID);

	//メッシュを検索する
	class GameEffect* FindEffect(EffectType effectTypeID);

	//
	// エフェクトの追加と削除
	//

	void AddEffect(class GameEffect* effect);
	void RemoveEffect(class GameEffect* effect);

	std::unordered_map<enum class EffectType, std::string> GetEffectFilepathList(void) { return unmap_effect_path_list_; }

	class Game* GetGame(void) { return game_; }
	class Effekseer::Manager* GetEffekseerManager(void) { return manager_; }
	class EffekseerRendererDX9::Renderer* GetEffekseerRenderer(void) { return renderer_; }

private:
	Effekseer::Manager*					manager_;			//Effekseer側のライブラリのマネージャ
	EffekseerRendererDX9::Renderer*		renderer_;			//Effekseer側のレンダラー
	EffekseerSound::Sound*				sound_;				//Effekseer側のサンウド管理クラス

	IXAudio2*							xaudio2_;			//XAudioへのポインタ
	IXAudio2MasteringVoice*				xaudio2_master_;	//XAudioへのマスターボイス

private:
	//マネージャーの所有者
	class Game* game_;

	//エフェクトのルートパス
	std::string effect_root_path_;

	//エフェクトのパスリスト
	std::unordered_map<enum class EffectType, std::string> unmap_effect_path_list_;

	//メッシュリストのコンテナ
	std::vector<class GameEffect*> effect_list_;
};

#endif //EFFECT_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/