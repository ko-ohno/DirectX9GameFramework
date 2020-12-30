/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ApplicationManager.cpp] アプリ全体の処理の管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アプリ全体の処理の管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "ApplicationManager.h"
#include "../Win32APIWindow.h"
#include "../DX9Graphics.h"
#include "../../ImGui/ImGuiManager.h"
#include "../../CodeDebug/DebugFunction.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ApplicationManager::ApplicationManager(const WindowStyle& windowStyle)
	: app_window_(nullptr)
	, window_handle_(nullptr)
	, dx9_graphics_(nullptr)
	, imgui_manager_(nullptr)
	, screen_scaler_(0.0f)
{
	app_window_	   = app_window_->Create();
	window_handle_ = app_window_->CreateNewWindow(windowStyle, true);
	screen_scaler_ = windowStyle.screen_scaler;	// 画面の拡縮倍率を取得できるように
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
ApplicationManager::~ApplicationManager(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool ApplicationManager::Init(void)
{
	//グラフィックスオブジェクトの生成。
	{
		dx9_graphics_ = dx9_graphics_->Create();
		const bool directx9_init = dx9_graphics_->CreateDX9Graphics(window_handle_, app_window_->GetWindowClientSize(window_handle_));
		if (directx9_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("directx9の初期化ができませんでした！");
			DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
			return false;
		}
	}

	//ImGuiの起動
	{
		imgui_manager_ = imgui_manager_->Create();
		const bool imgui_init = imgui_manager_->StartUp(dx9_graphics_, window_handle_);
		if (imgui_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("ImGuiの初期化ができませんでした！");
			DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void ApplicationManager::Uninit(void)
{
	imgui_manager_->ShutDown();

	SAFE_DELETE_(app_window_);
	SAFE_DELETE_(imgui_manager_);
	SAFE_DELETE_(dx9_graphics_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void ApplicationManager::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void ApplicationManager::Update(float deltaTime)
{
	imgui_manager_->UpdateBegin();

	imgui_manager_->ShowFramerate(deltaTime);

	imgui_manager_->UpdateEnd();
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void ApplicationManager::GenerateOutput(void)
{
	dx9_graphics_->RenderingBegin();

	imgui_manager_->ImGuiRender();

	dx9_graphics_->RenderingEnd();
}

/*=============================================================================
/*		End of File
=============================================================================*/