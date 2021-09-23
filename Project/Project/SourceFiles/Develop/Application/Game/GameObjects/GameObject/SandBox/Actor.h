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

	class SphereColliderComponent* GetSphereCollider(void) { return sphere_collider_; }
	class OBBColliderComponent* GetOBBCollider(void) { return obb_collider_; }

protected:
	// パラメータ

	float max_hit_point_;
	float hit_point_
		, hit_point_old_;
	float max_attack_;
	float attack_;

	// 破壊するか
	bool  is_destroy_;

	// 破棄までの時間
	float destroy_interval_time_;

	// ゲームマネージャへのポインタ
	class GameObject*					game_manager_;

	// エネミーのメッシュ
	class FFPMeshRendererComponent*		actor_mesh_;

	// 爆発のエフェクト
	class EffectRendererComponent*		explosion_effect_;

	// 衝突判定
	class SphereColliderComponent*		sphere_collider_;
	class SphereGizmoRendererComponent* sphere_gizmo_;
	class OBBColliderComponent*			obb_collider_;
	class BoxGizmoRendererComponent*	obb_collider_gizmo_;
};

#endif //ACTOR_H_
/*=============================================================================
/*		End of File
=============================================================================*/