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
	, Idle
	, End

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

	virtual TypeID GetType(void) const { return TypeID::ChargeBullet; }

	// チャージ弾の発射
	void Fire(void);

private:
	void UpdateMovement(float deltaTime);
	void UpdateChargeBulletState(float deltaTime);
	void UpdateParticleEffect(void);

	void UpdateParticleEffectPlayState(ChargeBulletState chargeBulletState);
	void UpdateColilision(ChargeBulletState chargeBulletState);

public:

	void SetWorldMatrix(D3DXMATRIX& worldMatrix)
	{
		transform_component_->SetRotationMatrix(worldMatrix);
		transform_component_->SetTranslation(worldMatrix._41, worldMatrix._42, worldMatrix._43);
	}

	// 生成座標の設定
	void SetTranslation(float posX, float posY, float posZ) { position_ = { posX, posY, posZ }; }
	void SetTranslation(const D3DXVECTOR3& position) { position_ = position; }

	// 移動速度の設定
	void SetMoveSpeed(float moveSpeed) { move_speed_ = moveSpeed; }

	// 自身を消滅させる時間の設定
	void SetKillTimer(float killTimer) { kill_timer_ = killTimer; }

	// ロックオンしているか
	void IsSetLockon(bool isLockon) { is_lockon_ = isLockon; }

public:
	// チャージ弾の状態の設定
	ChargeBulletState GetChargeBulletState(void) { return charge_bullet_state_; }
	void SetChargeBulletState(ChargeBulletState chargeBulletState) { charge_bullet_state_ = chargeBulletState; }

private:
	// チャージ弾の最大ステート数
	static constexpr int MAX_CHARGE_BULLET_STATE = 5;

	// それぞれのエフェクト番号の登録先
	enum class EffectType effect_type_[MAX_CHARGE_BULLET_STATE];

	// それぞれのエフェクトの配列
	class EffectRendererComponent* effect_[MAX_CHARGE_BULLET_STATE];	

	// 衝突判定
	class SphereColliderComponent*		sphere_collider_;
	class SphereGizmoRendererComponent* sphere_collider_gizmo_;

	// チャージ弾のステート
	ChargeBulletState charge_bullet_state_;
	ChargeBulletState charge_bullet_state_old_;

	bool		is_fire_;		// 発射しているか
	bool		is_hit_;		// ヒットしているか
	bool		is_lockon_;		// ロックオンをしているか？
	bool		is_next_state_;	// 次のステートへすすむか？

	D3DXVECTOR3 parent_front_vector_;	// 親オブジェクトの姿勢の前ベクトル
	float		move_speed_;			// 移動速度

	// 座標
	D3DXVECTOR3 position_;

	// 補間の座標
	D3DXVECTOR3 src_position_
			  , dst_position_;

	float		lerp_execute_time_;		// 補間の実行時間
	float		kill_timer_;			// 消滅までの制限時間
	float		alive_time_;			// 生存時間
	float		state_time_;			// ステートの実行時間

};

#endif //CHARGE_BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/