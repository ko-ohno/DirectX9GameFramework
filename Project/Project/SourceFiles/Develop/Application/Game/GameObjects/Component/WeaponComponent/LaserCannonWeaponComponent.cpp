/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Hoge.cpp] レーザー砲武器コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：レーザー砲武器コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "LaserCannonWeaponComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"
#include "../../GameObject/SandBox/LargeLaser.h"

#include "../RendererComponent/EffectRendererComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
LaserCannonWeaponComponent::LaserCannonWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, large_laser_(nullptr)
	, test_effect_(nullptr)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
LaserCannonWeaponComponent::~LaserCannonWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool LaserCannonWeaponComponent::Init(void)
{
	test_effect_ = NEW EffectRendererComponent(owner_);
	test_effect_->SetEffect(EffectType::RedLaser);

	D3DXMATRIX rot_mat;
	D3DXMatrixIdentity(&rot_mat);
	D3DXMatrixRotationX(&rot_mat, Math::ToRadian(90.f));
	test_effect_->SetRotationMatrix(rot_mat);
	test_effect_->Play();


	{
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(owner_);
		sphere_gizmo_->SetScale(2.f);
		sphere_gizmo_->SetVertexColor(0, 128, 255);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void LaserCannonWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void LaserCannonWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void LaserCannonWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);



	/*if (large_laser_ == nullptr)
	{
		auto game = owner_->GetGame();
		large_laser_ = NEW LargeLaser(game);

	}*/
}

/*=============================================================================
/*		End of File
=============================================================================*/