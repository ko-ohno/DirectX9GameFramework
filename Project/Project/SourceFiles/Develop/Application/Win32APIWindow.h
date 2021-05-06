/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Win32APIWindow.h] Win32APIウィンドウ管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：Win32APIウィンドウ管理クラス
=============================================================================*/
#ifndef WIN32API_WINDOW_H_
#define	WIN32API_WINDOW_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "Math.h"

/*-------------------------------------
/* ウィンドウデータ構造体
-------------------------------------*/
struct WindowStyle
{
public:
	WindowStyle(void)
		: hInstance(nullptr)
		, nShowCmd(1)
		, dwWindowStyle(0UL)
		, hIcon(nullptr)
		, windowTitle("")
		, windowSize(Vector2())
		, screen_scaler(1.f)
	{}

	~WindowStyle(void) {}

public:
	HINSTANCE	  hInstance;		//インスタンスハンドル
	int			  nShowCmd;			//ウィンドウの表示状態
	DWORD		  dwWindowStyle;	//ウィンドウの表示書式
	HICON		  hIcon;			//アイコンへのインスタンス
	std::string   windowTitle;		//ウィンドウタイトル
	Vector2		  windowSize;		//ウィンドウサイズ
	float		  screen_scaler;	//画面の拡縮倍率
};

/*-------------------------------------
/* ウィンドウ生成管理クラス
-------------------------------------*/
class Win32APIWindow
{
public:
	Win32APIWindow(void);
	~Win32APIWindow(void);

	static Win32APIWindow* Create();

	HWND CreateNewWindow(WindowStyle windowStyle, bool isAppWindow = false);

public:
	Vector2 CalculateWindowSize(const DWORD& dwWindowStyle
							   , const Vector2& windowSize
							   , const BOOL isCreateSysMenu) const;

	Vector2 CalculateFullScreenWindowSize(const DWORD& dwWindowStyle, const BOOL isCreateSysMenu) const;

	Vector2 CalculateWindowCreatePos(const Vector2& windowSize) const;

	void SetWindowSize(const Vector2& windowSize);
	void SetWindowSize(const float windowWidth, const float windowHeight);

	Vector2 GetWindowSize(void) const;
	Vector2 GetWindowClientSize(const HWND& windowHandle) const;
	Vector2 GetFullScreenSize(void) const;

private:
	WNDCLASSEX  wcex_;
	std::string window_class_name_;
	Vector2	    window_size_;
	HWND	    window_handle_;
};

#endif //WIN32API_WINDOW_H_
/*=============================================================================
/*		End of File
=============================================================================*/