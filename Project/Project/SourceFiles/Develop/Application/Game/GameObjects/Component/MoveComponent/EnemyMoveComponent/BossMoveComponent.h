/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossMoveComponent.h]  ボスの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスの移動コンポーネント
=============================================================================*/
#ifndef BOSS_MOVE_COMPONENT_H_
#define	BOSS_MOVE_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../EnemyMoveComponent.h"


/*-------------------------------------
/* ボスの移動コンポーネント
-------------------------------------*/
class BossMoveComponent : public EnemyMoveComponent
{
public:
	BossMoveComponent(class GameObject* owner, int updateOrder = 100);
	~BossMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BossMoveComponent; };

	//
	// ボスの実際の挙動を設定
	//

	void MoveActionEnter(float deltaTime);
	void MoveActionWait(float deltaTime);
	void MoveActionBodyPress(float deltaTime);
	void MoveActionShoot(float deltaTime);
	void MoveActionLaserCannon(float deltaTime);

private:

	// それぞれの初期座標
	static constexpr float offset_height_ = -3.0f;

	//
	// 登場に使うモーションの座標
	//

	const D3DXVECTOR3 enter_from_right_wait_position_ = {  40.f,   0.f + offset_height_, 13.f };
	const D3DXVECTOR3 enter_from_left_wait_position_  = { -40.f,   0.f + offset_height_, 13.f };
	const D3DXVECTOR3 enter_from_under_wait_position_ = {   0.f, -30.f + offset_height_, 13.f };

	//
	// 攻撃に使うモーションの座標
	//

	const D3DXVECTOR3 wait_position_				  = {   0.f,   0.f + offset_height_, 13.f };
	const D3DXVECTOR3 shoot_position_				  = {   0.f,   2.f + offset_height_, 20.f };
	const D3DXVECTOR3 body_press_startup_position_	  = {   0.f,   2.f + offset_height_, 16.f };
	const D3DXVECTOR3 body_press_position_			  = {   0.f,   0.f + offset_height_,  3.f };

	// 現在座標
	D3DXVECTOR3 position_;

	// 回転角度
	float yaw_;
	float pitch_;
	float roll_;

	// 実行時間
	float execute_time_;
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/