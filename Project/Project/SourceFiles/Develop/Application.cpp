/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Application.cpp] アプリケーションクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アプリケーションクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "StdAfx.h"
#include "Application.h"
#include "Application/SplashScreen.h"
#include "Application/MessageLoop.h"
#include "Application/Math.h"
#include "DebugCode/DebugFunction.h"
#include "DevelopSystemDefine.h"
#include "Application/Icon/resource.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Application::Application(void)
	: app_title_name_("")
	, window_style_(WindowStyle())
	, selected_screen_aspect_ratio_(Vector2())
	, message_loop_(nullptr)
	, is_shutdown_(false)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Application::~Application(void)
{
}

/*-----------------------------------------------------------------------------
/* 起動処理
-----------------------------------------------------------------------------*/
bool Application::StartUp(const HINSTANCE& hInstance, const int& nShowCmd)
{
	bool is_success;
	app_title_name_ = "ゲームタイトル";

	//アプリケーション用ウィンドウの設定
	{
		window_style_.hInstance		= hInstance;
		window_style_.nShowCmd		= nShowCmd;
		window_style_.dwWindowStyle = WS_POPUPWINDOW;
		window_style_.hIcon			= this->LoadAppIcon(hInstance, Vector2(256.f, 256.f));
		window_style_.windowTitle	= app_title_name_;
		window_style_.windowSize	= Vector2(200.f,200.f);
	}

#if defined(IN_DEVELOPMENT_)
	//開発用の設定
	{
		window_style_.windowSize = Win32APIWindow().GetFullScreenSize();
	}
#else
	//リリース用の設定

	//スプラッシュスクリーンの実行
	const bool is_failed_startup  = (this->RunSplashScreen() == false);
	if (is_failed_startup)
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("スプラッシュスクリーンの起動に失敗しました。ゲームを終了します。");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return false;
	}

	//シャットダウンの実行
	const bool is_active_shutdown = (is_shutdown_ == true);
	if (is_active_shutdown)
	{
		return false;
	}



	//アスペクト比率がモニターの比率と一致してるかチェック
	const bool is_full_screen = (selected_screen_aspect_ratio_ == Win32APIWindow().GetFullScreenSize());
	if (is_full_screen)
	{
		window_style_.dwWindowStyle = WS_POPUPWINDOW;
	}
	else
	{
		window_style_.dwWindowStyle = WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME);
	}

	//ウィンドウサイズの確定
	window_style_.windowSize = selected_screen_aspect_ratio_;

#endif // IN_DEVELOPMENT_ is not define

	//初期化に失敗したか
	//メッセージループに、アプリケーションのマネージャを登録
	{
		message_loop_ = MessageLoop::Create(MessageLoopType::ApplicationWindow, window_style_);
		is_success = message_loop_->StartUp();
		if (is_success == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("アプリケーションの起動に失敗しました。ゲームを終了します。");
			DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
			return false;	//メッセージループの起動に失敗
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 実行処理
-----------------------------------------------------------------------------*/
void Application::Run(void)
{ 
	message_loop_->Run();
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
void Application::ShutDown(void)
{
	if (message_loop_ != nullptr)
	{
		message_loop_->ShutDown();
		SAFE_DELETE_(message_loop_);
	}
}

/*-----------------------------------------------------------------------------
/* スプラッシュスクリーンの実行処理
-----------------------------------------------------------------------------*/
bool Application::RunSplashScreen(void)
{
	SplashScreen splash_screen;
	const bool   is_success	 = splash_screen.StartUp(window_style_);
	if (is_success)
	{
		splash_screen.Run();

		selected_screen_aspect_ratio_ = *splash_screen.GetSelectedAspectRatio();

		is_shutdown_ = splash_screen.IsApplicationShutDown();

		window_style_.screen_scaler = splash_screen.GetScreenScaler();
	}
	splash_screen.ShutDown();
	return is_success;
}

/*-----------------------------------------------------------------------------
/* アイコンの読み込み処理処理
-----------------------------------------------------------------------------*/
HICON Application::LoadAppIcon(const HINSTANCE& hInstance, const Vector2& iconSize)
{
	//以下のコードとリソースを組み込むことでアイコンを変更する
	HICON hIcon = (HICON)LoadImage(hInstance
								  , MAKEINTRESOURCE(IDI_ICON1)
								  , IMAGE_ICON
								  , static_cast<int>(iconSize.x_)
								  , static_cast<int>(iconSize.y_)
								  , 0);
	return hIcon;
}

/*=============================================================================
/*		End of File
=============================================================================*/