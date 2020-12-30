/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsRenderer.cpp] DirectX9レンダラークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：DirectX9グラフィックスによるレンダラークラス
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
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
DX9GraphicsRenderer* DX9GraphicsRenderer::Create()
{
	return NEW DX9GraphicsRenderer();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool DX9GraphicsRenderer::Init(void)
{
	if (lpd3d_device_ == nullptr) { return false; }

	//レンダリングパイプラインの初期化
	lpd3d_device_->SetPixelShader(nullptr);
	lpd3d_device_->SetVertexShader(nullptr);

	//レンダーステートの初期化
	//lpd3d_device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //背面カリングにしない
	lpd3d_device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //背面カリングにする

	//ライティングを初期化
	lpd3d_device_->SetRenderState(D3DRS_LIGHTING, FALSE);

	//深度バッファの設定を初期化
	lpd3d_device_->SetRenderState(D3DRS_ZENABLE, FALSE);

	//アルファ合成を有効化
	lpd3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//アルファテストの使用を無効化
	lpd3d_device_->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//アルファ合成の設定の初期化
	lpd3d_device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	lpd3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpd3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//クライアント領域の非描画部分にピクセルを書き込まないように設定
	lpd3d_device_->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);

	//プリミティブの塗りつぶし方法を初期化
	lpd3d_device_->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	//フォグを適用するかの設定を無効にして初期化
	lpd3d_device_->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//色の合成の設定の初期化
	lpd3d_device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	//アルファ合成の設定の初期化
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//表示するオブジェクトに対して、もっとも近いテクスチャのフィルタリングを行う。
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//テクスチャのUV座標への繰り返し処理を行わない。
	lpd3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::Uninit(void)
{
	//すべての設定を戻す
	this->Init();
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
	/*--- 画面のクリア ---*/
	//D3DCOLOR_RGBA(...)は画面クリアの色
	if (FAILED(lpd3d_device_->Clear(0UL
								   , nullptr
								   , (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER)
								   , D3DCOLOR_RGBA(50, 50, 50, 255)
								   , 1.0f
								   , 0UL)))
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

/*=============================================================================
/*		End of File
=============================================================================*/