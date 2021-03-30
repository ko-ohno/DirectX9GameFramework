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
/* �\����
-------------------------------------*/

enum class TextureType
{
	None = -1
	, Sample
	, Prototype
	, Planet

	, Max
};


/*-------------------------------------
/* �e�N�X�`���[�Ǘ��N���X
-------------------------------------*/
class TextureManager
{
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
	//�e�N�X�`���̓ǂݍ���
	class Texture* LoadTexture(TextureType textureTypeID);

	//�e�N�X�`���̉��
	void	 ReleaseTexture(TextureType textureTypeID);

	//�e�N�X�`������������
	class Texture* FindTexture(TextureType textureTypeID);

	void AddTexture(class Texture* texture);
	void RemoveTexture(class Texture* texture);

	std::unordered_map<TextureType, std::string> GetTextureFilepathList(void) { return unmap_texture_path_list_; }

	class Game* GetGame(void) { return game_; }
	 
private:
	//�}�l�[�W���̏��L��
	class Game* game_;

	//�e�N�X�`���[�̃��X�g
	std::unordered_map<TextureType, std::string> unmap_texture_path_list_;

	//�e�N�X�`���[�̃��X�g�폜�ƒǉ�
	std::vector<class Texture*> texture_list_;
};

#endif //TEXTURE_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/