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

#include "../../../../ImGui/ImGuiManager.h"

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

	static float test_rot = 0.f;
	ImGui::Begin("transform_test");
	ImGui::Text("transform_test:%f", test_rot);
	ImGui::SliderFloat("##test_rot_bar", &test_rot, 0.0f, 360.0f);
	ImGui::Text("transform_deg_:%f", transform_component_->GetAngleYaw());
	ImGui::End();

	transform_component_->IsSetExecuteSlerpRotation(true);
	this->transform_component_->SetRotationYaw(test_rot);

}

/*=============================================================================
/*		End of File
=============================================================================*/