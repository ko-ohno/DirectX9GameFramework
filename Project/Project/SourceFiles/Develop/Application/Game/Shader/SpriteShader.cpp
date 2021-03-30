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
#include "../Shader.h"
#include "../Manager/ShaderManager.h"
#include "../Game.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../Resource/Texture.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SpriteShader::SpriteShader(ShaderManager* manager)
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
SpriteShader::~SpriteShader(void)
{
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

	//���_�t�H�[�}�b�g�̍쐬
	{
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
			assert(!"�X�v���C�g�V�F�[�_�[�̒��_�t�H�[�}�b�g�̍쐬�Ɏ��s���܂����B");
			return false;
		}
	}

	//�V�F�[�_�[�̃R���p�C��
	{
		bool is_init_shader = this->ShaderCompile(lpd3d_device);
		if (is_init_shader == false)
		{
			assert(!"�X�v���C�g�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B");
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
	d3dxhandle_texture_ = shader_->GetParameterByName(nullptr, "g_Texture");

	return  true;
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�̃R���p�C��
-----------------------------------------------------------------------------*/
bool SpriteShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	//�V�F�[�_�[�̏�����
	bool is_init_shader;

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
/* �V�����V�F�[�_�̃R���p�C��
-----------------------------------------------------------------------------*/
bool SpriteShader::NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// �V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile( lpd3d_device
								 , "SourceFiles/Develop/HLSL/SpriteShader.hlsl" //exe����̑��΃p�X
								 , 0
								 , 0
								 , 0
								 , 0
								 , &shader_   // �R���p�C�������V�F�[�_�[�i�[��
								 , &error);   // �G���[���e�̒��o	

	// �G���[����
	if (FAILED(hr))
	{
		if (error)
		{
			// �R���p�C���G���[����
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile SpriteShader", MB_OK);
		}
		else
		{
			// ���̑��̃G���[
			MessageBox(nullptr, "�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "Failed to compile SpriteShader", MB_OK);
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
bool SpriteShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// �R���p�C���ς݃V�F�[�_�̓ǂݍ���
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "Assets/CompiledShaderObjects/SpriteShader.cso" //exe����̑��΃p�X
								 , 0
								 , 0
								 , 0
								 , 0
								 , &shader_
								 , 0);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�̃R���p�C��
-----------------------------------------------------------------------------*/
void SpriteShader::ShaderSet(Camera* camera, RendererComponent* rendererComponent, Texture* texture)
{
	//�g�p���Ȃ��l�̃��[�j���O���
	UNREFERENCED_PARAMETER(rendererComponent);
	
	//�����_���[����`��f�o�C�X�̎擾
	auto lpd3d_device = *manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//���_�t�H�[�}�b�g���̓]��
	lpd3d_device->SetVertexDeclaration(lpd3d_vertex_declaration_);

	//�V�F�[�_�[���̕`����@���v���O�������֎w��
	shader_->SetTechnique(d3dxhandle_technique_);

	//�V�F�[�_�[�Ƀv���W�F�N�V�����s���n���B
	shader_->SetMatrix("g_MatProjection", camera->GetProjection2DMatrix());

	if (texture == nullptr)
	{
		//null�̃e�N�X�`���Ƃ��ē]��
		shader_->SetTexture("g_Texture", nullptr);
	}
	else
	{
		//�V�F�[�_�[�Ƀe�N�X�`����]��
		shader_->SetTexture("g_Texture", texture->GetTexture());
	}

	//�萔�o�b�t�@���V�F�[�_�ɓ]��
	shader_->CommitChanges();
}

/*=============================================================================
/*		End of File
=============================================================================*/