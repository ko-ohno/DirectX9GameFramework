/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Boss.cpp] ボスゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../../StdAfx.h"
#include "Boss.h"

// 移動コンポーネント
#include "../../../../Component/MoveComponent/EnemyMoveComponent/BossMoveComponent.h"

// ボスAIコンポーネント
#include "../../../../Component/AIComponent/BossAIComponent/BossAIComponent.h"

// メッシュコンポーネント
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"

// 球の衝突判定
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// ボックスの衝突判定
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

// 入力チェック
#include "../../../../../Input/InputCheck.h"

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"


#include "../../../../../Game.h"
#include "../../../../../SandBoxManager/ActorManager.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Boss::Boss(Game* game)
	: Enemy(game)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Boss::~Boss(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Boss::Init(void)
{
	// ボスのAIを生成 
	enemy_ai_ = NEW BossAIComponent(this);

	// ボスの移動コンポーネントを生成
	enemy_move_ = NEW BossMoveComponent(this);

	{
		// ボスのメッシュ生成
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyBoss);
		actor_mesh_->SetEnableLighting(true);			// ライティングを有効にする

		// 生成座標を調整
		this->transform_component_->SetTranslationZ(15.f);
	}

	// ボスの状態を初期化
	{
		// AIの所有者を通知
		enemy_ai_->SetEnemyAIOwner(this);

		// 移動コンポーネントを通知
		enemy_ai_->SetOwnerMoveComponent(this->enemy_move_);

		// 敵の状態を初期化
		this->SetEnemyState(EnemyState::Enter);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Boss::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの入力処理
-----------------------------------------------------------------------------*/
void Boss::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* overrideで自分自身を更新
-----------------------------------------------------------------------------*/
void Boss::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// AIコンポーネントにボスのHPを通知する
	{
		enemy_ai_->SetHitPoint(this->GetHitPoint());
	}

	// AIコンポーネントから敵の行動状態を取得
	auto ai_state = enemy_ai_->GetEnemyState();
	{
		// AIコンポーネントの情報から、次の移動モーションを決定する
	}



	// 移動コンポーネントから移動モーション状態を取得
	auto move_motion_state = enemy_move_->GetEnemyMotionState();
	{
		// 移動コンポーネントの情報から、次の移動モーションを決定する
	}


	//boss_ai_->ChangeState(NEW BossStateEnter());
	//boss_ai_->ChangeState(NEW BossStateWait());
	//boss_ai_->ChangeState(NEW BossStateBodyblow());
	//boss_ai_->ChangeState(NEW BossStateShoot());
	//boss_ai_->ChangeState(NEW BossStateLaserCannon());

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

	//// エネミーの状態ステート
	//{
	//	switch (enemy_state_)
	//	{
	//	case EnemyState::Wait:
	//		enemy_move_->SetMoveActionState(EnemyState::Wait);
	//		break;
	//
	//	case EnemyState::Enter:
	//		enemy_move_->SetMoveActionState(EnemyState::Enter);
	//		break;

	//	case EnemyState::BodyPress:
	//		enemy_move_->SetMoveActionState(EnemyState::BodyPress);
	//		break;

	//	case EnemyState::Shooting:
	//		enemy_move_->SetMoveActionState(EnemyState::Shooting);
	//		break;

	//	case EnemyState::LaserCannon:
	//		enemy_move_->SetMoveActionState(EnemyState::LaserCannon);
	//		break;

	//	case EnemyState::Destroy:
	//		// 倒されたときのモーション
	//		enemy_move_->SetMoveActionState(EnemyState::Wait);
	//		break;

	//	default:
	//		assert(!"Boss::UpdateGameObject()：ボスが不正な状態をしています！");
	//		break;
	//	}
	//}

	//// 自身の状態をAIに通知
	//{
	//	if (enemy_move_->GetEnemyMotionState() == EnemyMotionState::End)
	//	{
	//		boss_ai_->SetEnemyState(EnemyState::Wait);
	//	}
	//	
	//	boss_ai_->SetHitPoint(this->GetHitPoint());
	//	this->SetEnemyState(boss_ai_->GetEnemyState());
	//}
}

/*=============================================================================
/*		End of File
=============================================================================*/