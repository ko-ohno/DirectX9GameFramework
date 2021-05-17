/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[FFPMeshRendererComponent.cpp] �Œ�@�\�p�C�v���C���ɂ�郁�b�V���`��
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Œ�@�\�p�C�v���C���ɂ�郁�b�V���`��R���|�[�l���g�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "FFPMeshRendererComponent.h"
#include "../../GameObject.h"
#include "../../../Shader.h"
#include "../../../Resource/XFileMesh.h"
#include "../../GameObject/Camera.h"
#include "../../../Resource/Material.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
FFPMeshRendererComponent::FFPMeshRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, xfile_mesh_(nullptr)
{
	// ������
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
FFPMeshRendererComponent::~FFPMeshRendererComponent(void)
{
	// �I����
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool FFPMeshRendererComponent::Init(void)
{
	//�`��V�F�[�_�[�̎w��
	this->shader_type_ = ShaderType::StandardMesh;
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void FFPMeshRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void FFPMeshRendererComponent::Draw(Shader* shader, Camera* camera)
{
	UNREFERENCED_PARAMETER(shader);
	UNREFERENCED_PARAMETER(camera);

	auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//���b�V�����̊m�F
	if (xfile_mesh_ == nullptr)
	{
		assert(!"FFPMeshRendererComponent::Draw():���b�V����񂪐ݒ肳��Ă��܂���I");
	}

	//�`�揈��
	{
		// �}�e���A�����̎擾
		auto material_count = xfile_mesh_->GetMaterialCounts();

		// �}�e���A�����X�g�̎擾
		auto material_list = xfile_mesh_->GetMeshMaterialList();

		//�}�e���A���̈ꎞ�i�[��
		class Material* material_buffers = nullptr;

		// Zfunc�̗L����
		lpd3d_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

		// FVF(������g�p���钸�_���)�̐ݒ�
		lpd3d_device->SetFVF(FVF_VERTEX_MESH);

		//���[���h���W�ϊ�
		lpd3d_device->SetTransform(D3DTS_WORLD, this->GetWorldMatrix()); 

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

					// �}�e���A���̐ݒ�
					lpd3d_device->SetMaterial(material_buffers->GetD3DMaterial());

					// �e�N�X�`���̐ݒ�
					lpd3d_device->SetTexture(0, *material_buffers->GetTexture());
				}

				// ���b�V���̕`��
				xfile_mesh_->GetMesh()->DrawSubset(i);

			}
		}
		else
		{
			// ���b�V���̕`��
			xfile_mesh_->GetMesh()->DrawSubset(0);
		}

		// Zfunc�̖�����
		lpd3d_device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	}
}

/*-----------------------------------------------------------------------------
/* ���b�V�����̐ݒ�
-----------------------------------------------------------------------------*/
void FFPMeshRendererComponent::SetMesh(XFileMeshType xfileMeshTypeID)
{
	//���b�V���̓ǂݍ���
	this->xfile_mesh_ = owner_->GetGame()->GetMeshManager()->LoadMesh(xfileMeshTypeID);
}

/*-----------------------------------------------------------------------------
/* ���b�V�����̎擾
-----------------------------------------------------------------------------*/
XFileMesh* FFPMeshRendererComponent::GetMesh(void)
{
	//���b�V�����̎擾
	if (this->xfile_mesh_ == nullptr)
	{
		assert(!"FFPMeshRendererComponent::GetMesh():���b�V����񂪐ݒ肳��Ă��܂���I");
	}
	return xfile_mesh_;
}

/*=============================================================================
/*		End of File
=============================================================================*/