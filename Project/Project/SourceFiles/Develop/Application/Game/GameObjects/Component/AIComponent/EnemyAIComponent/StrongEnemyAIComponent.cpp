/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyAIComponent.cpp] ボスAIコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスAIコンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "StrongEnemyAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
StrongEnemyAIComponent::StrongEnemyAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, boss_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
StrongEnemyAIComponent::~StrongEnemyAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool StrongEnemyAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Uninit(void)
{
	// ステートマシンを削除
	SAFE_DELETE_(boss_state_machine_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void StrongEnemyAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 敵のステートを操作する
	//this->EnemyStateController();
	//
	//ImGui::Begin("boss_ai_state");

	//{
	//	switch (enemy_state_)
	//	{
	//	case EnemyState::Wait:
	//		ImGui::Text("wait");
	//		this->ChangeState(NEW BossStateWait());
	//		break;

	//	case EnemyState::Enter:
	//		ImGui::Text("enter");
	//		this->ChangeState(NEW BossStateEnter());
	//		break;

	//	case EnemyState::BodyPress:
	//		ImGui::Text("body_press");
	//		this->ChangeState(NEW BossStateBodyPress());
	//		break;

	//	case EnemyState::Shooting:
	//		ImGui::Text("shooting");
	//		this->ChangeState(NEW BossStateShooting());
	//		break;

	//	case EnemyState::LaserCannon:
	//		ImGui::Text("laser_cannon");
	//		this->ChangeState(NEW BossStateLaserCannon());
	//		break;

	//	case EnemyState::Destroy:
	//		break;

	//	default:
	//		assert(!"StrongEnemyAIComponent::Update()：ボスがAIが不正な状態です！");
	//		break;
	//	}
	//}
	//ImGui::End();

	//switch (enemy_state_)
	//{
	//case EnemyState::Wait:
	//	this->ChangeState(NEW BossStateWait());
	//	break;

	//case EnemyState::Enter:
	//	this->ChangeState(NEW BossStateEnter());
	//	break;

	//case EnemyState::BodyPress:
	//	this->ChangeState(NEW BossStateBodyPress());
	//	break;

	//case EnemyState::Shooting:
	//	this->ChangeState(NEW BossStateShooting());
	//	break;

	//case EnemyState::LaserCannon:
	//	this->ChangeState(NEW BossStateLaserCannon());
	//	break;

	//case EnemyState::Destroy:
	//	break;

	//default:
	//	assert(!"StrongEnemyAIComponent::Update()：ボスがAIが不正な状態です！");
	//	break;
	//}

	// このAIのステートマシンがnullptrか？
	//if (boss_state_machine_ != nullptr)
	//{
	//	boss_state_machine_->Update(this, deltaTime);
	//}
}

/*=============================================================================
/*		End of File
=============================================================================*/