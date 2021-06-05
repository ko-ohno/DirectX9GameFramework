/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Material.cpp] マテリアルクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：マテリアルクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "Material.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Material::Material(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath, const D3DMATERIAL9& d3dMaterial)
	: is_load_completed_(false)
	, lpd3d_texture_(nullptr)
	, d3d_material_(D3DMATERIAL9())
	, diffuse_(1.f, 1.f, 1.f, 1.f)
	, ambient_(1.f, 1.f, 1.f, 1.f)
	, specular_(1.f, 1.f, 1.f, 1.f)
	, emissive_(1.f, 1.f, 1.f, 1.f)
	, light_power_(1.f)
{
	this->Init(lpd3dDevice, filePath, d3dMaterial);
}

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Material::Material(const D3DMATERIAL9& d3dMaterial)
	: is_load_completed_(false)
	, lpd3d_texture_(nullptr)
	, d3d_material_(D3DMATERIAL9())
	, diffuse_(1.f, 1.f, 1.f, 1.f)
	, ambient_(1.f, 1.f, 1.f, 1.f)
	, specular_(1.f, 1.f, 1.f, 1.f)
	, emissive_(1.f, 1.f, 1.f, 1.f)
	, light_power_(1.f)
{
	//テクスチャのの読み込み
	this->is_load_completed_ = true;

	//マテリアルの変換
	this->SetConvertMaterial(d3dMaterial);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Material::~Material(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Material::Init(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath, const D3DMATERIAL9& d3dMaterial)
{
	const bool is_load_success = this->LoadTexture(lpd3dDevice, filePath);
	if (is_load_success)
	{
		//テクスチャのの読み込み
		this->is_load_completed_ = true;

		//マテリアルの変換
		this->SetConvertMaterial(d3dMaterial);
	}
	else
	{
		this->is_load_completed_ = false;
	}
	return is_load_success;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Material::Uninit(void)
{
	SAFE_RELEASE_(lpd3d_texture_);
}

/*-----------------------------------------------------------------------------
/* テクスチャの読み込み処理
-----------------------------------------------------------------------------*/
bool Material::LoadTexture(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath)
{
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(lpd3dDevice
								  , filePath.c_str()
								  , &lpd3d_texture_);

	if (FAILED(hr))
	{
		// 作成していたテクスチャのファイルパスを取得
		std::string filepath = filePath;

		// ファイルパスの前方文字列 "Assets/Meshs/" を消す
		std::string front_keywords = "Assets/Meshs/";
		filepath.erase(0, front_keywords.length());

		// "Assets/Meshs/" を消したあとで、ファイルパスの"/"を先頭から探す。
		auto pos = filepath.find("/");
		{
			if (pos == INFINITE)
			{
				assert(!"Material::LoadTexture():マテリアルのテクスチャが読み込めませんでした。");
			}
		}

		//ファイルパスの"/"から後ろ部分を一括削除
		filepath.erase(pos);

		// 読み込んだモデルのテクスチャを格納したフォルダを表示
		std::string err_msg = "Model：" + filepath  + "\n";
		err_msg = err_msg + "Material::LoadTexture():マテリアルのテクスチャが読み込めませんでした。";
		MessageBox(nullptr
				  , err_msg.c_str()
				  , "警告"
				  , (MB_OK | MB_ICONWARNING));
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* マテリアルの変換処理
-----------------------------------------------------------------------------*/
void Material::SetConvertMaterial(const D3DMATERIAL9& d3dMaterial)
{
	//マテリアルを保存
	d3d_material_ = d3dMaterial;

	//色情報のバッファ
	D3DXVECTOR4 color_buffer;
	float		light_power;

	// 拡散反射光
	color_buffer.x = d3dMaterial.Diffuse.r;
	color_buffer.y = d3dMaterial.Diffuse.g;
	color_buffer.z = d3dMaterial.Diffuse.b;
	color_buffer.w = d3dMaterial.Diffuse.a;
	this->SetDiffuse(color_buffer);

	// 環境光
	color_buffer.x = d3dMaterial.Ambient.r;
	color_buffer.y = d3dMaterial.Ambient.g;
	color_buffer.z = d3dMaterial.Ambient.b;
	color_buffer.w = d3dMaterial.Ambient.a;
	this->SetAmbient(color_buffer);

	// 鏡面反射光 
	color_buffer.x = d3dMaterial.Specular.r;
	color_buffer.y = d3dMaterial.Specular.g;
	color_buffer.z = d3dMaterial.Specular.b;
	color_buffer.w = d3dMaterial.Specular.a;
	this->SetSpecular(color_buffer);

	// 自己発光
	color_buffer.x = d3dMaterial.Emissive.r;
	color_buffer.y = d3dMaterial.Emissive.g;
	color_buffer.z = d3dMaterial.Emissive.b;
	color_buffer.w = d3dMaterial.Emissive.a;
	this->SetEmissive(color_buffer);

	//ライトの強さ
	light_power = d3dMaterial.Power;
	this->SetLightPower(light_power);
}

/*=============================================================================
/*		End of File
=============================================================================*/