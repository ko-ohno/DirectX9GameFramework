/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Light.h] ���C�g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���C�g�N���X
=============================================================================*/
#ifndef LIGHT_H_
#define	LIGHT_H_

/*--- �C���N���[�h�t�@�C�� ---*/


/*-------------------------------------
/* ���C�g�N���X
-------------------------------------*/
class Light
{
public:
	Light(class LightManager* manager);
	~Light(void);

private:
	bool Init(void);	//������
	void Uninit(void);	//�I����

public:
	//
	// ���C�g��ނ̎擾
	//

	inline enum class LightType GetLightType(void) { return light_type_; };

	//
	// ���C�g���g�̋���
	//

	inline void SetLightStrength(float lightStrength) { light_strength_ = lightStrength; }
	inline float GetLightStrength(void) { return light_strength_; }

	//
	// �g�U���ˌ�
	//

	inline void SetDiffuseColor(float red = 1.f, float green = 1.f, float blue = 1.f, float alpha = 1.f ) { diffuse_ = D3DXVECTOR4(red, green, blue, alpha); }
	inline void SetDiffuseColorR(float red)   { diffuse_.x = red; }
	inline void SetDiffuseColorG(float green) { diffuse_.y = green; }
	inline void SetDiffuseColorB(float blue)  { diffuse_.z = blue; }
	inline void SetDiffuseColorA(float alpha) { diffuse_.w = alpha; }

	inline D3DXVECTOR4* GetDiffuseColor(void) { return &diffuse_; }

	//
	// ����
	//

	inline void SetAmbientColor(float red, float green, float blue, float alpha) { ambient_ = D3DXVECTOR4(red, green, blue, alpha); }
	inline void SetAmbientColorR(float red)   { ambient_.x = red; }
	inline void SetAmbientColorG(float green) { ambient_.y = green; }
	inline void SetAmbientColorB(float blue)  { ambient_.z = blue; }
	inline void SetAmbientColorA(float alpha) { ambient_.w = alpha; }

	inline D3DXVECTOR4* GetAmbientColor(void) { return &ambient_; }

	//
	// ���ʔ��ˌ�
	//

	inline void SetSpecularColor(float red, float green, float blue, float alpha) { specular_ = D3DXVECTOR4(red, green, blue, alpha); }
	inline void SetSpecularColorR(float red)   { specular_.x = red; }
	inline void SetSpecularColorG(float green) { specular_.y = green; }
	inline void SetSpecularColorB(float blue)  { specular_.z = blue; }
	inline void SetSpecularColorA(float alpha) { specular_.w = alpha; }

	inline D3DXVECTOR4* GetSpecularColor(void) { return &specular_; }

	//
	// ���Ȕ����F
	//

	inline void SetEmissiveColor(float red, float green, float blue, float alpha) { emissive_ = D3DXVECTOR4(red, green, blue, alpha); }
	inline void SetEmissiveColorR(float red)   { emissive_.x = red; }
	inline void SetEmissiveColorG(float green) { emissive_.y = green; }
	inline void SetEmissiveColorB(float blue)  { emissive_.z = blue; }
	inline void SetEmissiveColorA(float alpha) { emissive_.w = alpha; }

	inline D3DXVECTOR4* GetEmissiveColor(void) { return &emissive_; }

protected:
	//���C�g�̊Ǘ���
	class LightManager* light_manager;

	//���C�g�̎��
	enum class LightType light_type_;

	// ���C�g�{��
	D3DLIGHT9 light_;

	// �}�e���A���J���[
	D3DMATERIAL9 d3d_material_;

	//���C�g���g�̋���
	float light_strength_;

	D3DXVECTOR4 diffuse_;	//�g�U���ˌ�
	D3DXVECTOR4 ambient_;	//����
	D3DXVECTOR4 specular_;	//���ʔ��ˌ�
	D3DXVECTOR4 emissive_;	//���Ȕ����F
};


#endif //LIGHT_H_
/*=============================================================================
/*		End of File
=============================================================================*/