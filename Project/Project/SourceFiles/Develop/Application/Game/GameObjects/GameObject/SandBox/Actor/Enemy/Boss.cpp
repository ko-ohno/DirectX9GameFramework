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
#include "../../../../Component/MoveComponent/BossMoveComponent.h"

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

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"

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
	actor_state_ = ActorState::Wait;

	// ボスの移動コンポーネントを生成
	actor_move_ = NEW BossMoveComponent(this);

	// ボスのAIを生成 
	boss_ai_ = NEW BossAIComponent(this);

	{
		// ボスのメッシュ生成
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyBoss);
		actor_mesh_->SetEnableLighting(true);			// ライティングを有効にする

		this->transform_component_->SetTranslationZ(15.f);
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

	//boss_ai_->ChangeState(NEW BossStateEnter());

	//boss_ai_->ChangeState(NEW BossStateWait());



	//boss_ai_->ChangeState(NEW BossStateBodyblow());
	//boss_ai_->ChangeState(NEW BossStateShoot());
	//boss_ai_->ChangeState(NEW BossStateLaserCannon());

}

/*=============================================================================
/*		End of File
=============================================================================*/