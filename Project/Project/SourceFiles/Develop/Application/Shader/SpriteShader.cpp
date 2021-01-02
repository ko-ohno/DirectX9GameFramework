/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.cpp] �X�v���C�g�V�F�[�_�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�V�F�[�_�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "SpriteShader.h"
#include "../DX9Graphics.h"
#include "../../Application/GameObjects/Camera.h"


CUSTOM_VERTEX vertex_array_[] = {
	{ D3DXVECTOR3(-0.5f,  0.5f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(0.f, 0.f) },
	{ D3DXVECTOR3(0.5f,  0.5f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(1.f, 0.f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(0.f, 1.f) },
	{ D3DXVECTOR3(0.5f, -0.5f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(1.f, 1.f) }
};



/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SpriteShader::SpriteShader(void)
	: vertexshader_constant_table_(nullptr)
	, pixelshader_constant_table_(nullptr)
	, vertex_shader_(nullptr)
	, pixel_shader_(nullptr)
	, texture_(nullptr)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SpriteShader::~SpriteShader(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
SpriteShader* SpriteShader::Create(void)
{
	return NEW SpriteShader();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SpriteShader::Init(class Camera* camera)
{
	/* screen quad coordinates
		-1,1	        1,1
		 v0             v1
		  +-------------+
		  |             |
		  |    screen   |
		  |             |
		  +-------------+
		 v2             v3
		-1,-1          1,-1
	*/

	//D3DXVECTOR2 u0;
	//D3DXVECTOR2 v0;
	//D3DXVECTOR2 u1;
	//D3DXVECTOR2 v1;

	//u0 = D3DXVECTOR2(0.f, 0.f);
	//v0 = D3DXVECTOR2(0.f, 0.f);
	//u1 = D3DXVECTOR2(0.f, 0.f);
	//v1 = D3DXVECTOR2(0.f, 0.f);



	//// ���_�A�J���[�A�I��
	//D3DVERTEXELEMENT9	element[4] = {
	//	{}
	//}



	view_matrix_ = camera->GetViewMatrix();
	projection_matrix_ = camera->GetProjectionMatrix();

	const bool is_success = ShaderCompile(*DX9Graphics::GetLPD3DDevice());
	if (is_success == false)
	{
		return false;
	}
	return  is_success;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SpriteShader::Uninit(void)
{
	//D3DXMatrixIdentity(&world_matrix_);
	//D3DXMatrixIdentity(&projection_matrix_);
	//D3DXMatrixIdentity(&view_matrix_);
	
	SAFE_RELEASE_(texture_);
	SAFE_RELEASE_(vertex_shader_);
	SAFE_RELEASE_(pixel_shader_);
	SAFE_RELEASE_(vertexshader_constant_table_);
	SAFE_RELEASE_(pixelshader_constant_table_);
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�̃R���p�C��
-----------------------------------------------------------------------------*/
bool SpriteShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	LPD3DXBUFFER error_code_ = nullptr;
	LPD3DXBUFFER code_ = nullptr;

	HRESULT hr;	
	
	//���_�V�F�[�_���R���p�C��
	hr = D3DXCompileShaderFromFile("SourceFiles/Develop/HLSL/SpriteShader.hlsl"				// �t�@�C����
									, nullptr				// �v���v���Z�b�T��`�ւ̃|�C���^ 		
									, nullptr				// ID3DXInclude�i#include�^�����߁j		
									, "VS"					// ���_�V�F�[�_�[�֐��� 		
									, "vs_3_0"				// ���_�V�F�[�_�[�̃o�[�W���� 		
									, 0						// �R���p�C���I�v�V����		
									, &code_					// �R���p�C���ς݂̃V�F�[�_�[�R�[�h�iOUT�j	
									, &error_code_			// �R���p�C���G���[��񂪊i�[�����iOUT�j	
									, &vertexshader_constant_table_);	// �V�F�[�_�[���̃R���X�^���g�e�[�u���iOUT�j


	// �G���[����
	if (FAILED(hr))
	{
		if (error_code_) {
			// �R���p�C���G���[����
			MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// ���̑��̃G���[
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}

	// ���_�V�F�[�_�[�I�u�W�F�N�g���쐬����
	hr = lpd3d_device->CreateVertexShader((DWORD*)code_->GetBufferPointer(), &vertex_shader_);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "CreateVertexShader", MB_OK);
		return false;
	}

	//�R���p�C���ς݃R�[�h����s�N�Z���V�F�[�_���R���p�C��	
	hr = D3DXCompileShaderFromFile("SourceFiles/Develop/HLSL/SpriteShader.hlsl"				// �t�@�C����
							      , nullptr					// �v���v���Z�b�T��`�ւ̃|�C���^ 
							      , nullptr					// ID3DXInclude�i#include�^������
							      , "PS"					// ���_�V�F�[�_�[�֐��� 
							      , "ps_3_0"				// ���_�V�F�[�_�[�̃o�[�W���� 
							      , 0						// �R���p�C���I�v�V����
							      , &code_					// �R���p�C���ς݂̃V�F�[�_�[�R�[�h�iOUT�j
							      , &error_code_				// �R���p�C���G���[��񂪊i�[�����iOUT�j
							      , &pixelshader_constant_table_);	// �V�F�[�_�[���̃R���X�^���g�e�[�u���iOUT�j
							    
	// �G���[����
	if (FAILED(hr))
	{
		if (error_code_) {
			// �R���p�C���G���[����
			MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// ���̑��̃G���[
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}

	// �R���p�C���ς݃R�[�h����s�N�Z���V�F�[�_�[�I�u�W�F�N�g���쐬����
	hr = lpd3d_device->CreatePixelShader((DWORD*)code_->GetBufferPointer(), &pixel_shader_);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "CreatePixelShader", MB_OK);
		return false;
	}

	SAFE_RELEASE_(error_code_);
	SAFE_RELEASE_(code_);

	return true;
}

/*-----------------------------------------------------------------------------
/* �R���p�C���ς݃V�F�[�_�̓ǂݍ���
-----------------------------------------------------------------------------*/
bool SpriteShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	//D3DXCreateEffectFromFile();
	return false;
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void SpriteShader::Draw(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// �y�o�b�t�@�L��
	lpd3d_device->SetRenderState(D3DRS_ZENABLE, TRUE);

	lpd3d_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ���C�g�L��
	lpd3d_device->SetRenderState(D3DRS_LIGHTING, false);

	// �P�ʍs��ɂ���
	D3DXMatrixIdentity(&world_matrix_);

	// ���_�t�H�[�}�b�g�̎w��
	lpd3d_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	// ���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[���Z�b�g
	lpd3d_device->SetVertexShader(vertex_shader_);
	lpd3d_device->SetPixelShader(pixel_shader_);

	HRESULT hr = D3DXCreateTextureFromFile(lpd3d_device, "Assets/Textures/tex1.bmp", &texture_);

	//���_�t�H�[�}�b�g�̎w��
	lpd3d_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//�s�N�Z���V�F�[�_�ɃT���v���[�ϐ���
	int index = pixelshader_constant_table_->GetSamplerIndex("Sampler1");

	//UV�̐ݒ�
	lpd3d_device->SetSamplerState(index, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);//WRAP���ƌJ��Ԃ��p�^�[���FCLAMP���ƌJ��Ԃ������Ȃ��B
	lpd3d_device->SetSamplerState(index, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//�~�b�v�}�b�v�̐ݒ�
	lpd3d_device->SetSamplerState(index, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	lpd3d_device->SetSamplerState(index, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//�e�N�X�`���I�u�W�F�N�g��CPU���V�F�[�_�փZ�b�g����B
	lpd3d_device->SetTexture(index, texture_);

	// �萔���Z�b�g
	vertexshader_constant_table_->SetMatrix(lpd3d_device, "g_MatWorld"	   , &world_matrix_);
	vertexshader_constant_table_->SetMatrix(lpd3d_device, "g_MatView"	   , &view_matrix_);
	vertexshader_constant_table_->SetMatrix(lpd3d_device, "g_MatProjection", &projection_matrix_);

	// �R�p�`��`��
	//lpd3d_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, g_Vertices, sizeof(CUSTOMVERTEX));
	lpd3d_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex_array_, sizeof(CUSTOM_VERTEX));

}

/*=============================================================================
/*		End of File
=============================================================================*/