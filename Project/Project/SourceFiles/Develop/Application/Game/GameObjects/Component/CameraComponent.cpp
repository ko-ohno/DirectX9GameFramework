/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CameraComponent.cpp] カメラのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カメラコンポーネントの共通になる処理を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "CameraComponent.h"
#include "../../../Math.h"
#include "../GameObject.h"

//入力操作
#include "../../Input/InputCheck.h"

#include "../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
CameraComponent::CameraComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, is_camera_moved_(false)
	, is_using_camera_controller_(false)
	, is_rotation_lookat_(false)
	, is_execute_slerp_(false)
	, view_matrix_(D3DXMATRIX())
	, view_inverse_matrix_(D3DXMATRIX())
	, projection_matrix_2d_(D3DXMATRIX())
	, projection_matrix_3d_(D3DXMATRIX())
	, screen_aspect_size_(Vector2())
	, front_vector_(0.f, 0.f, 0.f)
	, up_vector_(0.f, 0.f, 0.f)
	, right_vector_(0.f, 0.f, 0.f)
	, degree_yaw_(0.f)
	, degree_pitch_(0.f)
	, degree_roll_(0.f)
	, degree_lookat_yaw_(0.f)
	, degree_lookat_pitch_(0.f)
	, degree_lookat_roll_(0.f)
	, slerp_spped_(0.f)
	, slerp_runtime_(0.f)
	, quaternion_(D3DXQUATERNION())
	, lookat_quaternion_(D3DXQUATERNION())
	, translation_matrix_(D3DXMATRIX())
	, rotation_lookat_matrix_(D3DXMATRIX())
	, rotation_matrix_(D3DXMATRIX())
	, world_matrix_(D3DXMATRIX())
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
CameraComponent::~CameraComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool CameraComponent::Init(void)
{
	//
	//	画面アスペクト比率の取得
	//

	screen_aspect_size_ = owner_->GetGame()->GetGraphics()->GetScreenSize();

	//
	//	カメラ座標と注視点
	//

	eye_point_	  = { 0.f, 0.f, -10.f };
	lookat_point_ = { 0.f, 0.f,   0.f };
						
	//
	//	カメラの姿勢ベクトル
	//

	up_vector_	  = { 0.f, 1.f,  0.f };

	//前ベクトルを求める
	front_vector_ = lookat_point_ - eye_point_;
	D3DXVec3Normalize(&front_vector_, &front_vector_);

	//右ベクトルを求める
	D3DXVec3Cross(&right_vector_, &up_vector_, &front_vector_);
	D3DXVec3Normalize(&right_vector_, &right_vector_);


	//
	//	カメラの各要素の初期化
	//
	{
		this->ComputeViewMatrix();
		this->ComputeViewInverseMatrix();
		this->ComputeProjection2DMatrix();
		this->ComputeProjection3DMatrix();
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void CameraComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void CameraComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void CameraComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);



			//回転行列
	//D3DXMatrixRotationQuaternion(&rotation_matrix_, &quaternion_);

	degree_yaw_ += deltaTime;

	//D3DXMATRIX rot_mat, trans_mat;

	//D3DXMatrixTranslation(&trans_mat, eye_point_.x, eye_point_.y, eye_point_.z);

	////trans_mat = trans_mat * rotation_matrix_;

	//rot_mat = rotation_matrix_;

	//D3DXMatrixInverse(&rot_mat, nullptr, &rot_mat);
	//D3DXMatrixInverse(&trans_mat, nullptr, &trans_mat);

	////view_matrix_ =  rot_mat * trans_mat;


	//{
	//	degree_yaw_ = Math::NormalizeDegree(degree_yaw_);
	//	degree_pitch_ = Math::NormalizeDegree(degree_pitch_);
	//	degree_roll_ = Math::NormalizeDegree(degree_roll_);
	//}

	//D3DXMatrixInverse(,nullptr,);
	//view_matrix_ = ;

	//カメラ座標の更新
	this->UpdateCameraPosition(deltaTime);

	//注視点座標の更新
	//this->UpdateLookatPosition(deltaTime);

	////姿勢ベクトルの更新
	//this->ComputeTransformVector();

	//各カメラの行列の要素を更新
	{
		this->ComputeViewMatrix();
		this->ComputeViewInverseMatrix();
		this->ComputeProjection2DMatrix();
		this->ComputeProjection3DMatrix();
	}

	//カメラが移動したか？
	if (old_eye_point_ != eye_point_)
	{
		is_camera_moved_ = true;
	}
	else
	{
		is_camera_moved_ = false;
	}

	ImGui::Begin("camera");
	ImGui::Text("%s", is_camera_moved_ ? "true" : "false");

	ImGui::Text("%f:lookat.x\n", lookat_point_.x);
	ImGui::Text("%f:lookat.y\n", lookat_point_.y);
	ImGui::Text("%f:lookat.z\n", lookat_point_.z);


	ImGui::Text("%f:eye.x\n", eye_point_.x);
	ImGui::Text("%f:eye.y\n", eye_point_.y);
	ImGui::Text("%f:eye.z\n", eye_point_.z);

	ImGui::Text("%f:deg\n", degree_yaw_);
	ImGui::Text("%f:deg\n", degree_pitch_);
	ImGui::Text("%f:deg\n", degree_roll_);

	ImGui::Text("%f:deg_lookat\n", degree_lookat_yaw_);
	ImGui::Text("%f:deg_lookat\n", degree_lookat_pitch_);
	ImGui::Text("%f:deg_lookat\n", degree_lookat_roll_);

	ImGui::End();

	//1フレーム前の情報を更新
	old_eye_point_ = eye_point_;
}

/*-----------------------------------------------------------------------------
/*　カメラ座標の更新処理
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateCameraPosition(float deltaTime)
{
	D3DXMATRIX rotation_matrix;


	//回転情報の生成
	{
		//回転クォータニオン
		//D3DXQuaternionRotationYawPitchRoll(&quaternion_
		//							   	  , Math::ToRadian(degree_yaw_)
		//							   	  , Math::ToRadian(degree_pitch_)
		//							   	  , Math::ToRadian(degree_roll_));

		D3DXQuaternionRotationAxis(&quaternion_, &up_vector_, Math::ToRadian(30 * deltaTime)); //注視点中心の回転はこれでできる。

		//回転行列
		D3DXMatrixRotationQuaternion(&rotation_matrix, &quaternion_);

	}

	//カメラ座標の更新
	{
		//回転行列をもとに、向きベクトルを回転させる
		D3DXVECTOR3 direction = eye_point_ - lookat_point_;
		D3DXVec3TransformNormal(&direction, &direction, &rotation_matrix);

		//up_vector_.x = rotation_matrix_._21;
		//up_vector_.y = rotation_matrix_._22;
		//up_vector_.z = rotation_matrix_._23;

		//カメラ座標：注視点に向きベクトルを加算することで、カメラ座標を更新する
		eye_point_ = lookat_point_ + direction;
		eye_point_ = eye_point_;
	}

	//カメラ座標中心の回転角度を正規化
	{
		degree_yaw_		= Math::NormalizeDegree(degree_yaw_);
		degree_pitch_	= Math::NormalizeDegree(degree_pitch_);
		degree_roll_	= Math::NormalizeDegree(degree_roll_);
	}
}

/*-----------------------------------------------------------------------------
/*　注視点座標の更新処理
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateLookatPosition(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);


	//回転情報の生成
	{
		//回転クォータニオン
		D3DXQuaternionRotationYawPitchRoll(&lookat_quaternion_
										  , Math::ToRadian(degree_lookat_yaw_)
										  , Math::ToRadian(degree_lookat_pitch_)
										  , Math::ToRadian(degree_lookat_roll_));

		//回転行列
		D3DXMatrixRotationQuaternion(&rotation_lookat_matrix_, &lookat_quaternion_);
	}

	//注視点座標の更新
	{

		//回転行列をもとに、向きベクトルを回転させる
		D3DXMATRIX rotation_matrix;
		D3DXVECTOR3 direction = lookat_point_ - eye_point_;
		D3DXVec3TransformNormal(&direction, &direction, &rotation_matrix);

		////注視点座標：カメラ座標に向きベクトルを加算することで、注視点を更新する
		lookat_point_ = eye_point_ + direction;
		lookat_point_ = lookat_point_;
	}

	//注視点座標中心の回転角度を正規化
	{
		degree_lookat_yaw_   = Math::NormalizeDegree(degree_lookat_yaw_);
		degree_lookat_pitch_ = Math::NormalizeDegree(degree_lookat_pitch_);
		degree_lookat_roll_  = Math::NormalizeDegree(degree_lookat_roll_);
	}
}

void CameraComponent::ComputeWorldMatrix(void)
{
}

void CameraComponent::ComputeLocalMatrix(void)
{
}

/*-----------------------------------------------------------------------------
/*　姿勢ベクトルの更新処理
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeTransformVector(void)
{
	front_vector_ = lookat_point_ - eye_point_;
	D3DXVec3Normalize(&front_vector_, &front_vector_);

	up_vector_ = { 0.f, 1.f, 0.f };
	up_vector_;
	up_vector_;

	right_vector_ = { 1.f, 0.f, 0.f };

	//right_vector_.x = 1.0f;
	//right_vector_.y = 0.f;
	//right_vector_.z = 0.f;

	D3DXVec3Normalize(&right_vector_, &right_vector_);
}


/*-----------------------------------------------------------------------------
/*　ビュー行列の計算
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeViewMatrix(void)
{
	// ビュー行列作成
	{
		//auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

		//
		//　ビュー行列の計算式
		//
		// view_matrix = rotation_matrixの逆行列 * translation_matrixの逆行列
		//

		D3DXMATRIX camera_matrix = local_matrix_ * world_matrix_;

		D3DXVECTOR3 eye_point	 = { camera_matrix._11, camera_matrix._12, camera_matrix._13 };
		D3DXVECTOR3 lookat_point = { camera_matrix._31, camera_matrix._32, camera_matrix._33 };
		D3DXVECTOR3 up_vector	 = { camera_matrix._21, camera_matrix._22, camera_matrix._23 };


		D3DXMatrixLookAtLH(&view_matrix_
						  , &eye_point_	 	// 視点
						  , &lookat_point_	// 注視点
						  , &up_vector_);	// カメラの頭の向き	
	}
}

/*-----------------------------------------------------------------------------
/*　逆ビュー行列の計算
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeViewInverseMatrix(void)
{
	// 逆ビュー行列作成
	{
		//ビュー行列を複製
		view_inverse_matrix_ = view_matrix_;

		//転置行列変換
		D3DXMatrixTranspose(&view_inverse_matrix_, &view_inverse_matrix_);

		//転置後の要素、移動情報を削除
		view_inverse_matrix_._41 = 0.0f;
		view_inverse_matrix_._42 = 0.0f;
		view_inverse_matrix_._43 = 0.0f;
	}
}

/*-----------------------------------------------------------------------------
/*　2D用のプロジェクション行列の計算
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeProjection2DMatrix(void)
{
	//実行中に画面サイズを変更したい場合は、この変換行列を"更新"できるようにする
	//射影変換行列の作成
	{
		Vector2 screen_size = owner_->GetGame()->GetGraphics()->GetScreenSize();

		projection_matrix_2d_ = {
			 (2.f / screen_size.x_),				     0.f, 0.f, 0.f,
								0.f, (-2.f / screen_size.y_), 0.f, 0.f,
								0.f,				     0.f, 1.f, 0.f,
							   -1.f,				     1.f, 0.f, 1.f,
		};
	}
}

/*-----------------------------------------------------------------------------
/*　3D用のプロジェクション行列の計算
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeProjection3DMatrix(void)
{
	// 3Dプロジェクション変換行列作成
	{
		D3DXMatrixPerspectiveFovLH(&projection_matrix_3d_												// 3D射影変換行列
								  , D3DX_PI / 3															// 視野角
								  , static_cast<FLOAT>(screen_aspect_size_.x_) / screen_aspect_size_.y_	// アスペクト比
								  , static_cast<FLOAT>(1.f)												// ニアクリップ   : カメラの描画領域の
								  , static_cast<FLOAT>(1000.f));										// ファークリップ : カメラの描画領域の奥までの距離
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/