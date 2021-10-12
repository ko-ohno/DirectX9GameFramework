/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9Graphics.cpp] DirectX9グラフィックスの窓口役クラスの動作定義
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：レンダリングに関する処理を各クラスに伝えるクラスの動作定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "DX9Graphics.h"
#include "DX9Graphics/DX9GraphicsDevice.h"
#include "DX9Graphics/DX9GraphicsRenderer.h"
#include "Math.h"
#include "../DebugCode/DebugFunction.h"


//静的変数宣言
LPDIRECT3DDEVICE9	  DX9Graphics::lpd3d_device_;		//Direct3Dデバイス
DX9GraphicsDevice*	  DX9Graphics::graphics_device_;	//デバイスクラス
DX9GraphicsRenderer*  DX9Graphics::graphics_renderer_;	//レンダラークラス

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
DX9Graphics::DX9Graphics(void)
	: screen_size_(0.f, 0.f)
	, screen_scaler_(1.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
DX9Graphics::~DX9Graphics(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
DX9Graphics* DX9Graphics::Create()
{
	return NEW DX9Graphics();
}

/*-----------------------------------------------------------------------------
/* DirectX9グラフィックスの生成
-----------------------------------------------------------------------------*/
bool DX9Graphics::CreateDX9Graphics(const HWND& windowHandle, const Vector2& screenSize)
{
	//画面サイズを取得
	screen_size_ = screenSize;

	//デバイスとレンダラーの生成
	lpd3d_device_ = CreateGraphicsDevice(windowHandle, screenSize);
	if (lpd3d_device_ == nullptr)
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("グラフィックスのデバイスを作成できませんでした！");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return false;
	}

	//レンダラーを作成
	CreateDX9Renderer(lpd3d_device_);
	return true;
}

/*-----------------------------------------------------------------------------
/* デバイスの取得
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9* DX9Graphics::GetLPD3DDevice(void)
{
	return &lpd3d_device_;
}

/*-----------------------------------------------------------------------------
/* グラフィックスの初期化
/*---------------------------------------------------------------------------*/
void DX9Graphics::Init(void)
{
	lpd3d_device_ = nullptr;
	graphics_device_ = nullptr;
	graphics_renderer_ = nullptr;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void DX9Graphics::Uninit(void)
{
	SAFE_RELEASE_(lpd3d_device_);
	SAFE_DELETE_(graphics_device_);
	SAFE_DELETE_(graphics_renderer_);
}

/*-----------------------------------------------------------------------------
/* レンダリングの開始
-----------------------------------------------------------------------------*/
bool DX9Graphics::RenderingBegin(void)
{
	return graphics_renderer_->RenderingBegin();
}

/*-----------------------------------------------------------------------------
/* レンダリングの終了
-----------------------------------------------------------------------------*/
void DX9Graphics::RenderingEnd(void)
{
	graphics_renderer_->RenderingEnd();
}

/*-----------------------------------------------------------------------------
/* グラフィックデバイスの生成処理
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9Graphics::CreateGraphicsDevice(const HWND& windowHandle, const Vector2& screenSize)
{
	graphics_device_ = graphics_device_->Create();
	return graphics_device_->CreateGraphicsDevice(windowHandle, screenSize);
}

/*-----------------------------------------------------------------------------
/* レンダラーの生成処理
-----------------------------------------------------------------------------*/
void DX9Graphics::CreateDX9Renderer(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	graphics_renderer_ = graphics_renderer_->Create();
	graphics_renderer_->CreateRenderer(lpd3d_device);
}

/*=============================================================================
/*		End of File
=============================================================================*/