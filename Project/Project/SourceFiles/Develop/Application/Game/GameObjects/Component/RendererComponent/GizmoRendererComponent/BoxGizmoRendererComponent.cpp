/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BoxGizmoRendererComponent.cpp] �{�b�N�X�M�Y���`��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�b�N�X�M�Y���`��R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "BoxGizmoRendererComponent.h"
#include "../../../GameObject.h"
#include "../../../../Shader.h"
#include "../../../../Resource/XFileMesh.h"
#include "../../../../Resource/Material.h"

/*-----------------------------------------------------------------------------
/*�@�R���X�g���N�^
-----------------------------------------------------------------------------*/
BoxGizmoRendererComponent::BoxGizmoRendererComponent(GameObject* owner, int drawOrder)
	: GizmoRendererComponent(owner, drawOrder)
	, xfile_mesh_(nullptr)
{
	// ������
	this->Init();
}

/*-----------------------------------------------------------------------------
/*�@�f�X�g���N�^
-----------------------------------------------------------------------------*/
BoxGizmoRendererComponent::~BoxGizmoRendererComponent(void)
{
	// �I����
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/*�@����������
-----------------------------------------------------------------------------*/
bool BoxGizmoRendererComponent::Init(void)
{
	//���b�V���̓ǂݍ���
	this->xfile_mesh_ = owner_->GetGame()->GetMeshManager()->LoadMesh(XFileMeshType::Box);

	return true;
}

/*-----------------------------------------------------------------------------
/*�@�I��������
-----------------------------------------------------------------------------*/
void BoxGizmoRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�`�揈��
-----------------------------------------------------------------------------*/
void BoxGizmoRendererComponent::Draw(Shader* shader, Camera* camera)
{
	//���b�V�����̊m�F
	if (xfile_mesh_ == nullptr)
	{
		assert(!"BoxGizmoRendererComponent::Draw():���b�V����񂪐ݒ肳��Ă��܂���I");
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
XFileMesh* BoxGizmoRendererComponent::GetMesh(void)
{
	//���b�V�����̎擾
	if (this->xfile_mesh_ == nullptr)
	{
		assert(!"BoxGizmoRendererComponent::GetMesh():���b�V����񂪐ݒ肳��Ă��܂���I");
	}
	return xfile_mesh_;
}


/*=============================================================================
/*		End of File
=============================================================================*/