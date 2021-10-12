/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AspectRatio.cpp] アスペクト比率自動計算クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アスペクト比率自動計算クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "AspectRatio.h"
#include "Win32APIWindow.h"
#include "Math.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
AspectRatio::AspectRatio(void)
{	
	//初期化
	aspect_ratio_list_.clear();
	screen_scaler_.clear();

	//アスペクト比率は16：9の比率を何倍にしたかの値
	//例):1920:1080は16：9を120倍にした値

	//拡大率の計算
	//1920x1080を倍率1.00とし、倍率0.5を最低とし、倍率0.8を最大(フルスクリーンを除く)とする。
	const float maximize_scaler  = 0.85f;
	const float scaler_add_value = 0.05f;
	float scaler = 0.5f;
	for (;;)
	{
		screen_scaler_.push_back(scaler);
		scaler += scaler_add_value;
		if (scaler >= maximize_scaler) { break; }

		if (scaler >= maximize_scaler)
		{
			assert(!"不正な画面比率の計算をしています！！");
		}
	}

	//画面サイズの最大値を取得
	Vector2 full_screen_window_size = Win32APIWindow().GetFullScreenSize();

	//画面サイズのリストの生成
	for (auto screen_scale : screen_scaler_)
	{
		//計算後のアスペクト比率を格納
		const Vector2 calculated_aspect_ratio = full_screen_window_size * screen_scale;
	
		const std::string asepct_ratio_string = this->OutputAspectRatioString(calculated_aspect_ratio);

		//vector配列に格納
		auto value = std::make_pair(asepct_ratio_string, Vector2(calculated_aspect_ratio));
		aspect_ratio_list_.push_back(value);

	}

	//フルスクリーンの場合の文字列を生成
	const std::string full_asepct_ratio_string = this->OutputAspectRatioString(full_screen_window_size);

	//画面サイズの最大値を登録
	auto value = std::make_pair("FullScreen("+ full_asepct_ratio_string +")"  ,  Vector2(full_screen_window_size));
	aspect_ratio_list_.push_back(value);
	screen_scaler_.push_back(1.f);		// 最後は原寸大拡縮値の倍率を保存
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
AspectRatio::~AspectRatio(void)
{
	while (!aspect_ratio_list_.empty())
	{
		aspect_ratio_list_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
AspectRatio* AspectRatio::Create(void)
{
	return NEW AspectRatio();
}

/*-----------------------------------------------------------------------------
/* アスペクト比率のリスト取得関数
-----------------------------------------------------------------------------*/
std::vector<std::pair<std::string, class Vector2>> AspectRatio::GetAspectRatioList(void)
{
	return aspect_ratio_list_;
}

/*-----------------------------------------------------------------------------
/* アスペクト比率の拡縮値
-----------------------------------------------------------------------------*/
std::vector<float> AspectRatio::GetScreenScalerList(void)
{
	return screen_scaler_;
}

/*-----------------------------------------------------------------------------
/* アスペクト比率の文字列生成
-----------------------------------------------------------------------------*/
std::string AspectRatio::OutputAspectRatioString(const Vector2& screenSize)
{
	//アスペクト比の表記文字列の生成
	const std::string str_screen_width  = std::to_string(static_cast<int>(screenSize.x_));
	const std::string str_screen_height = std::to_string(static_cast<int>(screenSize.y_));

	//文字列の合成
	return std::string(str_screen_width + "x" + str_screen_height);
}

/*=============================================================================
/*		End of File
=============================================================================*/