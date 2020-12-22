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

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ApplicationManager::ApplicationManager(const WindowStyle& windowStyle)
	: app_window_(nullptr)
	, window_handle_(nullptr)
	, dx9_graphics_(nullptr)
	, imgui_manager_(nullptr)
{
	app_window_	   = app_window_->Create();
	window_handle_ = app_window_->CreateNewWindow(windowStyle, true);
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
	dx9_graphics_ = dx9_graphics_->Create();
	dx9_graphics_->CreateDX9Graphics(window_handle_, app_window_->GetWindowClientSize(window_handle_));


	imgui_manager_->Create();
	imgui_manager_->StartUp(dx9_graphics_, window_handle_);

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void ApplicationManager::Uninit(void)
{

	imgui_manager_->ShutDown();
	SAFE_DELETE_(app_window_);
	SAFE_DELETE_(dx9_graphics_);
	SAFE_DELETE_(imgui_manager_);
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