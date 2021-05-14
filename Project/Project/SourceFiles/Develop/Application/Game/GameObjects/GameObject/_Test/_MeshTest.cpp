/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshTest.cpp] メッシュテスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メッシュテスト用ゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "_MeshTest.h"
#include "../../Component/RendererComponent/StdMeshRendererComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
MeshTest::MeshTest(Game* game)
	: GameObject(game)
{
	//ゲームレイヤーで描画
	this->renderer_layer_type_ = RendererLayerType::Game;

	std_mesh_renderer_component_ = NEW StdMeshRendererComponent(this);
	std_mesh_renderer_component_->SetMesh(XFileMeshType::Box);

	std_mesh_renderer_component_a = NEW StdMeshRendererComponent(this);
	std_mesh_renderer_component_a->SetMesh(XFileMeshType::BlueBullet);
	std_mesh_renderer_component_a->SetTranslationX(-5.f);


	std_mesh_renderer_component_b = NEW StdMeshRendererComponent(this);
	std_mesh_renderer_component_b->SetMesh(XFileMeshType::Cylinder);
	std_mesh_renderer_component_b->SetTranslationX(5.f);

	std_mesh_renderer_component_c = NEW StdMeshRendererComponent(this);
	std_mesh_renderer_component_c->SetMesh(XFileMeshType::AirPlane);
	std_mesh_renderer_component_c->SetTranslationY(-2.f);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
MeshTest::~MeshTest(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool MeshTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void MeshTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void MeshTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void MeshTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/