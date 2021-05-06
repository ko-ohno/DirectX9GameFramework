/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereGizmoRendererComponent.cpp] �X�t�B�A�M�Y���`��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�t�B�A�M�Y���`��R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "SphereGizmoRendererComponent.h"
#include "../../../GameObject.h"
#include "../../../../Shader.h"
#include "../../../../Resource/XFileMesh.h"
#include "../../../../Resource/Material.h"


/*-----------------------------------------------------------------------------
/*�@�R���X�g���N�^
-----------------------------------------------------------------------------*/
SphereGizmoRendererComponent::SphereGizmoRendererComponent(GameObject* owner, int drawOrder)
	: GizmoRendererComponent(owner, drawOrder)
	, xfile_mesh_(nullptr)
{
	// ������
	this->Init();
}

/*-----------------------------------------------------------------------------
/*�@�f�X�g���N�^
-----------------------------------------------------------------------------*/
SphereGizmoRendererComponent::~SphereGizmoRendererComponent(void)
{
	// �I����
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/*�@����������
-----------------------------------------------------------------------------*/
bool SphereGizmoRendererComponent::Init(void)
{
	//���b�V���̓ǂݍ���
	this->xfile_mesh_ = owner_->GetGame()->GetMeshManager()->LoadMesh(XFileMeshType::Sphere);

	return true;
}

/*-----------------------------------------------------------------------------
/*�@�I��������
-----------------------------------------------------------------------------*/
void SphereGizmoRendererComponent::Uninit(void)
{
	
}

/*-----------------------------------------------------------------------------
/*�@�`�揈��
-----------------------------------------------------------------------------*/
void SphereGizmoRendererComponent::Draw(Shader* shader, Camera* camera)
{
	//���b�V�����̊m�F
	if (xfile_mesh_ == nullptr)
	{
		assert(!"SphereGizmoRendererComponent::Draw():���b�V����񂪐ݒ肳��Ă��܂���I");
	}

	//�`�揈��
	{
		// NULL�̃}�e���A����n��
		class Material* material_buffer = nullptr;

		// �V�F�[�_�[�̃Z�b�g
		shader->ShaderSet(camera, this, material_buffer);

		//�V�F�[�_�[�p�X�̊J�n
		shader->ShaderPassBegin();

		// ���b�V���̕`��
		xfile_mesh_->GetMesh()->DrawSubset(0);

		//�V�F�[�_�[�p�X�̏I��
		shader->ShaderPassEnd();
	}
}

/*-----------------------------------------------------------------------------
/* ���b�V�����̎擾
-----------------------------------------------------------------------------*/
XFileMesh* SphereGizmoRendererComponent::GetMesh(void)
{
	//���b�V�����̎擾
	if (this->xfile_mesh_ == nullptr)
	{
		assert(!"SphereGizmoRendererComponent::GetMesh():���b�V����񂪐ݒ肳��Ă��܂���I");
	}
	return xfile_mesh_;
}

/*=============================================================================
/*		End of File
=============================================================================*/