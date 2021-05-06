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
Material::Material(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath, const D3DMATERIAL9& d3dxMaterial)
	: is_load_completed_(false)
	, lpd3d_texture_(nullptr)
	, diffuse_(1.f, 1.f, 1.f, 1.f)
	, ambient_(1.f, 1.f, 1.f, 1.f)
	, specular_(1.f, 1.f, 1.f, 1.f)
	, emissive_(1.f, 1.f, 1.f, 1.f)
	, light_power_(1.f)
{
	this->Init(lpd3dDevice, filePath, d3dxMaterial);
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
bool Material::Init(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath, const D3DMATERIAL9& d3dxMaterial)
{
	const bool is_load_success = this->LoadTexture(lpd3dDevice, filePath);
	if (is_load_success)
	{
		//テクスチャのの読み込み
		this->is_load_completed_ = true;

		//マテリアルの変換
		this->SetConvertMaterial(d3dxMaterial);
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
void Material::SetConvertMaterial(const D3DMATERIAL9& d3dxMaterial)
{
	D3DXVECTOR4 color_buffer;
	float		light_power;

	// 拡散反射光
	color_buffer.x = d3dxMaterial.Diffuse.r;
	color_buffer.y = d3dxMaterial.Diffuse.g;
	color_buffer.z = d3dxMaterial.Diffuse.b;
	color_buffer.w = d3dxMaterial.Diffuse.a;
	this->SetDiffuse(color_buffer);

	// 環境光
	color_buffer.x = d3dxMaterial.Ambient.r;
	color_buffer.y = d3dxMaterial.Ambient.g;
	color_buffer.z = d3dxMaterial.Ambient.b;
	color_buffer.w = d3dxMaterial.Ambient.a;
	this->SetAmbient(color_buffer);

	// 鏡面反射光 
	color_buffer.x = d3dxMaterial.Specular.r;
	color_buffer.y = d3dxMaterial.Specular.g;
	color_buffer.z = d3dxMaterial.Specular.b;
	color_buffer.w = d3dxMaterial.Specular.a;
	this->SetSpecular(color_buffer);

	// 自己発光
	color_buffer.x = d3dxMaterial.Emissive.r;
	color_buffer.y = d3dxMaterial.Emissive.g;
	color_buffer.z = d3dxMaterial.Emissive.b;
	color_buffer.w = d3dxMaterial.Emissive.a;
	this->SetEmissive(color_buffer);

	//ライトの強さ
	light_power = d3dxMaterial.Power;
	this->SetLightPower(light_power);
}

/*=============================================================================
/*		End of File
=============================================================================*/