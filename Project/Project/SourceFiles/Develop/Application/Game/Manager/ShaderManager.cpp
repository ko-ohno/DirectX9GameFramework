/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ShaderManager.cpp] �V�F�[�_�[�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�V�F�[�_�[�Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "ShaderManager.h"
#include "../Game.h"

#include "../Shader/SpriteShader.h"
#include "../Shader/DissolveShader.h"

#include "../Shader/BillboardShader.h"

#include "../Shader/StdMeshShader.h"
#include "../Shader/SkinMeshShader.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ShaderManager::ShaderManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ShaderManager::~ShaderManager(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
ShaderManager* ShaderManager::Create(Game* game)
{
	return NEW ShaderManager(game);
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�[�}�l�[�W���[�̋N��
-----------------------------------------------------------------------------*/
bool ShaderManager::StartUp(void)
{
	//�}�l�[�W���̏�����
	const bool is_init = this->Init();
	if(is_init == false)
	{
		return false;
	}

	//�V�F�[�_�̃��X�g�̍쐬
	this->LoadShaders();

	return true;
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�[�}�l�[�W���[�̒�~
-----------------------------------------------------------------------------*/
void ShaderManager::Shutdown(void)
{
	//�V�F�[�_�[�̔j��
	this->UnloadShaders();

	//�}�l�[�W���[�̏I��
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool ShaderManager::Init(void)
{
	//�V�F�[�_�[�̃��X�g�̏�����
	unmap_shader_list_.clear(); 

	if (!unmap_shader_list_.empty())
	{
		return false;
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void ShaderManager::Uninit(void)
{
	//�V�F�[�_�[�̃��X�g�̔j��
	unmap_shader_list_.clear();
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void ShaderManager::LoadShaders(void)
{	
	//�V�F�[�_�[
	unmap_shader_list_[ShaderType::Sprite]		 = NEW SpriteShader(this);
	unmap_shader_list_[ShaderType::DissolveFade] = NEW DissolveFadeShader(this);
	unmap_shader_list_[ShaderType::Billboard]	 = NEW BillboardShader(this);
	unmap_shader_list_[ShaderType::StandardMesh] = NEW StdMeshShader(this);
	unmap_shader_list_[ShaderType::SkinMesh]	 = NEW SkinMeshShader(this);
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�̔j��
-----------------------------------------------------------------------------*/
void ShaderManager::UnloadShaders(void)
{
	for (auto shader : unmap_shader_list_)
	{
		delete shader.second;
		shader.second = nullptr;
	}
}

/*-----------------------------------------------------------------------------
/* �V�F�[�_�̐؂�ւ�
-----------------------------------------------------------------------------*/
Shader* ShaderManager::ShaderDispatch(ShaderType shader)
{
	const bool shader_error = (shader == ShaderType::None
							  || shader == ShaderType::Max);
	if (shader_error)
	{
		assert(!"�s���ȃV�F�[�_�[�̐ݒ肪���蓖�Ă��悤�Ƃ��Ă��܂��B");
	}

	return unmap_shader_list_.at(shader);
}

/*=============================================================================
/*		End of File
=============================================================================*/