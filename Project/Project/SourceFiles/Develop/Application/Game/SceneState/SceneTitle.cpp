/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneTitle.cpp] �^�C�g����ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�^�C�g����ʃN���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "../GameObjects/GameObject.h"

// �J����
#include "../GameObjects/GameObject/Camera.h"

// �^�C�g�����
#include "../GameObjects/GameObject/UI/Title.h"

// �t�F�[�h���
#include "../GameObjects/GameObject/UI/Fade.h"

// ���[�h���
#include "../GameObjects/GameObject/UI/LoadingScreen.h"

// ����
#include "../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SceneTitle::SceneTitle(Game* game)
	: ISceneState(game)
	, title_(nullptr)
{
	// Game::SetSceneState()�ŏ���������邽�߁A������SceneTitle::Init()�͌Ă΂Ȃ��B
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SceneTitle::~SceneTitle(void)
{
	// Game::SetSceneState()�ŏI��������邽�߁A������SceneTitle::Uninit()�͌Ă΂Ȃ��B
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SceneTitle::Init(void)
{
	// �Q�[���̃X�e�[�g��ݒ�
	game_->SetGameState(Game::GameState::Title);

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
	
	// �^�C�g����ʂ̃Q�[���I�u�W�F�N�g�̐���
	{
		// �J�����̍쐬
		NEW Camera(game_);

		// �^�C�g����ʂ̍쐬
		title_ = NEW Title(game_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SceneTitle::Uninit(void)
{
	// �Q�[���̏�Ԃ��擾
	auto game_state = game_->GetGameState();

	// �Q�[���I�u�W�F�N�g�̑��I����
	auto game_objects = game_->GetGameObjects();
	for (auto game_object : game_objects)
	{
		// �Q�[���I�u�W�F�N�g�̎�ނ��擾
		auto game_object_type = game_object->GetType();

		// �Q�[�����I����Ԃ���Ȃ�������
		if (game_state != Game::GameState::Quit)
		{		
			// �t�F�[�h�̃Q�[���I�u�W�F�N�g�͔j�����Ȃ�
			if (game_object_type == GameObject::TypeID::Fade)
			{
				continue;
			}

			// ���[�h��ʂ̃Q�[���I�u�W�F�N�g�͔j�����Ȃ�
			if (game_object_type == GameObject::TypeID::LoadingScreen)
			{
				continue;
			}
		}
		game_object->SetGameObjectState(GameObject::State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void SceneTitle::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void SceneTitle::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	auto title_menu_state = title_->GetTitleMenuState();
	switch (title_menu_state)
	{
	case TitleMenuState::GameStart:
		//if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
		if (InputCheck::KeyTrigger(DIK_SPACE))
		{
			this->is_input_scene_changed_ = true;
		}
		break;

	case TitleMenuState::GameQuit:
		if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
		{
			// �Q�[���I��
			game_->SetGameState(Game::GameState::Quit);
		}
		break;

	default:
		assert("SceneTitle::Update()�F�^�C�g���̃X�e�[�g���s���ȏ�Ԃł��I");
		break;
	}

	// �؂�ւ��u�Ԃ݂̂��擾
	if (this->is_input_scene_changed_ == true)
	{
		// �l�R���|�[�l���g�Ƀt�F�[�h�����s���邱�Ƃ�ʒm
		parameter_is_fade_execute_->SetBool(true);
	
		// ���ɖ߂�
		this->is_input_scene_changed_ = false;
	}

	// �t�F�[�h�Q�[���I�u�W�F�N�g���t�F�[�h���������������擾
	const bool is_scene_changed = parameter_is_scene_changed->GetBool();
	if (is_scene_changed)
	{
		// �Q�[���J�n
		this->ChangeScene();
	}
}

/*-----------------------------------------------------------------------------
/* �V�[���̐؂�ւ�����
-----------------------------------------------------------------------------*/
void SceneTitle::ChangeScene(void)
{
	game_->SetSceneState(NEW SceneGame(game_));
}

/*=============================================================================
/*		End of File
=============================================================================*/