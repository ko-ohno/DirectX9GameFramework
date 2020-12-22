/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsRenderer.cpp] DirectX9のデバイスによるレンダラーの動作を定義。
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：DirectX9のデバイスによるレンダラーの動作を定義したクラス。
=============================================================================*/

/*--- インクルードファイル ---*/
#include "DX9GraphicsRenderer.h"
#include "../../Generic/Math.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
DX9GraphicsRenderer::DX9GraphicsRenderer(void)
	: lpd3d_device_(nullptr)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
DX9GraphicsRenderer::~DX9GraphicsRenderer(void)
{
}

/*-----------------------------------------------------------------------------
/* グラフィックデバイスの取得とレンダラーの生成
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::CreateRenderer(const LPDIRECT3DDEVICE9& lpd3dDevice)
{
	this->lpd3d_device_ = lpd3dDevice;
	this->Init();
}

/*-----------------------------------------------------------------------------
/* レンダリング開始処理
-----------------------------------------------------------------------------*/
bool DX9GraphicsRenderer::RenderingBegin()
{

	//// ビューポートパラメータ(画面クリアする範囲)
	//D3DVIEWPORT9 view_port;
	////Vector2 screen_split_size = Vector2(500.f, 600.f);
	//Vector2 screen_split_size = Vector2((1980.f), (1080.f));
	//Vector2 offset = Vector2(0.f, 0.f);

	//// ビューポートの左上座標
	//view_port.X = offset.x_;
	//view_port.Y = offset.y_;

	//// ビューポートの幅
	//view_port.Width = screen_split_size.x_;
	//// ビューポートの高さ
	//view_port.Height = screen_split_size.y_;

	//// ビューポート深度設定
	//view_port.MinZ = 0.0f;
	//view_port.MaxZ = 1.0f;

	//// ビューポート設定
	//if (FAILED(lpd3d_device_->SetViewport(&view_port)))
	//{
	//	return false;
	//}


	/*--- 画面のクリア ---*/
	//D3DCOLOR_RGBA(...)は画面クリアの色
	if (FAILED(lpd3d_device_->Clear(
		(DWORD)0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(50, 50, 50, 255),
		1.0f,
		0)))
	{
		return false;
	}


	//Direct3Dによる描画の開始
	if (SUCCEEDED(lpd3d_device_->BeginScene()))
	{
		return true;
	}


	return false;
}

/*-----------------------------------------------------------------------------
/* レンダリング終了処理
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::RenderingEnd(void)
{
	if (lpd3d_device_ == nullptr) { return; }

	//Direct3Dによる描画の終了
	lpd3d_device_->EndScene();
	lpd3d_device_->Present(NULL, NULL, NULL, NULL);
}

/*-----------------------------------------------------------------------------
/* レンダリング終了処理
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::SetRenderStateDisable(void)
{
	lpd3d_device_->SetRenderState(D3DRS_ZENABLE, false);
	lpd3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	lpd3d_device_->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
}

/*-----------------------------------------------------------------------------
/* アルファブレンドの有効化
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::SetRenderAlphaBlendEnable(void)
{
	//lpd3d_device_->SetRenderState();
	//lpd3d_device_->SetRenderState();
	//lpd3d_device_->SetRenderState();
}

/*-----------------------------------------------------------------------------
/* アルファブレンドの無効化
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::SetRenderAlphaBlendDisable(void)
{
	//lpd3d_device_->SetRenderState();
	//lpd3d_device_->SetRenderState();
	//lpd3d_device_->SetRenderState();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::Init(void)
{
	if (lpd3d_device_ == nullptr) { return; }

	this->InitRenderer();
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::Uninit(void)
{

}

/*-----------------------------------------------------------------------------
/* レンダラーの初期化
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitRenderer()
{
	this->InitRenderTarget();
	this->InitRenderState();
	this->InitTextureStageState();
	this->InitSumplerState();
}

/*-----------------------------------------------------------------------------
/* レンダリングステートの初期化
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitRenderState()
{
	//レンダーステートパラメーターの設定
	lpd3d_device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //背面カリングにする

	//αブレンドを行う
	//SRC...今から描くもの。つまりポリゴンにテクスチャを貼ったもの
	//DEST...すでに描画されている画面のこと。
	//SRC_RGB * SRC_α + DEST_RGB * (1 - SRC_α);
	//lpd3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//lpd3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//lpd3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/*-----------------------------------------------------------------------------
/* レンダリングターゲットの初期化
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitRenderTarget()
{
	return;	//なんもしない
}

/*-----------------------------------------------------------------------------
/* テクスチャーステージステートの初期化
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitTextureStageState()
{
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

/*-----------------------------------------------------------------------------
/* サンプラーの初期化
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitSumplerState()
{
	//テクスチャのUV座標への繰り返し処理を行わない。
	lpd3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//表示するオブジェクトに対して、もっとも近いテクスチャのフィルタリングを行う。
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

/*=============================================================================
/*		End of File
=============================================================================*/