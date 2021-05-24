/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DirectionalLight.cpp] ���s�������C�g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���s�������C�g�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "DirectionalLight.h"
#include "../../Manager/LightManager.h"
#include "../../Game.h"
#include "../../../DX9Graphics.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
DirectionalLight::DirectionalLight(LightManager* manager)
	: Light(manager)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
DirectionalLight::~DirectionalLight(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool DirectionalLight::Init(void)
{

	//���C�g�̏�������ނ��w��
	{
		//���C�g�̎�ނ��w��
		this->light_type_ = LightType::DirectionalLight;

		//���C�g�̌������w��
		this->SetLightDirection(1.f, -1.f, 0.3f);

		//�Œ�@�\�p�C�v���C���̃��C�g��������
		this->InitDirect3DLight();

	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool DirectionalLight::InitDirect3DLight(void)
{
	auto lpd3d_device = *light_manager->GetGame()->GetGraphics()->GetLPD3DDevice();

	// ���C�g�̏�����
	{
		//�Œ�@�\�p�C�v���C���̏�����
		light_.Type = D3DLIGHT_DIRECTIONAL;

		//�}�e���A���̊g�U���ˌ�
		light_.Diffuse.r = 1.0f;
		light_.Diffuse.g = 1.0f;
		light_.Diffuse.b = 1.0f;
		light_.Diffuse.a = 1.0f;

		//�}�e���A���̊����̐ݒ�
		light_.Ambient.r = 1.0f;
		light_.Ambient.g = 1.0f;
		light_.Ambient.b = 1.0f;
		light_.Ambient.a = 1.0f;

		//�}�e���A���̋��ʔ��ˌ��̐ݒ�
		light_.Specular.r = 1.0f;
		light_.Specular.g = 1.0f;
		light_.Specular.b = 1.0f;
		light_.Specular.a = 1.0f;

		lpd3d_device->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//(�P�ʃx�N�g���ɂȂ�悤�ɐ��K��)
		D3DXVec3Normalize((D3DXVECTOR3*)&light_.Direction, &direction_);

		lpd3d_device->SetLight(0, &light_);  //(SetLight�́A���C�g�ԍ���0�`3�Ԃ܂Ŏw��ł���B)
		lpd3d_device->LightEnable(0, TRUE);  //(LightEnable�Ń��C�g�ԍ���0�Ԃ�L���ɂ���B)
	}

	//�@�}�e���A���̏�����
	{
		//�}�e���A���̊g�U���ˌ�
		d3d_material_.Diffuse.r = 1.0f;
		d3d_material_.Diffuse.g = 1.0f;
		d3d_material_.Diffuse.b = 1.0f;
		d3d_material_.Diffuse.a = 1.0f;

		//�}�e���A���̊����̐ݒ�
		d3d_material_.Ambient.r = 1.0f;
		d3d_material_.Ambient.g = 1.0f;
		d3d_material_.Ambient.b = 1.0f;
		d3d_material_.Ambient.a = 1.0f;

		//�}�e���A���̋��ʔ��ˌ��̐ݒ�
		d3d_material_.Specular.r = 0.3f;
		d3d_material_.Specular.g = 0.3f;
		d3d_material_.Specular.b = 0.3f;
		d3d_material_.Specular.a = 1.0f;

		lpd3d_device->SetMaterial(&d3d_material_);
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void DirectionalLight::Uninit(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/