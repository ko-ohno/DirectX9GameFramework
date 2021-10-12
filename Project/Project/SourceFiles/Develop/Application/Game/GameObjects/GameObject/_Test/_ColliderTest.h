/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderTest.h] 衝突判定テスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：衝突判定テスト用ゲームオブジェクト
=============================================================================*/
#ifndef COLLIDER_TEST_H_
#define	COLLIDER_TEST_H_

/*--- インクルードファイル ---*/
#include "../../GameObject.h"

/*-------------------------------------
/* 衝突判定テスト用ゲームオブジェクト
-------------------------------------*/
class ColliderTest : public GameObject
{
public:
	ColliderTest(class Game* game);
	~ColliderTest(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::ColliderTest; }

private:
	class GridGizmoRendererComponent* grid_gizmo_renderer_component_;

	class BoxGizmoRendererComponent* box_gizmo_renderer_component_;
	class BoxGizmoRendererComponent* box_gizmo_renderer_component_a_;

	class OBBColliderComponent* obb_collider_component_;
	class OBBColliderComponent* obb_collider_component_a_;

	class SphereGizmoRendererComponent* sphere_gizmo_renderer_component_;
	class SphereGizmoRendererComponent* sphere_gizmo_renderer_component_a_;

	class SphereColliderComponent* sphere_collider_component_;
	class SphereColliderComponent* sphere_collider_component_a_;

};


#endif //COLLIDER_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/