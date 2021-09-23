/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[OBBColliderComponent.cpp] OBBコライダコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：OBBコライダコンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "OBBColliderComponent.h"
#include "../../GameObject.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
OBBColliderComponent::OBBColliderComponent(GameObject* owner, int updateOrder)
	: ColliderComponent(owner, updateOrder)
	, position_(0.f, 0.f, 0.f)
	, offset_position_(0.f, 0.f, 0.f)
	, axis_element_{
		{ 1.f, 0.f, 0.f}
		, { 0.f, 1.f, 0.f}
		, { 0.f, 0.f, 1.f}
	  }
	, axis_length_{ 0.5f, 0.5f, 0.5f }
{
	position_.y_ = -100.f;
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
OBBColliderComponent::~OBBColliderComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void OBBColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 衝突判定の位置情報の更新
	position_ = offset_position_ + *owner_->GetTransform()->GetPosition();

	// OBBの姿勢の更新
	auto rotate_matrix = *owner_->GetTransform()->GetRotationMatrix();
	this->SetDirElement(rotate_matrix);
}

/*=============================================================================
/*		End of File
=============================================================================*/