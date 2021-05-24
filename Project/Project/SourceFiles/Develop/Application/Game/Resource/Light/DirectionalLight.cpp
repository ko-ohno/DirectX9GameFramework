/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DirectionalLight.cpp] 平行光源ライトクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：平行光源ライトクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "DirectionalLight.h"
#include "../../Manager/LightManager.h"
#include "../../Game.h"
#include "../../../DX9Graphics.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
DirectionalLight::DirectionalLight(LightManager* manager)
	: Light(manager)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
DirectionalLight::~DirectionalLight(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool DirectionalLight::Init(void)
{

	//ライトの初期化種類を指定
	{
		//ライトの種類を指定
		this->light_type_ = LightType::DirectionalLight;

		//ライトの向きを指定
		this->SetLightDirection(1.f, -1.f, 0.3f);

		//固定機能パイプラインのライトを初期化
		this->InitDirect3DLight();

	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool DirectionalLight::InitDirect3DLight(void)
{
	auto lpd3d_device = *light_manager->GetGame()->GetGraphics()->GetLPD3DDevice();

	// ライトの初期化
	{
		//固定機能パイプラインの初期化
		light_.Type = D3DLIGHT_DIRECTIONAL;

		//マテリアルの拡散反射光
		light_.Diffuse.r = 1.0f;
		light_.Diffuse.g = 1.0f;
		light_.Diffuse.b = 1.0f;
		light_.Diffuse.a = 1.0f;

		//マテリアルの環境光の設定
		light_.Ambient.r = 1.0f;
		light_.Ambient.g = 1.0f;
		light_.Ambient.b = 1.0f;
		light_.Ambient.a = 1.0f;

		//マテリアルの鏡面反射光の設定
		light_.Specular.r = 1.0f;
		light_.Specular.g = 1.0f;
		light_.Specular.b = 1.0f;
		light_.Specular.a = 1.0f;

		lpd3d_device->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//(単位ベクトルになるように正規化)
		D3DXVec3Normalize((D3DXVECTOR3*)&light_.Direction, &direction_);

		lpd3d_device->SetLight(0, &light_);  //(SetLightは、ライト番号は0～3番まで指定できる。)
		lpd3d_device->LightEnable(0, TRUE);  //(LightEnableでライト番号の0番を有効にする。)
	}

	//　マテリアルの初期化
	{
		//マテリアルの拡散反射光
		d3d_material_.Diffuse.r = 1.0f;
		d3d_material_.Diffuse.g = 1.0f;
		d3d_material_.Diffuse.b = 1.0f;
		d3d_material_.Diffuse.a = 1.0f;

		//マテリアルの環境光の設定
		d3d_material_.Ambient.r = 1.0f;
		d3d_material_.Ambient.g = 1.0f;
		d3d_material_.Ambient.b = 1.0f;
		d3d_material_.Ambient.a = 1.0f;

		//マテリアルの鏡面反射光の設定
		d3d_material_.Specular.r = 0.3f;
		d3d_material_.Specular.g = 0.3f;
		d3d_material_.Specular.b = 0.3f;
		d3d_material_.Specular.a = 1.0f;

		lpd3d_device->SetMaterial(&d3d_material_);
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void DirectionalLight::Uninit(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/