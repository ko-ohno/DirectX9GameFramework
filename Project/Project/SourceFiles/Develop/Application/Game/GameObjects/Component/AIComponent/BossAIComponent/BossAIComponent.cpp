/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossAIComponent.cpp] ボスAIコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスAIコンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "BossAIComponent.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BossAIComponent::BossAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, boss_state_machine_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
BossAIComponent::~BossAIComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BossAIComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void BossAIComponent::Uninit(void)
{
	// ステートマシンを削除
	SAFE_DELETE_(boss_state_machine_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void BossAIComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void BossAIComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// このAIのステートマシンがnullptrか？
	if (boss_state_machine_ != nullptr)
	{
		boss_state_machine_->Update(this, deltaTime);
	}

	// 敵のステートを操作する
	this->EnemyStateController();
	{
		switch (enemy_state_)
		{
		case EnemyState::Wait:
			this->ChangeState(NEW BossStateWait());
			break;

		case EnemyState::Enter:
			this->ChangeState(NEW BossStateEnter());
			break;

		case EnemyState::BodyPress:
			this->ChangeState(NEW BossStateBodyPress());
			break;

		case EnemyState::Shooting:
			this->ChangeState(NEW BossStateShooting());
			break;

		case EnemyState::LaserCannon:
			this->ChangeState(NEW BossStateLaserCannon());
			break;

		case EnemyState::Destroy:
			break;

		default:
			assert(!"BossAIComponent::Update()：ボスがAIが不正な状態です！");
			break;
		}
	}
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void BossAIComponent::EnemyStateController(void)
{
	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_Y))
	{
		this->SetEnemyState(EnemyState::Enter);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_LEFT_SHOULDER))
	{
		this->SetEnemyState(EnemyState::Wait);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_LEFT_TRIGGER))
	{
		this->SetEnemyState(EnemyState::BodyPress);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_RIGHT_SHOULDER))
	{
		this->SetEnemyState(EnemyState::Shooting);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_RIGHT_TRIGGER))
	{
		this->SetEnemyState(EnemyState::LaserCannon);
	}
}

/*-----------------------------------------------------------------------------
/*　ボスのステートマシンの変更
-----------------------------------------------------------------------------*/
void BossAIComponent::ChangeState(BossStateMachine* bossStateMachine)
{
	if (boss_state_machine_ != nullptr)
		delete boss_state_machine_;

	boss_state_machine_ = bossStateMachine;

	if (boss_state_machine_ != nullptr)
		boss_state_machine_->Init();
}

/*-----------------------------------------------------------------------------
/*　ボスの待機行動
-----------------------------------------------------------------------------*/
void BossAIComponent::Wait(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　ボスの登場行動
-----------------------------------------------------------------------------*/
void BossAIComponent::Enter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Wait;
	}
}

/*-----------------------------------------------------------------------------
/*　ボスの体当たり行動
-----------------------------------------------------------------------------*/
void BossAIComponent::BodyPress(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Wait;
	}
}

/*-----------------------------------------------------------------------------
/*　ボスの射撃攻撃行動
-----------------------------------------------------------------------------*/
void BossAIComponent::Shoot(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Wait;
	}
}

/*-----------------------------------------------------------------------------
/*　ボスのレーザー砲攻撃行動
-----------------------------------------------------------------------------*/
void BossAIComponent::LaserCannon(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (motion_state_ == EnemyMotionState::End)
	{
		enemy_state_ = EnemyState::Wait;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/