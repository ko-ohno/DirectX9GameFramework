/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBullet.h] チャージ弾のゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：チャージ弾のゲームオブジェクト
=============================================================================*/
#ifndef CHARGE_BULLET_H_
#define	CHARGE_BULLET_H_

/*--- インクルードファイル ---*/
#include "../SandBox.h"

/*-------------------------------------
/* チャージ弾のステート
-------------------------------------*/
enum class ChargeBulletState
{
	None = -1
	, Charge
	, Hold
	, Fire
	, Bullet
	, Explosion
	, Max
};

/*-------------------------------------
/* チャージ弾のゲームオブジェクト
-------------------------------------*/
class ChargeBullet : public SandBox
{
public:
	ChargeBullet(class Game* game);
	~ChargeBullet(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	void UpdateChargeBullet(float deltaTime);
	void UpdateChargeBulletState(ChargeBulletState chargeBulletState);

private:
	static constexpr int MAX_CHARGE_BULLET_STATE = static_cast<int>(ChargeBulletState::Max);

	// バレットの処理を記述
	class SphereColliderComponent* sphere_collider_;
	class SphereGizmoRendererComponent* sphere_collider_gizmo_;

	// それぞれのエフェクト番号の登録先
	enum class EffectType effect_type_[MAX_CHARGE_BULLET_STATE];

	// それぞれのエフェクトの配列
	class EffectRendererComponent* effect_[MAX_CHARGE_BULLET_STATE];	

	// チャージ弾のステート
	ChargeBulletState charge_bullet_state_;
	ChargeBulletState charge_bullet_state_old_;
};

#endif //CHARGE_BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/