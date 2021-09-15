/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyMoveComponent.cpp] 敵の移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：敵の移動コンポーネントの処理を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "EnemyMoveComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EnemyMoveComponent::EnemyMoveComponent(GameObject* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
	, enemy_motion_state_(EnemyMotionState::None)
	, enemy_state_(EnemyState::None)
	, enemy_state_old_(EnemyState::None)
	, is_need_compute_(true)
	, position_(0.f, -100.f, 0.f)
	, position_start_(0.f, -100.f, 0.f)
	, position_finish_(0.f, 0.f, 0.f)
	, position_start_old_(0.f, 0.f, 0.f)
	, position_y_start_(0.f)
	, position_y_finish_(0.f)
	, angle_yaw_(0.f)
	, angle_pitch_(0.f)
	, angle_roll_(0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, move_direction_(0.f, 0.f, 0.f)
	, move_vector_length_(1.f)
	, move_action_magnitude_(1.f)
	, state_loop_count_(0)
	, max_execute_time_(1.f)
	, execute_time_(0.f)
	, yaw_(0.f)
	, pitch_(0.f)
	, roll_(0.f)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EnemyMoveComponent::~EnemyMoveComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* 向きベクトルの計算
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::ComputeMoveDirection(void)
{

}

/*-----------------------------------------------------------------------------
/* 補間座標の計算
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::ComputeLerpPosition(void)
{
	// 座標の計算が必要か
	is_need_compute_ = (enemy_state_old_ != enemy_state_)
					   || (position_start_ != position_start_old_);

	//必要なかったら計算しない
	if (is_need_compute_ == false) { return; }
	

	// 向き情報の生成
	D3DXMATRIX		direction_matrix_;		// 向き行列
	D3DXQUATERNION	direction_quaternion_;	// 向きクォータニオン

	// 各情報の初期化
	D3DXMatrixIdentity(&direction_matrix_);
	D3DXQuaternionIdentity(&direction_quaternion_);

	// 向きクォータニオンを生成
	D3DXQuaternionRotationYawPitchRoll(&direction_quaternion_
									  , D3DXToRadian(angle_yaw_)
									  , D3DXToRadian(angle_pitch_)
									  , D3DXToRadian(angle_roll_));

	// 向きクォータニオンを向き行列へ変換
	D3DXMatrixRotationQuaternion(&direction_matrix_, &direction_quaternion_);

	// 向きクォータニオンにより回転させた向き行列から向きベクトルへ変換
	move_direction_.x = direction_matrix_._31;
	move_direction_.y = direction_matrix_._32;
	move_direction_.z = direction_matrix_._33;

	// 向き行列から右ベクトルを抽出 
	right_vector_.x = direction_matrix_._11;
	right_vector_.y = direction_matrix_._12;
	right_vector_.z = direction_matrix_._13;

	// 各ベクトルの正規化
	D3DXVec3Normalize(&move_direction_, &move_direction_);
	D3DXVec3Normalize(&right_vector_, &right_vector_);

	//
	// 移動ベクトルの計算
	//

	// 終点座標の計算
	position_finish_ = move_direction_ * move_vector_length_; // 原点からオフセットした座標:終点座標
	position_finish_ += position_start_;					  // 移動ベクトルの原点をオフセットする

	// 1フレーム前の始点座標情報を更新
	position_start_old_ = position_start_;
}

/*-----------------------------------------------------------------------------
/* 待機行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionIdle(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 登場行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionEnter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 体当たり攻撃行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionBodyPress(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 射撃攻撃行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionShoot(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* レーザー砲攻撃行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionLaserCannon(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 直線移動行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionStraight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 直線移動して一回待つ行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionStraightWaitOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 直線移動して上下運動複数回待つ
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionStraightWaitUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 垂直に半円を描く移動行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionRoundVertical(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 水平に半円を描く移動行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionRoundHorizontal(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 上下ループ移動行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionLoopUpDown(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 左右ループ移動行動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionLoopLeftRight(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 画面の端からひょっこり顔をだす
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionShowOneTime(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* S字カーブで移動
-----------------------------------------------------------------------------*/
void EnemyMoveComponent::MoveActionSShapedCurve(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/