/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyAIComponent.cpp] ボスAIコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスAIコンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "WeakEnemyAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
WeakEnemyAIComponent::WeakEnemyAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, boss_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
WeakEnemyAIComponent::~WeakEnemyAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool WeakEnemyAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Uninit(void)
{
	// ステートマシンを削除
	SAFE_DELETE_(boss_state_machine_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void WeakEnemyAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//// 敵のステートを操作する
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
	//		assert(!"WeakEnemyAIComponent::Update()：ボスがAIが不正な状態です！");
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
	//	assert(!"WeakEnemyAIComponent::Update()：ボスがAIが不正な状態です！");
	//	break;
	//}

	//// このAIのステートマシンがnullptrか？
	//if (boss_state_machine_ != nullptr)
	//{
	//	boss_state_machine_->Update(this, deltaTime);
	//}
}

///*-----------------------------------------------------------------------------
///*　更新処理
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::EnemyStateController(void)
//{
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_Y))
//	{
//		this->SetEnemyState(EnemyState::Enter);
//	}
//
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_LEFT_SHOULDER))
//	{
//		this->SetEnemyState(EnemyState::Wait);
//	}
//
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_LEFT_TRIGGER))
//	{
//		this->SetEnemyState(EnemyState::BodyPress);
//	}
//
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_RIGHT_SHOULDER))
//	{
//		this->SetEnemyState(EnemyState::Shooting);
//	}
//
//	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_RIGHT_TRIGGER))
//	{
//		this->SetEnemyState(EnemyState::LaserCannon);
//	}
//}
//
///*-----------------------------------------------------------------------------
///*　ボスのステートマシンの変更
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::ChangeState(BossStateMachine* bossStateMachine)
//{
//	if (boss_state_machine_ != nullptr)
//		delete boss_state_machine_;
//
//	boss_state_machine_ = bossStateMachine;
//
//	if (boss_state_machine_ != nullptr)
//		boss_state_machine_->Init();
//}
//
///*-----------------------------------------------------------------------------
///*　ボスの待機行動
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::Wait(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//}
//
///*-----------------------------------------------------------------------------
///*　ボスの登場行動
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::Enter(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//
//	if (motion_state_ == EnemyMotionState::End)
//	{
//		enemy_state_ = EnemyState::Wait;
//	}
//}
//
///*-----------------------------------------------------------------------------
///*　ボスの体当たり行動
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::BodyPress(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//
//	if (motion_state_ == EnemyMotionState::End)
//	{
//		enemy_state_ = EnemyState::Wait;
//	}
//}
//
///*-----------------------------------------------------------------------------
///*　ボスの射撃攻撃行動
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::Shoot(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//
//	if (motion_state_ == EnemyMotionState::End)
//	{
//		enemy_state_ = EnemyState::Wait;
//	}
//}
//
///*-----------------------------------------------------------------------------
///*　ボスのレーザー砲攻撃行動
//-----------------------------------------------------------------------------*/
//void WeakEnemyAIComponent::LaserCannon(float deltaTime)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//
//	if (motion_state_ == EnemyMotionState::End)
//	{
//		enemy_state_ = EnemyState::Wait;
//	}
//}

/*=============================================================================
/*		End of File
=============================================================================*/