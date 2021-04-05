/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdMeshShader.cpp] 標準メッシュシェーダクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：標準メッシュシェーダクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "StdMeshShader.h"
#include "../../DX9Graphics.h"
#include "../Shader.h"
#include "../Manager/ShaderManager.h"
#include "../Game.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../Resource/Texture.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
StdMeshShader::StdMeshShader(ShaderManager* manager)
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
StdMeshShader::~StdMeshShader(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool StdMeshShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	//頂点フォーマットの作成
	{
		//頂点宣言格納インターフェイス作成
		D3DVERTEXELEMENT9 vertex_element[] =
		{
			//１つの頂点が持つ各属性、頂点座標、法線、頂点カラー、UV、終了
			{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0 },
			{ 0, 24, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
			{ 0, 28, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
			D3DDECL_END()
		};

		//頂点フォーマットの作成
		if (FAILED(lpd3d_device->CreateVertexDeclaration(vertex_element, &lpd3d_vertex_declaration_)))
		{
			assert(!"標準メッシュシェーダの頂点フォーマットの作成に失敗しました。");
			return false;
		}
	}

	//シェーダーのコンパイル
	{
		bool is_init_shader = this->ShaderCompile(lpd3d_device);
		if (is_init_shader == false)
		{
			assert(!"標準メッシュシェーダのコンパイルに失敗しました。");
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

	// シェーダ内のテクスチャのハンドル(ポインタ)取得


	d3dxhandle_pos_		= shader_->GetParameterByName(nullptr, "g_Pos");
	d3dxhandle_scale_	= shader_->GetParameterByName(nullptr, "g_Scale");
	d3dxhandle_view_	= shader_->GetParameterByName(nullptr, "g_MatView");

	d3dxhandle_texture_ = shader_->GetParameterByName(nullptr, "g_Texture");

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
bool StdMeshShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
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
/* 新規シェーダのコンパイル
-----------------------------------------------------------------------------*/
bool StdMeshShader::NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// シェーダの読み込み
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "SourceFiles/Develop/HLSL/StdMeshShader.hlsl" //exeからの相対パス
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
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile StdMeshShader", MB_OK);
		}
		else
		{
			// その他のエラー
			MessageBox(nullptr, "StdMeshShader::NewShaderCompile():シェーダーファイルが読見み込めません", "Failed to compile SpriteShader", MB_OK);
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
bool StdMeshShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// コンパイル済みシェーダの読み込み
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "Assets/CompiledShaderObjects/SpriteShader.cso" //exeからの相対パス
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
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile StdMeshShader", MB_OK);
		}
		else
		{
			// その他のエラー
			MessageBox(nullptr, "StdMeshShader::LoadCompiledShader():シェーダーファイルが読見み込めません", "Failed to compile StdMeshShader", MB_OK);
		}
		SAFE_RELEASE_(error);
		return false;
	}
	//バッファの解放
	SAFE_RELEASE_(error);
	return true;
}

/*-----------------------------------------------------------------------------
/* シェーダーへのセット
-----------------------------------------------------------------------------*/
void StdMeshShader::ShaderSet(Camera* camera, RendererComponent* rendererComponent, Texture* texture)
{
	//使用しない値のワーニング回避
	UNREFERENCED_PARAMETER(rendererComponent);

	//レンダラーから描画デバイスの取得
	auto lpd3d_device = *manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//頂点フォーマット情報の転送
	lpd3d_device->SetVertexDeclaration(lpd3d_vertex_declaration_);

	//シェーダー内の描画方法をプログラム側へ指定
	shader_->SetTechnique(d3dxhandle_technique_);


	// 光の設定情報
	D3DXVECTOR4		light_dir(1.0f, -1.0f, 0.0f, 0.0f);		// 光の方向

	FLOAT			light_strength(1.0f);

	D3DXVECTOR4		diffuse(1.0f, 1.0f, 1.0f, 1.0f);		// 平行光源の色
	D3DXVECTOR4		ambient(0.2f, 0.2f, 0.2f, 0.2f);		// 環境光
	D3DXVECTOR4		specular(0.2f, 0.2f, 0.2f, 0.2f);		// スペキュラ光
	D3DXVECTOR4		emissive(0.5f, 0.5f, 0.5f, 0.5f);		// 自己発光色

	//D3DXVECTOR4		cameraPos(0.0f, 0.0f, -10.0f, 0.0f);	// カメラの位置


	//シェーダーにライトの向きを渡す。
	shader_->SetVector("g_LightDir",	&light_dir);	// 光の方向

	shader_->SetFloat("g_LightStrength", light_strength); //ライトの強さ

	shader_->SetVector("g_Diffuse",		&diffuse);		// 拡散反射光
	shader_->SetVector("g_Ambient",		&ambient);		// 環境光
	shader_->SetVector("g_Specular",	&specular);		// 鏡面反射光光
	shader_->SetVector("g_Emissive",	&emissive);		// 自己発光

	//
	// ワールド座標の情報の作成
	//
	D3DXMATRIX world_matrix;			
	{
		//回転情報
		D3DXMATRIX rotation_matrix;
		D3DXMatrixIdentity(&rotation_matrix);

		//位置情報、拡縮情報
		D3DXVECTOR3 position = *rendererComponent->GetPosition();
		D3DXVECTOR3 scale = *rendererComponent->GetScale();


		//拡縮のベクトル値に、回転行列の値をくわえて計算

		//X軸
		world_matrix._11 = scale.x * rotation_matrix._11;
		world_matrix._12 = scale.x * rotation_matrix._12;
		world_matrix._13 = scale.x * rotation_matrix._13;

		//Y軸
		world_matrix._21 = scale.y * rotation_matrix._21;
		world_matrix._22 = scale.y * rotation_matrix._22;
		world_matrix._23 = scale.y * rotation_matrix._23;

		//Z軸
		world_matrix._31 = scale.z * rotation_matrix._31;
		world_matrix._32 = scale.z * rotation_matrix._32;
		world_matrix._33 = scale.z * rotation_matrix._33;

		//平行移動
		world_matrix._41 = position.x;
		world_matrix._42 = position.y;
		world_matrix._43 = position.z;

		//W成分
		world_matrix._14 = world_matrix._24 = world_matrix._34 = 0.0f;

		//1.0fに設定することでworld_matrix_._4*をベクトル化
		world_matrix._44 = 1.0f;
	}

	//シェーダーにワールド行列を渡す。
	shader_->SetMatrix("g_MatWorld", &world_matrix);

	//シェーダーにビュー行列を渡す。
	shader_->SetMatrix("g_MatView", camera->GetViewMatrix());

	//シェーダーにプロジェクション行列を渡す。
	shader_->SetMatrix("g_MatProjection", camera->GetProjection3DMatrix());

	if (texture == nullptr)
	{
		//nullのテクスチャとして転送
		shader_->SetTexture("g_Texture", nullptr);

		//
		shader_->SetBool("g_IsDrawingPrimitiveMesh", true);
	}
	else
	{
		//シェーダーにテクスチャを転送
		shader_->SetTexture("g_Texture", texture->GetTexture());

		shader_->SetBool("g_IsDrawingPrimitiveMesh", false);
	}

	//定数バッファをシェーダに転送
	shader_->CommitChanges();
}

/*=============================================================================
/*		End of File
=============================================================================*/