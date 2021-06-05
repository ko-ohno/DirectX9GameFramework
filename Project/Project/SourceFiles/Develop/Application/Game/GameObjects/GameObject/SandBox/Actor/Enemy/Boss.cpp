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

// メッシュコンポーネント
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../../Component/MoveComponent/BossMoveComponent.h"

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
	// ボスの移動コンポーネントを生成
	actor_move_ = NEW BossMoveComponent(this);

	{
		// ボスのメッシュ生成
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyBoss);
		actor_mesh_->SetEnableLighting(true);			// ライティングを有効にする


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

	static float value = 0.f;
	ImGui::Begin("Boss");
	ImGui::SliderFloat("##vertical", &value , -180.f, 180.0f);
	ImGui::End();

	this->transform_component_->SetRotationPitch(value);

}

/*=============================================================================
/*		End of File
=============================================================================*/