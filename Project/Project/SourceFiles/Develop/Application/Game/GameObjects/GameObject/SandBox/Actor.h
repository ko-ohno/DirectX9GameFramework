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

	// ゲームオブジェクトの種類
	virtual TypeID GetType(void) const { return TypeID::Actor; }

	// 体力の設定

	inline void SetMaxHitPoint(float maxHitPoint) { max_hit_point_ = maxHitPoint; }
	inline void SetHitPoint(float hitPoint) { hit_point_ = hitPoint; }
	inline float GetHitPoint(void) { return hit_point_; } 

	// 攻撃力の設定

	inline void SetMaxAttack(float maxAttack) { max_attack_ = maxAttack; }
	inline void SetAttack(float attack) { attack_ = attack; }
	inline float GetAttack(void) { return attack_; }

protected:
	// パラメータ

	float max_hit_point_;
	float hit_point_;
	float max_attack_;
	float attack_;

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