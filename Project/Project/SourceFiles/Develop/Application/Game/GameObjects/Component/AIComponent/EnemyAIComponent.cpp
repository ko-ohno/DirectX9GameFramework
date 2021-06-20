/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyAIComponent.cpp] 敵AIのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：敵AIコンポーネントの処理を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "EnemyAIComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EnemyAIComponent::EnemyAIComponent(GameObject* owner, int updateOrder)
	: AIComponent(owner, updateOrder)
	, ai_owner_(nullptr)
	, enemy_move_(nullptr)
	, enemy_state_(EnemyState::None)
	, max_hit_point_(0.f)
	, hit_point_(0.f)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EnemyAIComponent::~EnemyAIComponent(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/