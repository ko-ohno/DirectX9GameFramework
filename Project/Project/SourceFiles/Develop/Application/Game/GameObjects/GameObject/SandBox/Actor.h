/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Actor.h] アクターゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アクターゲームオブジェクト
=============================================================================*/
#ifndef ACTOR_H_
#define	ACTOR_H_

/*--- インクルードファイル ---*/
#include "../SandBox.h"

/*-------------------------------------
/* アクターゲームオブジェクト
-------------------------------------*/
class Actor : public SandBox
{
public:
	Actor(class Game* game);
	virtual ~Actor(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Actor; }

protected:
	// エネミーのメッシュ
	class FFPMeshRendererComponent*		actor_mesh_;

	// 衝突判定
	class SphereGizmoRendererComponent* sphere_gizmo_;
	class SphereColliderComponent*		sphere_collider_;
	class BoxGizmoRendererComponent*	box_gizmo_;
	class OBBColliderComponent*			obb_collider_;
};


#endif //ACTOR_H_
/*=============================================================================
/*		End of File
=============================================================================*/