/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BlasterWeaponComponent.cpp] 光線銃武器コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：光線銃武器コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "BlasterWeaponComponent.h"
#include "../../GameObject.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../GameObject/SandBox/Bullet/NormalBullet.h"
#include "../../../Game.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BlasterWeaponComponent::BlasterWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, muzzle_flash_(nullptr)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
BlasterWeaponComponent::~BlasterWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BlasterWeaponComponent::Init(void)
{
	// 弾の発射エフェクト
	{
		muzzle_flash_ = NEW EffectRendererComponent(owner_);
		muzzle_flash_->SetEffect(EffectType::MuzzluFrashBlue);

		// 所有者からの影響を無効に
		muzzle_flash_->IsSetOwnerTransfromOrder(false);
	}

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
void BlasterWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void BlasterWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void BlasterWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ギズモの更新
	{
		sphere_gizmo_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/*　発射処理
-----------------------------------------------------------------------------*/
void BlasterWeaponComponent::Fire(void)
{	
	// 平行移動情報の作成
	D3DXMATRIX translation_matrix;
	D3DXMatrixIdentity(&translation_matrix);

	translation_matrix._41 = position_.x;
	translation_matrix._42 = position_.y;
	translation_matrix._43 = position_.z;

	// 所有者の姿勢情報と合成する
	translation_matrix = translation_matrix  * *owner_transform_->GetWorldMatrix();

	// エフェクトの再生
	{
		// エフェクトの種類を設定
		muzzle_flash_->SetEffect(EffectType::MuzzluFrashBlue);

		// 発射光エフェクトの再生
		muzzle_flash_->Play(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}

	// 弾丸の生成
	{
		auto game = owner_->GetGame();
		auto bullet = NEW NormalBullet(game);
		bullet->SetParentGameObject(owner_);
		bullet->SetCreatePosition(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}
}
/*=============================================================================
/*		End of File
=============================================================================*/