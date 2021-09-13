/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactory.cpp] エネミーのファクトリクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エネミーのファクトリクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "EnemyFactory.h"
#include "EnemyFactoryState.h"

// エネミーのファクトリの状態クラス
#include "EnemyFactoryState/EnemyFactoryState_1.h"
#include "EnemyFactoryState/EnemyFactoryState_2.h"
#include "EnemyFactoryState/EnemyFactoryState_3.h"
#include "EnemyFactoryState/EnemyFactoryState_4.h"
#include "EnemyFactoryState/EnemyFactoryState_5.h"
#include "EnemyFactoryState/EnemyFactoryState_6.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EnemyFactory::EnemyFactory(class Game* game)
	: game_(game)
	, enemy_factory_state_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EnemyFactory::~EnemyFactory(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
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
/* 終了化処理
-----------------------------------------------------------------------------*/
void EnemyFactory::Uninit(void)
{
	SAFE_DELETE_(enemy_factory_state_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void EnemyFactory::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void EnemyFactory::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (enemy_factory_state_ == nullptr) { return; }
	enemy_factory_state_->Update(deltaTime);
}

/*-----------------------------------------------------------------------------
/* ファクトリの状態切り替え処理
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