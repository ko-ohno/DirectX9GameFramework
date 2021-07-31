/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshManager.cpp] メッシュ管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メッシュ管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "EffectManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"
#include "../Resource/GameEffect.h"

//エフェクトの名前リスト
const char* EffectManager::EffectTypeNames[static_cast<int>(EffectType::Max)] = {
	"Sample"
	, "BlueDust"
	, "YellowDust"
	, "RedDust"
	
	, "BlueMuzzluFrash"
	, "YellowMuzzluFrash"
	, "RedMuzzleFlash"

	, "ChargeBulletState1Charge"
	, "ChargeBulletState2Hold"
	, "ChargeBulletState3Fire"
	, "ChargeBulletState4Bullet"
	, "ChargeBulletState5Explosion"

	, "BlueLaser"
	, "AfterBurner"
};

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EffectManager::EffectManager(Game* game)
	: game_(game)
	, manager_(nullptr)
	, renderer_(nullptr)
	, sound_(nullptr)
	, xaudio2_(nullptr)
	, xaudio2_master_(nullptr)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EffectManager::~EffectManager(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
EffectManager* EffectManager::Create(Game* game)
{
	return NEW EffectManager(game);
}

/*-----------------------------------------------------------------------------
/* 起動処理
-----------------------------------------------------------------------------*/
bool EffectManager::StartUp(void)
{
	//自身の初期化
	const bool effect_manager_init = this->Init();
	if (effect_manager_init == false)
	{
		assert(!"EffectManager::StartUp()：エフェクトマネージャの初期化に失敗しました。");
		return false;
	}

	//エフェクトの読み込み処理
	{
		//this->LoadEffect(EffectType::AfterBurner);

		// チャージ弾のエフェクトの読み込み
		this->LoadEffect(EffectType::ChargeBulletState1Charge);
		this->LoadEffect(EffectType::ChargeBulletState2Hold);
		this->LoadEffect(EffectType::ChargeBulletState3Fire);
		this->LoadEffect(EffectType::ChargeBulletState4Bullet);
		this->LoadEffect(EffectType::ChargeBulletState5Explosion);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
void EffectManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool EffectManager::Init(void)
{
	//エフェクトのルートパスを設定
	effect_root_path_ = "Assets/ParticleEffects/";

	//エフェクトののリストを初期化
	effect_list_.clear();

	//エフェクトのファイルパスのリストを初期化
	unmap_effect_path_list_.clear();
	{
		//
		// エフェクトファイルの読み込み用ファイルパスリストの作成  
		//
		{
			//unmap_effect_path_list_[EffectType::Sample] = "Sample";

			// 宇宙ゴミのパーティクル
			unmap_effect_path_list_[EffectType::SpaceDustYellow]  = "SpaceDust/yellow_dust.efk";
			unmap_effect_path_list_[EffectType::SpaceDustBlue]	  = "SpaceDust/blue_dust.efk";
			unmap_effect_path_list_[EffectType::SpaceDustRed]	  = "SpaceDust/red_dust.efk";

			// マズルフラッシュのエフェクト
			unmap_effect_path_list_[EffectType::MuzzluFrashGreen]  = "Shot/shot_green.efk";
			unmap_effect_path_list_[EffectType::MuzzluFrashBlue]   = "Shot/shot_blue.efk";
			unmap_effect_path_list_[EffectType::MuzzluFrashOrange] = "Shot/shot_orange.efk";

			// チャージ弾のエフェクト
			unmap_effect_path_list_[EffectType::ChargeBulletState1Charge]	 = "ChargeBullet/cb_state_1_charge.efk";
			unmap_effect_path_list_[EffectType::ChargeBulletState2Hold]		 = "ChargeBullet/cb_state_2_hold.efk";
			unmap_effect_path_list_[EffectType::ChargeBulletState3Fire]		 = "ChargeBullet/cb_state_3_fire.efk";
			unmap_effect_path_list_[EffectType::ChargeBulletState4Bullet]	 = "ChargeBullet/cb_state_4_bullet.efk";
			unmap_effect_path_list_[EffectType::ChargeBulletState5Explosion] = "ChargeBullet/cb_state_5_explosion.efk";

			// 赤いレーザーのエフェクト
			unmap_effect_path_list_[EffectType::RedLaser]	 = "Laser/RedLaser.efk";

			//アフターバーナーのエフェクト
			unmap_effect_path_list_[EffectType::AfterBurner] = "AfterBurner/after_burner.efk";
		}
	}


	
	// COMコンポーネントは、ApplicationManager::Init()で初期化済み
	{
		//HRESULT hr;
		//hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		//if (FAILED(hr))
		//{
		//	assert(!"EffectManager::Init()：COMコンポーネントの初期化に失敗しました！");
		//	return false;
		//}
	}

	//XAudio2の初期化を行う
	{
		HRESULT hr;

		// XAudioのインスタンスを作成
		hr = XAudio2Create(&xaudio2_);
		if (FAILED(hr))
		{
			assert(!"EffectManager::Init()：XAudioのインスタンスの作成に失敗しました。");
			return false;
		}

		// XAudioのマスターボイス作成
		hr = xaudio2_->CreateMasteringVoice(&xaudio2_master_);	
		if (FAILED(hr))
		{
			assert(!"EffectManager::Init()：XAudioのマスターボイスの作成に失敗しました。");
			return false;
		}
	}

	// エフェクトの再生用の設定を初期化
	{	
			
		// 最大で出力するスプライトの数
		const int maximize_render_sprite_count = 2000;

		// 描画用インスタンスの生成
		renderer_ = EffekseerRendererDX9::Renderer::Create(*DX9Graphics::GetLPD3DDevice(), maximize_render_sprite_count);
		const bool renderer_initialize_failed = (renderer_ == nullptr);
		if (renderer_initialize_failed)
		{
			assert(!"EffectManager::Init()：描画用インスタンスの生成に失敗しました。");
			return false;
		}
	
		// エフェクト管理用インスタンスの生成
		manager_ = Effekseer::Manager::Create(maximize_render_sprite_count);
		const bool manager_initialize_failed = (manager_ == nullptr);
		if (manager_initialize_failed)
		{
			assert(!"EffectManager::Init()：エフェクト管理用インスタンスの生成に失敗しました。");
			return false;
		}

		// 描画用インスタンスから描画機能を設定
		manager_->SetSpriteRenderer(renderer_->CreateSpriteRenderer());
		manager_->SetRibbonRenderer(renderer_->CreateRibbonRenderer());
		manager_->SetRingRenderer(renderer_->CreateRingRenderer());
		manager_->SetTrackRenderer(renderer_->CreateTrackRenderer());
		manager_->SetModelRenderer(renderer_->CreateModelRenderer());


		// 描画用インスタンスからテクスチャの読込機能を設定
		// 独自拡張可能、現在はファイルから読み込んでいる。
		manager_->SetTextureLoader(renderer_->CreateTextureLoader());
		manager_->SetModelLoader(renderer_->CreateModelLoader());

		// 音声再生用インスタンスの生成
		sound_ = EffekseerSound::Sound::Create(xaudio2_, 16, 16);
		const bool sound_initialize_failed = (sound_ == nullptr);
		if (sound_initialize_failed)
		{
			assert(!"EffectManager::Init()：音声再生用インスタンスの生成に失敗しました。");
			return false;
		}

		// 音声再生用インスタンスから再生機能を指定
		manager_->SetSoundPlayer(sound_->CreateSoundPlayer());

		// 音声再生用インスタンスからサウンドデータの読込機能を設定
		// 独自拡張可能、現在はファイルから読み込んでいる。
		manager_->SetSoundLoader(sound_->CreateSoundLoader());
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void EffectManager::Uninit(void)
{
	//読み込んでいるエフェクトのデータを一括破棄
	while (!effect_list_.empty())
	{
		delete effect_list_.back();
		effect_list_.back() = nullptr;
		effect_list_.pop_back();
	}


	// エフェクトの再生用の設定を終了化
	{
		// 先にエフェクト管理用インスタンスを破棄
		manager_->Destroy();

		// 音再生用インスタンスを破棄
		sound_->Destroy();

		// 描画用インスタンスを破棄
		renderer_->Destroy();

		// XAudio2のマスターボイスを解放
		if (xaudio2_master_ != nullptr)
		{
			xaudio2_master_->DestroyVoice();
			xaudio2_master_ = nullptr;
		}

		// XAudioの解放
		ES_SAFE_RELEASE(xaudio2_);

		// COMコンポーネントは、ApplicationManager::Uninit()で終了化済み
		//CoUninitialize();
	}
}

/*-----------------------------------------------------------------------------
/* すべてのエフェクトを一時停止
-----------------------------------------------------------------------------*/
void EffectManager::SetPausedToAllEffect(bool isPaused)
{
	manager_->SetPausedToAllEffects(isPaused);
}

/*-----------------------------------------------------------------------------
/* DirectXの行列をEffekseerの43行列に変換
-----------------------------------------------------------------------------*/
const Effekseer::Matrix43 EffectManager::Convert43Matrix(const D3DXMATRIX& d3dxMatrix)
{
	// Effekseerへの変換行列
	Effekseer::Matrix43 convert_matrix_43;

	// DirectXの行列をEffekseerの行列に変換
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			convert_matrix_43.Value[i][j] = d3dxMatrix.m[i][j];
		}
	}
	return convert_matrix_43;
}

/*-----------------------------------------------------------------------------
/* DirectXの行列をEffekseerの44行列に変換
-----------------------------------------------------------------------------*/
const Effekseer::Matrix44 EffectManager::Convert44Matrix(const D3DXMATRIX& d3dxMatrix)
{
	// Effekseerへの変換行列
	Effekseer::Matrix44 convert_matrix_44;

	// DirectXの行列をEffekseerの行列に変換
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			convert_matrix_44.Values[i][j] = d3dxMatrix.m[i][j];
		}
	}
	return convert_matrix_44;
}

/*-----------------------------------------------------------------------------
/* エフェクトの読み込み処理
-----------------------------------------------------------------------------*/
GameEffect* EffectManager::LoadEffect(EffectType effectTypeID)
{
	auto effect = this->FindEffect(effectTypeID);
	if (effect != nullptr)
	{
		return effect;
	}
	else
	{
		//メッシュがなかったら
		const bool is_mesh_list_out_of_range = ((effectTypeID <= EffectType::None)
											   || (effectTypeID >= EffectType::Max));
		if (is_mesh_list_out_of_range)
		{
			assert("範囲外のエフェクトIDを参照しようとしています！");
			return nullptr;
		}
		this->AddEffect(NEW GameEffect(this, effectTypeID));
	}
	return this->FindEffect(effectTypeID);
}

/*-----------------------------------------------------------------------------
/* エフェクトの解放処理
-----------------------------------------------------------------------------*/
void EffectManager::ReleaseEffect(EffectType effectTypeID)
{
	for (auto effect : effect_list_)
	{
		auto id = effect->GetEffectTypeID();

		if (id == effectTypeID)
		{
			delete effect;
		}
	}
}

/*-----------------------------------------------------------------------------
/* エフェクトの検索処理
-----------------------------------------------------------------------------*/
GameEffect* EffectManager::FindEffect(EffectType effectTypeID)
{
	//エフェクトリストの検索
	for (auto effect : effect_list_)
	{
		//現在の調査対象からIDを取得
		auto id = effect->GetEffectTypeID();

		//取得したIDとeffectTypeIDが一致するか
		if (id == effectTypeID)
		{
			return effect;
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* エフェクトの追加処理
-----------------------------------------------------------------------------*/
void EffectManager::AddEffect(GameEffect* effect)
{
	effect_list_.emplace_back(effect);
}

/*-----------------------------------------------------------------------------
/* エフェクトの削除処理
-----------------------------------------------------------------------------*/
void EffectManager::RemoveEffect(GameEffect* effect)
{
	auto iter = std::find(effect_list_.begin()	//範囲0～
						 , effect_list_.end()	//範囲最大まで
						 , effect);				//探す対象

	if (iter != effect_list_.end())
	{
		effect_list_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/