/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Material.cpp] �}�e���A���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�}�e���A���N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "Material.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
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
/* �R���X�g���N�^
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
	//�e�N�X�`���̂̓ǂݍ���
	this->is_load_completed_ = true;

	//�}�e���A���̕ϊ�
	this->SetConvertMaterial(d3dMaterial);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Material::~Material(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Material::Init(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath, const D3DMATERIAL9& d3dMaterial)
{
	const bool is_load_success = this->LoadTexture(lpd3dDevice, filePath);
	if (is_load_success)
	{
		//�e�N�X�`���̂̓ǂݍ���
		this->is_load_completed_ = true;

		//�}�e���A���̕ϊ�
		this->SetConvertMaterial(d3dMaterial);
	}
	else
	{
		this->is_load_completed_ = false;
	}
	return is_load_success;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Material::Uninit(void)
{
	SAFE_RELEASE_(lpd3d_texture_);
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`���̓ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
bool Material::LoadTexture(const LPDIRECT3DDEVICE9& lpd3dDevice, const std::string& filePath)
{
	HRESULT hr;
	hr = D3DXCreateTextureFromFile(lpd3dDevice
								  , filePath.c_str()
								  , &lpd3d_texture_);

	if (FAILED(hr))
	{
		// �쐬���Ă����e�N�X�`���̃t�@�C���p�X���擾
		std::string filepath = filePath;

		// �t�@�C���p�X�̑O�������� "Assets/Meshs/" ������
		std::string front_keywords = "Assets/Meshs/";
		filepath.erase(0, front_keywords.length());

		// "Assets/Meshs/" �����������ƂŁA�t�@�C���p�X��"/"��擪����T���B
		auto pos = filepath.find("/");
		{
			if (pos == INFINITE)
			{
				assert(!"Material::LoadTexture():�}�e���A���̃e�N�X�`�����ǂݍ��߂܂���ł����B");
			}
		}

		//�t�@�C���p�X��"/"�����땔�����ꊇ�폜
		filepath.erase(pos);

		// �ǂݍ��񂾃��f���̃e�N�X�`�����i�[�����t�H���_��\��
		std::string err_msg = "Model�F" + filepath  + "\n";
		err_msg = err_msg + "Material::LoadTexture():�}�e���A���̃e�N�X�`�����ǂݍ��߂܂���ł����B";
		MessageBox(nullptr
				  , err_msg.c_str()
				  , "�x��"
				  , (MB_OK | MB_ICONWARNING));
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �}�e���A���̕ϊ�����
-----------------------------------------------------------------------------*/
void Material::SetConvertMaterial(const D3DMATERIAL9& d3dMaterial)
{
	//�}�e���A����ۑ�
	d3d_material_ = d3dMaterial;

	//�F���̃o�b�t�@
	D3DXVECTOR4 color_buffer;
	float		light_power;

	// �g�U���ˌ�
	color_buffer.x = d3dMaterial.Diffuse.r;
	color_buffer.y = d3dMaterial.Diffuse.g;
	color_buffer.z = d3dMaterial.Diffuse.b;
	color_buffer.w = d3dMaterial.Diffuse.a;
	this->SetDiffuse(color_buffer);

	// ����
	color_buffer.x = d3dMaterial.Ambient.r;
	color_buffer.y = d3dMaterial.Ambient.g;
	color_buffer.z = d3dMaterial.Ambient.b;
	color_buffer.w = d3dMaterial.Ambient.a;
	this->SetAmbient(color_buffer);

	// ���ʔ��ˌ� 
	color_buffer.x = d3dMaterial.Specular.r;
	color_buffer.y = d3dMaterial.Specular.g;
	color_buffer.z = d3dMaterial.Specular.b;
	color_buffer.w = d3dMaterial.Specular.a;
	this->SetSpecular(color_buffer);

	// ���Ȕ���
	color_buffer.x = d3dMaterial.Emissive.r;
	color_buffer.y = d3dMaterial.Emissive.g;
	color_buffer.z = d3dMaterial.Emissive.b;
	color_buffer.w = d3dMaterial.Emissive.a;
	this->SetEmissive(color_buffer);

	//���C�g�̋���
	light_power = d3dMaterial.Power;
	this->SetLightPower(light_power);
}

/*=============================================================================
/*		End of File
=============================================================================*/