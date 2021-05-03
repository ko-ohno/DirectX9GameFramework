/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ShaderManager.h] �V�F�[�_�[�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�V�F�[�_�[�Ǘ��N���X
=============================================================================*/
#ifndef SHADER_MANAGER_H_
#define	SHADER_MANAGER_H_ 

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* �V�F�[�_�[�̌^
-------------------------------------*/
enum class  ShaderType
{
	None = -1
	, Sprite			//�X�v���C�g
	, DissolveFade		//�t�F�[�h
	, Billboard			//�r���{�[�h
	, StandardMesh		//���b�V��(�{�[���Ȃ�)
	, SkinMesh			//�X�L�����b�V��
	, ParticleEffect    //�G�t�F�N�g
	, Gizmo				//�M�Y��
	, Max
};

/*-------------------------------------
/* �V�F�[�_�[�̊Ǘ��N���X
-------------------------------------*/
class ShaderManager
{
public:
	ShaderManager(class Game* game);
	~ ShaderManager(void);

	static ShaderManager* Create(class Game* game);

	bool StartUp(void);
	void Shutdown(void);
	
	class Game* GetGame(void) { return game_; }

	class Shader* ShaderDispatch(ShaderType shader);

private:
	bool Init(void);	//������
	void Uninit(void);	//�I����

	void LoadShaders(void);		//�V�F�[�_�̓ǂݍ���
	void UnloadShaders(void);	//�V�F�[�_�̔j��

private:
	//�}�l�[�W���[�̏��L��
	class Game* game_;

	//�V�F�[�_�[�̃��X�g
	std::unordered_map<enum class ShaderType, class Shader*> unmap_shader_list_;
};

#endif //SHADER_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/