/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Texture.h] �e�N�X�`���[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�e�N�X�`���[�N���X
=============================================================================*/
#ifndef TEXTURE_H_
#define	TEXTURE_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "../Manager/TextureManager.h"


/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �e�N�X�`���[�N���X
-------------------------------------*/
class Texture
{
public:
	Texture(class TextureManager* manager, TextureType textureType);
	~Texture(void);

	//�e�N�X�`���̓ǂݍ���
	bool LoadTexture(const TextureType textureType);
	
	bool IsLoadCompleted(void) { return is_loading_complete_; }

	TextureType GetTextureTypeID(void) { return texture_type_id_; }

	LPDIRECT3DTEXTURE9 GetTexture(void) { return lpd3d_texture_; }

	D3DXIMAGE_INFO* GetTextureImageInfo(void) { return &d3dximage_info_; }

private:
	//�e�N�X�`���[�̏��L��
	class TextureManager* texture_manager_;

	//���[�h�ł�����
	bool is_loading_complete_;

	//�e�N�X�`���[��ID
	enum class TextureType texture_type_id_;

	//�e�N�X�`���̉摜�f�[�^
	LPDIRECT3DTEXTURE9 lpd3d_texture_;

	//�e�N�X�`���̃T�C�Y���̏��
	D3DXIMAGE_INFO	   d3dximage_info_;
};

#endif //TEXTURE_H_
/*=============================================================================
/*		End of File
=============================================================================*/