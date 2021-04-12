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
	auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

	lpd3d_device->SetRenderState(D3DRS_LIGHTING, false);

	//lpd3d_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//void Scene::onWireFrame() {
	//	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//}

	//void Scene::offWireFrame() {
	//	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//}
	//���b�V�����̊m�F
	if (xfile_mesh_ == nullptr)
	{
		assert(!"StdMeshRendererComponent::Draw():���b�V����񂪐ݒ肳��Ă��܂���I");
	}

	//�`�揈��
	{
		//�V�F�[�_�[�̃Z�b�g
		shader->ShaderSet(camera, this);

		//�V�F�[�_�[�p�X�̊J�n
		shader->ShaderPassBegin();

		// ���b�V������}�e���A�����̎擾
		auto materials = (LPD3DXMATERIAL)xfile_mesh_->GetMaterialBuffer();
		if (materials == nullptr)
		{
			//�}�e���A���̂Ȃ����b�V���Ȃ炱��ŕ`��ł���
			xfile_mesh_->GetMesh()->DrawSubset(0);
		}
		else
		{
			//�}�e���A���̐��̎擾
			auto material_counts = xfile_mesh_->GetMaterialCounts();

			//���b�V���ۗ̕L����ʂ̐������`��
			for (unsigned int i = 0; i < static_cast<int>(material_counts); i++)
			{
				lpd3d_device->SetMaterial(&materials[i].MatD3D);
				//if (materials[i].pTextureFilename != nullptr)
				//{
				//	lpd3d_device->SetTexture(0, xfile_mesh_->GetMeshTextureList().at(i));
				//}
				//else
				//{
				//	lpd3d_device->SetTexture(0, nullptr);
				//}
				xfile_mesh_->GetMesh()->DrawSubset(i);
			}
		}

		//�V�F�[�_�[�p�X�̏I��
		shader->ShaderPassEnd();
	}

	//lpd3d_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

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