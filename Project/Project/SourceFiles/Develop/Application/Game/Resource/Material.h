/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Material.h] マテリアルクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：マテリアルクラス
=============================================================================*/
#ifndef MATERIAL_H_
#define	MATERIAL_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* マテリアルクラス
-------------------------------------*/
class Material
{
public:
	Material(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath, const D3DMATERIAL9& d3dxMaterial);
	~Material(void);

private:
	bool Init(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath, const D3DMATERIAL9& d3dxMaterial);
	void Uninit(void);

public:
	bool LoadTexture(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath);
	bool IsGetLoadCompleted(void) { return is_load_completed_; }

	//マテリアルを自分自身へ変換
	void SetConvertMaterial(const D3DMATERIAL9& d3dxMaterial);

	// 拡散反射光
	void SetDiffuse(const D3DXVECTOR4& diffuseColor) { diffuse_ = diffuseColor; }
	void SetDiffuse(float  red, float green, float blue, float alpha) { diffuse_ = { red, green, blue, alpha }; }

	// 環境光
	void SetAmbient(const D3DXVECTOR4& ambientColor) { ambient_ = ambientColor; }
	void SetAmbient(float  red, float green, float blue, float alpha) { ambient_ = { red, green, blue, alpha }; }

	// 鏡面反射光
	void SetSpecular(const D3DXVECTOR4& specularColor) { specular_ = specularColor; }
	void SetSpecular(float red, float green, float blue, float alpha) { specular_ = { red, green, blue, alpha }; }

	// 自己発光色
	void SetEmissive(const D3DXVECTOR4& emissiveColor) { emissive_ = emissiveColor; }
	void SetEmissive(float red, float green, float blue, float alpha) { emissive_ = { red, green, blue, alpha }; }

	//ライトの強さ
	void SetLightPower(float lightPower) { light_power_ = lightPower; }

	LPDIRECT3DTEXTURE9* GetTexture(void) { return &lpd3d_texture_; }
	D3DMATERIAL9* GetD3DMaterial(void) { return &d3d_material_; }

	D3DXVECTOR4* GetDiffuse(void) { return &diffuse_; }
	D3DXVECTOR4* GetAmbient(void) { return &ambient_; }
	D3DXVECTOR4* GetSpecular(void) { return &specular_; }
	D3DXVECTOR4* GetEmissive(void) { return &emissive_; }
	float		 GetLightPower(void) { return light_power_; }

private:
	//ロードが完了しているか
	bool is_load_completed_;

	//テクスチャ本体
	LPDIRECT3DTEXTURE9	lpd3d_texture_;
	
	//マテリアル
	D3DMATERIAL9		d3d_material_;

	//
	// マテリアルの色
	//

	D3DXVECTOR4 diffuse_;
	D3DXVECTOR4 ambient_;
	D3DXVECTOR4 specular_;
	D3DXVECTOR4 emissive_;
	float		light_power_;
};


#endif //MATERIAL_H_
/*=============================================================================
/*		End of File
=============================================================================*/