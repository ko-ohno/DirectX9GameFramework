/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Win32APIWindow.h] ウィンドウ生成管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ウィンドウ生成管理クラス
=============================================================================*/
#ifndef WIN32API_WINDOW_H_
#define	WIN32API_WINDOW_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "../Generic/Math.h"

/*-------------------------------------
/* ウィンドウデータ構造体
-------------------------------------*/
struct WindowStyle
{
public:
	WindowStyle(void)
		: hInstance(nullptr)
		, nCmdShow(1)
		, dwWindowStyle(0UL)
		, hIcon(nullptr)
		, windowTitle("")
		, windowSize(Math::Vector2())
		, isWindowed(TRUE)
	{}

	~WindowStyle(void) {}

public:
	HINSTANCE	  hInstance;		//インスタンスハンドル
	int			  nCmdShow;			//ウィンドウの表示状態
	DWORD		  dwWindowStyle;		//ウィンドウの表示書式
	HICON		  hIcon;			//アイコンへのインスタンス
	std::string   windowTitle;		//ウィンドウタイトル
	Math::Vector2 windowSize;		//ウィンドウサイズ
	BOOL		  isWindowed;		//ウィンドウ表示するか？
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
	HWND CreateAppWindow(WindowStyle windowStyle);

public:
	Math::Vector2 CalculateWindowSize(const DWORD& dwWindowStyle
								     , const Math::Vector2& windowSize
								     , const BOOL isCreateSysMenu) const;

	Math::Vector2 CalculateWindowCreatePos(const Math::Vector2& windowSize) const;

	void SetWindowSize(const Math::Vector2& windowSize);
	void SetWindowSize(const float windowWidth, const float windowHeight);

	Math::Vector2 GetWindowSize(void) const;
	Math::Vector2 GetWindowClientSize(const HWND& wndHandle) const;

private:
	Math::Vector2 window_size_;
};

#endif //WIN32API_WINDOW_H_
/*=============================================================================
/*		End of File
=============================================================================*/