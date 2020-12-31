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

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SpriteShader::SpriteShader(void)
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

void SpriteShader::Init(void)
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

	vertex_array_[0] = { D3DXVECTOR3(-5.0f,  5.0f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
	vertex_array_[1] = { D3DXVECTOR3( 5.0f,  5.0f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
	vertex_array_[2] = { D3DXVECTOR3(-5.0f, -5.0f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
	vertex_array_[3] = { D3DXVECTOR3( 5.0f, -5.0f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) } ;




}

void SpriteShader::Uninit(void)
{
}

bool SpriteShader::ShaderCompile(LPDIRECT3DDEVICE9 device)
{
	LPD3DXBUFFER error_code = NULL;
	LPD3DXBUFFER code;

	HRESULT hr;	

	//頂点シェーダをコンパイル
	hr = D3DXCompileShaderFromFile("basic.fx"				// ファイル名
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
	hr = device->CreateVertexShader((DWORD*)code->GetBufferPointer(), &vertex_shader_);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "CreateVertexShader", MB_OK);
		return false;
	}

	//コンパイル済みコードからピクセルシェーダをコンパイル	
	hr = D3DXCompileShaderFromFile("basic.fx"				// ファイル名
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
	hr = device->CreatePixelShader((DWORD*)code->GetBufferPointer(), &pixel_shader_);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "CreatePixelShader", MB_OK);
		return false;
	}

	return true;
}

void SpriteShader::Draw()
{
}


/*=============================================================================
/*		End of File
=============================================================================*/