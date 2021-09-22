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
#include "../ChargeBullet.h"

// 値コンポーネント
#include "../../../Component/ParameterComponent/IntParameterComponent.h"
#include "../../../Component/ParameterComponent/FloatParameterComponent.h"

// 描画コンポーネント
#include "../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../../Component/RendererComponent/BillboardRendererComponent.h"

// 武器コンポーネント
#include "../../../Component/WeaponComponent/BlasterWeaponComponent.h"
#include "../../../Component/WeaponComponent/ChargeBlasterWeaponComponent.h"

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
	, player_move_(nullptr)
	, effect_after_burner_(nullptr)
	, near_reticle_(nullptr)
	, far_reticle_(nullptr)
	, lockon_reticle_(nullptr)
	, left_blaster_(nullptr)
	, right_blaster_(nullptr)
	, charge_blaster_(nullptr)
	, max_hp_param_(nullptr)
	, hp_param_(nullptr)
	, is_blaster_fire_(false)
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
				far_reticle_ = NEW BillboardRendererComponent(this, 290);
				far_reticle_->SetTexture(TextureType::FarReticle);
				far_reticle_->SetVertexColor(0, 255, 0, 255);
				far_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// レティクルの性質の調整
				far_reticle_->SetScale(1.2f);
				far_reticle_->SetTranslationZ(10.f);
			}

			//　手前のレティクル
			{
				near_reticle_ = NEW BillboardRendererComponent(this, 290);
				near_reticle_->SetTexture(TextureType::NearReticle);
				near_reticle_->SetVertexColor(0, 255, 0, 255);
				near_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// レティクルの性質の調整
				near_reticle_->SetScale(1.4f);
				near_reticle_->SetTranslationZ(9.f);
				//near_reticle_->GetPosition();
			}

			//　ロックオンのレティクル
			{
				lockon_reticle_ = NEW BillboardRendererComponent(this, 290);
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

		// チャージ弾用の光線銃
		charge_blaster_ = NEW ChargeBlasterWeaponComponent(this);
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

	// 値コンポーネントの作成
	{
		// 最大HP
		max_hp_param_ = NEW FloatParameterComponent(this);
		max_hp_param_->SetParameterType(ParameterType::MaxHP);
		max_hp_param_->SetFloat(max_hit_point_);

		// HP
		hp_param_ = NEW FloatParameterComponent(this);
		hp_param_->SetParameterType(ParameterType::HP);
		hp_param_->SetFloat(hit_point_);
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
	// チャージ弾の武器コンポーネントの確認
	if(charge_blaster_ == nullptr)
	{
		assert(!"Player::InputGameObject()：チャージ弾の武器コンポーネントが、nullptrでした！");
	}

	// 弾を発射するか
	is_blaster_fire_ = InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A);

	// ボタンを長押ししたら
	if (charge_blaster_->IsCheckChargeBulletInstance() == false)
	{
		if (InputCheck::XInputRepeat(PadIndex::Pad1, XInputButton::XIB_A, 2.f))
		{
			charge_blaster_->CreateChargeBullet();
		}
	}

	if (charge_blaster_->IsCheckChargeBulletInstance() == true)
	{
		// ボタンを離したら
		if (charge_blaster_->GetChargeBulletState() == ChargeBulletState::Hold)
		{
			if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_A) == false)
			{
				charge_blaster_->Fire();
			}
		}
	}
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Player::UpdateGameObject(float deltaTime)
{
	// チャージ弾の武器コンポーネントの確認
	if (charge_blaster_ == nullptr)
	{
		assert(!"Player::UpdateWeapon():チャージ弾の武器コンポーネントが、nullptrでした！");
	}

	// 値コンポーネントの更新処理
	this->UpdateParameter(deltaTime);

	// 武器の更新処理
	this->UpdateWeapon(deltaTime);

	// エフェクトの更新処理
	this->UpdatePirticleEffect(deltaTime);

	ImGui::Begin("PlayerTransform");
	ImGui::Text("Yaw:%f", transform_component_->GetAngleYaw());
	ImGui::Text("Pitch:%f", transform_component_->GetAnglePitch());
	ImGui::Text("Roll:%f", transform_component_->GetAngleRoll());

	auto pos = *transform_component_->GetPosition();
	ImGui::Text("PosX:%f", pos.x);
	ImGui::Text("PosY:%f", pos.y);
	ImGui::Text("PosZ:%f", pos.z);

	ImGui::End();



	// 1フレーム前の情報を更新
	hit_point_old_ = hit_point_;
}

/*-----------------------------------------------------------------------------
/* 値コンポーネントの更新処理
-----------------------------------------------------------------------------*/
void Player::UpdateParameter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const bool is_nullptr_max_hp_param	= (max_hp_param_ == nullptr);
	const bool is_nullptr_hp_param		= (hp_param_ == nullptr);

	// 最大HPの値コンポーネントのnullチェック
	if (is_nullptr_max_hp_param)
	{
		assert(!"Player::UpdateParameter():値コンポーネント:max_hp_param_ が”nullptr”でした");
		return;
	}

	// HPの値コンポーネントのnullチェック
	if (is_nullptr_hp_param)
	{
		assert(!"Player::UpdateParameter():値コンポーネント:hp_param_ が”nullptr”でした");
		return;
	}

	// 最大HPの更新
	max_hp_param_->SetFloat(max_hit_point_);

	// 現在のHPの更新
	hp_param_->SetFloat(hit_point_);
}

/*-----------------------------------------------------------------------------
/* 武器の更新処理
-----------------------------------------------------------------------------*/
void Player::UpdateWeapon(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 武器の位置を調整
	{
		left_blaster_->SetTranslation(-1.5f, 0.1f, 1.0f);
		right_blaster_->SetTranslation(1.5f, 0.1f, 1.0f);
		charge_blaster_->SetTranslation(0.f, 0.1f, 3.0f);
	}

	// 弾の発射
	if (is_blaster_fire_)
	{
		left_blaster_->Fire();
		right_blaster_->Fire();
		is_blaster_fire_ = false;
	}
}

/*-----------------------------------------------------------------------------
/* エフェクトの更新処理
-----------------------------------------------------------------------------*/
void Player::UpdatePirticleEffect(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// エフェクトの位置を調整
	{
		effect_after_burner_->SetTranslation(0.f, 0.1f, -1.1f);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/