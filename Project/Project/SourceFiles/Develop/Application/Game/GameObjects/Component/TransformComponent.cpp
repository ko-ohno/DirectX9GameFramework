/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TransformComponent.cpp] 姿勢制御コンポーネントのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：姿勢制御コンポーネントに共通する処理の定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "TransformComponent.h"
#include "../../../Math.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
TransformComponent::TransformComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, is_set_rotation_matrix_(false)
	, is_execute_slerp_(false)

	, front_vector_(0.f, 0.f, 1.f)
	, up_vector_(0.f, 1.f, 0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, direction_(0.f, 0.f, 0.f)

	, position_(0.f, 0.f, 0.f)
	, old_position_(0.f, 0.f, 0.f)

	, scale_(1.f, 1.f, 1.f)
	, old_scale_(1.f, 1.f, 1.f)

	, degree_yaw_(0.f)
	, degree_pitch_(0.f)
	, degree_roll_(0.f)

	, slerp_spped_(1.f)
	, slerp_runtime_(0.f)

	, quaternion_(0.f, 0.f, 0.f, 0.f)
	, direction_quaternion_(0.f, 0.f, 0.f, 0.f)

	, rotation_matrix_(D3DXMATRIX())
	, world_matrix_(D3DXMATRIX())
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
TransformComponent::~TransformComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool TransformComponent::Init(void)
{
	D3DXQuaternionIdentity(&quaternion_);
	D3DXQuaternionIdentity(&direction_quaternion_);
	D3DXMatrixIdentity(&rotation_matrix_);
	D3DXMatrixIdentity(&world_matrix_);
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void TransformComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void TransformComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void TransformComponent::Update(float deltaTime)
{
	//向きベクトルの情報生成
	this->ComputeDirectionVector();

	//姿勢ベクトルの情報の生成
	this->ComputeTransformVector();

	const bool is_need_update = this->IsNeedUpdate();
	if (is_need_update == false) { return; }

	//回転行列がほかのクラスから設定されているか
	if (is_set_rotation_matrix_ == false)
	{
		//回転行列の生成
		this->ComputeRotationMatrixQuaternion(deltaTime);
	}

	//ワールド行列の生成
	this->ComputeWorldMatrix();
}

/*-----------------------------------------------------------------------------
/*　更新が必要かのチェック
-----------------------------------------------------------------------------*/
bool TransformComponent::IsNeedUpdate(void)
{
	//前ベクトルと向きベクトルが一致していない
	const bool is_direction_not_front = (front_vector_ != direction_);

	//１フレーム前の拡縮情報が一致していない
	const bool is_old_scale_non_matched = (old_scale_ != scale_);

	//１フレーム前の拡縮情報が一致していない
	const bool is_old_position_non_matched = (old_position_ != position_);

	//更新するか？
	const bool is_need_update = (is_direction_not_front
								|| is_old_scale_non_matched
								|| is_old_position_non_matched);
	if (is_need_update == false)
	{
		return false; 
	}
	return true;
}

/*-----------------------------------------------------------------------------
/*　向きベクトル情報の生成
-----------------------------------------------------------------------------*/
void TransformComponent::ComputeDirectionVector(void)
{
	//向き行列
	D3DXMATRIX direction_matrix;

	//向きクォータニオンを作成
	{
		D3DXQuaternionRotationYawPitchRoll(&direction_quaternion_
										  , Math::ToRadian(degree_yaw_)
										  , Math::ToRadian(degree_pitch_)
										  , Math::ToRadian(degree_roll_));
	}
	 
	//向き行列と、向きベクトルを作成
	{
		//向き行列を作成
		D3DXMatrixRotationQuaternion(&direction_matrix, &direction_quaternion_);

		//向きベクトルの作成
		{
			direction_.x = direction_matrix._31;
			direction_.y = direction_matrix._32;
			direction_.z = direction_matrix._33;
		}
	}

	// クォータニオンの角度を 0.f ～ 360.f で正規化
	{
		degree_yaw_   = Math::NormalizeDegree(degree_yaw_);
		degree_pitch_ = Math::NormalizeDegree(degree_pitch_);
		degree_roll_  = Math::NormalizeDegree(degree_roll_);
	}

}

/*-----------------------------------------------------------------------------
/*　姿勢ベクトル情報の生成
-----------------------------------------------------------------------------*/
void TransformComponent::ComputeTransformVector(void)
{
	// 右ベクトル情報の生成
	right_vector_.x = world_matrix_._11;
	right_vector_.y = world_matrix_._12;
	right_vector_.z = world_matrix_._13;

	// 上ベクトル情報の生成
	up_vector_.x	= world_matrix_._21;
	up_vector_.y	= world_matrix_._22;
	up_vector_.z	= world_matrix_._23;

	// 前ベクトル情報の生成
	front_vector_.x = world_matrix_._31;
	front_vector_.y = world_matrix_._32;
	front_vector_.z = world_matrix_._33;
}

/*-----------------------------------------------------------------------------
/*　クォータニオンによる回転行列の生成
-----------------------------------------------------------------------------*/
void TransformComponent::ComputeRotationMatrixQuaternion(float deltaTime)
{
	//球面補間をするか？
	if (is_execute_slerp_ == false)
	{
		D3DXQuaternionSlerp(&quaternion_
						   , &quaternion_
						   , &direction_quaternion_
						   , 1.f);
	}
	else
	{
		//各ベクトルを取得
		D3DXVECTOR3 front_vector = front_vector_;
		D3DXVECTOR3 direction = direction_;

		//正規化
		D3DXVec3Normalize(&front_vector, &front_vector);
		D3DXVec3Normalize(&direction, &direction);
		{
			if (front_vector_ != direction_)
			{
				slerp_runtime_ = 0.f;
			}

			if (slerp_runtime_ <= 0.999f)
			{
				//補間の実行値への加算
				slerp_runtime_ += slerp_spped_ * deltaTime;

				//補間の実行値を正規化
				if (slerp_runtime_ >= 1.000f)
				{
					slerp_runtime_ = 1.f;
				}
			}
		
			D3DXQuaternionSlerp(&quaternion_
							   , &quaternion_
							   , &direction_quaternion_
							   , slerp_runtime_);
		}
	}

	//クォータニオンから回転行列を生成
	D3DXMatrixRotationQuaternion(&rotation_matrix_, &quaternion_);
}

/*-----------------------------------------------------------------------------
/*　ワールド行列の生成
-----------------------------------------------------------------------------*/
void TransformComponent::ComputeWorldMatrix(void)
{

	//位置情報、拡縮情報
	D3DXVECTOR3 position
			  , scale;

	position = *this->GetPosition();
	scale	 = *this->GetScale();


	//回転情報
	D3DXMATRIX rotation_matrix;

	rotation_matrix = *this->GetRotationMatrix();


	//
	// ワールド行列への合成
	//

	//1フレーム前の情報を更新
	old_position_ = position;
	old_scale_ = scale;

	//拡縮のベクトル値に、回転行列の値をくわえて計算

	//X軸
	world_matrix_._11 = scale.x * rotation_matrix._11;
	world_matrix_._12 = scale.x * rotation_matrix._12;
	world_matrix_._13 = scale.x * rotation_matrix._13;

	//Y軸
	world_matrix_._21 = scale.y * rotation_matrix._21;
	world_matrix_._22 = scale.y * rotation_matrix._22;
	world_matrix_._23 = scale.y * rotation_matrix._23;

	//Z軸
	world_matrix_._31 = scale.z * rotation_matrix._31;
	world_matrix_._32 = scale.z * rotation_matrix._32;
	world_matrix_._33 = scale.z * rotation_matrix._33;

	//平行移動
	world_matrix_._41 = position.x;
	world_matrix_._42 = position.y;
	world_matrix_._43 = position.z;

	//W成分
	world_matrix_._14 = world_matrix_._24 = world_matrix_._34 = 0.0f;

	//1.0fに設定することでworld_matrix_._4*をベクトル化
	world_matrix_._44 = 1.0f;
}

/*=============================================================================
/*		End of File
=============================================================================*/