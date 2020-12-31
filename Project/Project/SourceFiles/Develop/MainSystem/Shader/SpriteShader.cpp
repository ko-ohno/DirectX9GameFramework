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

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SpriteShader::SpriteShader(void)
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

void SpriteShader::Init(void)
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

	vertex_array_[0] = { D3DXVECTOR3(-5.0f,  5.0f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) };
	vertex_array_[1] = { D3DXVECTOR3( 5.0f,  5.0f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) };
	vertex_array_[2] = { D3DXVECTOR3(-5.0f, -5.0f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) };
	vertex_array_[3] = { D3DXVECTOR3( 5.0f, -5.0f, 0.0f), D3DCOLOR_RGBA(255,  255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) } ;




}

void SpriteShader::Uninit(void)
{
}

bool SpriteShader::ShaderCompile(LPDIRECT3DDEVICE9 device)
{
	LPD3DXBUFFER error_code = NULL;
	LPD3DXBUFFER code;

	HRESULT hr;	

	//���_�V�F�[�_���R���p�C��
	hr = D3DXCompileShaderFromFile("basic.fx"				// �t�@�C����
									, nullptr				// �v���v���Z�b�T��`�ւ̃|�C���^ 		
									, nullptr				// ID3DXInclude�i#include�^�����߁j		
									, "VS"					// ���_�V�F�[�_�[�֐��� 		
									, "vs_3_0"				// ���_�V�F�[�_�[�̃o�[�W���� 		
									, 0						// �R���p�C���I�v�V����		
									, &code					// �R���p�C���ς݂̃V�F�[�_�[�R�[�h�iOUT�j	
									, &error_code			// �R���p�C���G���[��񂪊i�[�����iOUT�j	
									, &vs_constant_table_);	// �V�F�[�_�[���̃R���X�^���g�e�[�u���iOUT�j
// �G���[����
	if (FAILED(hr))
	{
		if (error_code) {
			// �R���p�C���G���[����
			MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// ���̑��̃G���[
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}

	// ���_�V�F�[�_�[�I�u�W�F�N�g���쐬����
	hr = device->CreateVertexShader((DWORD*)code->GetBufferPointer(), &vertex_shader_);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "CreateVertexShader", MB_OK);
		return false;
	}

	//�R���p�C���ς݃R�[�h����s�N�Z���V�F�[�_���R���p�C��	
	hr = D3DXCompileShaderFromFile("basic.fx"				// �t�@�C����
							      , nullptr					// �v���v���Z�b�T��`�ւ̃|�C���^ 
							      , nullptr					// ID3DXInclude�i#include�^������
							      , "PS"					// ���_�V�F�[�_�[�֐��� 
							      , "ps_3_0"				// ���_�V�F�[�_�[�̃o�[�W���� 
							      , 0						// �R���p�C���I�v�V����
							      , &code					// �R���p�C���ς݂̃V�F�[�_�[�R�[�h�iOUT�j
							      , &error_code				// �R���p�C���G���[��񂪊i�[�����iOUT�j
							      , &ps_constant_table_);	// �V�F�[�_�[���̃R���X�^���g�e�[�u���iOUT�j
							    
	// �G���[����
	if (FAILED(hr))
	{
		if (error_code) {
			// �R���p�C���G���[����
			MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		}
		else {
			// ���̑��̃G���[
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
		}
		return false;
	}

	// �R���p�C���ς݃R�[�h����s�N�Z���V�F�[�_�[�I�u�W�F�N�g���쐬����
	hr = device->CreatePixelShader((DWORD*)code->GetBufferPointer(), &pixel_shader_);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPSTR)error_code->GetBufferPointer(), "CreatePixelShader", MB_OK);
		return false;
	}

	return true;
}

void SpriteShader::Draw()
{
}


/*=============================================================================
/*		End of File
=============================================================================*/