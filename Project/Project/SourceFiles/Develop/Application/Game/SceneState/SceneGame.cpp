/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneGame.cpp] �Q�[����ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[����ʃN���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "../GameObjects/GameObject.h"

// �Q�[���Ǘ��Q�[���I�u�W�F�N�g
#include "../GameObjects/GameObject/GameManager.h"

// �J����
#include "../GameObjects/GameObject/Camera/GameCamera.h"

// �w�i���C���[
#include "../GameObjects/GameObject/BackGround/SkyBox.h"
#include "../GameObjects/GameObject/BackGround/Planet.h"

// �T���h�{�b�N�X���C���[
#include "../GameObjects/GameObject/SandBox/Actor/Player.h"

// UI���C���[
#include "../GameObjects/GameObject/UI/HUD.h"
#include "../GameObjects/GameObject/UI/BossHUD.h"

// ����
#include "../Input/InputCheck.h"

#include "../GameObjects/GameObject/SandBox/Actor/Enemy/Boss.h"
#include "../GameObjects/GameObject/SandBox/Actor/Enemy/WeakEnemy.h"
#include "../GameObjects/GameObject/SandBox/Actor/Enemy/StrongEnemy.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SceneGame::SceneGame(Game* game)
	: ISceneState(game)
	, is_show_screen_(false)
{
	// Game::SetSceneState()�ŏ���������邽�߁A������SceneGame::Init()�͌Ă΂Ȃ��B
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SceneGame::~SceneGame(void)
{
	// Game::SetSceneState()�ŏI��������邽�߁A������SceneGame::Uninit()�͌Ă΂Ȃ��B
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SceneGame::Init(void)
{
	// �Q�[���̃X�e�[�g��ݒ�
	//game_->SetGameState(Game::GameState::Gameplay);

	//
	// �����̃Q�[���I�u�W�F�N�g����l�R���|�[�l���g�̎擾
	// 

	// �Q�[���I�u�W�F�N�g�̃��X�g���擾
	auto game_objects = game_->GetGameObjects();
	for (auto game_object : game_objects)
	{
		//�@�Q�[���I�u�W�F�N�g�����L����l�R���|�[�l���g�̃��X�g���擾
		auto parameter_components = game_object->GetParameterComponents();

		// �Q�[���I�u�W�F�N�g�̌^�𒲂ׂ�
		auto game_object_type = game_object->GetType();

		// ��ʐ؂�ւ��p�̒l�R���|�[�l���g�̎擾
		{
			// �t�F�[�h��ʃQ�[���I�u�W�F�N�g����l�R���|�[�l���g�̃|�C���^���擾
			if (game_object_type == GameObject::TypeID::Fade)
			{
				// �Q�[���I�u�W�F�N�g�����L����l�R���|�[�l���g�𒲂ׂ�
				for (auto parameter_component : parameter_components)
				{
					// �t�F�[�h�����s���邩�̒l�R���|�[�l���g�̎擾
					auto parameter_component_type = parameter_component->GetParameterType();
					if (parameter_component_type == ParameterType::IsFadeExecute)
					{
						// �|�C���^�̎擾
						this->parameter_is_fade_execute_ = parameter_component;
					}
				}
			}

			// ���[�h��ʃQ�[���I�u�W�F�N�g����l�R���|�[�l���g�̃|�C���^���擾
			if (game_object_type == GameObject::TypeID::LoadingScreen)
			{
				// �Q�[���I�u�W�F�N�g�����L����l�R���|�[�l���g�𒲂ׂ�
				for (auto parameter_component : parameter_components)
				{
					// �l�R���|�[�l���g�̌^�𒲂ׂ�
					auto parameter_component_type = parameter_component->GetParameterType();

					// ��ʂ�؂�ւ��邩�̒l�R���|�[�l���g
					if (parameter_component_type == ParameterType::IsSceneChanged)
					{
						// �|�C���^�̎擾
						this->parameter_is_scene_changed = parameter_component;
						this->parameter_is_scene_changed->SetBool(false);
					}

					// �Q�[����ʂ�\�����邩�̒l�R���|�[�l���g
					if (parameter_component_type == ParameterType::IsShowGameScreen)
					{
						// �|�C���^�̎擾
						this->parameter_is_show_game_screen_ = parameter_component;
					}
				}
			}
		}
	}

	// �Q�[���̏�Ԃ�������
	//game_->SetGameState(Game::GameState::GameStartScene);

	// �Q�[����ʂ̃Q�[���I�u�W�F�N�g�̐���
	{
		// �Q�[���J����
		NEW GameCamera(game_);

		//�Q�[���Ǘ��Q�[���I�u�W�F�N�g
		NEW GameManager(game_);

		// �w�i���C���[�̃I�u�W�F�N�g�쐬
		NEW SkyBox(game_);
		NEW Planet(game_);

		// �T���h�{�b�N�X���C���[�̃I�u�W�F�N�g�쐬
		NEW Player(game_);

		// �G�̐���
		//NEW WeakEnemy(game_);
		//NEW StrongEnemy(game_);

		// UI���C���[�̃I�u�W�F�N�g�쐬
		//NEW HUD(game_);
		//NEW BossHUD(game_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SceneGame::Uninit(void)
{
	// �Q�[���I�u�W�F�N�g�̑��I����
	auto game_objects = game_->GetGameObjects();
	for (auto game_object : game_objects)
	{
		// �Q�[���I�u�W�F�N�g�̎�ނ��擾
		auto game_object_type = game_object->GetType();

		// �t�F�[�h�̃Q�[���I�u�W�F�N�g�̂ݔj�����Ȃ�
		if (game_object_type == GameObject::TypeID::Fade)
		{
			continue;
		}

		// ���[�h��ʂ̃Q�[���I�u�W�F�N�g�͔j�����Ȃ�
		if (game_object_type == GameObject::TypeID::LoadingScreen)
		{
			continue;
		}

		game_object->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void SceneGame::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void SceneGame::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const bool is_show_game_screen = parameter_is_show_game_screen_->GetBool();
	if (is_show_game_screen && (is_show_screen_ == false))
	{
		// �Q�[���̏�Ԃ��^�C�g����ʂ̏�ԂƂ��Đݒ�
		game_->SetGameState(Game::GameState::GameStartScene);

		// �Q�[���̏�Ԃ�������
		is_show_screen_ = true;
	}

	if (is_scene_change_tirgger_ == false)
	{
		auto game_state = game_->GetGameState();

		const bool is_game_state_game_over_  = (game_state == Game::GameState::GameOver);
		const bool is_game_state_game_clear_ = (game_state == Game::GameState::GameClear);
		if (is_game_state_game_over_ || is_game_state_game_clear_)
		{
			const bool is_input_key_space = (InputCheck::KeyTrigger(DIK_SPACE));
			const bool is_input_button_A = (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_A));
			if (is_input_key_space || is_input_button_A)
			{
				// ��ʐ؂�ւ��̃g���K�[��ON�ɂ��ē��͂𖳌���
				is_scene_change_tirgger_ = true;

				// ��ʐ؂�ւ���\��
				this->is_need_scene_changed_ = true;
			}
		}
	}
	
	// �؂�ւ��u�Ԃ݂̂��擾
	if (this->is_need_scene_changed_ == true)
	{
		// �l�R���|�[�l���g�Ƀt�F�[�h�����s���邱�Ƃ�ʒm
		parameter_is_fade_execute_->SetBool(true);

		// ���ɖ߂�
		this->is_need_scene_changed_ = false;
	}

	// �t�F�[�h�Q�[���I�u�W�F�N�g���t�F�[�h���������������擾
	const bool is_scene_changed = parameter_is_scene_changed->GetBool();
	if (is_scene_changed)
	{
		// �Q�[���̏�Ԃ����[�h��ʂ̏�ԂƂ��Đݒ�
		game_->SetGameState(Game::GameState::Loading);

		// �Q�[���J�n
		this->ChangeScene();
	}
}

/*-----------------------------------------------------------------------------
/* �V�[���̐؂�ւ�����
-----------------------------------------------------------------------------*/
void SceneGame::ChangeScene(void)
{
	game_->SetSceneState(NEW SceneResult(game_));
}

/*=============================================================================
/*		End of File
=============================================================================*/