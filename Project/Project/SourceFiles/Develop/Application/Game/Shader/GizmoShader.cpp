/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GizmoShader.cpp] �M�Y���V�F�[�_�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�M�Y���V�F�[�_�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "GizmoShader.h"
#include "../../DX9Graphics.h"
#include "../Shader.h"
#include "../Manager/ShaderManager.h"
#include "../Game.h"
#include "../GameObjects/GameObject/Camera.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
GizmoShader::GizmoShader(ShaderManager* manager)
	: Shader(manager)
	, d3dxhandle_technique_(nullptr)
{
	//�f�o�C�X�̎擾
	auto lpd3d_device = *manager->GetGame()->GetGraphics()->GetLPD3DDevice();

	//�V�F�[�_�[�̏�����
	this->Init(lpd3d_device);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
GizmoShader::~GizmoShader(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool GizmoShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
{

	//���_�t�H�[�}�b�g�̍쐬
	{
		//���_�錾�i�[�C���^�[�t�F�C�X�쐬
		D3DVERTEXELEMENT9 vertex_element[] =
		{
			//�P�̒��_�����e�����A���_���W�A���_�J���[�AUV�A�I��
			{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
			{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
			D3DDECL_END()
		};

		//���_�t�H�[�}�b�g�̍쐬
		if (FAILED(lpd3d_device->CreateVertexDeclaration(vertex_element, &lpd3d_vertex_declaration_)))
		{
			assert(!"�M�Y���V�F�[�_�[�̒��_�t�H�[�}�b�g�̍쐬�Ɏ��s���܂����B");
			return false;
		}
	}

	//�V�F�[�_�[�̃R���p�C��
	{
		bool is_init_shader = this->ShaderCompile(lpd3d_device);
		if (is_init_shader == false)
		{
			assert(!"�M�Y���V�F�[�_�[�̃R���p�C���Ɏ��s���܂����B");
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

	return  true;
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�̃R���p�C��
-----------------------------------------------------------------------------*/
bool GizmoShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
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
/* �V�����V�F�[�_�̃R���p�C��
-----------------------------------------------------------------------------*/
bool GizmoShader::NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// �V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "SourceFiles/Develop/HLSL/GizmoShader.hlsl" //exe����̑��΃p�X
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
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile GizmoShader", MB_OK);
		}
		else
		{
			// ���̑��̃G���[
			MessageBox(nullptr, "GizmoShader::NewShaderCompile():�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "Failed to compile GizmoShader", MB_OK);
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
bool GizmoShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	// �R���p�C���ς݃V�F�[�_�̓ǂݍ���
	LPD3DXBUFFER error = nullptr;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(lpd3d_device
								 , "Assets/CompiledShaderObjects/GizmoShader.cso" //exe����̑��΃p�X
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
			MessageBox(nullptr, (LPSTR)error->GetBufferPointer(), "Failed to compile GizmoShader", MB_OK);
		}
		else
		{
			// ���̑��̃G���[
			MessageBox(nullptr, "GizmoShader::LoadCompiledShader():�V�F�[�_�[�t�@�C�����ǌ��ݍ��߂܂���", "Failed to compile GizmoShader", MB_OK);
		}
		SAFE_RELEASE_(error);
		return false;
	}
	//�o�b�t�@�̉��
	SAFE_RELEASE_(error);
	return true;
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�̃R���p�C��
-----------------------------------------------------------------------------*/
void GizmoShader::ShaderSet(Camera* camera, RendererComponent* rendererComponent, Material* material)
{
	//�g�p���Ȃ��l�̃��[�j���O���
	UNREFERENCED_PARAMETER(material);

	//�����_���[����`��f�o�C�X�̎擾
	auto lpd3d_device = *manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//���_�t�H�[�}�b�g���̓]��
	lpd3d_device->SetVertexDeclaration(lpd3d_vertex_declaration_);

	//�V�F�[�_�[���̕`����@���v���O�������֎w��
	shader_->SetTechnique(d3dxhandle_technique_);

	//�V�F�[�_�[�Ƀ��[���h�s���n���B
	shader_->SetVector("g_Color", rendererComponent->GetVertexColor());

	//�V�F�[�_�[�Ƀ��[���h�s���n���B
	shader_->SetMatrix("g_MatWorld", rendererComponent->GetWorldMatrix());

	//�V�F�[�_�[�Ƀr���[�s���n���B
	shader_->SetMatrix("g_MatView", camera->GetViewMatrix());

	//�V�F�[�_�[�Ƀv���W�F�N�V�����s���n���B
	shader_->SetMatrix("g_MatProjection", camera->GetProjection3DMatrix());

	//�萔�o�b�t�@���V�F�[�_�ɓ]��
	shader_->CommitChanges();
}

/*=============================================================================
/*		End of File
=============================================================================*/