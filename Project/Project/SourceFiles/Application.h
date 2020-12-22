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
/* メアプリケーションクラス
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
	//初期化と終了化
	bool Init(void);
	void Uninit(void);

	HICON LoadAppIcon(const HINSTANCE& hInstance);

private:
	std::string			app_title_name_;
	WindowStyle			window_style_;
	class MessageLoop*	message_loop_;
};

#endif //APPLICATION_H_
/*=============================================================================
/*		End of File
=============================================================================*/