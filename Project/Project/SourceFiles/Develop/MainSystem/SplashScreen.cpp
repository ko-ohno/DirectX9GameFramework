/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreen.cpp] スプラッシュスクリーンクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプラッシュスクリーンクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "SplashScreen.h"
#include "MessageLoop.h"
#include "Win32APIWindow.h"
#include "../Generic/Math.h"
#include "../CodeDebug/DebugFunction.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SplashScreen::SplashScreen(void)
    : window_style_(WindowStyle())
    , message_loop_(nullptr)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SplashScreen::~SplashScreen(void)
{
}

/*-----------------------------------------------------------------------------
/* 起動処理
-----------------------------------------------------------------------------*/
bool SplashScreen::StartUp(const WindowStyle& windowStyle)
{
    std::string window_name     =  windowStyle.windowTitle;
    std::string window_sub_name = "：スプラッシュスクリーン";

    //ローカル変数に、スプラッシュスクリーンのウィンドウの設定書き込む
    window_style_ = windowStyle;
    {
        //window_style.hInstance    = hinstance;    //Application.cppでの設定を引き継ぐ
        //window_style.nShowCmd     = nShowCmd;     //Application.cppでの設定を引き継ぐ
        //window_style.hIcon;                      //Application.cppでの設定を引き継ぐ
        window_style_.dwWindowStyle = WS_POPUPWINDOW;
        window_style_.windowTitle   = window_name + window_sub_name;
        window_style_.windowSize    = Vector2(500.f, 600.f);
    }

    //メッセージループに、スプラッシュスクリーンのマネージャを登録
    message_loop_ = MessageLoop::Create(MessageLoopType::SplashScreenWindow, window_style_);
    const bool is_success = message_loop_->StartUp();
    if (is_success == false)
    {
        std::string msg_str = OUTPUT_FORMAT_STRING("スプラッシュスクリーンの初期化ができませんでした！");
        DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
        return false;
    }
    return true;
}

/*-----------------------------------------------------------------------------
/* 実行処理
-----------------------------------------------------------------------------*/
void SplashScreen::Run(void)
{
    message_loop_->Run();
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
void SplashScreen::ShutDown(void)
{
    message_loop_->ShutDown();
    SAFE_DELETE_(message_loop_);
}

/*-----------------------------------------------------------------------------
/* 選択したアスペクト比率の取得処理
-----------------------------------------------------------------------------*/
Vector2* SplashScreen::GetSelectedAspectRatio(void)
{
    if (message_loop_ == nullptr) { return nullptr; }
    return message_loop_->GetSelectedAspectRatio();
}

/*-----------------------------------------------------------------------------
/* 画面比率
-----------------------------------------------------------------------------*/
float SplashScreen::GetScreenScaler(void)
{
    if (message_loop_ == nullptr) { return 1.0f; }
    return message_loop_->GetScreenScaler();
}

/*-----------------------------------------------------------------------------
/*  アプリケーションを終了するか
-----------------------------------------------------------------------------*/
bool SplashScreen::IsApplicationShutDown(void)
{
    if (message_loop_ == nullptr) { return false; }
    return message_loop_->IsShutDown();
}

/*=============================================================================
/*		End of File
=============================================================================*/