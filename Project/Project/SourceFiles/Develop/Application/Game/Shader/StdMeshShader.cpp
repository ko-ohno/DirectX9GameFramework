/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdMeshShader.cpp] �W�����b�V���V�F�[�_�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�W�����b�V���V�F�[�_�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "StdMeshShader.h"
#include "../../DX9Graphics.h"
#include "../Shader.h"
#include "../Manager/ShaderManager.h"
#include "../Game.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../Resource/Texture.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
StdMeshShader::StdMeshShader(ShaderManager* manager)
	: Shader(manager)
	, d3dxhandle_technique_(nullptr) 
	, d3dxhandle_texture_(nullptr)
{
	//�f�o�C�X�̎擾
	auto lpd3d_device = *manager->GetGame()->GetGraphics()->GetLPD3DDevice();

	//�V�F�[�_�[�̏�����
	this->Init(lpd3d_device);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
StdMeshShader::~StdMeshShader(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool StdMeshShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	//���_�t�H�[�}�b�g�̍쐬
	{
		//���_�錾�i�[�C���^�[�t�F�C�X�쐬
		D3DVERTEXELEMENT9 vertex_element[] =
		{
			//�P�̒��_�����e�����A���_���W�A�@���A���_�J���[�AUV�A�I��
			{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0 },
			{ 0, 24, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
			{ 0, 28, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
			D3DDECL_END()
		};

		//���_�t�H�[�}�b�g�̍쐬
		if (FAILED(lpd3d_device->CreateVertexDeclaration(vertex_element, &lpd3d_vertex_declaration_)))
		{
			assert(!"�W�����b�V���V�F�[�_�̒��_�t�H�[�}�b�g�̍쐬�Ɏ��s���܂����B");
			return false;
		}
	}

	//�V�F�[�_�[�̃R���p�C��
	{
		bool is_init_shader = this->ShaderCompile(lpd3d_device);
		if (is_init_shader == false)
		{
			assert(!"�W�����b�V���V�F�[�_�̃R���p�C���Ɏ��s���܂����B");
			return false;
		}
	}

	// �V�F�[�_���̃e�N�j�b�N�̃n���h��(�|�C���^)�擾
	d3dxhandle_technique_ = shader_->GetTechniqueByName("Tech");

	HRESULT hr = shader_->ValidateTechnique(d3dxhandle_technique_);
	if (FAILED(hr))
	{
		MessageBox(NULL, "technique���Ԉ���Ă��܂�", "ValidateTechnique", MB_OK);
		return false;
	}

	// �V�F�[�_���̃e�N�X�`���̃n���h��(�|�C���^)�擾


	d3dxhandle_pos_		= shader_->GetParameterByName(nullptr, "g_Pos");
	d3dxhandle_scale_	= shader_->GetParameterByName(nullptr, "g_Scale");
	d3dxhandle_view_	= shader_->GetParameterByName(nullptr, "g_MatView");

	d3dxhandle_texture_ = shader_->GetParameterByName(nullptr, "g_Texture");

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
bool StdMeshShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	//�V�F�[�_�[�̏�����
	bool is_init_shader = false;

#if defined(_DEBUG) || defined(DEBUG) 
	is_init_shader = this->NewShaderCompile(lpd3d_device);
#else
	is_init_shader = this->LoadCompiledShader(lpd3d_device);
#endif // !DEBUG

	if (is_init_shader == false)
	{
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �V�K�V�F�[�_�̃R���p�C��
-----------------------------------------------------------------------------*/
bool StdMeshShader::NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// �V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "SourceFiles/Develop/HLSL/StdMeshShader.hlsl" //exe����̑��΃p�X
								 , NULL
								 , NULL
								 , NULL
								 , NULL
								 , &shader_   // �R���p�C�������V�F�[�_�[�i�[��
								 , &error);   // �G���[���e�̒��o	

	// �G���[����
	if (FAILED(hr))
	{
		if (error)
		{
			// �R���p�C���G���[����
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile StdMeshShader", MB_OK);
		}
		else
		{
			// ���̑��̃G���[
			MessageBox(nullptr, "StdMeshShader::NewShaderCompile():�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "Failed to compile SpriteShader", MB_OK);
		}
		//�o�b�t�@�̉��
		SAFE_RELEASE_(error);
		return false;
	}
	//�o�b�t�@�̉��
	SAFE_RELEASE_(error);
	return true;
}

/*-----------------------------------------------------------------------------
/* �R���p�C���ς݃V�F�[�_�̓ǂݍ���
-----------------------------------------------------------------------------*/
bool StdMeshShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// �R���p�C���ς݃V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "Assets/CompiledShaderObjects/SpriteShader.cso" //exe����̑��΃p�X
								 , NULL
								 , NULL
								 , D3DXSHADER_SKIPVALIDATION
								 , NULL
								 , &shader_
								 , &error);
	if (FAILED(hr))
	{
		if (error)
		{
			// �R���p�C���G���[����
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile StdMeshShader", MB_OK);
		}
		else
		{
			// ���̑��̃G���[
			MessageBox(nullptr, "StdMeshShader::LoadCompiledShader():�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "Failed to compile StdMeshShader", MB_OK);
		}
		SAFE_RELEASE_(error);
		return false;
	}
	//�o�b�t�@�̉��
	SAFE_RELEASE_(error);
	return true;
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�[�ւ̃Z�b�g
-----------------------------------------------------------------------------*/
void StdMeshShader::ShaderSet(Camera* camera, RendererComponent* rendererComponent, Texture* texture)
{
	//�g�p���Ȃ��l�̃��[�j���O���
	UNREFERENCED_PARAMETER(rendererComponent);

	//�����_���[����`��f�o�C�X�̎擾
	auto lpd3d_device = *manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//���_�t�H�[�}�b�g���̓]��
	lpd3d_device->SetVertexDeclaration(lpd3d_vertex_declaration_);

	//�V�F�[�_�[���̕`����@���v���O�������֎w��
	shader_->SetTechnique(d3dxhandle_technique_);


	// ���̐ݒ���
	D3DXVECTOR4		light_dir(1.0f, -1.0f, 0.0f, 0.0f);		// ���̕���

	FLOAT			light_strength(1.0f);

	D3DXVECTOR4		diffuse(1.0f, 1.0f, 1.0f, 1.0f);		// ���s�����̐F
	D3DXVECTOR4		ambient(0.2f, 0.2f, 0.2f, 0.2f);		// ����
	D3DXVECTOR4		specular(0.2f, 0.2f, 0.2f, 0.2f);		// �X�y�L������
	D3DXVECTOR4		emissive(0.5f, 0.5f, 0.5f, 0.5f);		// ���Ȕ����F

	//D3DXVECTOR4		cameraPos(0.0f, 0.0f, -10.0f, 0.0f);	// �J�����̈ʒu


	//�V�F�[�_�[�Ƀ��C�g�̌�����n���B
	shader_->SetVector("g_LightDir",	&light_dir);	// ���̕���

	shader_->SetFloat("g_LightStrength", light_strength); //���C�g�̋���

	shader_->SetVector("g_Diffuse",		&diffuse);		// �g�U���ˌ�
	shader_->SetVector("g_Ambient",		&ambient);		// ����
	shader_->SetVector("g_Specular",	&specular);		// ���ʔ��ˌ���
	shader_->SetVector("g_Emissive",	&emissive);		// ���Ȕ���

	//
	// ���[���h���W�̏��̍쐬
	//
	D3DXMATRIX world_matrix;			
	{
		//��]���
		D3DXMATRIX rotation_matrix;
		D3DXMatrixIdentity(&rotation_matrix);

		//�ʒu���A�g�k���
		D3DXVECTOR3 position = *rendererComponent->GetPosition();
		D3DXVECTOR3 scale = *rendererComponent->GetScale();


		//�g�k�̃x�N�g���l�ɁA��]�s��̒l�����킦�Čv�Z

		//X��
		world_matrix._11 = scale.x * rotation_matrix._11;
		world_matrix._12 = scale.x * rotation_matrix._12;
		world_matrix._13 = scale.x * rotation_matrix._13;

		//Y��
		world_matrix._21 = scale.y * rotation_matrix._21;
		world_matrix._22 = scale.y * rotation_matrix._22;
		world_matrix._23 = scale.y * rotation_matrix._23;

		//Z��
		world_matrix._31 = scale.z * rotation_matrix._31;
		world_matrix._32 = scale.z * rotation_matrix._32;
		world_matrix._33 = scale.z * rotation_matrix._33;

		//���s�ړ�
		world_matrix._41 = position.x;
		world_matrix._42 = position.y;
		world_matrix._43 = position.z;

		//W����
		world_matrix._14 = world_matrix._24 = world_matrix._34 = 0.0f;

		//1.0f�ɐݒ肷�邱�Ƃ�world_matrix_._4*���x�N�g����
		world_matrix._44 = 1.0f;
	}

	//�V�F�[�_�[�Ƀ��[���h�s���n���B
	shader_->SetMatrix("g_MatWorld", &world_matrix);

	//�V�F�[�_�[�Ƀr���[�s���n���B
	shader_->SetMatrix("g_MatView", camera->GetViewMatrix());

	//�V�F�[�_�[�Ƀv���W�F�N�V�����s���n���B
	shader_->SetMatrix("g_MatProjection", camera->GetProjection3DMatrix());

	if (texture == nullptr)
	{
		//null�̃e�N�X�`���Ƃ��ē]��
		shader_->SetTexture("g_Texture", nullptr);

		//
		shader_->SetBool("g_IsDrawingPrimitiveMesh", true);
	}
	else
	{
		//�V�F�[�_�[�Ƀe�N�X�`����]��
		shader_->SetTexture("g_Texture", texture->GetTexture());

		shader_->SetBool("g_IsDrawingPrimitiveMesh", false);
	}

	//�萔�o�b�t�@���V�F�[�_�ɓ]��
	shader_->CommitChanges();
}

/*=============================================================================
/*		End of File
=============================================================================*/