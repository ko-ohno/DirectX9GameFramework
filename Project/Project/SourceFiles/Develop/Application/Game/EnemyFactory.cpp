/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactory.cpp] �G�l�~�[�̃t�@�N�g���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�̃t�@�N�g���N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "EnemyFactory.h"
#include "EnemyFactoryState.h"

// �G�l�~�[�̃t�@�N�g���̏�ԃN���X
#include "EnemyFactoryState/EnemyFactoryState_1.h"
#include "EnemyFactoryState/EnemyFactoryState_2.h"
#include "EnemyFactoryState/EnemyFactoryState_3.h"
#include "EnemyFactoryState/EnemyFactoryState_4.h"
#include "EnemyFactoryState/EnemyFactoryState_5.h"
#include "EnemyFactoryState/EnemyFactoryState_6.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactory::EnemyFactory(class Game* game)
	: game_(game)
	, enemy_factory_state_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EnemyFactory::~EnemyFactory(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool EnemyFactory::Init(void)
{
	auto a = 6;
	switch (a)
	{
	case 1:
		this->ChangeFactoryState(NEW EnemyFactoryState_1(game_));
		break;
	
	case 2:
		this->ChangeFactoryState(NEW EnemyFactoryState_2(game_));
		break;

	case 3:
		this->ChangeFactoryState(NEW EnemyFactoryState_3(game_));
		break;
	
	case 4:
		this->ChangeFactoryState(NEW EnemyFactoryState_4(game_));
		break;
	
	case 5:
		this->ChangeFactoryState(NEW EnemyFactoryState_5(game_));
		break;
	
	case 6:
		this->ChangeFactoryState(NEW EnemyFactoryState_6(game_));
		break;

	default:
		break;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void EnemyFactory::Uninit(void)
{
	SAFE_DELETE_(enemy_factory_state_);
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void EnemyFactory::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void EnemyFactory::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (enemy_factory_state_ == nullptr) { return; }
	enemy_factory_state_->Update(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g���̏�Ԑ؂�ւ�����
-----------------------------------------------------------------------------*/
void EnemyFactory::ChangeFactoryState(EnemyFactoryState* factory_state_)
{
	if (enemy_factory_state_ != nullptr)
		enemy_factory_state_->Uninit();

	delete enemy_factory_state_;
	enemy_factory_state_ = factory_state_;

	if (enemy_factory_state_ != nullptr)
		enemy_factory_state_->Init();
}

/*=============================================================================
/*		End of File
=============================================================================*/