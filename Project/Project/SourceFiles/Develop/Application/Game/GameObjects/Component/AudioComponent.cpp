/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioComponent.cpp] 音声コンポーネントのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：音声コンポーネントの共有のクラス定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "AudioComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
AudioComponent::AudioComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
AudioComponent::~AudioComponent(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/