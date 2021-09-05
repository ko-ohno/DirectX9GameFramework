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
#include "ISceneState.h"
#include "SceneState/SceneTitle.h"
#include "SceneState/SceneGame.h"
#include "SceneState/SceneResult.h"
#include "Renderer.h"

#include "ResourceManager/ShaderManager.h"
#include "ResourceManager/TextureManager.h"
#include "ResourceManager/MeshManager.h"
#include "ResourceManager/EffectManager.h"
#include "ResourceManager/LightManager.h"
#include "ResourceManager/SoundManager.h"
#include "ResourceManager/ColliderManager.h"
#include "ResourceManager/SaveDataManager.h"

#include "SandBoxManager/ActorManager.h"
#include "SandBoxManager/EnemieManager.h"

#include "GameObjectFactory.h"
#include "GameObjects/GameObject.h"

#include "../ImGui/ImGuiManager.h"

// �ÓI�ϐ��̃v���g�^�C�v�錾
ISceneState* Game::scene_state_ = nullptr;

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Game::Game(void)
	: is_shutdown_(false)
	, input_game_objects_(false)
	, updating_game_objects_(false)
	, game_state_(GameState::None)
	, game_object_fuctory_(nullptr)
	, dx9_graphics_(nullptr)
	, renderer_(nullptr)

	, shader_manager_(nullptr)
	, texture_manager_(nullptr)
	, mesh_manager_(nullptr)
	, effect_manager_(nullptr)
	, light_manager_(nullptr)
	, sound_manager_(nullptr)
	, collider_manager_(nullptr)
	, save_data_manager_(nullptr)

	, actor_manager_(nullptr)
	, enemie_manager_(nullptr)

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

	//���\�[�X�p�̊e�}�l�[�W���[�̋N��
	{
		//�V�F�[�_�[�}�l�[�W���̋N��
		shader_manager_ = shader_manager_->Create(this);
		const bool shader_manager_init = shader_manager_->StartUp();
		if (shader_manager_init == false)
		{
			assert(!"Game::StartUp()�F�V�F�[�_�[�}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}

		//�e�N�X�`���}�l�[�W���̋N��
		texture_manager_ = texture_manager_->Create(this);
		const bool texture_manager_init = texture_manager_->StartUp();
		if (texture_manager_init == false)
		{
			assert(!"Game::StartUp()�F�e�N�X�`���}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}
	
		//���b�V���}�l�[�W���̋N��
		mesh_manager_ = mesh_manager_->Create(this);
		const bool mesh_manager_init = mesh_manager_->StartUp();
		if (texture_manager_init == false)
		{
			assert(!"Game::StartUp()�F���b�V���}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}

		//�G�t�F�N�g�}�l�[�W���̋N��
		effect_manager_ = effect_manager_->Create(this);
		const bool effect_manager_init = effect_manager_->StartUp();
		if (effect_manager_init == false)
		{
			assert(!"Game::StartUp()�F�G�t�F�N�g�}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}

		//���C�g�}�l�[�W���̋N��
		light_manager_ = light_manager_->Create(this);
		const bool light_manager_init = light_manager_->StartUp();
		if (light_manager_init == false)
		{
			assert(!"Game::StartUp()�F���C�g�}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}

		//�T�E���h�}�l�[�W���̋N��
		sound_manager_ = sound_manager_->Create(this);
		const bool sound_manager_init = sound_manager_->StartUp();
		if (sound_manager_init == false)
		{
			assert(!"Game::StartUp()�F�T�E���h�}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}
	
		//�R���C�_�}�l�[�W���̋N��
		collider_manager_ = collider_manager_->Create(this);
		const bool collider_manager_init = collider_manager_->StartUp();
		if (collider_manager_init == false)
		{
			assert(!"Game::StartUp()�F�R���C�_�}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}

		//�Z�[�u�f�[�^�}�l�[�W���̋N��
		save_data_manager_ = save_data_manager_->Create(this);
		const bool save_data_manager_init = save_data_manager_->StartUp();
		if (save_data_manager_init == false)
		{
			assert(!"Game::StartUp()�F�Z�[�u�f�[�^�}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}
	}

	// �T���h�{�b�N�X�p�̃}�l�[�W���̋N��
	{
		//�A�N�^�[�̃}�l�[�W���̋N��
		actor_manager_ = actor_manager_->Create(this);
		const bool actor_manager_init = actor_manager_->StartUp();
		if (actor_manager_init == false)
		{
			assert(!"Game::StartUp()�F�A�N�^�[�}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}

		//�G�l�~�[�̃}�l�[�W���̋N��
		enemie_manager_ = enemie_manager_->Create(this);
		const bool enemie_manager_init = enemie_manager_->StartUp();
		if (enemie_manager_init == false)
		{
			assert(!"Game::StartUp()�F�G�l�~�[�}�l�[�W���̋N���Ɏ��s���܂����B");
			return false;
		}
	}

	//�����_���[�̋N��
	renderer_ = renderer_->Create(this);
	const bool renderer_init = renderer_->StartUp();
	if (renderer_init == false)
	{
		assert(!"Game::StartUp()�F�����_���[�̋N���Ɏ��s���܂����B");
		return false;	//�����_���̋N���Ɏ��s������
	}

	//�Q�[���I�u�W�F�N�g�̃t�@�N�g���̋N��
	game_object_fuctory_ = game_object_fuctory_->Create(this);
	const bool game_object_fuctory_init = game_object_fuctory_->StartUp();
	if(game_object_fuctory_init == false)
	{
		assert(!"Game::StartUp()�F�Q�[���I�u�W�F�N�g�̃t�@�N�g���̋N���Ɏ��s���܂����B");
		return false;
	}

	// ��ʂ̏�����
	{
		this->SetSceneState(NEW SceneTitle(this));
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

	// �T���h�{�b�N�X�̊e�}�l�[�W���̔j��
	{
		//�A�N�^�[�}�l�[�W���̔j��
		actor_manager_->Shutdown();
		SAFE_DELETE_(actor_manager_);

		//�G�l�~�[�}�l�[�W���̔j��
		enemie_manager_->Shutdown();
		SAFE_DELETE_(enemie_manager_);

	}

	// ���\�[�X�̊e�}�l�[�W���[�̔j��
	{
		//�Z�[�u�f�[�^�}�l�[�W���̔j��
		{
			save_data_manager_->Shutdown();
			SAFE_DELETE_(save_data_manager_);
		}

		//�T�E���h�}�l�[�W���̔j��
		{
			sound_manager_->Shutdown();
			SAFE_DELETE_(sound_manager_);
		}

		//�R���C�_�}�l�[�W���̔j��
		{
			collider_manager_->Shutdown();
			SAFE_DELETE_(collider_manager_);
		}

		//�R���C�_�}�l�[�W���̔j��
		{
			light_manager_->Shutdown();
			SAFE_DELETE_(light_manager_);
		}

		//�G�t�F�N�g�}�l�[�W���̔j��
		{
			effect_manager_->Shutdown();
			SAFE_DELETE_(effect_manager_);
		}

		//���b�V���}�l�[�W���̔j��
		{
			mesh_manager_->Shutdown();
			SAFE_DELETE_(mesh_manager_);
		}

		//�e�N�X�`���}�l�[�W���̔j��
		{
			texture_manager_->Shutdown();
			SAFE_DELETE_(texture_manager_);
		}

		//�V�F�[�_�[�}�l�[�W���̔j��
		{
			shader_manager_->Shutdown();
			SAFE_DELETE_(shader_manager_);
		}
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
	// ��ʂ��Ƃ̓��͏���
	if (scene_state_ != nullptr)
	{
		scene_state_->Input();
	}

	// �Q�[���I�u�W�F�N�g�̓��͏���
	this->InputGameObjects();
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Game::Update(float deltaTime)
{
	// FPS�̕\��
	ImGui::ShowFPS(deltaTime);

	// ��ʂ��Ƃ̓��͏���
	if (scene_state_ != nullptr)
	{
		scene_state_->Update(deltaTime);
	}

	//�Q�[���I�u�W�F�N�g�̑��X�V
	this->UpdateGameObjects(deltaTime);

	// �Q�[�����I������
	if (game_state_ == Game::GameState::Quit)
	{
		is_shutdown_ = true;
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
/* ��ʂ̐؂�ւ�����
-----------------------------------------------------------------------------*/
void Game::SetSceneState(ISceneState* sceneState)
{
	if (scene_state_ != nullptr)
		scene_state_->Uninit();

	scene_state_ = sceneState;

	if (scene_state_ != nullptr)
		scene_state_->Init();
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̒ǉ�����
-----------------------------------------------------------------------------*/
void Game::AddGameObject(GameObject* gameObject)
{
	// �Q�[���I�u�W�F�N�g�̍X�V�����œo�^���ύX
	if (updating_game_objects_ == true
		|| input_game_objects_ == true)
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
/* �Q�[���I�u�W�F�N�g�̑����͏���
-----------------------------------------------------------------------------*/
void Game::InputGameObjects(void)
{
	//�Q�[���I�u�W�F�N�g�̓��͏���
	input_game_objects_ = true;
	for (auto game_object : game_objects_)
	{
		game_object->Input();
	}
	input_game_objects_ = false;
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̑��X�V����
-----------------------------------------------------------------------------*/
void Game::UpdateGameObjects(float deltaTime)
{
	//�Q�[���I�u�W�F�N�g�ƃG�t�F�N�g�̑��X�V����
	{
		//�G�t�F�N�g�}�l�[�W���̍X�V�J�n
		//effect_manager_->GetEffekseerManager()->BeginUpdate();

		//���ׂẴQ�[���I�u�W�F�N�g�̍X�V
		updating_game_objects_ = true;
		for (auto game_object : game_objects_)
		{
			if (game_state_ == GameState::Paused)
			{
				// �|�[�Y���j���[�̃Q�[���I�u�W�F�N�g�������X�V����
				auto game_object_type = game_object->GetType();
				if (game_object_type == GameObject::TypeID::PauseMenu)
				{
					game_object->Update(deltaTime);
				}

				// �t�F�[�h���X�V����
				if (game_object_type == GameObject::TypeID::Fade)
				{
					game_object->Update(deltaTime);
				}
			}
			else
			{
				game_object->Update(deltaTime);
			}
		}
		updating_game_objects_ = false;

		//�G�t�F�N�g�}�l�[�W���̈ꊇ�X�V����
		if (game_state_ != GameState::Paused)
		{
			effect_manager_->GetEffekseerManager()->Update();
		}

		//�G�t�F�N�g�}�l�[�W���̍X�V�I��
		//effect_manager_->GetEffekseerManager()->EndUpdate();
	}

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
		if (game_object->GetGameObjectState() == GameObject::State::Dead)
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