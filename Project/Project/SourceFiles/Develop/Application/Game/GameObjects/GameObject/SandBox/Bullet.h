/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Bullet.h] バレットのインターフェースゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：バレットのインターフェースゲームオブジェクト
=============================================================================*/
#ifndef BULLET_H_
#define	BULLET_H_

/*--- インクルードファイル ---*/
#include "../SandBox.h"

/*-----------------------------------------------------
/* バレットのインターフェースゲームオブジェクトクラス
-----------------------------------------------------*/
class Bullet : public SandBox
{
public:
	Bullet(class Game* game);
	~Bullet(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::IBullet; }

	// 球の衝突判定の取得
	class SphereColliderComponent*	GetSphereCollider(void) { return sphere_collider_; }

	// OBBの衝突判定の取得
	class OBBColliderComponent*		GetOBBCollider(void) { return obb_collider_; }

protected:
	// 球の衝突判定
	class SphereColliderComponent*		sphere_collider_;
	class SphereGizmoRendererComponent* sphere_collider_gizmo_;

	// OBBの衝突判定
	class OBBColliderComponent*			obb_collider_;
	class BoxGizmoRendererComponent*	obb_collider_gizmo_;
};


#endif //BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/