/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Effect.cpp] エフェクトクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エフェクトクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "Effect.h"
#include "../Manager/EffectManager.h"

#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Effect::Effect(EffectManager* manager, EffectType effectType)
	: effect_manager_(manager)
	, effect_type_id_(EffectType::None)
	, is_loading_complete_(false)
	, effect_(nullptr)
	, handle_(-1)
{
	//エフェクトIDの設定
	effect_type_id_ = effectType;

	//エフェクトの読み込み
	is_loading_complete_ = this->LoadEffect(effectType);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Effect::~Effect(void)
{
	SAFE_RELEASE_(effect_);
}

/*-----------------------------------------------------------------------------
/* 読み込み処理
-----------------------------------------------------------------------------*/
bool Effect::LoadEffect(const EffectType effectType)
{
	// エフェクシアのマネージャの取得
	auto effekseer_manager_ = effect_manager_->GetEffekseerManager();

	//ルートパスとファイルパスの合成
	auto effect_filepath = effect_manager_->GetEffectRootpath() + effect_manager_->GetEffectFilepathList().at(effectType);

	//stringをwstringへ変換
	std::wstring filepath = this->StringToWString(effect_filepath);

	// エフェクトの作成
	effect_ = Effekseer::Effect::Create(effekseer_manager_, (const EFK_CHAR*)filepath.c_str());
	if (effect_ == nullptr)
	{
		//ファイルパスと最後のディレクトリパスを取得
		auto filename		= effect_manager_->GetEffectFilepathList().at(effectType);
		auto str_offset_pos = filename.find("/");

		//ファイル名だけを取り出す
		filename.erase(0, str_offset_pos +1); // "/" 分オフセット

		//エラーメッセージの作成
		std::string err_msg = "Effect::LoadEffect()：Effekseerによるエフェクトの作成に失敗しました。\nEffectType：" + filename;
		MessageBox(nullptr
			, err_msg.c_str()
			, "警告"
			, (MB_OK | MB_ICONWARNING));
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* stringをwstringへ変換
-----------------------------------------------------------------------------*/
std::wstring Effect::StringToWString(const std::string& str)
{
	// SJIS → wstring
	int buf_size = MultiByteToWideChar(CP_ACP
									  , NULL
									  , str.c_str()
									  , -1
									  , (wchar_t*)NULL
									  , NULL);

	// バッファの取得
	wchar_t* wchar_buf = NEW wchar_t[buf_size];

	// SJIS → wstring
	MultiByteToWideChar(CP_ACP
					   , 0
					   , str.c_str()
					   , -1
					   , wchar_buf
					   , buf_size);

	// wstringの生成
	std::wstring wstr(wchar_buf, wchar_buf + buf_size - 1);

	// バッファの破棄
	delete[] wchar_buf;

	// 変換結果を返す
	return wstr;
}


/*=============================================================================
/*		End of File
=============================================================================*/