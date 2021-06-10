/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ActorManager.cpp] �A�N�^�[�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�N�^�[�Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "ActorManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ActorManager::ActorManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ActorManager::~ActorManager(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
ActorManager* ActorManager::Create(Game* game)
{
	return NEW ActorManager(game);
}

/*-----------------------------------------------------------------------------
/* �N������
-----------------------------------------------------------------------------*/
bool ActorManager::StartUp(void)
{
	//���g�̏�����
	const bool Enemie_manager_init = this->Init();
	if (Enemie_manager_init == false)
	{
		assert(!"ActorManager::StartUp()�F�A�N�^�[�[�}�l�[�W���̏������Ɏ��s���܂����B");
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void ActorManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool ActorManager::Init(void)
{
	//���g�̏�����
	{
		actor_list_.clear();
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void ActorManager::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �A�N�^�[�Q�[���I�u�W�F�N�g�̃A�h���X�̒ǉ�����
-----------------------------------------------------------------------------*/
void ActorManager::AddActorGameObjectAddress(Actor* Actor)
{
	actor_list_.emplace_back(Actor);
}

/*-----------------------------------------------------------------------------
/* �A�N�^�[�Q�[���I�u�W�F�N�g�̃A�h���X�̍폜����
-----------------------------------------------------------------------------*/
void ActorManager::RemoveActorGameObjectAddress(Actor* Actor)
{
	auto iter = std::find(actor_list_.begin() //�͈�0�`
						 , actor_list_.end()  //�͈͍ő�܂�
						 , Actor);			   //�T���Ώ�

	if (iter != actor_list_.end())
	{
		actor_list_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/