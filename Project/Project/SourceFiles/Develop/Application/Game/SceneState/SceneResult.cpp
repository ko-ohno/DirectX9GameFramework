/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneResult.cpp] ���U���g��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���U���g��ʃN���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "SceneResult.h"
#include "SceneTitle.h"
#include "../GameObjects/GameObject.h"

// �J����
#include "../GameObjects/GameObject/Camera.h"

// �^�C�g�����
#include "../GameObjects/GameObject/UI/Result.h"

// ����
#include "../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SceneResult::SceneResult(Game* game)
	: ISceneState(game)
{
	// Game::SetSceneState()�ŏI��������邽�߁A������SceneResult::Init()�͌Ă΂Ȃ��B
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SceneResult::~SceneResult(void)
{
	// Game::SetSceneState()�ŏI��������邽�߁A������SceneResult::Uninit()�͌Ă΂Ȃ��B
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SceneResult::Init(void)
{
	// �Q�[���̃X�e�[�g��ݒ�
	//game_->SetGameState(Game::GameState::Result);

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

	// ���U���g��ʂ̃Q�[���I�u�W�F�N�g�̐���
	{
		// �J����
		NEW Camera(game_);

		// ���U���g���
		NEW Result(game_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SceneResult::Uninit(void)
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
void SceneResult::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void SceneResult::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const bool is_show_game_screen = parameter_is_show_game_screen_->GetBool();
	if (is_show_game_screen)
	{
		// �Q�[���̏�Ԃ��^�C�g����ʂ̏�ԂƂ��Đݒ�
		game_->SetGameState(Game::GameState::Result);
	}

	if (is_scene_change_tirgger_ == false)
	{
		const bool is_input_key_space = (InputCheck::KeyTrigger(DIK_SPACE));
		const bool is_input_button_A  = (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_A));
		if (is_input_key_space || is_input_button_A)
		{
			// ��ʐ؂�ւ��̃g���K�[��ON�ɂ��ē��͂𖳌���
			is_scene_change_tirgger_ = true;

			// ��ʐ؂�ւ���\��
			this->is_need_scene_changed_ = true;
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

		// �^�C�g����ʂ�
		this->ChangeScene();
	}
}

/*-----------------------------------------------------------------------------
/* �V�[���̐؂�ւ�����
-----------------------------------------------------------------------------*/
void SceneResult::ChangeScene(void)
{
	game_->SetSceneState(NEW SceneTitle(game_));
}

/*=============================================================================
/*		End of File
=============================================================================*/