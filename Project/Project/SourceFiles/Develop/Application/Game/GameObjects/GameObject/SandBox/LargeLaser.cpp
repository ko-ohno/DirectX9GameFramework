/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LargeLaser.cpp] 大型レーザーゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：大型レーザーゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "LargeLaser.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../Component/ColliderComponent/OBBColliderComponent.h"



/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
LargeLaser::LargeLaser(Game* game)
	: SandBox(game)
	, owner_transform_(nullptr)
	, large_laser_(nullptr)
	, obb_collider_(nullptr)
	, box_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
LargeLaser::~LargeLaser(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool LargeLaser::Init(void)
{
	// レーザーのエフェクト
	{
		large_laser_ = NEW EffectRendererComponent(this);
		large_laser_->SetEffect(EffectType::RedLaser);

		D3DXMATRIX rot_mat;
		D3DXMatrixIdentity(&rot_mat);
		D3DXMatrixRotationX(&rot_mat, Math::ToRadian(90.f));
		large_laser_->SetRotationMatrix(rot_mat);
		large_laser_->SetScale(1.5f);
		large_laser_->Play();
	}

	// 衝突判定の作成
	{
		const float laser_length_ = 50.f;
		const float laser_scale_  = 3.f;

		obb_collider_ = NEW OBBColliderComponent(this);
		obb_collider_->SetDirLength(laser_scale_, AxisType::X);
		obb_collider_->SetDirLength(laser_length_, AxisType::Y);
		obb_collider_->SetDirLength(laser_scale_, AxisType::Z);

		box_gizmo_ = NEW BoxGizmoRendererComponent(this);
		box_gizmo_->SetVertexColor(0, 255, 255, 128);
		box_gizmo_->SetScaleX(laser_scale_);
		box_gizmo_->SetScaleY(laser_length_);
		box_gizmo_->SetScaleZ(laser_scale_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void LargeLaser::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void LargeLaser::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void LargeLaser::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 所有者の姿勢を通知する
	transform_component_ = owner_transform_;
}

/*=============================================================================
/*		End of File
=============================================================================*/