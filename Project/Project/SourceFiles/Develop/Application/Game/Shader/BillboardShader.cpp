/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardShader.cpp] �r���{�[�h�V�F�[�_�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�r���{�[�h�V�F�[�_�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "BillboardShader.h"
#include "../../DX9Graphics.h"
#include "../Shader.h"
#include "../Manager/ShaderManager.h"
#include "../Game.h"
#include "../GameObjects/GameObject/Camera.h"
#include "../GameObjects/Component/RendererComponent.h"

#include "../Resource/Texture.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BillboardShader::BillboardShader(ShaderManager* manager)
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
BillboardShader::~BillboardShader(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool BillboardShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
{
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
			assert(!"�r���{�[�h�V�F�[�_�[�̒��_�t�H�[�}�b�g�̍쐬�Ɏ��s���܂����B");
			return false;
		}
	}

	//�V�F�[�_�[�̃R���p�C��
	{
		bool is_init_shader = this->ShaderCompile(lpd3d_device);
		if (is_init_shader == false)
		{
			assert(!"�r���{�[�h�V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B");
			return false;
		}
	}

	// �V�F�[�_���̃e�N�j�b�N�̃n���h��(�|�C���^)�擾
	d3dxhandle_technique_ = shader_->GetTechniqueByName("Tech");

	HRESULT hr = shader_->ValidateTechnique(d3dxhandle_technique_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "technique���Ԉ���Ă��܂�", "ValidateTechnique", MB_OK);
		return false;
	}

	// �V�F�[�_���̃e�N�X�`���̃n���h��(�|�C���^)�擾
 
	d3dxhandle_pos_			 = shader_->GetParameterByName(nullptr, "g_Pos");
	d3dxhandle_scale_		 = shader_->GetParameterByName(nullptr, "g_Scale");
	d3dxhandle_view_		 = shader_->GetParameterByName(nullptr, "g_MatView");
	d3dxhandle_view_inverse_ = shader_->GetParameterByName(nullptr, "g_MatInverseView");
	d3dxhandle_projection_	 = shader_->GetParameterByName(nullptr, "g_MatProjection");
	d3dxhandle_texture_		 = shader_->GetParameterByName(nullptr, "g_Texture");

	return  true;
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�̃R���p�C��
-----------------------------------------------------------------------------*/
bool BillboardShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
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
/* ����������
-----------------------------------------------------------------------------*/
bool BillboardShader::NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// �V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "SourceFiles/Develop/HLSL/BillboardShader.hlsl" //exe����̑��΃p�X
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
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile BillboardShader", MB_OK);
		}
		else
		{
			// ���̑��̃G���[
			MessageBox(nullptr, "BillboardShader::LoadCompiledShader():�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "Failed to compile BillboardShader", MB_OK);
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
/* ����������
-----------------------------------------------------------------------------*/
bool BillboardShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// �R���p�C���ς݃V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "Assets/CompiledShaderObjects/BillboardShader.cso" //exe����̑��΃p�X
								 , NULL
								 , NULL
								 , D3DXSHADER_SKIPVALIDATION
								 , NULL
								 , &shader_
								 , &error);
	// �G���[����
	if (FAILED(hr))
	{
		if (error)
		{
			// �R���p�C���G���[����
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile BillboardShader", MB_OK);
		}
		else
		{
			// ���̑��̃G���[
			MessageBox(nullptr, "BillboardShader::LoadCompiledShader():�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "Failed to compile BillboardShader", MB_OK);
		}
		SAFE_RELEASE_(error);
		return false;
	}
	//�o�b�t�@�̉��
	SAFE_RELEASE_(error);
	return true;
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
void BillboardShader::ShaderSet(Camera* camera, RendererComponent* rendererComponent, Texture* texture)
{
	//�����_���[����`��f�o�C�X�̎擾
	auto lpd3d_device = *manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//���_�t�H�[�}�b�g���̓]��
	lpd3d_device->SetVertexDeclaration(lpd3d_vertex_declaration_);

	//�V�F�[�_�[���̕`����@���v���O�������֎w��
	shader_->SetTechnique(d3dxhandle_technique_);

	//
	// ���[���h�s��ւ̍���
	//
	D3DXMATRIX world_matrix;
	{
		//
		// ���s�ړ��E�g�k���̍쐬
		//

		//�ʒu���A�g�k���
		D3DXVECTOR3 position = *rendererComponent->GetPosition();
		D3DXVECTOR3 scale	 = *rendererComponent->GetScale();

		D3DXMATRIX rotation_matrix = *camera->GetViewInverseMatrix();


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
	}
	else
	{
		//�V�F�[�_�[�Ƀe�N�X�`����]��
		shader_->SetTexture("g_Texture", texture->GetTexture());
	}

	//�萔�o�b�t�@���V�F�[�_�ɓ]��
	shader_->CommitChanges();
}
