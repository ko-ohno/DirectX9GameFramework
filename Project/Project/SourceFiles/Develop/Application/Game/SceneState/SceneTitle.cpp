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
			// �t�F�[�h�̃Q�[���I�u�W�F�N�g�̂ݔj�����Ȃ�
			if (game_object_type == GameObject::TypeID::Fade)
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
		if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
		{
			// �Q�[���J�n
			this->ChangeScene();
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