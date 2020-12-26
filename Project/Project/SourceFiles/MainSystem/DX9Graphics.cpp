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
#include "../Generic/Math.h"


//静的変数宣言
LPDIRECT3DDEVICE9	  DX9Graphics::lpd3d_device_;		//Direct3Dデバイス
DX9GraphicsDevice*	  DX9Graphics::graphics_device_;	//デバイスクラス
DX9GraphicsRenderer*  DX9Graphics::graphics_renderer_;	//レンダラークラス

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
DX9Graphics::DX9Graphics(void)
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
/* fデストラクタファクトリメソッド
-----------------------------------------------------------------------------*/
DX9Graphics* DX9Graphics::Create()
{
	return NEW DX9Graphics();
}

/*-----------------------------------------------------------------------------
/* DirectX9グラフィックスの生成
-----------------------------------------------------------------------------*/
void DX9Graphics::CreateDX9Graphics(const HWND& windowHandle, const Vector2& screenSize)
{
	//デバイスとレンダラーの生成
	lpd3d_device_ = CreateDevice(windowHandle, screenSize);
	CreateRenderer(lpd3d_device_);
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
	graphics_device_ = nullptr;
	graphics_renderer_ = nullptr;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void DX9Graphics::Uninit(void)
{
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
LPDIRECT3DDEVICE9 DX9Graphics::CreateDevice(const HWND& windowHandle, const Vector2& screenSize)
{
	graphics_device_ = NEW DX9GraphicsDevice();
	return graphics_device_->CreateGraphicsDevice(windowHandle, screenSize);
}

/*-----------------------------------------------------------------------------
/* レンダラーの生成処理
-----------------------------------------------------------------------------*/
void DX9Graphics::CreateRenderer(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	graphics_renderer_ = NEW DX9GraphicsRenderer();
	graphics_renderer_->CreateRenderer(lpd3d_device);
}

/*=============================================================================
/*		End of File
=============================================================================*/