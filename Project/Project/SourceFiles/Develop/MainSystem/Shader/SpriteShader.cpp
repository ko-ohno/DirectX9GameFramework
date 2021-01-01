/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.cpp] スプライトシェーダクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトシェーダクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "SpriteShader.h"
#include "../DX9Graphics.h"
#include "../../GameObjects/Camera.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SpriteShader::SpriteShader(void)
	: vs_constant_table_(nullptr)
	, ps_constant_table_(nullptr)
	, vertex_shader_(nullptr)
	, pixel_shader_(nullptr)
	, texture_(nullptr)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SpriteShader::~SpriteShader(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
SpriteShader* SpriteShader::Create(void)
{
	return NEW SpriteShader();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SpriteShader::Init(class Camera* camera)
{
	/* screen quad coordinates
		-1,1	        1,1
		 v0             v1
		  +-------------+
		  |             |
		  |    screen   |
		  |             |
		  +-------------+
		 v2             v3
		-1,-1          1,-1
	*/

	//D3DXVECTOR2 u0;
	//D3DXVECTOR2 v0;
	//D3DXVECTOR2 u1;
	//D3DXVECTOR2 v1;

	//u0 = D3DXVECTOR2(0.f, 0.f);
	//v0 = D3DXVECTOR2(0.f, 0.f);
	//u1 = D3DXVECTOR2(0.f, 0.f);
	//v1 = D3DXVECTOR2(0.f, 0.f);



	vertex_array_[0] = { D3DXVECTOR3(-0.5f,  0.5f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(0.f, 0.f) };
	vertex_array_[1] = { D3DXVECTOR3( 0.5f,  0.5f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(1.f, 0.f) };
	vertex_array_[2] = { D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(0.f, 1.f) };
	vertex_array_[3] = { D3DXVECTOR3( 0.5f, -0.5f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(1.f, 1.f) };



	view_matrix_ = camera->GetViewMatrix();
	projection_matrix_ = camera->GetProjectionMatrix();

	const bool is_success = ShaderCompile(*DX9Graphics::GetLPD3DDevice());
	if (is_success == false)
	{
		return false;
	}
	return  is_success;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SpriteShader::Uninit(void)
{
	D3DXMatrixIdentity(&world_matrix_);
	D3DXMatrixIdentity(&projection_matrix_);
	D3DXMatrixIdentity(&view_matrix_);

	SAFE_RELEASE_(texture_);
	SAFE_RELEASE_(vertex_shader_);
	SAFE_RELEASE_(pixel_shader_);
	SAFE_RELEASE_(vs_constant_table_);
	SAFE_RELEASE_(vs_constant_table_);
}

/*-----------------------------------------------------------------------------
/* シェーダのコンパイル
-----------------------------------------------------------------------------*/
bool SpriteShader::ShaderCompile(LPDIRECT3DDEVICE9 lpd3d_device)
{
	LPD3DXBUFFER error_code = NULL;
	LPD3DXBUFFER code;

	HRESULT hr;	
	
	//頂点シェーダをコンパイル
	hr = D3DXCompileShaderFromFile("SourceFiles/Develop/HLSL/SpriteShader.hlsl"				// ファイル名
									, nullptr				// プリプロセッサ定義へのポインタ 		
									, nullptr				// ID3DXInclude（#include疑似命令）		
									, "VS"					// 頂点シェーダー関数名 		
									, "vs_3_0"				// 頂点シェーダーのバージョン 		
									, 0						// コンパイルオプション		
									, &code					// コンパイル済みのシェーダーコード（OUT）	
									, &error_code			// コンパイルエラー情報が格納される（OUT）	
									, &vs_constant_table_);	// シェーダー内のコンスタントテーブル（OUT）

	// エラー発生
	if (FAILED(hr))
	{
		if (error_code) {
			// コンパイルエラーあり
			MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// その他のエラー
			MessageBox(NULL, "シェーダーファイルが読見み込めません", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}

	// 頂点シェーダーオブジェクトを作成する
	hr = lpd3d_device->CreateVertexShader((DWORD*)code->GetBufferPointer(), &vertex_shader_);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "CreateVertexShader", MB_OK);
		return false;
	}

	//コンパイル済みコードからピクセルシェーダをコンパイル	
	hr = D3DXCompileShaderFromFile("SourceFiles/Develop/HLSL/SpriteShader.hlsl"				// ファイル名
							      , nullptr					// プリプロセッサ定義へのポインタ 
							      , nullptr					// ID3DXInclude（#include疑似命令
							      , "PS"					// 頂点シェーダー関数名 
							      , "ps_3_0"				// 頂点シェーダーのバージョン 
							      , 0						// コンパイルオプション
							      , &code					// コンパイル済みのシェーダーコード（OUT）
							      , &error_code				// コンパイルエラー情報が格納される（OUT）
							      , &ps_constant_table_);	// シェーダー内のコンスタントテーブル（OUT）
							    
	// エラー発生
	if (FAILED(hr))
	{
		if (error_code) {
			// コンパイルエラーあり
			MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// その他のエラー
			MessageBox(NULL, "シェーダーファイルが読見み込めません", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}

	// コンパイル済みコードからピクセルシェーダーオブジェクトを作成する
	hr = lpd3d_device->CreatePixelShader((DWORD*)code->GetBufferPointer(), &pixel_shader_);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "CreatePixelShader", MB_OK);
		return false;
	}

	SAFE_RELEASE_(error_code);
	SAFE_RELEASE_(code);

	return true;
}

/*-----------------------------------------------------------------------------
/* コンパイル済みシェーダの読み込み
-----------------------------------------------------------------------------*/
bool SpriteShader::LoadCompiledShader(LPDIRECT3DDEVICE9 lpd3d_device)
{
	return false;
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void SpriteShader::Draw(LPDIRECT3DDEVICE9 lpd3d_device)
{
	// Ｚバッファ有効
	lpd3d_device->SetRenderState(D3DRS_ZENABLE, TRUE);

	lpd3d_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ライト有効
	lpd3d_device->SetRenderState(D3DRS_LIGHTING, false);

	// 単位行列にする
	D3DXMatrixIdentity(&world_matrix_);

	// 頂点フォーマットの指定
	lpd3d_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	// 頂点シェーダーとピクセルシェーダーをセット
	lpd3d_device->SetVertexShader(vertex_shader_);
	lpd3d_device->SetPixelShader(pixel_shader_);

	HRESULT hr = D3DXCreateTextureFromFile(lpd3d_device, "Assets/Textures/tex1.bmp", &texture_);

	//頂点フォーマットの指定
	lpd3d_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//ピクセルシェーダにサンプラー変数を
	int index = ps_constant_table_->GetSamplerIndex("Sampler1");

	//UVの設定
	lpd3d_device->SetSamplerState(index, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);//WRAPだと繰り返しパターン：CLAMPだと繰り返しをしない。
	lpd3d_device->SetSamplerState(index, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//ミップマップの設定
	lpd3d_device->SetSamplerState(index, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	lpd3d_device->SetSamplerState(index, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//テクスチャオブジェクトをCPU側シェーダへセットする。
	lpd3d_device->SetTexture(index, texture_);

	// 定数をセット
	vs_constant_table_->SetMatrix(lpd3d_device, "g_world_matrix", &world_matrix_);
	vs_constant_table_->SetMatrix(lpd3d_device, "g_view_matrix", &view_matrix_);
	vs_constant_table_->SetMatrix(lpd3d_device, "g_projectionmatrix", &projection_matrix_);

	// ３角形を描画
	//lpd3d_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, g_Vertices, sizeof(CUSTOMVERTEX));
	lpd3d_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex_array_, sizeof(CUSTOM_VERTEX));

}

/*=============================================================================
/*		End of File
=============================================================================*/