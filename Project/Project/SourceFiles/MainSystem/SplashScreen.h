/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreen.h] スプラッシュスクリーンクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプラッシュスクリーンクラス
=============================================================================*/
#ifndef SPLASHSCREEN_H_
#define	SPLASHSCREEN_H_

/*--- インクルードファイル ---*/
#include "Win32APIWindow.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* スプラッシュスクリーンクラス
-------------------------------------*/
class SplashScreen
{
public:
	SplashScreen(void);
	~SplashScreen(void);

public:
	bool StartUp(const WindowStyle& windowStyle);
	void Run(void);
	void ShutDown(void);

	class Vector2* GetSelectedAspectRatio(void);
	bool IsApplicationShutDown(void);
	
private:
	WindowStyle			  window_style_;
	class MessageLoop*	  message_loop_;
};

#endif //SPLASHSCREEN_H_
/*=============================================================================
/*		End of File
=============================================================================*/