/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.cpp] �X�v���C�g�V�F�[�_�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�V�F�[�_�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "SpriteShader.h"
#include "../../DX9Graphics.h"
#include "../GameObjects/GameObject/Camera.h"


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
bool SpriteShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
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

	//���_�錾�i�[�C���^�[�t�F�C�X�쐬
	D3DVERTEXELEMENT9 vertex_element[] =
	{
		//�P�̒��_�����e�����A���_���W�A���_�J���[�AUV�A�I��
		{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
		{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
		{ 0, 16, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
		D3DDECL_END()
	};

	//���_�t�H�[�}�b�g�̍쐬
	if (FAILED(lpd3d_device->CreateVertexDeclaration(vertex_element, &lpd3d_vertex_declaration_)))
	{
		return false;
	}

	//���_�o�b�t�@�̍쐬
	if (FAILED(lpd3d_device->CreateVertexBuffer((MAX_VERTEX_COUNT * sizeof(CUSTOM_VERTEX))	//���_�����̃o�b�t�@
											   , D3DUSAGE_WRITEONLY
											   , 0
											   , D3DPOOL_MANAGED
											   , &vertex_buffer_
											   , nullptr)))
	{
		return false;
	}

	// ���_��ҏW���邽�߂Ƀ��b�N
	CUSTOM_VERTEX* tmp_vertex;	//VRAM�̋^���A�h���X��RAM�ɍ쐬
	vertex_buffer_->Lock(0, 0, (void**)&tmp_vertex, 0);

	// RAM��̋^���A�h���X��ʂ��āAVRAM�̒��_���̍X�V
	tmp_vertex[0] = { D3DXVECTOR3(-100.0f,  100.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.f, 0.f) };
	tmp_vertex[1] = { D3DXVECTOR3( 100.0f,  100.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.f, 0.f) };
	tmp_vertex[2] = { D3DXVECTOR3(-100.0f, -100.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.f, 1.f) };
	tmp_vertex[3] = { D3DXVECTOR3( 100.0f, -100.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.f, 1.f) };

	// ���_�̃��b�N������
	vertex_buffer_->Unlock();



	view_matrix_ = camera_->GetViewMatrix();
	projection_matrix_ = camera_->GetProjectionMatrix();

	//const bool is_success = ShaderCompile(lpd3d_device);
	//if (is_success == false)
	//{
	//	return false;
	//}


	// �V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER error = NULL;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device,
							"SourceFiles/Develop/HLSL/SpriteShader.hlsl",
							0,
							0,
							0,
							0,
							&shader_,
							&error);


	// �G���[����
	if (FAILED(hr))
	{
		if (error) {
			// �R���p�C���G���[����
			MessageBox(NULL, (LPSTR)error->GetBufferPointer(), "D3DXCreateEffectFromFile", MB_OK);
		}
		else {
			// ���̑��̃G���[
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "D3DXCreateEffectFromFile", MB_OK);
		}
		return false;
	}

	// �e�N�j�b�N�̃n���h���擾
	d3dxhandle_technique_ = shader_->GetTechniqueByName("Tech");

	shader_->ValidateTechnique(d3dxhandle_technique_);
	// �G���[����
	if (FAILED(hr))
	{
		MessageBox(NULL, "technique���Ԉ���Ă��܂�", "ValidateTechnique", MB_OK);
		return false;
	}

	hr = D3DXCreateTextureFromFile(lpd3d_device, "Assets/Textures/texture_09.png", &texture_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "texture", "error", MB_OK);
	}

	// �P�ʍs��ɂ���
	D3DXMatrixIdentity(&world_matrix_);

	// �p�����[�^(�O���[�o���ϐ��̐ݒ�)
	d3dxhandle_matrix_	= shader_->GetParameterByName(nullptr, "g_MatWorld");
	d3dxhandle_view_	= shader_->GetParameterByName(nullptr, "g_MatView");
	d3dxhandle_proj_	= shader_->GetParameterByName(nullptr, "g_MatProjection");

	d3dxhandle_color_ = shader_->GetParameterByName(nullptr, "g_Color");
	d3dxhandle_texture_ = shader_->GetParameterByName(nullptr, "g_Texture");

	return  true;
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
	//LPD3DXBUFFER error_code_ = nullptr;
	//LPD3DXBUFFER code_ = nullptr;

	//HRESULT hr;	

	////���_�V�F�[�_���R���p�C��
	//hr = D3DXCompileShaderFromFile("SourceFiles/Develop/HLSL/SpriteShader.hlsl"	// �t�@�C����
	//								, nullptr									// �v���v���Z�b�T��`�ւ̃|�C���^ 		
	//								, nullptr									// ID3DXInclude�i#include�^�����߁j		
	//								, "VS"										// ���_�V�F�[�_�[�֐��� 		
	//								, "vs_3_0"									// ���_�V�F�[�_�[�̃o�[�W���� 		
	//								, 0											// �R���p�C���I�v�V����		
	//								, &code_									// �R���p�C���ς݂̃V�F�[�_�[�R�[�h�iOUT�j	
	//								, &error_code_								// �R���p�C���G���[��񂪊i�[�����iOUT�j	
	//								, &vertexshader_constant_table_);			// �V�F�[�_�[���̃R���X�^���g�e�[�u���iOUT�j

	//// �G���[����
	//if (FAILED(hr))
	//{
	//	if (error_code_) {
	//		// �R���p�C���G���[����
	//		MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
	//	}
	//	else {
	//		// ���̑��̃G���[
	//		MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
	//	}
	//	return false;
	//}

	//// ���_�V�F�[�_�[�I�u�W�F�N�g���쐬����
	//hr = lpd3d_device->CreateVertexShader((DWORD*)code_->GetBufferPointer(), &vertex_shader_);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "CreateVertexShader", MB_OK);
	//	return false;
	//}

	////�R���p�C���ς݃R�[�h����s�N�Z���V�F�[�_���R���p�C��	
	//hr = D3DXCompileShaderFromFile("SourceFiles/Develop/HLSL/SpriteShader.hlsl"	// �t�@�C����
	//						      , nullptr										// �v���v���Z�b�T��`�ւ̃|�C���^ 
	//						      , nullptr										// ID3DXInclude�i#include�^������
	//						      , "PS"										// ���_�V�F�[�_�[�֐��� 
	//						      , "ps_3_0"									// ���_�V�F�[�_�[�̃o�[�W���� 
	//						      , 0											// �R���p�C���I�v�V����
	//						      , &code_										// �R���p�C���ς݂̃V�F�[�_�[�R�[�h�iOUT�j
	//						      , &error_code_								// �R���p�C���G���[��񂪊i�[�����iOUT�j
	//						      , &pixelshader_constant_table_);				// �V�F�[�_�[���̃R���X�^���g�e�[�u���iOUT�j
	//						    
	//// �G���[����
	//if (FAILED(hr))
	//{
	//	if (error_code_) {
	//		// �R���p�C���G���[����
	//		MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
	//	}
	//	else {
	//		// ���̑��̃G���[
	//		MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "D3DXCompileShaderFromFile", MB_OK);
	//	}
	//	return false;
	//}

	//// �R���p�C���ς݃R�[�h����s�N�Z���V�F�[�_�[�I�u�W�F�N�g���쐬����
	//hr = lpd3d_device->CreatePixelShader((DWORD*)code_->GetBufferPointer(), &pixel_shader_);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, (LPSTR)error_code_->GetBufferPointer(), "CreatePixelShader", MB_OK);
	//	return false;
	//}

	//SAFE_RELEASE_(error_code_);
	//SAFE_RELEASE_(code_);

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

	//// �y�o�b�t�@�L��
	//lpd3d_device->SetRenderState(D3DRS_ZENABLE, TRUE);

	lpd3d_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//// ���C�g�L��
	//lpd3d_device->SetRenderState(D3DRS_LIGHTING, false);

	static float rot = 0.0f;
	rot += 0.016f;



	// 2D�`��p�ˉe�ϊ��s��
	projection_matrix_._11 = 2.0f / 1920.f;
	projection_matrix_._22 = -2.0f / 1080.f;

	//projection_matrix_._11 =  1.0f / 1920.f;
	//projection_matrix_._22 = -1.0f / 1080.f;

	//projection_matrix_._41 = -1.0f;
	//projection_matrix_._42 =  1.0f;

	D3DXMATRIX proj(
		2.f/ 1920.f, 0.0f, 0.0f, 0.0f,
		0.0f, -2 / 1080.f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
	);
	lpd3d_device->SetTransform(D3DTS_PROJECTION, &proj);



	lpd3d_device->SetTransform(D3DTS_PROJECTION, &proj);


	//D3DXMatrixRotationY(&world_matrix_, rot);

	lpd3d_device->SetStreamSource(0, vertex_buffer_, 0, sizeof(CUSTOM_VERTEX));

	// ���_�t�H�[�}�b�g�̐ݒ�
	lpd3d_device->SetVertexDeclaration(lpd3d_vertex_declaration_);

	// �e�N�j�b�N�̐ݒ�
	shader_->SetTechnique("Tech");


	// �V�F�[�_�N��
	shader_->Begin(0, 0);
	// �p�X�N��
	shader_->BeginPass(0);

	// �p�����[�^(�O���[�o���ϐ��̐ݒ�)
	shader_->SetMatrix(d3dxhandle_matrix_,	&world_matrix_);
	shader_->SetMatrix(d3dxhandle_view_,	&view_matrix_);
	shader_->SetMatrix(d3dxhandle_proj_,	&proj);

	shader_->SetTexture(d3dxhandle_texture_, texture_);

	// �F�ύX
	D3DXVECTOR4 color;
	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	color.w = 1.0f;

	shader_->SetVector(d3dxhandle_color_, &color);

	//�萔���V�F�[�_�[�ɓ`���� 
	shader_->CommitChanges();

	// �|���S���`��
	lpd3d_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//lpd3d_device->DrawIndexedPrimitive

	// �p�X�I��
	shader_->EndPass();
	// �V�F�[�_�I��
	shader_->End();

}

/*=============================================================================
/*		End of File
=============================================================================*/