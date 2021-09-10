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

// ����
#include "../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SceneGame::SceneGame(Game* game)
	: ISceneState(game)
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
	// �Q�[����ʂ̃Q�[���I�u�W�F�N�g�̐���
	{
		// �Q�[���̃X�e�[�g��ݒ�
		game_->SetGameState(Game::GameState::Gameplay);

		// �Q�[���J����
		NEW GameCamera(game_);

		//�Q�[���Ǘ��Q�[���I�u�W�F�N�g
		NEW GameManager(game_);

		// �w�i���C���[�̃I�u�W�F�N�g�쐬
		NEW SkyBox(game_);
		NEW Planet(game_);

		// �T���h�{�b�N�X���C���[�̃I�u�W�F�N�g�쐬
		NEW Player(game_);

		// UI���C���[�̃I�u�W�F�N�g�쐬
		NEW HUD(game_);
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

	if ( InputCheck::KeyTrigger(DIK_SPACE))
	{
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