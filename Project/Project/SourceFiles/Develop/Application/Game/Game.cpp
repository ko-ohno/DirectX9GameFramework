/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[game.cpp] �Q�[���̏�Ԃ�I�u�W�F�N�g�̊Ǘ����W���[��
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[����ԂƃI�u�W�F�N�g�̊Ǘ��B�ǉ��ƍ폜�B���́A�X�V�A�`��Ȃ�
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "Game.h"
#include "Renderer.h"


#include "Manager/ShaderManager.h"
#include "Manager/TextureManager.h"


#include "GameObjectFactory.h"
#include "GameObjects/GameObject.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Game::Game(void)
	: updating_game_objects_(false)
	, game_state_(GameState::None)
	, dx9_graphics_(nullptr)
	, renderer_(nullptr)

	, shader_manager_(nullptr)

	, game_object_fuctory_(nullptr)
{
	pending_game_objects_.clear();
	game_objects_.clear();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Game::~Game(void)
{
	pending_game_objects_.clear();
	game_objects_.clear();
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
Game* Game::Create(void)
{
	return NEW Game();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Game::StartUp(class DX9Graphics* dx9Graphics)
{
	//�O���t�B�b�N�X�̗����グ��Z�[�u�f�[�^�̃��[�h�Ȃǂ��s��

	//�O���t�B�b�N�X�̃R�s�[
	dx9_graphics_ = dx9Graphics;

	//�Q�[���̏��
	game_state_ = GameState::Gameplay;

	//�}�l�[�W���[�̃t�@�N�g��������
	{
		//�V�F�[�_�[�}�l�[�W���̋N��
		shader_manager_ = shader_manager_->Create(this);
		const bool shader_manager_init = shader_manager_->StartUp();
		if (shader_manager_init == false)
		{
			return false;
		}

		//�V�F�[�_�[�}�l�[�W���̋N��
		texture_manager_ = texture_manager_->Create(this);
		const bool texture_manager_init = texture_manager_->StartUp();
		if (texture_manager_init == false)
		{
			return false;
		}
	}

	//�����_���[�̋N��
	renderer_ = renderer_->Create(this);
	const bool renderer_init = renderer_->StartUp();
	if (renderer_init == false)
	{
		return false;	//�����_���̋N���Ɏ��s������
	}

	//�Q�[���I�u�W�F�N�g�̃t�@�N�g���̋N��
	game_object_fuctory_ = game_object_fuctory_->Create(this);
	const bool game_object_fuctory_init = game_object_fuctory_->StartUp();
	if(game_object_fuctory_init == false)
	{
		return false;
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Game::ShutDown(void)
{
	//�Q�[���I�u�W�F�N�g�����ׂĔj��
	while (!game_objects_.empty())
	{
		delete game_objects_.back();
	}

	//�Q�[���I�u�W�F�N�g�̃t�@�N�g���̔j��
	{
		game_object_fuctory_->ShutDown();
		SAFE_DELETE_(game_object_fuctory_);
	}

	//�V�F�[�_�[�}�l�[�W���̔j��
	{
		shader_manager_->Shutdown();
		SAFE_DELETE_(shader_manager_);
	}
	 
	//�����_���[�̔j��
	{
		renderer_->ShutDown();
		SAFE_DELETE_(renderer_);
	}
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void Game::Input(void)
{
	if (game_state_ == GameState::Gameplay)
	{
		//�Q�[���I�u�W�F�N�g�̓��͏���
		for (auto game_object : game_objects_)
		{
			game_object->Input();
		}
	}
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Game::Update(float deltaTime)
{
	if (game_state_ == GameState::Gameplay)
	{
		//�Q�[���I�u�W�F�N�g�̍X�V
		this->UpdateGameObjects(deltaTime);
	}


	switch (game_state_)
	{
	case Game::GameState::Title:
		break;

	case Game::GameState::Gameplay:
		break;

	case Game::GameState::Result:
		break;

	case Game::GameState::Paused:
		break;

	case Game::GameState::Quit:
		break;

	default:
		assert(!"�Q�[���̕s���ȏ�ԑJ�ڂ����m�I");
		break;
	}
}

/*-----------------------------------------------------------------------------
/* �o�͐�������
-----------------------------------------------------------------------------*/
void Game::GenerateOutput(void)
{
	//�����_���[�ɂ��`�揈��
	renderer_->Draw();
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̒ǉ�����
-----------------------------------------------------------------------------*/
void Game::AddGameObject(GameObject* gameObject)
{
	// �Q�[���I�u�W�F�N�g�̍X�V�����œo�^���ύX
	if (updating_game_objects_)
	{
		pending_game_objects_.emplace_back(gameObject);//�ҋ@�R���e�i
	}
	else
	{
		game_objects_.emplace_back(gameObject);//�ғ��R���e�i
	}
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̍폜����
-----------------------------------------------------------------------------*/
void Game::RemoveGameObject(GameObject* gameObject)
{
	// �ҋ@�R���e�i
	// "gameObject"���R���e�i�̒�����T���o���Ĕj������
	auto iter = std::find(pending_game_objects_.begin(), pending_game_objects_.end(), gameObject);
	if (iter != pending_game_objects_.end())
	{
		//��v����"gameObject"���R���e�i�̖����ֈړ������A���������̂�j������
		std::iter_swap(iter, pending_game_objects_.end() - 1);
		pending_game_objects_.pop_back();
	}

	// �ғ��R���e�i
	// "gameObject"���R���e�i�̒�����T���o���Ĕj������
	iter = std::find(game_objects_.begin(), game_objects_.end(), gameObject);
	if (iter != game_objects_.end())
	{
		//��v����"gameObject"���R���e�i�̖����ֈړ������A���������̂�j������
		std::iter_swap(iter, game_objects_.end() - 1);
		game_objects_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̌�������
-----------------------------------------------------------------------------*/
//GameObject* Game::FindGameObject(TypeID gameObjectTypeID)
//{
//	for (auto game_object : game_objects_)
//	{
//		auto game_object_type_id = game_object->GetType();
//
//		if (game_object_type_id == gameObjectTypeID)
//		{
//			return game_object;
//		}
//	}
//	assert(!"gameObjectTypeID�́A�Q�[���I�u�W�F�N�g�̃��X�g�Ɉ�v������̂�����܂���ł����I");
//	return nullptr;
//}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̑��X�V����
-----------------------------------------------------------------------------*/
void Game::UpdateGameObjects(float deltaTime)
{
	//���ׂẴQ�[���I�u�W�F�N�g�̍X�V
	updating_game_objects_ = true;
	for (auto game_object : game_objects_)
	{
		game_object->Update(deltaTime);
	}
	updating_game_objects_ = false;

	//�ҋ@���X�g�̃Q�[���I�u�W�F�N�g�̑���
	for (auto pending_game_object : pending_game_objects_)
	{
		pending_game_object->Update(deltaTime);
		game_objects_.emplace_back(pending_game_object);
	}
	pending_game_objects_.clear();

	//�Q�[���I�u�W�F�N�g���j���̏�Ԃ��`�F�b�N
	std::vector<class GameObject*> dead_game_objects;
	for (auto game_object : game_objects_)
	{
		if (game_object->GetState() == GameObject::State::Dead)
		{
			dead_game_objects.emplace_back(game_object);
		}
	}

	//�j���\��̃Q�[���I�u�W�F�N�g�̃�������j��
	for (auto dead_game_object : dead_game_objects)
	{
		delete dead_game_object;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/