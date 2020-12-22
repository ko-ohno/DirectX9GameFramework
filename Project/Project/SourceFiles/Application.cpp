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
#include "MainSystem/SplashScreen.h"
#include "MainSystem/MessageLoop.h"
#include "Generic/Math.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Application::Application(void)
	: app_title_name_("")
	, window_style_(WindowStyle())
	, message_loop_(nullptr)
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

	//ゲーム用ウィンドウの設定
	{
		window_style_.hInstance		= hInstance;
		window_style_.nShowCmd		= nShowCmd;
		window_style_.dwWindowStyle = WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME);
		window_style_.windowTitle	= app_title_name_;
		window_style_.hIcon			= LoadAppIcon(hInstance);
		//window_style_.windowSize	= Vector2(100.f, 100.f);
		window_style_.windowSize	= Vector2(1280.f, 720.f);
	}

	//自身の初期化
	is_success = this->Init();
	if (is_success == false)
	{
		return false;	//初期化の失敗
	}

	//メッセージループに、アプリケーションのマネージャを登録
	{
		message_loop_ = MessageLoop::Create(MessageLoopType::ApplicationWindow, window_style_);
		is_success = message_loop_->StartUp();
		if (is_success == false)
		{
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
	message_loop_->ShutDown();
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Application::Init(void)
{
	//スプラッシュスクリーンの実行
	{
		SplashScreen splash_screen;
		const bool is_success = splash_screen.StartUp(window_style_);
		if (is_success)
		{
			splash_screen.Run();
		}
		else
		{
			return false;	//スプラッシュスクリーンの起動に失敗
		}
		splash_screen.ShutDown();
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Application::Uninit(void)
{
	SAFE_DELETE_(message_loop_);
}

/*-----------------------------------------------------------------------------
/* アイコンの読み込み処理処理
-----------------------------------------------------------------------------*/
HICON Application::LoadAppIcon(const HINSTANCE& hInstance)
{
	//以下のコードとリソースを組み込むことでアイコンを変更する
	//HICON hIcon = (HICON)LoadImage(hInstance_
	//								, MAKEINTRESOURCE(IDI_ICON1)
	//								, IMAGE_ICON
	//								, 64
	//								, 64
	//								, 0);

	return HICON();
}

/*=============================================================================
/*		End of File
=============================================================================*/