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
#include "../../../../../ImGui/ImGuiManager.h"


// 配列のインデックス名
enum class EnemyStateArrayIndex
{
	None = -1
	, BodyPress
	, Shooting
	, LaserCannon

	, Max
};

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BossAIComponent::BossAIComponent(GameObject* owner, int updateOrder)
	: EnemyAIComponent(owner, updateOrder)
	, state_exe_time_(0.f)
	, array_index_(0)
	, is_state_change_(false)
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
	// ステートの登録
	{
		enemy_state_array_[static_cast<int>(EnemyStateArrayIndex::BodyPress)]   = EnemyState::BodyPress;
		enemy_state_array_[static_cast<int>(EnemyStateArrayIndex::Shooting)]	= EnemyState::Shooting;
		enemy_state_array_[static_cast<int>(EnemyStateArrayIndex::LaserCannon)] = EnemyState::LaserCannon;
	}
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
	// 敵のステートを操作する
	this->EnemyStateController(deltaTime);
	
#ifdef DEBUG_MODE_
	ImGui::Begin("boss_ai_state");
	{
		switch (enemy_state_)
		{
		case EnemyState::Idle:
			ImGui::Text("wait");
			break;

		case EnemyState::Enter:
			ImGui::Text("enter");
			break;

		case EnemyState::BodyPress:
			ImGui::Text("body_press");
			break;

		case EnemyState::Shooting:
			ImGui::Text("shooting");
			break;

		case EnemyState::LaserCannon:
			ImGui::Text("laser_cannon");
			break;

		case EnemyState::Destroy:
			break;

		default:
			assert(!"BossAIComponent::Update()：ボスがAIが不正な状態です！");
			break;
		}
	}
	ImGui::End();
#endif

	switch (enemy_state_)
	{
	case EnemyState::Idle:
		this->ChangeState(NEW BossStateIdle());
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
		owner_->SetGameObjectState(GameObject::State::Destroy);
		break;

	default:
		assert(!"BossAIComponent::Update()：ボスがAIが不正な状態です！");
		break;
	}

	// このAIのステートマシンがnullptrか？
	if (boss_state_machine_ != nullptr)
	{
		boss_state_machine_->Update(this, deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/*　ステートの制御処理
-----------------------------------------------------------------------------*/
void BossAIComponent::EnemyStateController(float deltaTime)
{
	const bool is_controll = false;
	if (is_controll)
	{
		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_Y))
		{
			this->SetEnemyState(EnemyState::Enter);
		}

		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_LEFT_SHOULDER))
		{
			this->SetEnemyState(EnemyState::Idle);
		}

		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_LEFT_TRIGGER))
		{
			this->SetEnemyState(EnemyState::BodyPress);
		}

		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_RIGHT_SHOULDER))
		{
			this->SetEnemyState(EnemyState::Shooting);
		}

		if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_RIGHT_TRIGGER))
		{
			this->SetEnemyState(EnemyState::LaserCannon);
		}
	}
	else
	{
		state_exe_time_ += deltaTime;

		if ((this->GetEnemyState() == EnemyState::Idle)
			&& (is_state_change_ == false))
		{
			array_index_ += 1;
			is_state_change_ = true;
		}

		const float MAX_WAIT_TIME = 3.f;
		if (is_state_change_ == true)
		{
			if (state_exe_time_ >= MAX_WAIT_TIME)
			{
				this->SetEnemyState(enemy_state_array_[array_index_]);
				is_state_change_ = false;
				state_exe_time_ = 0.f;
			}
		}

		if (array_index_ >= MAX_STATE_ARRAY_SIZE)
		{
			array_index_ = 0;
		}
	}
}

/*-----------------------------------------------------------------------------
/*　ボスのステートマシンの変更
-----------------------------------------------------------------------------*/
void BossAIComponent::ChangeState(BossEnemyStateMachine* bossStateMachine)
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
void BossAIComponent::Idle(float deltaTime)
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
		enemy_state_ = EnemyState::Idle;
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
		enemy_state_ = EnemyState::Idle;
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
		enemy_state_ = EnemyState::Idle;
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
		enemy_state_ = EnemyState::Idle;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/