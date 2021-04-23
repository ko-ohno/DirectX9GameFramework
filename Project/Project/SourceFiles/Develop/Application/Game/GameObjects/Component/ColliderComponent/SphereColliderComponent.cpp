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

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SphereColliderComponent::SphereColliderComponent(GameObject* owner, int updateOrder)
	: ColliderComponent(owner, updateOrder)
	, position_(0.f, 0.f, 0.f)
	, radius_(0.5f)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SphereColliderComponent::~SphereColliderComponent(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/