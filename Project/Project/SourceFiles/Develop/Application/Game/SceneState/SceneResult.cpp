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
	// ���U���g��ʂ̃Q�[���I�u�W�F�N�g�̐���
	{
		// �Q�[���̃X�e�[�g��ݒ�
		game_->SetGameState(Game::GameState::Result);

		// �Q�[���J����
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

	if (InputCheck::KeyTrigger(DIK_SPACE))
	{
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