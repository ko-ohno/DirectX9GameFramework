/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ApplicationManager.h] アプリ全体の処理の管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アプリ全体の処理の管理クラス
=============================================================================*/
#ifndef APPLICATION_MANAGER_H_
#define	APPLICATION_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../IManager.h"
#include "../Win32APIWindow.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* アプリ全体の処理の管理クラス
-------------------------------------*/
class ApplicationManager : public IManager
{
public:
	ApplicationManager(const WindowStyle& windowStyle);
	~ApplicationManager(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void GenerateOutput(void) override;

	bool IsShutDown(void) override;

	// Application側は override しない
	// class Vector2* GetSelectedAspectRatio(void) override;
	// float GetScreenScaler(void) override;
	// bool IsLoopBreak(void) override;

private:
	HWND					window_handle_;
	class Win32APIWindow*	app_window_;
	class DX9Graphics*		dx9_graphics_;
	class InputDevice*		input_device_;	
	class ImGuiManager*		imgui_manager_;
	WindowStyle				window_style_;
	float					screen_scaler_;

	//ゲーム用の環境
	class Game*				game_;
	bool					is_shutdown_;
};

#endif //APPLICATION_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/