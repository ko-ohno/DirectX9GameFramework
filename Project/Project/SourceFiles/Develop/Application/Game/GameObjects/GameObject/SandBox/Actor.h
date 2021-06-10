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
/*  アクターのステート
-------------------------------------*/
enum class ActorState
{
	None = -1
	, Wait				// 待機
	, Enter				// 登場
	, BodyPress			// ボディプレス
	, Shooting			// 射撃
	, LaserCannone		// レーザー砲

	, Max
};

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

	virtual ActorState GetActorState(void) { return actor_state_; }
	virtual void SetActorState(ActorState actorState) { actor_state_ = actorState; }

	// 体力の設定

	void SetMaxHitPoint(float maxHitPoint) { max_hit_point_ = maxHitPoint; }
	void SetHitPoint(float hitPoint) { hit_point_ = hitPoint; }
	float GetHitPoint(void) { return hit_point_; } 
	// 攻撃力の設定

	void SetMaxAttack(float maxAttack) { max_attack_ = maxAttack; }
	void SetAttack(float attack) { attack_ = attack; }
	float GetAttack(void) { return attack_; }


protected:
	// アクターの状態ステート
	ActorState actor_state_;

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