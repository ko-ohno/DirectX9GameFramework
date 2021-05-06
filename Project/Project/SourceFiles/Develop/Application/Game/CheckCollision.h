/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CheckCollision.h] 衝突判定の関数群
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：衝突判定の関数群
=============================================================================*/
#ifndef CHECK_COLLISION_H_
#define	CHECK_COLLISION_H_

/*--- インクルードファイル ---*/


// 2Dの衝突判定
#include "GameObjects/Component/ColliderComponent/CircleColliderComponent.h"
#include "GameObjects/Component/ColliderComponent/RectangleColliderComponent.h"

// 3Dの衝突判定
#include "GameObjects/Component/ColliderComponent/SphereColliderComponent.h"
#include "GameObjects/Component/ColliderComponent/OBBColliderComponent.h"


/*-------------------------------------
/* 衝突判定の関数群
-------------------------------------*/
namespace CheckCollision
{
	static D3DXVECTOR3 directx_vec3;

	// DirectXの形式に変換
	D3DXVECTOR3* ConvertDirectXVec3(Vector3* vec3);

	//
	// 2Dの衝突判定
	//

	// 円どうしの衝突判定
	bool CircleVSCircle(class CircleColliderComponent* circleA, class CircleColliderComponent* circleB);

	// 矩形どうしの衝突判定
	bool RectangleVSRectangle(class RectangleColliderComponent* rectA, class RectangleColliderComponent* rectB);

	//
	// 3Dの衝突判定
	//

	// 球どうしの衝突判定
	bool SphereVSSpghre(class SphereColliderComponent* sphereA, class SphereColliderComponent* sphereB);

	// Obbどうしの衝突判定
	bool ObbVSObb(class OBBColliderComponent* obbA, class OBBColliderComponent* obbB);
};

#endif //CHECK_COLLISION_H_
/*=============================================================================
/*		End of File
=============================================================================*/