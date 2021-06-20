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

	// このAIの所有者がnullptrか？
	if (ai_owner_ != nullptr)
	{
		// ボスの状態を遷移
		auto enemy_state = ai_owner_->GetEnemyState();
		{
			switch (enemy_state)
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

		// このAIの所有者が移動コンポーネントがnullptrか？
		if (enemy_move_ != nullptr)
		{
			if (enemy_move_->GetEnemyMotionState() == EnemyMotionState::End)
			{
				ai_owner_->SetEnemyState(EnemyState::Wait);
			}
			enemy_move_->SetEnemyState(enemy_state);
		}
	}

	// このAIのステートマシンがnullptrか？
	if (boss_state_machine_ != nullptr)
	{
		boss_state_machine_->Update(this, deltaTime);
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

	enemy_move_->SetEnemyState(EnemyState::Wait);
}

/*-----------------------------------------------------------------------------
/*　ボスの登場行動
-----------------------------------------------------------------------------*/
void BossAIComponent::Enter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	enemy_move_->SetEnemyState(EnemyState::Enter);
}

/*-----------------------------------------------------------------------------
/*　ボスの体当たり行動
-----------------------------------------------------------------------------*/
void BossAIComponent::BodyPress(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	enemy_move_->SetEnemyState(EnemyState::BodyPress);
}

/*-----------------------------------------------------------------------------
/*　ボスの射撃攻撃行動
-----------------------------------------------------------------------------*/
void BossAIComponent::Shoot(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	enemy_move_->SetEnemyState(EnemyState::Shooting);
}

/*-----------------------------------------------------------------------------
/*　ボスのレーザー砲攻撃行動
-----------------------------------------------------------------------------*/
void BossAIComponent::LaserCannon(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	enemy_move_->SetEnemyState(EnemyState::LaserCannon);
}

/*=============================================================================
/*		End of File
=============================================================================*/