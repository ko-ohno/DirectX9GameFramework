/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LargeLaser.cpp] 大型レーザーゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：大型レーザーゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "LargeLaser.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../Component/ColliderComponent/OBBColliderComponent.h"



/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
LargeLaser::LargeLaser(Game* game)
	: Bullet(game)
	, owner_transform_(nullptr)
	, large_laser_(nullptr)
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
	// 生成座標を初期化
	{
		this->transform_component_->SetTranslationY(-100.f);
	}

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
		// レーザーの判定の長さ
		const float laser_length = 30.f;

		// レーザーの判定の各縮率
		const float laser_scale  = 1.5f;

		obb_collider_ = NEW OBBColliderComponent(this);
		obb_collider_->SetDirLength(laser_scale, AxisType::X);
		obb_collider_->SetDirLength(laser_length, AxisType::Y);
		obb_collider_->SetDirLength(laser_scale, AxisType::Z);

		obb_collider_gizmo_ = NEW BoxGizmoRendererComponent(this);
		obb_collider_gizmo_->SetScaleX(laser_scale);
		obb_collider_gizmo_->SetScaleY(laser_length);
		obb_collider_gizmo_->SetScaleZ(laser_scale);
		obb_collider_gizmo_->SetVertexColor(0, 255, 255, 128);
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
	
	//所有者が不明だった場合
	const bool is_owner_type_unkown = (parent_game_object_type_ == GameObject::TypeID::None);
	if (is_owner_type_unkown)
	{
		// 親ゲームオブジェクトの種類を記憶
		parent_game_object_type_ = this->GetParentGameObject()->GetType();
	}

	const bool is_owner_destroy = (this->GetParentGameObject()->GetGameObjectState() == GameObject::State::Destroy);
	if (is_owner_destroy)
	{
		// 地震を破棄
		this->SetGameObjectState(GameObject::State::Dead);

		// エフェクトの再生を停止
		large_laser_->Stop();
		return;
	}

	// 所有者の姿勢を通知する
	transform_component_ = owner_transform_;
}

/*=============================================================================
/*		End of File
=============================================================================*/