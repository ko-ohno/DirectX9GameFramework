/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Texture.cpp] �e�N�X�`���[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�e�N�X�`���[�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "Texture.h"
#include "../Manager/TextureManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Texture::Texture(class TextureManager* manager, TextureType textureType)
	: texture_manager_(manager)
	, texture_type_id_(TextureType::None)
	, is_loading_complete_(false)
	, lpd3d_texture_(nullptr)
{
	//�e�N�X�`��ID�̐ݒ�
	texture_type_id_ = textureType;

	//�e�N�X�`���[�̓ǂݍ���
	is_loading_complete_ = this->LoadTexture(textureType);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Texture::~Texture()
{
	//�e�N�X�`���̉��
	SAFE_RELEASE_(lpd3d_texture_);
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`���̓ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
bool Texture::LoadTexture(const TextureType textureType)
{
	auto lpd3d_device = *texture_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();
	{
		auto texture_filepath = texture_manager_->GetTextureFilepathList().at(textureType);

		HRESULT hr = D3DXCreateTextureFromFile(lpd3d_device, texture_filepath.c_str(), &lpd3d_texture_);
		if (FAILED(hr))
		{
			assert(!"�e�N�X�`���[�̍쐬�Ɏ��s���܂����I");
			return false;
		}

		hr = D3DXGetImageInfoFromFile(texture_filepath.c_str(), &d3dximage_info_);
		if (FAILED(hr))
		{
			assert(!"�e�N�X�`���[�̉摜���̎擾�Ɏ��s���܂����I");
			return false;
		}
	}
	return true;
}

/*=============================================================================
/*		End of File
=============================================================================*/