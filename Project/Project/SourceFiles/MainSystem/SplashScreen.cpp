/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreen.cpp] モジュール
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "SplashScreen.h"
#include "MessageLoop.h"
#include "Win32APIWindow.h"
#include "../Generic/Math.h"

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
    std::string window_sub_name = ":スプラッシュスクリーン";

    //ローカル変数に、スプラッシュスクリーンのウィンドウの設定書き込む
    window_style_ = windowStyle;
    {
        //window_style.hInstance    = hinstance;    //Application.cppでの設定を引き継ぐ
        //window_style.nCmdShow     = nShowCmd;     //Application.cppでの設定を引き継ぐ
        window_style_.dwWindowStyle = WS_POPUPWINDOW;
        window_style_.windowTitle   = window_name + window_sub_name;
        //window_style.hIcon;                       //Application.cppでの設定を引き継ぐ
        window_style_.windowSize    = Vector2(500.f, 600.f);
    }

    //メッセージループに、スプラッシュスクリーンのマネージャを登録
    message_loop_ = MessageLoop::Create(MessageLoopType::SplashScreenWindow, window_style_);
    const bool is_success = message_loop_->StartUp();
    if (is_success == false)
    {
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

/*=============================================================================
/*		End of File
=============================================================================*/