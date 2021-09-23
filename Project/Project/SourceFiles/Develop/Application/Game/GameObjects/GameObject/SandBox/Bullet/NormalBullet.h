/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[NormalBullet.h] 通常バレットゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：通常バレットゲームオブジェクト
=============================================================================*/
#ifndef NORMAL_BULLET_H_
#define	NORMAL_BULLET_H_

/*--- インクルードファイル ---*/
#include "../Bullet.h"

/*-------------------------------------
/* バレットゲームオブジェクト
-------------------------------------*/
class NormalBullet : public Bullet
{
public:
	NormalBullet(class Game* game);
	~NormalBullet(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	// GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Bullet; }

	// プレイヤーの姿勢を合成
	void CombinePlayerTransform(void);

	// 生成座標の設定
	void SetCreatePosition(float posX, float posY, float posZ) { transform_component_->SetTranslation(posX, posY, posZ); }

	// 生成座標の設定
	void SetCreatePosition(const D3DXVECTOR3& position) { transform_component_->SetTranslation(position); }

	// 移動速度の設定
	void SetMoveSpeed(float moveSpeed) { move_speed_ = moveSpeed; }

	// 前ベクトルを設定
	void SetFrontVector(const D3DXVECTOR3& frontVector)
	{
		is_set_front_vector_ = true;

		front_vector_ = frontVector;
	}

	// 自身を消滅させる時間の設定
	void SetKillTimer(float killTimer) { kill_timer_ = killTimer; }

private:
	class FFPMeshRendererComponent*		bullet_mesh_;
 
	// 弾丸を生成したフレームか
	bool is_bullet_create_frame_;

	// 前ベクトルを設定しているか？
	bool is_set_front_vector_;

	D3DXVECTOR3 parent_front_vector_;
	D3DXVECTOR3 right_vector_
			  , up_vector_
			  , front_vector_;
	float		kill_timer_;
	float		alive_time_;
	float		move_speed_;
};

#endif //NORMAL_BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/