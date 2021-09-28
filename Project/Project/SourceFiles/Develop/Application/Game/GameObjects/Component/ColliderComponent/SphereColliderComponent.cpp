/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereColliderComponent.cpp] スフィアコライダのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スフィアコライダのコンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "SphereColliderComponent.h"
#include "../../GameObject.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SphereColliderComponent::SphereColliderComponent(GameObject* owner, int updateOrder)
	: ColliderComponent(owner, updateOrder)
	, radius_(0.5f)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SphereColliderComponent::~SphereColliderComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void SphereColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// このコンポーネントの所有者の座標を取得
	Vector3 owner_position = *owner_->GetTransform()->GetPosition();

	// 衝突判定の位置情報の更新
	position_ = owner_position;
}

/*=============================================================================
/*		End of File
=============================================================================*/