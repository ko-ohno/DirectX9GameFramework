/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Application.h] アプリケーションクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アプリケーションクラス
=============================================================================*/
#ifndef APPLICATION_H_
#define	APPLICATION_H_

/*--- インクルードファイル ---*/
#include "MainSystem/Win32APIWindow.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* アプリケーションクラス
-------------------------------------*/
class Application
{
public:
	Application(void);
	~Application(void);

public:
	bool StartUp(const HINSTANCE& hInstance, const int& nShowCmd);
	void Run(void);
	void ShutDown(void);

private:
	//スプラッシュスクリーンの実行
	bool RunSplashScreen(void);

	HICON LoadAppIcon(const HINSTANCE& hInstance);

private:
	std::string			app_title_name_;
	WindowStyle			window_style_;
	class Vector2*		selected_screen_aspect_ratio_;
	class MessageLoop*	message_loop_;
	bool				is_shutdown_;
};

#endif //APPLICATION_H_
/*=============================================================================
/*		End of File
=============================================================================*/