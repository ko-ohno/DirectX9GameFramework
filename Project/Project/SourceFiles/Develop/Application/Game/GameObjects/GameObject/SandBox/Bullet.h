/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Bullet.h] バレットゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：バレットゲームオブジェクト
=============================================================================*/
#ifndef BULLET_H_
#define	BULLET_H_

/*--- インクルードファイル ---*/
#include "../SandBox.h"

/*-------------------------------------
/* バレットゲームオブジェクト
-------------------------------------*/
class Bullet : public SandBox
{
public:
	Bullet(class Game* game);
	~Bullet(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	// GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	// 生成座標の設定
	void SetCreatePosition(float posX, float posY, float posZ) { transform_component_->SetTranslation(posX, posY, posZ); }

	// 生成座標の設定
	void SetCreatePosition(const D3DXVECTOR3& position) { transform_component_->SetTranslation(position); }

	// 移動速度の設定
	void SetMoveSpeed(float moveSpeed) { move_speed_ = moveSpeed; }

	// 自身を消滅させる時間の設定
	void SetKillTimer(float killTimer) { kill_timer_ = killTimer; }

private:
	class FFPMeshRendererComponent*		bullet_mesh_;
	class SphereColliderComponent*		sphere_collider_;
	class SphereGizmoRendererComponent* sphere_collider_gizmo_;

	D3DXVECTOR3 parent_front_vector_;
	D3DXVECTOR3 front_vector_;
	float		kill_timer_;
	float		alive_time_;
	float		move_speed_;
};

#endif //BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/