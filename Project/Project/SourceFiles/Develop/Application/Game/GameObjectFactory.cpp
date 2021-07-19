/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameObjectFactory.cpp] �Q�[���I�u�W�F�N�g�̃t�@�N�g���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���I�u�W�F�N�g�̃t�@�N�g���N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "GameObjectFactory.h"
#include "Game.h"
#include "GameObjects/GameObject.h"

//�e�X�g�p�Q�[���I�u�W�F�N�g
#include "GameObjects/GameObject/_Test/_CameraTest.h"
#include "GameObjects/GameObject/_Test/_SpriteTest.h"
#include "GameObjects/GameObject/_Test/_MeshTest.h"
#include "GameObjects/GameObject/_Test/_BillboardTest.h"
#include "GameObjects/GameObject/_Test/_EffectTest.h"
#include "GameObjects/GameObject/_Test/_AudioTest.h"
#include "GameObjects/GameObject/_Test/_ColliderTest.h"
#include "GameObjects/GameObject/_Test/_SaveDataTest.h"

// �Q�[���Ǘ��Q�[���I�u�W�F�N�g
#include "GameObjects/GameObject/GameManager.h"

// �J����
#include "GameObjects/GameObject/Camera/GameCamera.h"

// �w�i���C���[
#include "GameObjects/GameObject/BackGround/SkyBox.h"
#include "GameObjects/GameObject/BackGround/Planet.h"

// �T���h�{�b�N�X���C���[
#include "GameObjects/GameObject/SandBox/Actor/Player.h"
#include "GameObjects/GameObject/SandBox/Actor/Enemy.h"
#include "GameObjects/GameObject/SandBox/Actor/Enemy/Boss.h"

#include "GameObjects/GameObject/SandBox/ChargeBullet.h"

// UI���C���[
#include "GameObjects/GameObject/UI/HUD.h"
#include "GameObjects/GameObject/UI/Fade.h"

#include "GameObjects/GameObject/UI/Title.h"
#include "GameObjects/GameObject/UI/Result.h"
#include "GameObjects/GameObject/UI/PauseMenu.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
GameObjectFactory::GameObjectFactory(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
GameObjectFactory::~GameObjectFactory(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
GameObjectFactory* GameObjectFactory::Create(Game* game)
{
	return NEW GameObjectFactory(game);
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool GameObjectFactory::StartUp(void)
{
	//�R���e�i�̏�����
	game_objects_.clear();

	//�Q�[���I�u�W�F�N�g�̍쐬�ƒǉ�
	const bool isTestMode = false;
	if(isTestMode)
	{
		this->AddGameObject(NEW CameraTest(game_));
		this->AddGameObject(NEW SpriteTest(game_));
		this->AddGameObject(NEW BillboardTest(game_));
		this->AddGameObject(NEW MeshTest(game_));
		this->AddGameObject(NEW EffectTest(game_));
		this->AddGameObject(NEW AudioTest(game_));
		this->AddGameObject(NEW ColliderTest(game_));
		this->AddGameObject(NEW SaveDataTest(game_));
	}
	else
	{

		// �J����
		this->AddGameObject(NEW GameCamera(game_));

		//�Q�[���Ǘ��Q�[���I�u�W�F�N�g
		this->AddGameObject(NEW GameManager(game_));

		// �w�i���C���[�̃I�u�W�F�N�g�쐬
		this->AddGameObject(NEW SkyBox(game_));
		this->AddGameObject(NEW Planet(game_));

		// �T���h�{�b�N�X���C���[�̃I�u�W�F�N�g�쐬
		this->AddGameObject(NEW Player(game_));
		//this->AddGameObject(NEW Boss(game_));

		this->AddGameObject(NEW ChargeBullet(game_));


		// UI���C���[�̃I�u�W�F�N�g�쐬
		this->AddGameObject(NEW Fade(game_));
		this->AddGameObject(NEW HUD(game_));

		//this->AddGameObject(NEW Title(game_));
		//this->AddGameObject(NEW Result(game_));
		//this->AddGameObject(NEW PauseMenu(game_));

		 
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void GameObjectFactory::ShutDown(void)
{
	this->RemoveGameObjectAll();
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void GameObjectFactory::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void GameObjectFactory::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̒ǉ�
-----------------------------------------------------------------------------*/
void GameObjectFactory::AddGameObject(GameObject* gameObject)
{
	game_objects_.emplace_back(gameObject);
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̍폜
-----------------------------------------------------------------------------*/
void GameObjectFactory::RemoveGameObjectAll(void)
{
	//Game.cpp�ł���Ă���̂ō폜�����͕s�v
	//while (!game_objects_.empty())
	//{
	//	delete game_objects_.back();
	//	game_objects_.pop_back();
	//}
}

/*=============================================================================
/*		End of File
=============================================================================*/