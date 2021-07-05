/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyMoveComponent.cpp] ボスの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスの移動コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "WeakEnemyMoveComponent.h"
#include "../../../GameObject.h"
#include "../../../../../Math.h"
#include "../../../GameObject/SandBox/Actor/Enemy.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
WeakEnemyMoveComponent::WeakEnemyMoveComponent(GameObject* owner, int updateOrder)
	: EnemyMoveComponent(owner, updateOrder)
	, position_(0.f, 0.f, 0.f)
	, yaw_(0.f)
	, pitch_(0.f)
	, roll_(0.f)
	, execute_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ 
-----------------------------------------------------------------------------*/
WeakEnemyMoveComponent::~WeakEnemyMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool WeakEnemyMoveComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void WeakEnemyMoveComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 各回転値の取得
	yaw_   = owner_transform_->GetAngleYaw();
	pitch_ = owner_transform_->GetAnglePitch();
	roll_  = owner_transform_->GetAngleRoll();

	// 線形球面保管を行うフラグをONに
	{
		owner_transform_->IsSetExecuteSlerp(true);
	}

	// 自身の状態を表記
	ImGui::Begin("boss_move_state");
	{
		switch (enemy_state_)
		{
		case EnemyState::Enter:
			ImGui::Text("enter");
			break;

		case EnemyState::Wait:
			ImGui::Text("wait");
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
		}
	}
	ImGui::End();

	//// 敵の状態更新
	//switch (enemy_state_)
	//{
	//case EnemyState::Enter:
	//	this->MoveActionEnter(deltaTime);
	//	break;
	//
	//case EnemyState::Wait:
	//	this->MoveActionWait(deltaTime);
	//	break;

	//case EnemyState::BodyPress:
	//	this->MoveActionBodyPress(deltaTime);
	//	break;

	//case EnemyState::Shooting:
	//	this->MoveActionShoot(deltaTime);
	//	break;
	//
	//case EnemyState::LaserCannon:
	//	this->MoveActionLaserCannon(deltaTime);
	//	break;

	//default:
	//	assert(!"WeakEnemyMoveComponent::Update()：ボスが不正な行動ステートにあります！");
	//	break;
	//}

	//ボスのステートの更新
	enemy_state_old_ = enemy_state_;
}


/*=============================================================================
/*		End of File
=============================================================================*/