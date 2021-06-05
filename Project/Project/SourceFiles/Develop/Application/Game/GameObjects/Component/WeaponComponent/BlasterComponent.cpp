/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BlasterComponent.cpp] 光線銃コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：光線銃コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "BlasterComponent.h"
#include "../../GameObject.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../GameObject/SandBox/Bullet.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BlasterComponent::BlasterComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, muzzle_flash_(nullptr)
{
	muzzle_flash_ = NEW EffectRendererComponent(owner);
	muzzle_flash_->SetEffect(EffectType::MuzzluFrashGreen);

	// 所有者からの影響を無効に
	muzzle_flash_->SetOwnerTransfromOrder(false);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
BlasterComponent::~BlasterComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BlasterComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void BlasterComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void BlasterComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void BlasterComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*　発射処理
-----------------------------------------------------------------------------*/
void BlasterComponent::Fire(void)
{	
	// 平行移動情報の作成
	D3DXMATRIX translation_matrix;
	D3DXMatrixIdentity(&translation_matrix);

	translation_matrix._41 = position_.x;
	translation_matrix._42 = position_.y;
	translation_matrix._43 = position_.z;

	// 所有者の姿勢情報と合成する
	translation_matrix = translation_matrix  * *owner_transform_->GetWorldMatrix();

	// 発射光エフェクトの再生
	muzzle_flash_->Play(translation_matrix._41, translation_matrix._42, translation_matrix._43);

	//
	// エフェクトの再生時に、生成座標そのままだと、ちらつきが残ってしまうバグがあるので注意
	//
	//muzzle_flash_->Play(position_);

	// 弾丸の生成
	{
		auto bullet = NEW Bullet(owner_->GetGame());

		bullet->SetCreatePosition(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/