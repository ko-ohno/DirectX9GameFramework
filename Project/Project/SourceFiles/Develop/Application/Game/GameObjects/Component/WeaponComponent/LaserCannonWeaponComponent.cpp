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
#include "../../GameObject/SandBox/Bullet/LargeLaser.h"

#include "../RendererComponent/EffectRendererComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
LaserCannonWeaponComponent::LaserCannonWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, enemy_motion_state_(EnemyMotionState::None)
	, large_laser_(nullptr)
	, is_fire_(false)
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
	// 武器の位置を表示するギズモ
	{
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(owner_);
		sphere_gizmo_->SetScale(2.f);
		sphere_gizmo_->SetVertexColor(0, 128, 255);
		//sphere_gizmo_->IsSetDrawable(false);
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

	if (large_laser_ != nullptr)
	{
		if (enemy_motion_state_ == EnemyMotionState::Complete)
		{
			//　発射したかのフラグを初期化
			is_fire_ = false;

			//　役目を終えたゲームオブジェクトとする
			large_laser_->SetGameObjectState(GameObject::State::Dead);
		}
	}
}

/*-----------------------------------------------------------------------------
/*　レーザーの発射処理
-----------------------------------------------------------------------------*/
void LaserCannonWeaponComponent::Shoot(void)
{
	// レーザーを発射していないか
	if (is_fire_ == false)
	{
		// レーザーを生成
		auto game = owner_->GetGame();
		large_laser_ = NEW LargeLaser(game);
		large_laser_->SetTransfrom(owner_transform_);

		// 発射したことを記憶
		is_fire_ = true;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/