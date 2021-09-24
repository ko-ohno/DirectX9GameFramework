/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Enemy.h] 敵ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明： 敵ゲームオブジェクト
=============================================================================*/
#ifndef ENEMY_H_
#define	ENEMY_H_

/*--- インクルードファイル ---*/
#include "../Actor.h"

/*-------------------------------------
/*  エネミーのステート
-------------------------------------*/
enum class EnemyState
{
	None = -1
	, Idle				// 待機
	, Enter				// 登場
	, BodyPress			// 体当たり
	, Shooting			// 射撃
	, LaserCannon		// レーザー砲

	, MoveStraight				// 直線移動
	, MoveStraightWaitOneTime	// 直線移動：一時待機：直線移動
	, MoveStraightWaitUpDown	// 直線移動：上下運動と一時待機を繰り返す
	, MoveRoundVertical			// 垂直に半円を描く移動
	, MoveRoundHorizontal		// 水平に半円を描く移動
	, MoveLoopUpDown			// 上下ループ移動
	, MoveLoopLeftRight			// 左右ループ移動
	, MoveShowOneTime			// 画面の端から顔出し

	, Destroy			// 撃破された状態
	, End				// 役目を終えた状態

	, Max
};

/*-------------------------------------
/*  敵ゲームオブジェクト
-------------------------------------*/
class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	~Enemy(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Enemy; }

	//
	// 自身の状態の設定
	//

	void SetEnemyState(EnemyState enemyState);
	EnemyState GetEnemyState(void);

	//
	// 移動座標の設定
	//

	// 始点座標の設定

	void SetStartPosition(const D3DXVECTOR3& startPosition) { position_start_ = startPosition; }
	void SetStartPosition(float posX, float posY, float posZ) { position_start_ = { posX, posY, posZ }; }
	void SetStartPositionX(float posX) { position_start_.x = posX; }
	void SetStartPositionY(float posY) { position_start_.y = posY; }
	void SetStartPositionZ(float posZ) { position_start_.z = posZ; }

	// 向きベクトルの回転の設定

	void SetRotationMoveDirection(float degreeYaw, float degreePitch, float degreeRoll)
	{
		angle_yaw_   = degreeYaw;
		angle_pitch_ = degreePitch;
		angle_roll_  = degreeRoll;
	}

	void SetRotationMoveDirectionYaw(float degreeYaw)     { angle_yaw_   = degreeYaw; }
	void SetRotationMoveDirectionPitch(float degreePitch) { angle_pitch_ = degreePitch; }
	void SetRotationMoveDirectionRoll(float degreeRoll)	  { angle_roll_  = degreeRoll; }


	// 移動ベクトルの長さ
	void SetMoveVectorLength(float moveVectorLength) { move_vector_length_ = moveVectorLength; }

	// 最大の実行時間
	void SetMaxExecuteTime(float maxExecuteTime) { max_execute_time_ = maxExecuteTime; }

	// 移動アクションの深さの設定
	void SetMoveActionMagnitude(float moveActionMagnitude) { move_action_magnitude_ = moveActionMagnitude; }


protected:
	// 敵のAIコンポーネント
	class EnemyAIComponent*   enemy_ai_;

	// 移動コンポーネント
	class EnemyMoveComponent* enemy_move_;

protected:

	//
	// 座標の設定
	//

	// 始点座標
	D3DXVECTOR3 position_start_;	

	// 移動ベクトルの向き情報
	float		angle_yaw_;		// 移動ベクトルの向き：yaw
	float		angle_pitch_;	// 移動ベクトルの向き：pitch
	float		angle_roll_;	// 移動ベクトルの向き：roll

	// 移動ベクトルの長さ
	float		move_vector_length_;

	// 移動アクションの深さ
	float		move_action_magnitude_;

	// 最大の実行時間
	float		max_execute_time_;	
};

#endif //ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/