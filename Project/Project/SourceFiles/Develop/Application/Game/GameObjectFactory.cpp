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

//�e�X�g�p
#include "GameObjects/GameObject/_SpriteTest.h"
#include "GameObjects/GameObject/_MeshTest.h"
#include "GameObjects/GameObject/_BillboardTest.h"
#include "GameObjects/GameObject/_EffectTest.h"
#include "GameObjects/GameObject/_AudioTest.h"
#include "GameObjects/GameObject/_ColliderTest.h"
#include "GameObjects/GameObject/_SaveDataTest.h"



//�Q�[���I�u�W�F�N�g
#include "GameObjects/GameObject/Camera.h"
#include "GameObjects/GameObject/Player.h"
#include "GameObjects/GameObject/Enemy.h"


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
	{
		this->AddGameObject(NEW Camera(game_));
		//this->AddGameObject(NEW Player(game_));
		//this->AddGameObject(NEW Enemy(game_));

		this->AddGameObject(NEW SpriteTest(game_));
		this->AddGameObject(NEW BillboardTest(game_));
		this->AddGameObject(NEW MeshTest(game_));
		this->AddGameObject(NEW EffectTest(game_));
		this->AddGameObject(NEW AudioTest(game_));
		this->AddGameObject(NEW ColliderTest(game_));
		this->AddGameObject(NEW SaveDataTest(game_));

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
	//while (!game_objects_.empty())
	//{
	//	delete game_objects_.back();
	//}
}

/*=============================================================================
/*		End of File
=============================================================================*/