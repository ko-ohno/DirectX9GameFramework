/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreenManager.h] スプラッシュスクリーン全体の処理の管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプラッシュスクリーンの全体の処理の管理クラス
=============================================================================*/
#ifndef SPLASHSCREEN_MANAGER_H_
#define	SPLASHSCREEN_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../IManager.h"
#include "../Win32APIWindow.h"
#include "../../Generic/Math.h"

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
	~SplashScreenManager(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void GenerateOutput(void) override;

	//スプラッシュスクリーン側からアプリケーション側に、アスペクト比率を渡す
	class Vector2* GetSelectedAspectRatio(void) override;

	// メッセージループの状態をマネージャ側から制御
	bool IsLoopBreak(void) override;
	bool IsShutDown(void) override;

private:
	//アスペクト比率の作成
	void MakeListAspectRatio(void);

private:
	//アスペクト比率の計算
	std::vector<std::string> aspact_ratio_string_array_;
	std::vector<Vector2>	 aspect_ratio_size_array_;
	Vector2					 aspect_ratio_size_;

	//スプラッシュスクリーン用の画像データ
	LPDIRECT3DTEXTURE9		 texture_;
	Vector2					 texture_size_;

	HWND					 window_handle_;
	class Win32APIWindow*	 splash_window_;
	class DX9Graphics*		 dx9_graphics_;
	class ImGuiManager*		 imgui_manager_;
	bool					 is_loop_break_;
	bool					 is_shutdown_;
};

#endif //SPLASHSCREEN_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/