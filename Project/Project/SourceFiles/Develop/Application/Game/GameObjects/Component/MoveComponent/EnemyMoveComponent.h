/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyMoveComponent.h]  敵の移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：敵の移動コンポーネントのクラス定義
=============================================================================*/
#ifndef ENEMY_MOVE_COMPONENT_H_
#define	ENEMY_MOVE_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../MoveComponent.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"

/*-------------------------------
/* 敵のモーション状態
-------------------------------*/
enum class EnemyMotionState
{
	None = -1
	, Idle			// 待機状態
	, StartUp		// 攻撃の立ち上がり
	, Relay			// 攻撃への移行状態
	, Attack		// 実際の攻撃状態
	, MoveState_0	// 移動ステート_0
	, MoveState_1	// 移動ステート_1
	, MoveState_2	// 移動ステート_2
	, MoveState_3	// 移動ステート_3
	, MoveState_4	// 移動ステート_4
	, Complete		// 完了状態
	, End			// 終了状態

	, Max
};

/*-------------------------------------
/* 敵の移動コンポーネント
-------------------------------------*/
class EnemyMoveComponent : public MoveComponent
{
public:
	EnemyMoveComponent(class GameObject* owner, int updateOrder);
	~EnemyMoveComponent(void);

	// 向きベクトルの計算
	void ComputeMoveDirection(void);

	//
	// 敵AIの状態を設定
	//

	void SetEnemyState(EnemyState enemyState) { enemy_state_ = enemyState; }
	
	//
	// 移動座標の設定
	//

	// 始点座標の設定

	void SetStartPosition(const D3DXVECTOR3& startPosition ) { position_start_ = startPosition; }
	void SetStartPosition(float posX, float posY, float posZ) { position_start_ = { posX, posY, posZ }; }
	void SetStartPositionX(float posX) { position_start_.x = posX; }
	void SetStartPositionY(float posY) { position_start_.y = posY; }
	void SetStartPositionZ(float posZ) { position_start_.z = posZ; }

	// 向きベクトルの回転の設定

	void SetRotationMoveDirection(float degreeYaw, float degreePitch, float degreeRoll)
	{
		angle_yaw_	 = degreeYaw;
		angle_pitch_ = degreePitch;
		angle_roll_  = degreeRoll;
	}

	void SetRotationMoveDirectionYaw(float degreeYaw)	  { angle_yaw_	 = degreeYaw; }
	void SetRotationMoveDirectionPitch(float degreePitch) { angle_pitch_ = degreePitch; }
	void SetRotationMoveDirectionRoll(float degreeRoll)   { angle_roll_  = degreeRoll; }


	// 移動ベクトルの長さ
	void SetMoveVectorLength(float moveVectorLength) { move_vector_length_ = moveVectorLength; }

	// 最大の実行時間
	void SetMaxExecuteTime(float maxExecuteTime) { max_execute_time_ = maxExecuteTime; }

	// 移動アクションの深さの設定
	void SetMoveActionMagnitude(float moveActionMagnitude) { move_action_magnitude_ = moveActionMagnitude; }

	//
	// 移動座標の計算
	//
	void ComputeLerpPosition(void);

	//
	// モーションの状態の設定・取得
	//

	void GetMotionState(EnemyMotionState enemyMotionState) { enemy_motion_state_ = enemyMotionState; }
	EnemyMotionState GetMotionState(void) const { return enemy_motion_state_; }

	virtual TypeID GetComponentType() const override { return TypeID::EnemyMoveComponent; };

	// 実行時間の取得
	float GetExecuteTime(void) { return execute_time_; }

	//
	// 敵の実際の挙動を設定
	//

	virtual void MoveActionIdle(float deltaTime);					// 待機行動
	virtual void MoveActionEnter(float deltaTime);					// 登場
	virtual void MoveActionBodyPress(float deltaTime);				// 体当たり
	virtual void MoveActionShoot(float deltaTime);					// 射撃
	virtual void MoveActionLaserCannon(float deltaTime);			// レーザー砲	
	virtual void MoveActionStraight(float deltaTime);				// 直線移動
	virtual void MoveActionStraightWaitOneTime(float deltaTime);	// 直線移動一回待つ
	virtual void MoveActionStraightWaitUpDown(float deltaTime);		// 直線移動して上下運動複数回待つ
	virtual void MoveActionRoundVertical(float deltaTime);			// 垂直に半円を描く：｜
	virtual void MoveActionRoundHorizontal(float deltaTime);		// 水平に半円を描く：─
	virtual void MoveActionLoopUpDown(float deltaTime);				// 上下行動をループ
	virtual void MoveActionLoopLeftRight(float deltaTime);			// 左右行動をループ
	virtual void MoveActionShowOneTime(float deltaTime);			// 一度だけ、ひょっこり顔出しする 
	virtual void MoveActionSShapedCurve(float deltaTime);			// S字カーブ移動

protected:

	//
	// 敵のモーション状態
	//

	enum class EnemyMotionState  enemy_motion_state_;

	//
	// 敵の状態
	//

	enum class EnemyState		 enemy_state_;
	enum class EnemyState		 enemy_state_old_;

	//
	// 敵の座標関係
	//

	// 座標の計算が必要か？
	bool		is_need_compute_;

	// 現在座標
	D3DXVECTOR3 position_;

	// 補間する座標
	D3DXVECTOR3 position_start_		//　始点座標
			  , position_finish_;	//　終点座標

	// 1フレーム前の始点座標
	D3DXVECTOR3 position_start_old_;

	// Y軸座標の一時保管先
	float		position_y_start_	//　始点座標
			  , position_y_finish_;	//　終点座標

	// 自機の回転角度
	float		angle_yaw_;
	float		angle_pitch_;
	float		angle_roll_;

	// 右ベクトル
	D3DXVECTOR3 right_vector_;

	// 向きベクトル
	D3DXVECTOR3 move_direction_;

	// 移動ベクトルの長さ
	float		move_vector_length_;

	// 移動アクションの深さ
	float		move_action_magnitude_;

	// ステートを繰り返した数
	int			state_loop_count_;

	// 実行時間
	float		max_execute_time_;	// 最大の実行時間
	float		execute_time_;		// 現在の実行時間

	// 自機の回転角度
	float		yaw_;
	float		pitch_;
	float		roll_;
};

#endif //ENEMY_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/