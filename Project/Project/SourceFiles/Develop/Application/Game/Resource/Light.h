/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Light.h] ライトクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ライトクラス
=============================================================================*/
#ifndef LIGHT_H_
#define	LIGHT_H_

/*--- インクルードファイル ---*/


/*-------------------------------------
/* ライトクラス
-------------------------------------*/
class Light
{
public:
	Light(class LightManager* manager);
	~Light(void);

private:
	bool Init(void);	//初期化
	void Uninit(void);	//終了化

public:
	//
	// ライト種類の取得
	//

	inline enum class LightType GetLightType(void) { return light_type_; };

	//
	// ライト自身の強さ
	//

	inline void SetLightStrength(float lightStrength) { light_strength_ = lightStrength; }
	inline float GetLightStrength(void) { return light_strength_; }

	//
	// 拡散反射光
	//

	inline void SetDiffuseColor(float red = 1.f, float green = 1.f, float blue = 1.f, float alpha = 1.f ) { diffuse_ = D3DXVECTOR4(red, green, blue, alpha); }
	inline void SetDiffuseColorR(float red)   { diffuse_.x = red; }
	inline void SetDiffuseColorG(float green) { diffuse_.y = green; }
	inline void SetDiffuseColorB(float blue)  { diffuse_.z = blue; }
	inline void SetDiffuseColorA(float alpha) { diffuse_.w = alpha; }

	inline D3DXVECTOR4* GetDiffuseColor(void) { return &diffuse_; }

	//
	// 環境光
	//

	inline void SetAmbientColor(float red, float green, float blue, float alpha) { ambient_ = D3DXVECTOR4(red, green, blue, alpha); }
	inline void SetAmbientColorR(float red)   { ambient_.x = red; }
	inline void SetAmbientColorG(float green) { ambient_.y = green; }
	inline void SetAmbientColorB(float blue)  { ambient_.z = blue; }
	inline void SetAmbientColorA(float alpha) { ambient_.w = alpha; }

	inline D3DXVECTOR4* GetAmbientColor(void) { return &ambient_; }

	//
	// 鏡面反射光
	//

	inline void SetSpecularColor(float red, float green, float blue, float alpha) { specular_ = D3DXVECTOR4(red, green, blue, alpha); }
	inline void SetSpecularColorR(float red)   { specular_.x = red; }
	inline void SetSpecularColorG(float green) { specular_.y = green; }
	inline void SetSpecularColorB(float blue)  { specular_.z = blue; }
	inline void SetSpecularColorA(float alpha) { specular_.w = alpha; }

	inline D3DXVECTOR4* GetSpecularColor(void) { return &specular_; }

	//
	// 自己発光色
	//

	inline void SetEmissiveColor(float red, float green, float blue, float alpha) { emissive_ = D3DXVECTOR4(red, green, blue, alpha); }
	inline void SetEmissiveColorR(float red)   { emissive_.x = red; }
	inline void SetEmissiveColorG(float green) { emissive_.y = green; }
	inline void SetEmissiveColorB(float blue)  { emissive_.z = blue; }
	inline void SetEmissiveColorA(float alpha) { emissive_.w = alpha; }

	inline D3DXVECTOR4* GetEmissiveColor(void) { return &emissive_; }

protected:
	//ライトの管理者
	class LightManager* light_manager;

	//ライトの種類
	enum class LightType light_type_;

	// ライト本体
	D3DLIGHT9 light_;

	// マテリアルカラー
	D3DMATERIAL9 d3d_material_;

	//ライト自身の強さ
	float light_strength_;

	D3DXVECTOR4 diffuse_;	//拡散反射光
	D3DXVECTOR4 ambient_;	//環境光
	D3DXVECTOR4 specular_;	//鏡面反射光
	D3DXVECTOR4 emissive_;	//自己発光色
};


#endif //LIGHT_H_
/*=============================================================================
/*		End of File
=============================================================================*/