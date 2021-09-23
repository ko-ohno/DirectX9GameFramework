/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBlasterWeaponComponent.cpp] 光線銃武器コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：光線銃武器コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "ChargeBlasterWeaponComponent.h"
#include "../../GameObject.h"
#include "../../Component/RendererComponent/BillboardRendererComponent.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../GameObject/SandBox/Bullet/ChargeBullet.h"
#include "../../../Game.h"
#include "../../GameObject/SandBox/Actor.h"
#include "../../../SandBoxManager/ActorManager.h"

#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ChargeBlasterWeaponComponent::ChargeBlasterWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, is_lockon_(false)
	, is_fire_(false)
	, charge_bullet_(nullptr)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
ChargeBlasterWeaponComponent::~ChargeBlasterWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool ChargeBlasterWeaponComponent::Init(void)
{
	// 銃の発射光の生成
	muzzle_flash_ = NEW EffectRendererComponent(owner_);
	muzzle_flash_->SetEffect(EffectType::ChargeBulletState3Fire);
	muzzle_flash_->SetScale(0.5f);

	// ギズモの生成
	{
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(owner_);
		sphere_gizmo_->SetScale(0.5f);
		sphere_gizmo_->SetVertexColor(0, 255, 255);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (charge_bullet_ != nullptr)
	{
		// 平行移動情報の作成
		D3DXMATRIX translation_matrix;
		D3DXMatrixIdentity(&translation_matrix);
		{
			translation_matrix._41 = position_.x;
			translation_matrix._42 = position_.y;
			translation_matrix._43 = position_.z;

			// 所有者の姿勢情報と合成する
			translation_matrix = translation_matrix * *owner_transform_->GetWorldMatrix();
		}

		ImGui::Begin("BulletCreatePos");
		ImGui::Text("posX:%f", translation_matrix._41);
		ImGui::Text("posY:%f", translation_matrix._42);
		ImGui::Text("posZ:%f", translation_matrix._43);
		ImGui::End();

		if (charge_bullet_->GetChargeBulletState() <= ChargeBulletState::Hold)
		{
			// 弾の座標を更新
			charge_bullet_->SetTranslation(translation_matrix._41, translation_matrix._42, translation_matrix._43);
		}

		if (charge_bullet_->GetChargeBulletState() == ChargeBulletState::Fire)
		{
			if (is_fire_ == false)
			{	
				// エフェクト再生を更新
				muzzle_flash_->Play();
				is_fire_ = true;
			}
		}

		// チャージ弾の状態を確認
		if (charge_bullet_->GetChargeBulletState() == ChargeBulletState::End)
		{
			charge_bullet_->SetGameObjectState(GameObject::State::Dead);
			is_fire_ = false;
		}
	}

	// ギズモの更新
	{
		sphere_gizmo_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/*　チャージ弾の発射処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::CreateChargeBullet(void)
{
	//// 平行移動情報の作成
	D3DXMATRIX translation_matrix;
	D3DXMatrixIdentity(&translation_matrix);
	{
		translation_matrix._41 = position_.x;
		translation_matrix._42 = position_.y;
		translation_matrix._43 = position_.z;

		// 所有者の姿勢情報と合成する
		translation_matrix = translation_matrix * *owner_transform_->GetWorldMatrix();
	}

	// 弾丸の生成
	{
		if (charge_bullet_ != nullptr) { return; }
		auto game = owner_->GetGame();
		charge_bullet_ = NEW ChargeBullet(game);
		charge_bullet_->SetParentGameObject(owner_);
		charge_bullet_->SetTranslation(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}
}

/*-----------------------------------------------------------------------------
/*　発射処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Fire(void)
{	
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::ChargeBulletFire()：チャージ弾のインスタンスが生成されていません！");
	}
	charge_bullet_->Fire();	// チャージ弾の発射
}

/*-----------------------------------------------------------------------------
/*　チャージ弾のインスタンスがあるか確認
-----------------------------------------------------------------------------*/
bool ChargeBlasterWeaponComponent::IsCheckChargeBulletInstance(void)
{
	if (charge_bullet_ == nullptr) { return false; }
	return true;
}

/*-----------------------------------------------------------------------------
/*　チャージ弾の状態の取得処理
-----------------------------------------------------------------------------*/
ChargeBulletState ChargeBlasterWeaponComponent::GetChargeBulletState(void)
{
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::GetChargeBulletState()：チャージ弾のインスタンスが生成されていません！");
	}
	return charge_bullet_->GetChargeBulletState();
}

/*-----------------------------------------------------------------------------
/*　チャージ弾の状態の設定処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::SetChargeBulletState(ChargeBulletState chargeBulletState)
{
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::SetChargeBulletState()：チャージ弾のインスタンスが生成されていません！");
	}
	charge_bullet_->SetChargeBulletState(chargeBulletState);
}

/*=============================================================================
/*		End of File
=============================================================================*/