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
#include "../TransformComponent.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
FFPMeshRendererComponent::FFPMeshRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, is_enable_lighting_(false)
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

	//// ���g�̏��L�҂̃��[���h�s��ƁA���g�̃��[���h�s����擾
	//auto owner_world_matrix = *owner_->GetTransform()->GetWorldMatrix();
	//auto mesh_world_matrix = *this->GetWorldMatrix();

	//// ���[���h�s����v�Z
	//auto world_matrix = mesh_world_matrix * owner_world_matrix;

	//���b�V�����̊m�F
	if (xfile_mesh_ == nullptr)
	{
		assert(!"FFPMeshRendererComponent::Draw():���b�V����񂪐ݒ肳��Ă��܂���I");
	}

	lpd3d_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	lpd3d_device->SetFVF(FVF_VERTEX_MESH);

	lpd3d_device->SetTransform(D3DTS_WORLD, &world_matrix_);

	if (is_enable_lighting_)
	{
		lpd3d_device->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	//�`�揈��
	{
		// �}�e���A�����̎擾
		auto material_count = xfile_mesh_->GetMaterialCounts();

		// �}�e���A���̎擾
		auto material_buffer = (LPD3DXMATERIAL)xfile_mesh_->GetMaterialBuffer()->GetBufferPointer();

		for (unsigned int i = 0; i < material_count; i++)
		{
			lpd3d_device->SetMaterial(&material_buffer[i].MatD3D);
			if (material_buffer[i].pTextureFilename != nullptr)
			{
				lpd3d_device->SetTexture(0, *xfile_mesh_->GetMeshMaterialList().at(i)->GetTexture());
			}
			else
			{
				lpd3d_device->SetTexture(0, nullptr);
			}

			xfile_mesh_->GetMesh()->DrawSubset(i);
		}
	}

	if (is_enable_lighting_)
	{
		lpd3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	lpd3d_device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
}

/*-----------------------------------------------------------------------------
/* ���C�g
-----------------------------------------------------------------------------*/
void FFPMeshRendererComponent::SetEnableLighting(bool isEnable)
{
	this->is_enable_lighting_ = isEnable;
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