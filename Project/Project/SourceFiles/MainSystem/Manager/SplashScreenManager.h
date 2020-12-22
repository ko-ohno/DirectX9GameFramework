/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreenManager.h] アプリ全体の処理の管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：全体の処理の管理クラス
=============================================================================*/
#ifndef SPLASHSCREEN_MANAGER_H_
#define	SPLASHSCREEN_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../IManager.h"
#include "../Win32APIWindow.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* アプリ全体の処理の管理クラス
-------------------------------------*/
class SplashScreenManager : public IManager
{
public:
	SplashScreenManager(const WindowStyle& windowStyle);
	~SplashScreenManager(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void GenerateOutput(void) override;

private:
	HWND					window_handle_;
	class Win32APIWindow*	splash_window_;
	class DX9Graphics*		dx9_graphics_;
	class ImGuiManager*		imgui_manager_;

};

#endif //SPLASHSCREEN_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/