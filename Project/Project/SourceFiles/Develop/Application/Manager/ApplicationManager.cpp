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
#include "../InputDevice/InputDevice.h"
#include "../Game/Input/InputCheck.h"
#include "../ImGui/ImGuiManager.h"
#include "../../DebugCode/DebugFunction.h"

//ゲームの実行環境
#include "../Game/Game.h"

//シェーダテスト
//#include "..Test/Shader/SpriteShader.h"
//#include "Test/GameObject/TestCamera.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ApplicationManager::ApplicationManager(const WindowStyle& windowStyle)
	: app_window_(nullptr)
	, window_handle_(nullptr)
	, dx9_graphics_(nullptr)
	, input_device_(nullptr)
	, imgui_manager_(nullptr)
	, window_style_(WindowStyle())
	, screen_scaler_(0.0f)
	, game_(nullptr)
	, sprite_shader_(nullptr)
	, test_camera_(nullptr)
{
	app_window_	   = app_window_->Create();
	window_handle_ = app_window_->CreateNewWindow(windowStyle, true);

	// ウィンドウについての情報を取得できるように
	window_style_  = windowStyle;
	screen_scaler_ = window_style_.screen_scaler;	// 画面の拡縮倍率を取得できるように
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

	//入力デバイスの生成
	{
		input_device_ = input_device_->Create();
		const bool input_device_init = input_device_->CreateInputDevice(window_style_.hInstance, window_handle_);
		if (input_device_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("InputDeviceの初期化ができませんでした！");
			DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());

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

	//ゲームの起動
	{
		game_ = game_->Create();
		const bool game_init = game_->StartUp(dx9_graphics_);
		if (game_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("ゲームの初期化ができませんでした！");
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
	//ImGuiの終了
	{
		imgui_manager_->ShutDown();
		SAFE_DELETE_(imgui_manager_);
	}

	//ゲームの終了
	{
		game_->ShutDown();
		SAFE_DELETE_(game_);
	}

	SAFE_DELETE_(app_window_);
	SAFE_DELETE_(input_device_);
	SAFE_DELETE_(dx9_graphics_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void ApplicationManager::Input(void)
{
	//入力デバイス更新処理
	if (input_device_ != nullptr)
	{
		//デバイスの更新
		input_device_->Update(window_handle_);

		//デバイス入力検知クラスの更新
		InputCheck::SetInputDeviceState(input_device_);

		game_->Input();
	}
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void ApplicationManager::Update(float deltaTime)
{
	imgui_manager_->UpdateBegin();

	game_->Update(deltaTime);

	imgui_manager_->ShowFramerate(deltaTime);

	imgui_manager_->UpdateEnd();
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void ApplicationManager::GenerateOutput(void)
{
	dx9_graphics_->RenderingBegin();

	game_->GenerateOutput();

	imgui_manager_->ImGuiRender();

	dx9_graphics_->RenderingEnd();
}

/*=============================================================================
/*		End of File
=============================================================================*/