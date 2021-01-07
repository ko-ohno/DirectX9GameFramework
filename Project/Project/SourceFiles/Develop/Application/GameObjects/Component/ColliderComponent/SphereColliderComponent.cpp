/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereColliderComponent.cpp] カプセルコライダのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カプセルコライダのコンポーネントの処理を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "SphereColliderComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SphereColliderComponent::SphereColliderComponent(GameObject* owner, int updateOrder)
	: ColliderComponent(owner, updateOrder)
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