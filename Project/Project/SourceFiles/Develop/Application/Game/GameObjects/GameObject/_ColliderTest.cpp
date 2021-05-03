/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderTest.cpp] 衝突判定テスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：衝突判定テスト用ゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "_ColliderTest.h"
#include "../../Manager/ColliderManager.h"

#include "../Component/RendererComponent/GizmoRendererComponent/GridGizmoRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ColliderTest::ColliderTest(Game* game)
	: GameObject(game)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

	game->GetColliderManager()->GetColliderComponentList();

	grid_gizmo_renderer_component_ = NEW GridGizmoRendererComponent(this);

	box_gizmo_renderer_component_ = NEW BoxGizmoRendererComponent(this);

	sphere_gizmo_renderer_component_ = NEW SphereGizmoRendererComponent(this);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
ColliderTest::~ColliderTest(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
ColliderTest* ColliderTest::Create(Game* game)
{
	return NEW ColliderTest(game);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool ColliderTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void ColliderTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void ColliderTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void ColliderTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	box_gizmo_renderer_component_->SetTranslationY( 3.f);
	box_gizmo_renderer_component_->SetTranslationX(-1.5f);
	box_gizmo_renderer_component_->SetVertexColor(255, 0, 0, 255);

	sphere_gizmo_renderer_component_->SetTranslationY(3.f);
	sphere_gizmo_renderer_component_->SetTranslationX(1.5f);
	sphere_gizmo_renderer_component_->SetVertexColor(0, 0, 255, 255);


	grid_gizmo_renderer_component_->SetTranslation(0.f, 0.f, 0.f);
	grid_gizmo_renderer_component_->SetVertexColor();


}

/*=============================================================================
/*		End of File
=============================================================================*/