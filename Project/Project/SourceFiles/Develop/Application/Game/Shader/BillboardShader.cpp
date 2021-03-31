/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardShader.cpp] ビルボードシェーダクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ビルボードシェーダクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "BillboardShader.h"
#include "../../DX9Graphics.h"
#include "../Shader.h"
#include "../Manager/ShaderManager.h"
#include "../Game.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../GameObjects/Component/RendererComponent.h"

#include "../Resource/Texture.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BillboardShader::BillboardShader(ShaderManager* manager)
    : Shader(manager)
    , d3dxhandle_technique_(nullptr)
    , d3dxhandle_texture_(nullptr)
{
    //デバイスの取得
    auto lpd3d_device = *manager->GetGame()->GetGraphics()->GetLPD3DDevice();

    //シェーダーの初期化
    this->Init(lpd3d_device);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
BillboardShader::~BillboardShader(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BillboardShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	//頂点フォーマットの作成
	{
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
			assert(!"ビルボードシェーダーの頂点フォーマットの作成に失敗しました。");
			return false;
		}
	}

	//シェーダーのコンパイル
	{
		bool is_init_shader = this->ShaderCompile(lpd3d_device);
		if (is_init_shader == false)
		{
			assert(!"ビルボードシェーダーのコンパイルに失敗しました。");
			return false;
		}
	}

	// シェーダ内のテクニックのハンドル(ポインタ)取得
	d3dxhandle_technique_ = shader_->GetTechniqueByName("Tech");

	HRESULT hr = shader_->ValidateTechnique(d3dxhandle_technique_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "techniqueが間違っています", "ValidateTechnique", MB_OK);
		return false;
	}

	// シェーダ内のテクスチャのハンドル(ポインタ)取得
 
	d3dxhandle_pos_			 = shader_->GetParameterByName(nullptr, "g_Pos");
	d3dxhandle_scale_		 = shader_->GetParameterByName(nullptr, "g_Scale");
	d3dxhandle_view_		 = shader_->GetParameterByName(nullptr, "g_MatView");
	d3dxhandle_view_inverse_ = shader_->GetParameterByName(nullptr, "g_MatInverseView");
	d3dxhandle_projection_	 = shader_->GetParameterByName(nullptr, "g_MatProjection");
	d3dxhandle_texture_		 = shader_->GetParameterByName(nullptr, "g_Texture");

	return  true;
}

/*-----------------------------------------------------------------------------
/* シェーダのコンパイル
-----------------------------------------------------------------------------*/
bool BillboardShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	//シェーダーの初期化
	bool is_init_shader = false;

#if defined(_DEBUG) || defined(DEBUG) 
	is_init_shader = this->NewShaderCompile(lpd3d_device);
#else
	is_init_shader = this->LoadCompiledShader(lpd3d_device);
#endif // !DEBUG

	if (is_init_shader == false)
	{
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BillboardShader::NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// シェーダの読み込み
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "SourceFiles/Develop/HLSL/BillboardShader.hlsl" //exeからの相対パス
								 , NULL
								 , NULL
								 , NULL
								 , NULL
								 , &shader_   // コンパイルしたシェーダー格納先
								 , &error);   // エラー内容の抽出	

	// エラー発生
	if (FAILED(hr))
	{
		if (error)
		{
			// コンパイルエラーあり
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile BillboardShader", MB_OK);
		}
		else
		{
			// その他のエラー
			MessageBox(nullptr, "BillboardShader::LoadCompiledShader():シェーダーファイルが読見み込めません", "Failed to compile BillboardShader", MB_OK);
		}
		//バッファの解放
		SAFE_RELEASE_(error);
		return false;
	}
	//バッファの解放
	SAFE_RELEASE_(error);
	return true;
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BillboardShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// コンパイル済みシェーダの読み込み
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "Assets/CompiledShaderObjects/BillboardShader.cso" //exeからの相対パス
								 , NULL
								 , NULL
								 , D3DXSHADER_SKIPVALIDATION
								 , NULL
								 , &shader_
								 , &error);
	// エラー発生
	if (FAILED(hr))
	{
		if (error)
		{
			// コンパイルエラーあり
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile BillboardShader", MB_OK);
		}
		else
		{
			// その他のエラー
			MessageBox(nullptr, "BillboardShader::LoadCompiledShader():シェーダーファイルが読見み込めません", "Failed to compile BillboardShader", MB_OK);
		}
		SAFE_RELEASE_(error);
		return false;
	}
	//バッファの解放
	SAFE_RELEASE_(error);
	return true;
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
void BillboardShader::ShaderSet(Camera* camera, RendererComponent* rendererComponent, Texture* texture)
{
	//レンダラーから描画デバイスの取得
	auto lpd3d_device = *manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//頂点フォーマット情報の転送
	lpd3d_device->SetVertexDeclaration(lpd3d_vertex_declaration_);

	//シェーダー内の描画方法をプログラム側へ指定
	shader_->SetTechnique(d3dxhandle_technique_);

	//
	// 平行移動・拡縮情報の作成
	//
	{
		D3DXMATRIX translation_matrix, scale_matrix;
		D3DXVECTOR3 position, scale;

		position = rendererComponent->GetPositon();
		scale = rendererComponent->GetScale();
		
		
		D3DXMatrixTranslation(&translation_matrix, position.x, position.y, position.z);
		D3DXMatrixScaling(&scale_matrix, scale.x, scale.y, scale.z);

		//シェーダーに平行移動行列を渡す。
		shader_->SetMatrix("g_MatTranslation", &translation_matrix);

		//シェーダーに拡縮行列を渡す。
		shader_->SetMatrix("g_MatScale", &scale_matrix);
	}

	//シェーダーに逆ビュー行列を渡す。
	shader_->SetMatrix("g_MatInverseView", camera->GetViewInverseMatrix());

	//シェーダーにビュー行列を渡す。
	shader_->SetMatrix("g_MatView", camera->GetViewMatrix());

	//シェーダーにプロジェクション行列を渡す。
	shader_->SetMatrix("g_MatProjection", camera->GetProjection3DMatrix());

	//シェーダーにテクスチャを転送
	shader_->SetTexture("g_Texture", texture->GetTexture());

	//定数バッファをシェーダに転送
	shader_->CommitChanges();
}
