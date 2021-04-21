/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TextureManager.cpp] �e�N�X�`���[�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�e�N�X�`���[�Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "TextureManager.h"
#include "../Resource/Texture.h"

//�e�N�X�`���[�̃��X�g
const char* TextureManager::TextureTypeNames[static_cast<int>(TextureType::Max)] = {
	//�������g
	"Sample"
	, "Prototype"
	, "Planet"
};

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
TextureManager::TextureManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
TextureManager::~TextureManager(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
TextureManager* TextureManager::Create(Game* game)
{
	return NEW TextureManager(game);
}

/*-----------------------------------------------------------------------------
/* �N������
-----------------------------------------------------------------------------*/
bool TextureManager::StartUp(void)
{
	//���g�̏�����
	const bool texture_manager_init =  this->Init();
	if (texture_manager_init == false)
	{
		assert(!"TextureManager::StartUp()�F�e�N�X�`���[�}�l�[�W���̏������Ɏ��s���܂����B");
		return false;
	}

	//�e�N�X�`���[�̓ǂݍ���
	{
		//this->LoadTexture(TextureType::Sample);
		//this->LoadTexture(TextureType::Prototype);
		//this->LoadTexture(TextureType::Planet);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void TextureManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool TextureManager::Init(void)
{
	// �e�N�X�`���̃��[�g�p�X��ݒ�
	texture_root_path_ = "Assets/Textures/";

	// ���X�g�̏�����
	unmap_texture_path_list_.clear();
	{
		unmap_texture_path_list_[TextureType::Sample]    = "tex1.bmp";
		unmap_texture_path_list_[TextureType::Prototype] = "PrototypingTextures/texture_01.png";
		unmap_texture_path_list_[TextureType::Planet]	 = "Planet.png";

	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void TextureManager::Uninit(void)
{
	while (!texture_list_.empty())
	{
		delete texture_list_.back();
		texture_list_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`���̓ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
Texture* TextureManager::LoadTexture(TextureType textureTypeID)
{
	//�e�N�X�`������������
	auto texture = this->FindTexture(textureTypeID);
	if (texture != nullptr)
	{
		return texture;
	}
	else
	{
		//�e�N�X�`�����Ȃ�������
		const bool is_texture_list_out_of_range = ((textureTypeID == TextureType::None)
											      || (textureTypeID == TextureType::Max));
		if (is_texture_list_out_of_range)
		{
			assert(!"�͈͊O�̃e�N�X�`��ID���Q�Ƃ��悤�Ƃ��Ă��܂��I");
			return nullptr;
		}
		this->AddTexture(NEW Texture(this, textureTypeID));
	}
	return this->FindTexture(textureTypeID);
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`���̉������
-----------------------------------------------------------------------------*/
void TextureManager::ReleaseTexture(TextureType textureTypeID)
{
	for (auto texture : texture_list_)
	{
		auto id = texture->GetTextureTypeID();

		if (id == textureTypeID)
		{
			delete texture;
		}
	}
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`����������
-----------------------------------------------------------------------------*/
Texture* TextureManager::FindTexture(TextureType textureTypeID)
{
	//�e�N�X�`�����X�g�̌���
	for (auto texture : texture_list_)
	{
		//���݂̒����Ώۂ���ID���擾
		auto id = texture->GetTextureTypeID();

		//�擾����ID��textureType
		if (id == textureTypeID)
		{
			return texture;
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`���̒ǉ�����
-----------------------------------------------------------------------------*/
void TextureManager::AddTexture(Texture* texture)
{
	texture_list_.emplace_back(texture);
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`���̍폜����
-----------------------------------------------------------------------------*/
void TextureManager::RemoveTexture(Texture* texture)
{
	auto iter = std::find(texture_list_.begin() //�͈�0�`
						 , texture_list_.end()	//�͈͍ő�܂�
						 , texture);			//�T���Ώ�

	if (iter != texture_list_.end())
	{
		texture_list_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/