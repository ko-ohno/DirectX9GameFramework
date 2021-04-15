/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdMeshRendererComponent.cpp] �W�����b�V�������_���[�R���|�[�l���g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�W�����b�V�������_���[�R���|�[�l���g�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "StdMeshRendererComponent.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "../../../VertexData.h"
#include "../../../Shader.h"
#include "../../../../Math.h"
#include "../../../Resource/XFileMesh.h"
#include "../../GameObject/Camera.h"
#include "../../../Resource/Material.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
StdMeshRendererComponent::StdMeshRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, xfile_mesh_(nullptr)
{
	// ������
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
StdMeshRendererComponent::~StdMeshRendererComponent(void)
{
	// �I����
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool StdMeshRendererComponent::Init(void)
{
	//�`��V�F�[�_�[�̎w��
	this->shader_type_ = ShaderType::StandardMesh;

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void StdMeshRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void StdMeshRendererComponent::Draw(Shader* shader, Camera* camera)
{
	//���b�V�����̊m�F
	if (xfile_mesh_ == nullptr)
	{
		assert(!"StdMeshRendererComponent::Draw():���b�V����񂪐ݒ肳��Ă��܂���I");
	}

	//�`�揈��
	{
		// �}�e���A�����̎擾
		auto material_count = xfile_mesh_->GetMaterialCounts();

		// �}�e���A�����X�g�̎擾
		auto material_list = xfile_mesh_->GetMeshMaterialList();

		//�}�e���A���̈ꎞ�i�[��
		class Material* material_buffers = nullptr;

		//�`�悷�郁�b�V�����v���~�e�B�u�̃��b�V����
		const bool is_primitive_mesh = xfile_mesh_->IsGetPrimitiveMesh();
		if (is_primitive_mesh)
		{
			shader->SetTechnique("Tech2");
		}
		else
		{
			shader->SetTechnique("Tech");
		}

		//�}�e���A�������邩�H
		if (material_count > 0)
		{
			// �}�e���A�����������`��
			for (int i = 0; i < static_cast<int>(material_count); i++)
			{
				//�}�e���A���̏�����
				material_buffers = nullptr;

				// �쐬���ꂽ�}�e���A���̃��X�g����ł͂Ȃ���
				if (!material_list.empty())
				{
					// �쐬���ꂽ�}�e���A�����X�g�ƃ}�e���A�������H���Ⴄ�Ƃ�
					const bool is_list_out_of_range = (static_cast<unsigned int>(i) < material_list.size());
					if (is_list_out_of_range)
					{
						material_buffers = xfile_mesh_->GetMeshMaterialList().at(i);
					}
				}

				// �V�F�[�_�[�̃Z�b�g
				shader->ShaderSet(camera, this, material_buffers);

				//�V�F�[�_�[�p�X�̊J�n
				shader->ShaderPassBegin();

				// ���b�V���̕`��
				xfile_mesh_->GetMesh()->DrawSubset(i);

				//�V�F�[�_�[�p�X�̏I��
				shader->ShaderPassEnd();
			}
		}
		else
		{
			// �V�F�[�_�[�̃Z�b�g
			shader->ShaderSet(camera, this, material_buffers);

			//�V�F�[�_�[�p�X�̊J�n
			shader->ShaderPassBegin();

			// ���b�V���̕`��
			xfile_mesh_->GetMesh()->DrawSubset(0);

			//�V�F�[�_�[�p�X�̏I��
			shader->ShaderPassEnd();
		}
	}
}

/*-----------------------------------------------------------------------------
/* ���b�V���̐ݒ�
-----------------------------------------------------------------------------*/
void StdMeshRendererComponent::SetMesh(XFileMeshType xfileMeshTypeID)
{
	//���b�V���̓ǂݍ���
	this->xfile_mesh_ = owner_->GetGame()->GetMeshManager()->LoadMesh(xfileMeshTypeID);
}

/*-----------------------------------------------------------------------------
/* ���b�V�����̎擾
-----------------------------------------------------------------------------*/
XFileMesh* StdMeshRendererComponent::GetMesh(void)
{
	//���b�V�����̎擾
	if (this->xfile_mesh_ == nullptr)
	{
		assert(!"StdMeshRendererComponent::GetMesh():���b�V����񂪐ݒ肳��Ă��܂���I");
	}
	return xfile_mesh_;
}

/*=============================================================================
/*		End of File
=============================================================================*/