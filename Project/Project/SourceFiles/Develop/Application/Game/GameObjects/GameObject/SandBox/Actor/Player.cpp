/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Player.cpp] プレイヤーのゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：プレイヤーの処理を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "Player.h"

#include "../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"

// 武器コンポーネント
#include "../../../Component/WeaponComponent/BlasterComponent.h"

// 移動コンポーネント
#include "../../../Component/MoveComponent/PlayerMoveComponent.h"

// 衝突判定コンポーネント
#include "../../../Component/ColliderComponent/OBBColliderComponent.h"
#include "../../../Component/ColliderComponent/SphereColliderComponent.h"

// ギズモコンポーネント
#include "../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

// 入力コンポーネント 
#include "../../../../Input/InputCheck.h"

// ImGUI
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Player::Player(Game* game)
	: Actor(game)
	, effect_after_burner_(nullptr)
	, left_blaster_(nullptr)
	, right_blaster_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Player::~Player(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Player::Init(void)
{
	// プレイヤーの移動コンポーネントの生成
	actor_move_ = NEW  PlayerMoveComponent(this);

	// 描画コンポーネント
	{
		// 自機の表示
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::SpaceShip);
		actor_mesh_->SetEnableLighting(true);
		actor_mesh_->SetScale(0.5f);

		// アフターバーナーの表示
		effect_after_burner_ = NEW EffectRendererComponent(this);
		effect_after_burner_->SetEffect(EffectType::AfterBurner);
		effect_after_burner_->Play();
	}

	// 武器コンポーネント
	{
		// 左の光線銃
		left_blaster_ = NEW BlasterComponent(this);

		// 右の光線銃
		right_blaster_ = NEW BlasterComponent(this);
	}

	//　衝突判定コンポーネント
	{
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_gizmo_->SetVertexColor(255, 255, 0, 255);

		obb_collider_ = NEW OBBColliderComponent(this);
		box_gizmo_ = NEW BoxGizmoRendererComponent(this);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Player::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void Player::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Player::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// エフェクトの位置を調整
	effect_after_burner_->SetTranslation(0.f, 0.1f, -1.1f);

	// 武器の位置を調整
	{
		left_blaster_->SetTranslation(-1.5f, 0.1f, 1.0f);
		right_blaster_->SetTranslation(1.5f, 0.1f, 1.0f);
	}

	if (InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A))
	{
		left_blaster_->Fire();
		right_blaster_->Fire();
	}


	ImGui::Begin("PlayerTransform");
	ImGui::Text("Yaw:%f", transform_component_->GetAngleYaw());
	ImGui::Text("Pitch:%f", transform_component_->GetAnglePitch());
	ImGui::Text("Roll:%f", transform_component_->GetAngleRoll());
	ImGui::End();
}

/*=============================================================================
/*		End of File
=============================================================================*/