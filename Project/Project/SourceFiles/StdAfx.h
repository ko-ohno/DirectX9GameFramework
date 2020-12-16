/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdAfx.h] 標準アプリケーション拡張フレームワーク
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：標準のシステム インクルード ファイルのインクルードファイル、
/*	または参照回数が多く、かつあまり変更されない、プロジェクト専用の
/*	インクルードファイル を記述します。
=============================================================================*/
#ifndef STDAFX_H_
#define	STDAFX_H_

//標準アプリケーション拡張フレームワーク
//"StdAfx" Standard Application Framework Extensions.

/*--- インクルードファイル ---*/
#include <Windows.h>	// WindowsAPIの機能を利用するためのヘッダーファイル。

//Windows.hのマクロ関数、minとmaxの除外。
#undef min
#undef max

/*--- ゲームに必要なライブラリの呼び出し ---*/
//グラフィックス系
#include <d3d9.h>		//DirectX9のインターフェース
#include <d3dx9.h>		//DirectX9の機能を利用するためのヘッダ

//入力系
#define DIRECTINPUT_VERSION (0x0800) //DirectInputのバージョンを指定。
#include<dinput.h>		//入力用ライブラリ

/*--- Cランタイムヘッダーファイル ---*/
#include <cstdio>	
#include <cstdlib>	
#include <cassert>
#include <crtdbg.h>
#include <cmath>	
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

/*--- STLのファイルをインクルード ---*/
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

/*--- ライブラリのリンク ---*/
#pragma comment(lib,"winmm.lib")	//WindowsAPIのライブラリをリンク
#pragma comment(lib,"d3d9.lib")		//DirectX9の機能を使うためにライブラリをリンク
#if defined(_DEBUG)||(DEBUG)
#pragma comment(lib,"d3dx9d.lib")	//デバッグ時	
#else
#pragma comment(lib,"d3dx9.lib")	//リリース時
#endif
#pragma comment(lib,"dxguid.lib")	//入力や音声の処理に必要。
#pragma comment(lib,"dinput8.lib")	//入力用のライブラリをリンク

/*--- マクロの定義 ---*/

//メモリーリークを検知用の処理
#if defined(_DEBUG) || defined(DEBUG) && !defined(NEW)
#define _CRTDBG_MAP_ALLOC //newのoperatorをoverrideした定義を呼び出すためのマクロ
#define NEW  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW  new
#endif

//メモリ解放マクロ関数
#define SAFE_RELEASE_(x) if((x) != NULL){ (x)->Release(); x = nullptr; }

//中身をdeleteするマクロ関数
#define SAFE_DELETE_(p) { if(p) { delete p; p = nullptr; } }

//配列の中身をdeleteするマクロ関数
#define SAFE_DELETE_ARRAY_(p) { if(p) { delete []p;   p = nullptr; } }

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/

#endif //STDAFX_H_
/*=============================================================================
/*		End of File
=============================================================================*/