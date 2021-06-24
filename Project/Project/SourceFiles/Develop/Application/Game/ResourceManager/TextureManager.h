/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TextureManager.h] �e�N�X�`���[�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�e�N�X�`���[�Ǘ��N���X
=============================================================================*/
#ifndef TEXTURE_MANAGER_H_
#define	TEXTURE_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/

/*-------------------------------------
/* �e�N�X�`���̎��
-------------------------------------*/
enum class TextureType
{
	None = -1
	, Sample
	, Prototype
	, Blank
	, FarReticle
	, NearReticle
	, Planet
	, Max
};


/*-------------------------------------
/* �e�N�X�`���[�Ǘ��N���X
-------------------------------------*/
class TextureManager
{
public:
	static const char* TextureTypeNames[static_cast<int>(TextureType::Max)];

public:
	TextureManager(class Game* game);
	~TextureManager(void);

	static TextureManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~

private:

	bool Init(void);	//������
	void Uninit(void);	//�I����

public:
	//�e�N�X�`���̃��[�g�p�X�̎擾
	std::string GetTextureRootpath(void) const { return texture_root_path_; }

	//�e�N�X�`���̓ǂݍ���
	class Texture* LoadTexture(TextureType textureTypeID);

	//�e�N�X�`���̉��
	void ReleaseTexture(TextureType textureTypeID);

	//�e�N�X�`������������
	class Texture* FindTexture(TextureType textureTypeID);

	//
	// �e�N�X�`���̒ǉ��ƍ폜
	//

	void AddTexture(class Texture* texture);
	void RemoveTexture(class Texture* texture);

	std::unordered_map<TextureType, std::string> GetTextureFilepathList(void) { return unmap_texture_path_list_; }

	class Game* GetGame(void) { return game_; }
	 
private:
	//�}�l�[�W���̏��L��
	class Game* game_;

	//�e�N�X�`���̃��[�g�p�X
	std::string texture_root_path_;

	//�e�N�X�`���[�̃p�X���X�g
	std::unordered_map<TextureType, std::string> unmap_texture_path_list_;

	//�e�N�X�`���[�̃R���e�i
	std::vector<class Texture*> texture_list_;
};

#endif //TEXTURE_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/