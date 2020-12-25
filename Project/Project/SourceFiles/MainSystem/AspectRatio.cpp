/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AspectRatio.cpp] モジュール
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "AspectRatio.h"
#include "Win32APIWindow.h"

//アスペクト比率は16：9の比率を何倍にしたかの値
//1920:1080は16：9を120倍にした値


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
AspectRatio::AspectRatio(void)
{
	//
	Win32APIWindow window;
	DWORD window_style = WS_POPUPWINDOW; //フルスクリーンの際の設定
	Vector2 fullscreen_aspect = window.CalculateFullScreenWindowSize(window_style, false);

	RECT fullscreen_padding;
	fullscreen_padding.left		= 0.0f;
	fullscreen_padding.right	= 2.0f;
	fullscreen_padding.top		= 0.0f;
	fullscreen_padding.bottom	= 2.0f;


	const float screen_padding_width = static_cast<float>(fullscreen_padding.left - fullscreen_padding.right);
	const float screen_padding_height = static_cast<float>(fullscreen_padding.top - fullscreen_padding.bottom);

	Vector2 true_fullscreen_aspect = { fullscreen_aspect.x_ -screen_padding_width
									 , fullscreen_aspect.y_ -screen_padding_height };


	int a = GetSystemMetrics(SM_CXSCREEN);
	int b = GetSystemMetrics(SM_CYSCREEN);


}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
AspectRatio::~AspectRatio(void)
{
}

/*-----------------------------------------------------------------------------
/* アスペクト比率の計算
-----------------------------------------------------------------------------*/
Vector2* AspectRatio::CaiculationAspectRatio(const DWORD& dwWindowStyle)
{
	DWORD winodw_style = WS_POPUPWINDOW;
	


	//画面のフルスクリーンのサイズを取得

	//このサイズを倍率1.00とし、順番に0.25ずつ引いた値をかけ合わせる

	std::unordered_map<std::string, int> a;
	std::vector<float> vec_array_float = {0.5f, 0.6f, 0.7f, 0.8f, 1.0f};
	
	auto iter = vec_array_float.begin();

	a.emplace(std::to_string(1), 999);

	return NEW Vector2();
}

/*-----------------------------------------------------------------------------
/* フルスクリーンのウィンドウサイズの取得
-----------------------------------------------------------------------------*/
Vector2* AspectRatio::GetFullScreenWindowSize(const DWORD& dwWindowStyle)
{
	Win32APIWindow window;
	return NEW Vector2(window.CalculateFullScreenWindowSize(dwWindowStyle, false));
}

/*=============================================================================
/*		End of File
=============================================================================*/