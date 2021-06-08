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
#include "../ResourceManager/TextureManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Texture::Texture(TextureManager* manager, TextureType textureType)
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
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Texture::Texture(const LPDIRECT3DTEXTURE9& texture)
	: texture_manager_(nullptr)
	, texture_type_id_(TextureType::None)
	, is_loading_complete_(false)
	, lpd3d_texture_(nullptr)
	, d3dximage_info_(D3DXIMAGE_INFO())
{
	if (lpd3d_texture_ != nullptr)
	{
		is_loading_complete_ = true;
	}

	lpd3d_texture_ = texture;
	lpd3d_texture_ = lpd3d_texture_;
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Texture::~Texture(void)
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
		// �e�N�X�`���̃��[�g�p�X���擾
		auto texture_filepath = texture_manager_->GetTextureRootpath();

		// ���[�g�p�X�ƃt�@�C���p�X������
		texture_filepath = texture_filepath + texture_manager_->GetTextureFilepathList().at(textureType);

		std::string texture_type_name = TextureManager::TextureTypeNames[static_cast<int>(textureType)];

		// �e�N�X�`���̍쐬
		HRESULT hr = D3DXCreateTextureFromFile(lpd3d_device, texture_filepath.c_str(), &lpd3d_texture_);
		if (FAILED(hr))
		{
			assert(!texture_type_name.c_str() + ":�e�N�X�`���[�̍쐬�Ɏ��s���܂����I");
			return false;
		}

		// �e�N�X�`�����̍쐬
		hr = D3DXGetImageInfoFromFile(texture_filepath.c_str(), &d3dximage_info_);
		if (FAILED(hr))
		{
			assert(!texture_type_name.c_str() + ":�e�N�X�`���[�̉摜���̎擾�Ɏ��s���܂����I");
			return false;
		}
	}
	return true;
}

/*=============================================================================
/*		End of File
=============================================================================*/