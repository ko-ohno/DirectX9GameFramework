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
#include "../MoveComponent.h"

/*-------------------------------
/* ボスの移動状態
-------------------------------*/
enum class BossMotionState
{
	NONE = -1
	, ENTER
	, WAIT
	, BODY_PRESS
	, SHOOT
	, LASER_CANNON
};

/*-------------------------------
/* ボスの攻撃モーション状態
-------------------------------*/
enum class AttackMotionState
{
	NONE = -1
	, START_UP	// 攻撃の立ち上がり
	, RELAY		// 攻撃への移行状態
	, ATTACK	// 実際の攻撃状態
	, END		// 初期状態へ戻る
};

/*-------------------------------
/* ボスの登場モーションの状態
-------------------------------*/
enum class EnterMotionState
{
	NONE = -1
	, FROM_RIGHT	// 右から左へ
	, FLOM_LEFT		// 左から右へ
	, FLOM_UNDER	// 下からババーン！！する。
	, END			// 待機行動へ移行　
};

/*-------------------------------------
/* ボスの移動コンポーネント
-------------------------------------*/
class BossMoveComponent : public MoveComponent
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

	void MoveActionEnter(float deltaTime);
	void MoveActionWait(float deltaTime);
	void MoveActionBodyPress(float deltaTime);
	void MoveActionShoot(float deltaTime);
	void MoveActionLaserCannon(float deltaTime);

	//
	// ボスの状態を設定
	//
	BossMotionState GetBossMotionState(void) { return boss_motion_state_; }
	void SetBossMotionState(BossMotionState bossState) { boss_motion_state_ = bossState; }

private:
	// 所有者のボスアクター
	class Actor* owner_boss_actor_;

	//
	// ボスの行動状態
	//

	EnterMotionState  enter_motion_state_;		// ボスの登場の行動状態
	AttackMotionState attack_motion_state_;		// ボスの攻撃の行動状態
	BossMotionState	  boss_motion_state_;		// ボスの行動状態
	BossMotionState	  boss_motion_state_old_;	// ボスの１フレーム前の行動状態


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