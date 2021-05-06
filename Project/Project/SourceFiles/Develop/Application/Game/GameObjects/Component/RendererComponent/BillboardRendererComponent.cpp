/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardRendererComponent.cpp] �r���{�[�h�����_���[�R���|�l���g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�r���{�[�h�����_���[�R���|�l���g�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "BillboardRendererComponent.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "../../../VertexData.h"
#include "../../../Shader.h"
#include "../../../../Math.h"
#include "../../GameObject/Camera.h"
#include "../../../Resource/Texture.h"


//�o�b�t�@

LPDIRECT3DVERTEXBUFFER9 BillboardRendererComponent::vertex_buffer_ = nullptr;
LPDIRECT3DINDEXBUFFER9	BillboardRendererComponent::index_buffer_ = nullptr;

//�e�o�b�t�@�̃A�h���X

VERTEX_MESH*  BillboardRendererComponent::vertex_buffer_address_ = nullptr;
LPWORD*		BillboardRendererComponent::index_buffer_address_ = nullptr;


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BillboardRendererComponent::BillboardRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, texture_(nullptr)
	, is_compute_texcord_(false)
	, texture_cut_x_(0)
	, texture_cut_y_(0)
	, texture_cut_width_(256)
	, texture_cut_height_(256)
{
	// ������
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
BillboardRendererComponent::~BillboardRendererComponent(void)
{
	// �I����
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool BillboardRendererComponent::Init(void)
{
	//�`��V�F�[�_�[�̎w��
	this->shader_type_ = ShaderType::Billboard;

	//�o�b�t�@�̍쐬
	{
		//���_�o�b�t�@�̍쐬
		bool vtx_buffer_init = this->CreateVertexBuffer();
		if (vtx_buffer_init == false)
		{
			assert(!"BillboardRendererComponent::Init()�F���_�o�b�t�@�̍쐬�Ɏ��s���܂����B");
			return false;
		}

		//�C���f�b�N�X�o�b�t�@�̍쐬
		bool idx_buffer_init = this->CreateIndexBuffer();
		if (idx_buffer_init == false)
		{
			assert(!"BillboardRendererComponent::Init()�F�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂����B");
			return false;
		}
	}

	//�o�b�t�@�̏�����
	this->ComputeVertexBuffer();

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void BillboardRendererComponent::Uninit(void)
{
	SAFE_RELEASE_(vertex_buffer_);
	SAFE_RELEASE_(index_buffer_);
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void BillboardRendererComponent::Draw(Shader* shader, Camera* camera)
{
	auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//��]���ɋt�r���[�s��n��
	this->rotation_matrix_ = *camera->GetViewInverseMatrix();

	//���_�o�b�t�@�̍č\��
	this->ComputeVertexBuffer();

	//���_�o�b�t�@�̓o�^
	lpd3d_device->SetStreamSource(0, vertex_buffer_, 0, sizeof(VERTEX_STD));

	//�C���f�b�N�X�o�b�t�@�̓o�^
	lpd3d_device->SetIndices(index_buffer_);

	//�`�揈��
	{
		//�V�F�[�_�[�̃Z�b�g
		shader->ShaderSet(camera, this, texture_);

		//�V�F�[�_�[�p�X�̊J�n
		shader->ShaderPassBegin();

		// �|���S���`��
		lpd3d_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST	//�|���S���̕`��^�C�v
										  , 0					//���_�o�b�t�@�̊J�n�I�t�Z�b�g�o�C�g���W
										  , 0					//0�Ԗڂ̒��_�o�b�t�@
										  , 4					//�g�p���钸�_��
										  , 0					//�C���f�b�N�X�o�b�t�@�̊J�n�I�t�Z�b�g�o�C�g���W
										  , 2);					//�O�p�`�|���S���̖ʂ̐�

		//�V�F�[�_�[�p�X�̏I��
		shader->ShaderPassEnd();
	}
}

/*-----------------------------------------------------------------------------
/*�@���_�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
bool BillboardRendererComponent::CreateVertexBuffer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();
	if (lpd3d_device == nullptr)
	{
		assert("�X�v���C�g�̒��_�o�b�t�@�쐬���ɁA�f�o�C�X��������܂���ł����B");
		return false;
	}

	//
	// ���_�o�b�t�@�C���X�^���X�������̏ꍇ
	//
	if (vertex_buffer_ != nullptr)
	{
		return true;
	}

	//���_�o�b�t�@�̍쐬
	if (FAILED(lpd3d_device->CreateVertexBuffer((MAX_VERTEX_COUNT * sizeof(VERTEX_STD))	//���_�o�b�t�@�T�C�Y
											   , D3DUSAGE_WRITEONLY						//�o�b�t�@�̎g�p���@
											   , FVF_VERTEX_STD							//���_�̃t�H�[�}�b�g
											   , D3DPOOL_MANAGED						//�������Ǘ����f�o�C�X�ɔC����
											   , &vertex_buffer_						//���_�o�b�t�@�̃C���^�[�t�F�[�X
											   , nullptr)))
	{
		assert("�X�v���C�g�̒��_�o�b�t�@�쐬�Ɏ��s���܂����B");
		return false;
	}

	//�V�X�e����������̒��_�f�[�^
	VERTEX_STD vtx[4] = {
		{ D3DXVECTOR3(-0.5f,  0.5f, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3( 0.5f,  0.5f, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR3( 0.5f, -0.5f, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) }
	};

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

/*-----------------------------------------------------------------------------
/* �C���f�b�N�X�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
bool BillboardRendererComponent::CreateIndexBuffer(void)
{
	//
	// �C���f�b�N�X�o�b�t�@�̃C���X�^���X�������̏ꍇ
	//
	if (index_buffer_ != nullptr)
	{
		return true;
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();
	if (lpd3d_device == nullptr)
	{
		assert("�X�v���C�g�̃C���f�b�N�X�o�b�t�@�쐬���ɁA�f�o�C�X��������܂���ł����B");
		return false;
	}

	//�C���f�b�N�X�o�b�t�@�̍쐬
	if (FAILED(lpd3d_device->CreateIndexBuffer((MAX_INDEX_COUNT * sizeof(VERTEX_STD))	//�C���f�b�N�X�o�b�t�@�T�C�Y
											  , D3DUSAGE_WRITEONLY						//�o�b�t�@�̎g�p���@
											  , D3DFMT_INDEX16							//�C���f�b�N�X�̃t�H�[�}�b�g
											  , D3DPOOL_MANAGED							//�������Ǘ����f�o�C�X�ɔC����
											  , &index_buffer_							//���_�o�b�t�@�̃C���^�[�t�F�[�X
											  , nullptr)))
	{
		assert("�X�v���C�g�̃C���f�b�N�X�o�b�t�@�쐬�Ɏ��s���܂����B");
		return false;
	}

	//16bit�ŃC���f�b�N�X���(����Ȃ��Ȃ�����32bit�ł�DWORD�^�ɕύX)
	WORD index[] = {
		0,1,2,
		1,3,2,
	};

	//VRAM�Ƃ̐ڑ����~
	index_buffer_->Lock(0
					   , 0
					   , (void**)&index_buffer_address_
					   , D3DLOCK_DISCARD);

	//�C���f�b�N�X�����������ɏ�������
	memcpy(index_buffer_address_				//�R�s�[��̃A�h���X
		  , index								//�R�s�[���̃�����
		  , sizeof(WORD) * MAX_INDEX_COUNT);	//�R�s�[����T�C�Y

	//VRAM�Ƃ̐ڑ����ĊJ
	index_buffer_->Unlock();

	return true;
}

/*-----------------------------------------------------------------------------
/* ���_�o�b�t�@�̍č\��
-----------------------------------------------------------------------------*/
void BillboardRendererComponent::ComputeVertexBuffer(void)
{
	//VRAM�֏������݂��s�����߂�RAM��ł̋c���A�h���X
	VERTEX_STD* vtx = nullptr;

	//VRAM�Ƃ̐ڑ����~
	vertex_buffer_->Lock(0
						, 0
						, (void**)&vtx
						, D3DLOCK_DISCARD);

	//�|���S���̒��_�F���ꊇ�ŊǗ�
	for (int i = 0; i < MAX_VERTEX_COUNT; i++)
		vtx[i].vtx_color_ = vertex_color_;

	//UV�A�j���[�V������I���ł���悤��
	if (is_compute_texcord_ == true)
	{
		//�e�N�X�`�����̎擾
		auto texture_image_info = *texture_->GetTextureImageInfo();

		//�e�N�X�`���̕��ƍ������i�[
		int texture_width_ = texture_image_info.Width;
		int texture_height_ = texture_image_info.Height;

		//�i�[���ꂽ�e�N�X�`���̕��ƍ�������UV���W���v�Z
		float u0 = (float)texture_cut_x_ / texture_width_;
		float v0 = (float)texture_cut_y_ / texture_height_;
		float u1 = (float)(texture_cut_x_ + texture_cut_width_) / texture_width_;
		float v1 = (float)(texture_cut_y_ + texture_cut_height_) / texture_height_;

		//UV���W��ݒ�B
		vtx[0].texcoord_ = D3DXVECTOR2(u0, v0);
		vtx[1].texcoord_ = D3DXVECTOR2(u1, v0);
		vtx[2].texcoord_ = D3DXVECTOR2(u0, v1);
		vtx[3].texcoord_ = D3DXVECTOR2(u1, v1);
	}
	else
	{
		//UV���W��ݒ�B
		vtx[0].texcoord_ = D3DXVECTOR2(0.f, 0.f);
		vtx[1].texcoord_ = D3DXVECTOR2(1.f, 0.f);
		vtx[2].texcoord_ = D3DXVECTOR2(0.f, 1.f);
		vtx[3].texcoord_ = D3DXVECTOR2(1.f, 1.f);
	}

	//VRAM�Ƃ̐ڑ����ĊJ
	vertex_buffer_->Unlock();
}

/*-----------------------------------------------------------------------------
/* ���_�o�b�t�@�̍œK���ɂ���
-----------------------------------------------------------------------------*/
//void BillboardRendererComponent::ComputeTransform(void)
//{
//	�r���{�[�h�̍œK���ɂ���
//
//	���_�o�b�t�@�ł̕`�斈��VRAM�Ƃ̐ڑ����J���߂�������͌����������̂ŁA
//
//	�p��������ŁA�g�k�A��]�A���s�ړ��Ȃǂ̏����܂�world�s����V�F�[�_�[�֓]�����邱�Ƃ�
//
//	��ʓ��ł̑傫����A��]�p�x�Ȃǂ̎p������]������
//
//	UV�X�N���[���́AUV���W�𒼐ڃV�F�[�_�[�֓]�����邱�Ƃōs��
//
//	�V�F�[�_�[�֓]��������
//	�F�g�k�E��]�B���s�ړ������܂񂾃��[���h�s��
//	�F���_�J���[
//	�FUV���W
//
//}

/*-----------------------------------------------------------------------------
/* �e�N�X�`���̐ݒ�
-----------------------------------------------------------------------------*/
void BillboardRendererComponent::SetTexture(TextureType textureTypeID)
{
	//�e�N�X�`���̓ǂݍ���
	this->texture_ = owner_->GetGame()->GetTextureManager()->LoadTexture(textureTypeID);
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`�����̎擾
-----------------------------------------------------------------------------*/
Texture* BillboardRendererComponent::GetTexture(void)
{
	//�e�N�X�`�����̎擾
	if (this->texture_ == nullptr)
	{
		assert(!"GetTexture():BillboardRendererComponent�Ƀe�N�X�`����񂪐ݒ肳��Ă��܂���I");
	}
	return texture_;
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`���\�����̎擾
-----------------------------------------------------------------------------*/
D3DXIMAGE_INFO* BillboardRendererComponent::GetTextureImageInfo(void)
{
	//�e�N�X�`���\�����̎擾
	if (this->texture_ == nullptr)
	{
		assert(!"GetTextureImageInfo():BillboardRendererComponent�ɏ��̎擾���ł��܂���ł����I");
	}
	return texture_->GetTextureImageInfo();
}

/*=============================================================================
/*		End of File
=============================================================================*/