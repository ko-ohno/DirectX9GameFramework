/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MainProcess.cpp] メインの実行処理
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メインの実行処理
=============================================================================*/

/*--- インクルードファイル ---*/
#include "StdAfx.h"
#include "Application.h"
#include "ApplicationManager.h"
#include "Window/Win32APIWindow.h"
#include "Generic/Math.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Application::Application(void)
	:app_manager_(nullptr)
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
bool Application::StartUp(const HINSTANCE& hinstance, const int& nCmdShow)
{
#if defined(_DEBUG) || defined(DEBUG)
	OutputDebugString("アプリケーションを起動します。\n");
#endif

	//以下のコードとリソースを組み込むことでアイコンを変更する
	//HICON hIcon = (HICON)LoadImage(hInstance_
	//	, MAKEINTRESOURCE(IDI_ICON1)
	//	, IMAGE_ICON
	//	, 64
	//	, 64
	//	, 0);

	//Math::Vector2 screen_size(0.f, 0.f);
	//BOOL is_windowed = TRUE;
	//bool is_init_success = false;

	//ウィンドウのインスタンス作成
	app_window_ = Win32APIWindow::Create();


	//ウィンドウスタイルの指定
	WindowStyle window_style;
	{
		window_style.hInstance	 = hinstance;
		window_style.nCmdShow	 = nCmdShow;
		window_style.windowTitle = "test";
		window_style.hIcon;
		window_style.windowSize  = {1280.f, 720.f};
		window_style.isWindowed  = TRUE;
	}
	app_window_->CreateAppWindow(window_style);

	////成功したかどうか
	//Application::Init();
	//ApplicationManager::Init();

	return true;
}

/*-----------------------------------------------------------------------------
/* 実行処理
-----------------------------------------------------------------------------*/
void Application::Run(void)
{ 
#if defined(_DEBUG) || defined(DEBUG)
	OutputDebugString("アプリケーションを実行します。\n");
#endif

	MSG msg;
	DWORD execute_last_time			= 0UL;		//1フレーム前の終了時間
	DWORD current_time				= 0UL;		//現在の時間
	DWORD ticks_counts				= 0UL;		//1フレームの経過時間
	float delta_time				= 0.f;		//1フレーム前との差分の秒数		
	const float maximum_delta_time	= 0.05f;	//deltaTimeの最大制限値

	timeBeginPeriod(1); //分解能を設定

	for(;;)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			//ウィンドウメッセージ処理 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//60fps化
			current_time = timeGetTime(); //実行時間を取得

			//1フレーム前との差分を取得
			ticks_counts = (current_time - execute_last_time);

			//秒数に変換
			delta_time = ((float)ticks_counts / 1000.f);

			if (delta_time >= (1 / 60))
			{
				//delta_time >= (1 / 60)
				//1フレーム前との差分が0.016...ミリ秒以上だったら実行する

				//delta_timeの制限
				//実行中やブレークポイント発行時等の予防措置
				if (delta_time >= maximum_delta_time)
				{
					delta_time = maximum_delta_time;
				}

				ApplicationManager::Input();
				ApplicationManager::Update(delta_time);
				ApplicationManager::GenerateOutput();

				//現在のフレームの実行前時間に実行後時間を代入。
				execute_last_time = current_time;
			}
		}
		if (msg.message == WM_QUIT) { break; }
	}

	timeEndPeriod(1); //分解能を解除
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
void Application::ShutDown(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	OutputDebugString("アプリケーションを終了します。\n");
#endif

	ApplicationManager::Uninit();
	Application::Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Application::Init(void)
{
	app_manager_ = app_manager_->Create();
	if (app_manager_ == nullptr) { return false; }
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Application::Uninit(void)
{
	delete app_manager_;
}

/*=============================================================================
/*		End of File
=============================================================================*/