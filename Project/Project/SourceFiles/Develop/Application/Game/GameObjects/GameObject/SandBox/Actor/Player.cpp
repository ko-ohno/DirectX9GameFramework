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

// 描画コンポーネント
#include "../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../../Component/RendererComponent/BillboardRendererComponent.h"

// 武器コンポーネント
#include "../../../Component/WeaponComponent/BlasterWeaponComponent.h"

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
	, near_reticle_(nullptr)
	, far_reticle_(nullptr)
	, lockon_reticle_(nullptr)
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
	player_move_ = NEW  PlayerMoveComponent(this);

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

		// レティクルの設定
		{
			// 遠くのレティクル
			{
				far_reticle_ = NEW BillboardRendererComponent(this);
				far_reticle_->SetTexture(TextureType::FarReticle);
				far_reticle_->SetVertexColor(0, 255, 0, 255);
				far_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// レティクルの性質の調整
				far_reticle_->SetScale(1.2f);
				far_reticle_->SetTranslationZ(10.f);
			}

			//　手前のレティクル
			{
				near_reticle_ = NEW BillboardRendererComponent(this);
				near_reticle_->SetTexture(TextureType::NearReticle);
				near_reticle_->SetVertexColor(0, 255, 0, 255);
				near_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// レティクルの性質の調整
				near_reticle_->SetScale(1.4f);
				near_reticle_->SetTranslationZ(9.f);
			}

			//　ロックオンのレティクル
			{
				lockon_reticle_ = NEW BillboardRendererComponent(this);
				lockon_reticle_->SetTexture(TextureType::NearReticle);
				lockon_reticle_->SetVertexColor(0, 255, 0, 255);
				lockon_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// レティクルの性質の調整
				lockon_reticle_->SetScale(1.4f);
				lockon_reticle_->SetTranslationZ(9.f);
			}
		}
	}

	// 武器コンポーネント
	{
		// 左の光線銃
		left_blaster_ = NEW BlasterWeaponComponent(this);

		// 右の光線銃
		right_blaster_ = NEW BlasterWeaponComponent(this);
	}

	//　衝突判定コンポーネント
	{
		// 球の衝突判定
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_gizmo_->SetVertexColor(255, 255, 0, 255);

		// OBBの衝突判定
		obb_collider_ = NEW OBBColliderComponent(this);
		box_gizmo_ = NEW BoxGizmoRendererComponent(this);

		// ロックオンの箱の衝突判定
		{
			const float lockon_langth_ = 20.f;

			lockon_collider_ = NEW OBBColliderComponent(this);
			lockon_collider_->SetDirLength(1.1f, AxisType::X);
			lockon_collider_->SetDirLength(1.1f, AxisType::Y);
			lockon_collider_->SetDirLength(lockon_langth_, AxisType::Z);

			lockon_gizmo_ = NEW BoxGizmoRendererComponent(this);
			lockon_gizmo_->SetVertexColor(0, 255, 255, 128);
			lockon_gizmo_->SetScaleX(1.1f);
			lockon_gizmo_->SetScaleY(1.1f);
			lockon_gizmo_->SetScaleZ(lockon_langth_);
		}
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
		left_blaster_->BulletFire();
		right_blaster_->BulletFire();
	}

	ImGui::Begin("PlayerTransform");
	ImGui::Text("Yaw:%f", transform_component_->GetAngleYaw());
	ImGui::Text("Pitch:%f", transform_component_->GetAnglePitch());
	ImGui::Text("Roll:%f", transform_component_->GetAngleRoll());

	auto pos = *transform_component_->GetPosition();
	ImGui::Text("PosX:%f", pos.x);
	ImGui::Text("PosY:%f", pos.y);
	ImGui::Text("PosZ:%f", pos.z);

	ImGui::End();
}

/*=============================================================================
/*		End of File
=============================================================================*/