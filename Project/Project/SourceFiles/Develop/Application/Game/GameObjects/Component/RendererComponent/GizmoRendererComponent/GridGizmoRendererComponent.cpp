/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GridGizmoRendererComponent.cpp] �O���b�h�M�Y���`��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�O���b�h�M�Y���`��R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "GridGizmoRendererComponent.h"
#include "../../../GameObject.h"
#include "../../../../VertexData.h"
#include "../../../../Shader.h"
#include "../../../../Resource/Material.h"
#include "../../../GameObject/Camera.h"

//�o�b�t�@

LPDIRECT3DVERTEXBUFFER9 GridGizmoRendererComponent::vertex_buffer_ = nullptr;

//�e�o�b�t�@�̃A�h���X

VERTEX_GIZMO* GridGizmoRendererComponent::vertex_buffer_address_ = nullptr;


/*-----------------------------------------------------------------------------
/*�@�R���X�g���N�^
-----------------------------------------------------------------------------*/
GridGizmoRendererComponent::GridGizmoRendererComponent(GameObject* owner, int drawOrder)
	: GizmoRendererComponent(owner, drawOrder)
{
	const bool init_this_renderer = this->Init();
	if (init_this_renderer == false)
	{
		assert(!"�O���b�h�M�Y�������_���[�̏������Ɏ��s����");
	}
}

/*-----------------------------------------------------------------------------
/*�@�f�X�g���N�^
-----------------------------------------------------------------------------*/
GridGizmoRendererComponent::~GridGizmoRendererComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/*�@����������
-----------------------------------------------------------------------------*/
bool GridGizmoRendererComponent::Init(void)
{
	//�`��V�F�[�_�[�̎w��
	this->shader_type_ = ShaderType::Gizmo;

	//�o�b�t�@�̍쐬
	{
		//���_�o�b�t�@�̍쐬
		bool vtx_buffer_init = this->CreateVertexBuffer();
		if (vtx_buffer_init == false)
		{
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/*�@�I��������
-----------------------------------------------------------------------------*/
void GridGizmoRendererComponent::Uninit(void)
{
	SAFE_RELEASE_(vertex_buffer_);
}

/*-----------------------------------------------------------------------------
/*�@�`�揈��
-----------------------------------------------------------------------------*/
void GridGizmoRendererComponent::Draw(Shader* shader, Camera* camera)
{
	auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//���_�o�b�t�@�̓o�^
	lpd3d_device->SetStreamSource(0, vertex_buffer_, 0, sizeof(VERTEX_GIZMO));

	//�`�揈��
	{
		// NULL�̃}�e���A����n��
		class Material* material_buffer = nullptr;

		// �V�F�[�_�[�̃Z�b�g
		shader->ShaderSet(camera, this, material_buffer);

		//�V�F�[�_�[�p�X�̊J�n
		shader->ShaderPassBegin();

		// �|���S���`��
		lpd3d_device->DrawPrimitive(D3DPT_LINELIST		//�|���S���̕`��^�C�v
								   , 0					//0�Ԗڂ̒��_�o�b�t�@
								   , MAX_VERTEX_COUNT);	//�v���~�e�B�u�̐�

		//�V�F�[�_�[�p�X�̏I��
		shader->ShaderPassEnd();
	}

}

/*-----------------------------------------------------------------------------
/*�@���_�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
bool GridGizmoRendererComponent::CreateVertexBuffer(void)
{
	//
	// ���_�o�b�t�@�C���X�^���X�������̏ꍇ
	//
	if (vertex_buffer_ != nullptr)
	{
		return true;
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();
	if (lpd3d_device == nullptr)
	{
		assert("�O���b�h�M�Y���̒��_�o�b�t�@�쐬���ɁA�f�o�C�X��������܂���ł����B");
		return false;
	}

	//���_�o�b�t�@�̍쐬
	if (FAILED(lpd3d_device->CreateVertexBuffer((MAX_VERTEX_COUNT * sizeof(VERTEX_GIZMO))	//���_�o�b�t�@�T�C�Y
											   , D3DUSAGE_WRITEONLY							//�o�b�t�@�̎g�p���@
											   , FVF_VERTEX_GIZMO							//���_�̃t�H�[�}�b�g
											   , D3DPOOL_MANAGED							//�������Ǘ����f�o�C�X�ɔC����
											   , &vertex_buffer_							//���_�o�b�t�@�̃C���^�[�t�F�[�X
											   , nullptr)))
	{
		assert("�O���b�h�M�Y���̒��_�o�b�t�@�쐬�Ɏ��s���܂����B");
		return false;
	}

	//�V�X�e����������̒��_�f�[�^
	VERTEX_GIZMO vtx[MAX_VERTEX_COUNT];

	const int StartLine = (GRID_SIZE / 2);
	const int EndLine	=-(GRID_SIZE / 2);

	//�z�u�������̐���������
	int line_count_ = 0;
	for (int i = 0; i < ONE_STRIPES_VERTEX_COUNT; i++)
	{
		// �����̒��_�̔z�u
		vtx[i] = { D3DXVECTOR3(StartLine,  0.f, static_cast<float>(StartLine - line_count_)), D3DCOLOR_RGBA(255, 255, 255, 255) };
		i++;
		vtx[i] = { D3DXVECTOR3(EndLine,	   0.f, static_cast<float>(StartLine - line_count_)), D3DCOLOR_RGBA(255, 255, 255, 255) };
		line_count_++;
	}

	//�z�u�������̐���������
	line_count_ = 0;
	for (int i = 0; i < ONE_STRIPES_VERTEX_COUNT; i++)
	{
		// �c���̒��_�̔z�u
		vtx[ONE_STRIPES_VERTEX_COUNT + i] = { D3DXVECTOR3(static_cast<float>(StartLine - line_count_),  0.f, StartLine), D3DCOLOR_RGBA(255, 255, 255, 255) };
		i++;
		vtx[ONE_STRIPES_VERTEX_COUNT + i] = { D3DXVECTOR3(static_cast<float>(StartLine - line_count_),  0.f, EndLine),   D3DCOLOR_RGBA(255, 255, 255, 255) };
		line_count_++;
	}

	//VRAM�Ƃ̐ڑ����~
	vertex_buffer_->Lock(0
						, 0
						, (void**)&vertex_buffer_address_
						, D3DLOCK_DISCARD);

	//���_�����������ɏ�������
	memcpy(vertex_buffer_address_
		  , vtx
		  , sizeof(vtx));

	//VRAM�Ƃ̐ڑ����ĊJ
	vertex_buffer_->Unlock();

	return true;
}

/*=============================================================================
/*		End of File
=============================================================================*/