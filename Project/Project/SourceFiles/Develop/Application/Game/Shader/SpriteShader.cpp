/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.cpp] スプライトシェーダクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトシェーダクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "SpriteShader.h"
#include "../../DX9Graphics.h"
#include "../GameObjects/GameObject/Camera.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SpriteShader::SpriteShader(void)
	: vertexshader_constant_table_(nullptr)
	, pixelshader_constant_table_(nullptr)
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
bool SpriteShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
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

	//頂点宣言格納インターフェイス作成
	D3DVERTEXELEMENT9 vertex_element[] =
	{
		//１つの頂点が持つ各属性、頂点座標、頂点カラー、UV、終了
		{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
		{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
		{ 0, 16, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
		D3DDECL_END()
	};

	//頂点フォーマットの作成
	if (FAILED(lpd3d_device->CreateVertexDeclaration(vertex_element, &lpd3d_vertex_declaration_)))
	{
		return false;
	}

	//頂点バッファの作成
	if (FAILED(lpd3d_device->CreateVertexBuffer((MAX_VERTEX_COUNT * sizeof(CUSTOM_VERTEX))	//頂点数分のバッファ
											   , D3DUSAGE_WRITEONLY
											   , 0
											   , D3DPOOL_MANAGED
											   , &vertex_buffer_
											   , nullptr)))
	{
		return false;
	}

	// 頂点を編集するためにロック
	CUSTOM_VERTEX* tmp_vertex;	//VRAMの疑似アドレスをRAMに作成
	vertex_buffer_->Lock(0, 0, (void**)&tmp_vertex, 0);

	// RAM上の疑似アドレスを通じて、VRAMの頂点情報の更新
	tmp_vertex[0] = { D3DXVECTOR3(-100.0f,  100.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.f, 0.f) };
	tmp_vertex[1] = { D3DXVECTOR3( 100.0f,  100.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.f, 0.f) };
	tmp_vertex[2] = { D3DXVECTOR3(-100.0f, -100.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.f, 1.f) };
	tmp_vertex[3] = { D3DXVECTOR3( 100.0f, -100.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.f, 1.f) };

	// 頂点のロックを解除
	vertex_buffer_->Unlock();



	view_matrix_ = camera_->GetViewMatrix();
	projection_matrix_ = camera_->GetProjectionMatrix();

	//const bool is_success = ShaderCompile(lpd3d_device);
	//if (is_success == false)
	//{
	//	return false;
	//}


	// シェーダの読み込み
	LPD3DXBUFFER error = NULL;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device,
							"SourceFiles/Develop/HLSL/SpriteShader.hlsl",
							0,
							0,
							0,
							0,
							&shader_,
							&error);


	// エラー発生
	if (FAILED(hr))
	{
		if (error) {
			// コンパイルエラーあり
			MessageBox(NULL, (LPSTR)error->GetBufferPointer(), "D3DXCreateEffectFromFile", MB_OK);
		}
		else {
			// その他のエラー
			MessageBox(NULL, "シェーダーファイルが読見み込めません", "D3DXCreateEffectFromFile", MB_OK);
		}
		return false;
	}

	// テクニックのハンドル取得
	d3dxhandle_technique_ = shader_->GetTechniqueByName("Tech");

	shader_->ValidateTechnique(d3dxhandle_technique_);
	// エラー発生
	if (FAILED(hr))
	{
		MessageBox(NULL, "techniqueが間違っています", "ValidateTechnique", MB_OK);
		return false;
	}

	hr = D3DXCreateTextureFromFile(lpd3d_device, "Assets/Textures/texture_09.png", &texture_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "texture", "error", MB_OK);
	}

	// 単位行列にする
	D3DXMatrixIdentity(&world_matrix_);

	// パラメータ(グローバル変数の設定)
	d3dxhandle_matrix_	= shader_->GetParameterByName(nullptr, "g_MatWorld");
	d3dxhandle_view_	= shader_->GetParameterByName(nullptr, "g_MatView");
	d3dxhandle_proj_	= shader_->GetParameterByName(nullptr, "g_MatProjection");

	d3dxhandle_color_ = shader_->GetParameterByName(nullptr, "g_Color");
	d3dxhandle_texture_ = shader_->GetParameterByName(nullptr, "g_Texture");

	return  true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SpriteShader::Uninit(void)
{
	//D3DXMatrixIdentity(&world_matrix_);
	//D3DXMatrixIdentity(&projection_matrix_); 
	//D3DXMatrixIdentity(&view_matrix_);
	
	SAFE_RELEASE_(texture_);
	SAFE_RELEASE_(vertex_shader_);
	SAFE_RELEASE_(pixel_shader_);
	SAFE_RELEASE_(vertexshader_constant_table_);
	SAFE_RELEASE_(pixelshader_constant_table_);
}

/*-----------------------------------------------------------------------------
/* シェーダのコンパイル
-----------------------------------------------------------------------------*/
bool SpriteShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	//LPD3DXBUFFER error_code_ = nullptr;
	//LPD3DXBUFFER code_ = nullptr;

	//HRESULT hr;	

	////頂点シェーダをコンパイル
	//hr = D3DXCompileShaderFromFile("SourceFiles/Develop/HLSL/SpriteShader.hlsl"	// ファイル名
	//								, nullptr									// プリプロセッサ定義へのポインタ 		
	//								, nullptr									// ID3DXInclude（#include疑似命令）		
	//								, "VS"										// 頂点シェーダー関数名 		
	//								, "vs_3_0"									// 頂点シェーダーのバージョン 		
	//								, 0											// コンパイルオプション		
	//								, &code_									// コンパイル済みのシェーダーコード（OUT）	
	//								, &error_code_								// コンパイルエラー情報が格納される（OUT）	
	//								, &vertexshader_constant_table_);			// シェーダー内のコンスタントテーブル（OUT）

	//// エラー発生
	//if (FAILED(hr))
	//{
	//	if (error_code_) {
	//		// コンパイルエラーあり
	//		MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
	//	}
	//	else {
	//		// その他のエラー
	//		MessageBox(NULL, "シェーダーファイルが読見み込めません", "D3DXCompileShaderFromFile", MB_OK);
	//	}
	//	return false;
	//}

	//// 頂点シェーダーオブジェクトを作成する
	//hr = lpd3d_device->CreateVertexShader((DWORD*)code_->GetBufferPointer(), &vertex_shader_);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "CreateVertexShader", MB_OK);
	//	return false;
	//}

	////コンパイル済みコードからピクセルシェーダをコンパイル	
	//hr = D3DXCompileShaderFromFile("SourceFiles/Develop/HLSL/SpriteShader.hlsl"	// ファイル名
	//						      , nullptr										// プリプロセッサ定義へのポインタ 
	//						      , nullptr										// ID3DXInclude（#include疑似命令
	//						      , "PS"										// 頂点シェーダー関数名 
	//						      , "ps_3_0"									// 頂点シェーダーのバージョン 
	//						      , 0											// コンパイルオプション
	//						      , &code_										// コンパイル済みのシェーダーコード（OUT）
	//						      , &error_code_								// コンパイルエラー情報が格納される（OUT）
	//						      , &pixelshader_constant_table_);				// シェーダー内のコンスタントテーブル（OUT）
	//						    
	//// エラー発生
	//if (FAILED(hr))
	//{
	//	if (error_code_) {
	//		// コンパイルエラーあり
	//		MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
	//	}
	//	else {
	//		// その他のエラー
	//		MessageBox(NULL, "シェーダーファイルが読見み込めません", "D3DXCompileShaderFromFile", MB_OK);
	//	}
	//	return false;
	//}

	//// コンパイル済みコードからピクセルシェーダーオブジェクトを作成する
	//hr = lpd3d_device->CreatePixelShader((DWORD*)code_->GetBufferPointer(), &pixel_shader_);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "CreatePixelShader", MB_OK);
	//	return false;
	//}

	//SAFE_RELEASE_(error_code_);
	//SAFE_RELEASE_(code_);

	return true;
}

/*-----------------------------------------------------------------------------
/* コンパイル済みシェーダの読み込み
-----------------------------------------------------------------------------*/
bool SpriteShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	//D3DXCreateEffectFromFile();
	return false;
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void SpriteShader::Draw(const LPDIRECT3DDEVICE9& lpd3d_device)
{

	//// Ｚバッファ有効
	//lpd3d_device->SetRenderState(D3DRS_ZENABLE, TRUE);

	lpd3d_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//// ライト有効
	//lpd3d_device->SetRenderState(D3DRS_LIGHTING, false);

	static float rot = 0.0f;
	rot += 0.016f;



	// 2D描画用射影変換行列
	projection_matrix_._11 = 2.0f / 1920.f;
	projection_matrix_._22 = -2.0f / 1080.f;

	//projection_matrix_._11 =  1.0f / 1920.f;
	//projection_matrix_._22 = -1.0f / 1080.f;

	//projection_matrix_._41 = -1.0f;
	//projection_matrix_._42 =  1.0f;

	D3DXMATRIX proj(
		2.f/ 1920.f, 0.0f, 0.0f, 0.0f,
		0.0f, -2 / 1080.f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
	);
	lpd3d_device->SetTransform(D3DTS_PROJECTION, &proj);



	lpd3d_device->SetTransform(D3DTS_PROJECTION, &proj);


	//D3DXMatrixRotationY(&world_matrix_, rot);

	lpd3d_device->SetStreamSource(0, vertex_buffer_, 0, sizeof(CUSTOM_VERTEX));

	// 頂点フォーマットの設定
	lpd3d_device->SetVertexDeclaration(lpd3d_vertex_declaration_);

	// テクニックの設定
	shader_->SetTechnique("Tech");


	// シェーダ起動
	shader_->Begin(0, 0);
	// パス起動
	shader_->BeginPass(0);

	// パラメータ(グローバル変数の設定)
	shader_->SetMatrix(d3dxhandle_matrix_,	&world_matrix_);
	shader_->SetMatrix(d3dxhandle_view_,	&view_matrix_);
	shader_->SetMatrix(d3dxhandle_proj_,	&proj);

	shader_->SetTexture(d3dxhandle_texture_, texture_);

	// 色変更
	D3DXVECTOR4 color;
	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	color.w = 1.0f;

	shader_->SetVector(d3dxhandle_color_, &color);

	//定数をシェーダーに伝える 
	shader_->CommitChanges();

	// ポリゴン描画
	lpd3d_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//lpd3d_device->DrawIndexedPrimitive

	// パス終了
	shader_->EndPass();
	// シェーダ終了
	shader_->End();

}

/*=============================================================================
/*		End of File
=============================================================================*/