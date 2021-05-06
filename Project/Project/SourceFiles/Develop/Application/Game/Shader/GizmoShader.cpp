/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GizmoShader.cpp] ギズモシェーダクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ギズモシェーダクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "GizmoShader.h"
#include "../../DX9Graphics.h"
#include "../Shader.h"
#include "../Manager/ShaderManager.h"
#include "../Game.h"
#include "../GameObjects/GameObject/Camera.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
GizmoShader::GizmoShader(ShaderManager* manager)
	: Shader(manager)
	, d3dxhandle_technique_(nullptr)
{
	//デバイスの取得
	auto lpd3d_device = *manager->GetGame()->GetGraphics()->GetLPD3DDevice();

	//シェーダーの初期化
	this->Init(lpd3d_device);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
GizmoShader::~GizmoShader(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool GizmoShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
{

	//頂点フォーマットの作成
	{
		//頂点宣言格納インターフェイス作成
		D3DVERTEXELEMENT9 vertex_element[] =
		{
			//１つの頂点が持つ各属性、頂点座標、頂点カラー、UV、終了
			{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
			{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
			D3DDECL_END()
		};

		//頂点フォーマットの作成
		if (FAILED(lpd3d_device->CreateVertexDeclaration(vertex_element, &lpd3d_vertex_declaration_)))
		{
			assert(!"ギズモシェーダーの頂点フォーマットの作成に失敗しました。");
			return false;
		}
	}

	//シェーダーのコンパイル
	{
		bool is_init_shader = this->ShaderCompile(lpd3d_device);
		if (is_init_shader == false)
		{
			assert(!"ギズモシェーダーのコンパイルに失敗しました。");
			return false;
		}
	}

	// シェーダ内のテクニックのハンドル(ポインタ)取得
	d3dxhandle_technique_ = shader_->GetTechniqueByName("Tech");

	HRESULT hr = shader_->ValidateTechnique(d3dxhandle_technique_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "techniqueが間違っています", "ValidateTechnique", MB_OK);
		return false;
	}

	return  true;
}

/*-----------------------------------------------------------------------------
/* シェーダのコンパイル
-----------------------------------------------------------------------------*/
bool GizmoShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
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
/* 新しくシェーダのコンパイル
-----------------------------------------------------------------------------*/
bool GizmoShader::NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// シェーダの読み込み
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "SourceFiles/Develop/HLSL/GizmoShader.hlsl" //exeからの相対パス
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
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile GizmoShader", MB_OK);
		}
		else
		{
			// その他のエラー
			MessageBox(nullptr, "GizmoShader::NewShaderCompile():シェーダーファイルが読見み込めません", "Failed to compile GizmoShader", MB_OK);
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
/* コンパイル済みシェーダの読み込み
-----------------------------------------------------------------------------*/
bool GizmoShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// コンパイル済みシェーダの読み込み
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "Assets/CompiledShaderObjects/GizmoShader.cso" //exeからの相対パス
								 , NULL
								 , NULL
								 , D3DXSHADER_SKIPVALIDATION
								 , NULL
								 , &shader_
								 , &error);
	if (FAILED(hr))
	{
		if (error)
		{
			// コンパイルエラーあり
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile GizmoShader", MB_OK);
		}
		else
		{
			// その他のエラー
			MessageBox(nullptr, "GizmoShader::LoadCompiledShader():シェーダーファイルが読見み込めません", "Failed to compile GizmoShader", MB_OK);
		}
		SAFE_RELEASE_(error);
		return false;
	}
	//バッファの解放
	SAFE_RELEASE_(error);
	return true;
}

/*-----------------------------------------------------------------------------
/* シェーダのコンパイル
-----------------------------------------------------------------------------*/
void GizmoShader::ShaderSet(Camera* camera, RendererComponent* rendererComponent, Material* material)
{
	//使用しない値のワーニング回避
	UNREFERENCED_PARAMETER(material);

	//レンダラーから描画デバイスの取得
	auto lpd3d_device = *manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//頂点フォーマット情報の転送
	lpd3d_device->SetVertexDeclaration(lpd3d_vertex_declaration_);

	//シェーダー内の描画方法をプログラム側へ指定
	shader_->SetTechnique(d3dxhandle_technique_);

	//シェーダーにワールド行列を渡す。
	shader_->SetVector("g_Color", rendererComponent->GetVertexColor());

	//シェーダーにワールド行列を渡す。
	shader_->SetMatrix("g_MatWorld", rendererComponent->GetWorldMatrix());

	//シェーダーにビュー行列を渡す。
	shader_->SetMatrix("g_MatView", camera->GetViewMatrix());

	//シェーダーにプロジェクション行列を渡す。
	shader_->SetMatrix("g_MatProjection", camera->GetProjection3DMatrix());

	//定数バッファをシェーダに転送
	shader_->CommitChanges();
}

/*=============================================================================
/*		End of File
=============================================================================*/