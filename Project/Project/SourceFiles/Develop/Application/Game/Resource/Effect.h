/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[XFileMesh.h] Xファイルメッシュクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：Xファイルメッシュクラス
=============================================================================*/
#ifndef EFFECT_H_
#define	EFFECT_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "../Manager/EffectManager.h"


/*-------------------------------------
/* エフェクトクラス
-------------------------------------*/
class Effect
{
public:
	Effect(class EffectManager* manager, EffectType effectType);
	~Effect(void);

	// エフェクトの読み込み
	bool LoadEffect(const EffectType effectType);

	// テクスチャの読み込みができているか
	bool IsGetLoadCompleted(void) { return is_loading_complete_; }

	//
	// エフェクトのデータ取得関数
	//

	// エフェクトIDの取得
	EffectType GetEffectTypeID(void) { return effect_type_id_; }

	// エフェクト情報の取得
	Effekseer::Effect* GetEffect(void) { return effect_; }

	// エフェクトのハンドル取得
	Effekseer::Handle* GetEffectHandle(void) { return &handle_; }

private:
	std::wstring StringToWString(const std::string& str);

private:
	static constexpr int ERROR_CODE_EFFECT_HANDLE = -1;

	// エフェクトの所有者
	class EffectManager* effect_manager_;

	//
	// エフェクトののデータ
	//

	bool				is_loading_complete_;	// ロードが完了しているか

	EffectType			effect_type_id_;		// エフェクトのID

	Effekseer::Effect*	effect_;				// 操作するエフェクト
	
	Effekseer::Handle	handle_;				// エフェクト操作用のハンドル
};

#endif //EFFECT_H_
/*=============================================================================
/*		End of File
=============================================================================*/
