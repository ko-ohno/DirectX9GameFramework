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
	, is_rotation_lookat_(false)
	, is_rotation_yaw_(false)
	, is_rotation_pitch_(false)
	, is_rotation_roll_(false)
	, eye_point_(0.f, 0.f, 0.f)
	, old_eye_point_(0.f, 0.f, 0.f)
	, lookat_point_(0.f, 0.f, 0.f)
	, front_vector_(0.f, 0.f, 1.f)
	, up_vector_(0.f, 1.f, 0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, degree_yaw_(0.f)
	, degree_pitch_(0.f)
	, degree_roll_(0.f)
	, degree_lookat_yaw_(0.f)
	, degree_lookat_pitch_(0.f)
	, degree_lookat_roll_(0.f)
	, screen_aspect_size_(Vector2())
	, view_matrix_(D3DXMATRIX())
	, view_inverse_matrix_(D3DXMATRIX())
	, projection_matrix_2d_(D3DXMATRIX())
	, projection_matrix_3d_(D3DXMATRIX())
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

	eye_point_	   = { 0.f, 0.f, -10.f };
	old_eye_point_ = eye_point_;
	lookat_point_  = { 0.f, 0.f,   0.f };
	old_eye_point_ = lookat_point_;

	//
	// カメラの回転情報
	//

	degree_yaw_   =
	degree_pitch_ =
	degree_roll_  = 0.f;

	degree_lookat_yaw_	 =
	degree_lookat_pitch_ =
	degree_lookat_roll_  = 0.f;

	//
	//	カメラの姿勢ベクトル
	//


	//前ベクトルを求める
	front_vector_ = lookat_point_ - eye_point_;
	D3DXVec3Normalize(&front_vector_, &front_vector_);

	up_vector_ = { 0.f, 1.f,  0.f };
	D3DXVec3Normalize(&up_vector_, &up_vector_);

	//右ベクトルを求める
	D3DXVec3Cross(&right_vector_, &front_vector_, &up_vector_);
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

	if (InputCheck::KeyPress(DIK_LEFTARROW))
	{
		is_rotation_lookat_ = true;
		is_rotation_yaw_ = true;
		this->AddLookAtRotationYaw(30 * deltaTime);
	} 


	if (InputCheck::KeyPress(DIK_RIGHTARROW))
	{
		is_rotation_lookat_ = true;
		is_rotation_yaw_ = true;
		this->AddLookAtRotationYaw(-30 * deltaTime);
	}


	if (InputCheck::KeyPress(DIK_UP))
	{
		is_rotation_lookat_ = true;
		is_rotation_pitch_  = true;
		this->AddLookAtRotationPitch(30 * deltaTime);
	}


	if (InputCheck::KeyPress(DIK_DOWN))
	{
		is_rotation_lookat_ = true;
		is_rotation_pitch_	= true;
		this->AddLookAtRotationPitch(-30 * deltaTime);
	}



	ImGui::Begin("camera");
	{	
		ImGui::Text("is_camera_moved_:%s", is_camera_moved_ ? "true" : "false");

		if (ImGui::TreeNode("transform_vector_"))
		{
			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("front_vector_"))
			{
				ImGui::Text("%05f:front_vector_.x\n", front_vector_.x);
				ImGui::Text("%05f:front_vector_.y\n", front_vector_.y);
				ImGui::Text("%05f:front_vector_.z\n", front_vector_.z);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("up_vector_"))
		
			{
				ImGui::Text("%0f:up_vector_.x\n", up_vector_.x);
				ImGui::Text("%0f:up_vector_.y\n", up_vector_.y);
				ImGui::Text("%0f:up_vector_.z\n", up_vector_.z);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("right_vector_"))
			{
				ImGui::Text("%0f:right_vector_.x\n", right_vector_.x);
				ImGui::Text("%0f:right_vector_.y\n", right_vector_.y);
				ImGui::Text("%0f:right_vector_.z\n", right_vector_.z);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("camera_position"))
		{
			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("lookat_point"))
			{
				ImGui::Text("%f:lookat.x\n", lookat_point_.x);
				ImGui::Text("%f:lookat.y\n", lookat_point_.y);
				ImGui::Text("%f:lookat.z\n", lookat_point_.z);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("eye_point"))
			{
				ImGui::Text("%f:eye.x\n", eye_point_.x);
				ImGui::Text("%f:eye.y\n", eye_point_.y);
				ImGui::Text("%f:eye.z\n", eye_point_.z);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("camera_deg"))
		{
			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("deg"))
			{
				ImGui::Text("%f:deg_yaw_\n", degree_yaw_);
				ImGui::Text("%f:deg_pitch_\n", degree_pitch_);
				ImGui::Text("%f:deg_roll_\n", degree_roll_);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("deg_lookat")) {
				ImGui::Text("%f:deg_lookat_yaw_\n", degree_lookat_yaw_);
				ImGui::Text("%f:deg_lookat_pitch_\n", degree_lookat_pitch_);
				ImGui::Text("%f:deg_lookat_roll_\n", degree_lookat_roll_);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}
	ImGui::End();


	//is_rotation_lookat_	= true;
	//is_rotation_yaw_	= true;
	//is_rotation_pitch_	= true;
	//is_rotation_roll_		= true;

	//視線ベクトルの長さの更新
	{
		this->UpdateViewingVectorLength();
	}

	//カメラの姿勢情報を更新
	{
		if (is_rotation_lookat_)
		{
			this->UpdateLookatPosition();
		}
		else
		{
			this->UpdateCameraPosition();
		}
	}

	//カメラが移動したかの状態を更新
	{
		this->UpdateCameraState();
	}

	//各カメラの行列の要素を更新
	{
		this->ComputeViewMatrix();
		this->ComputeViewInverseMatrix();
		this->ComputeProjection2DMatrix();
		this->ComputeProjection3DMatrix();
	}

	//1フレーム前の情報を更新
	old_eye_point_ = eye_point_;
}

/*-----------------------------------------------------------------------------
/*　カメラの状態更新処理
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateCameraState(void)
{
	//カメラが移動したか？
	if (old_eye_point_ != eye_point_)
	{
		is_camera_moved_ = true;
	}
	else
	{
		is_camera_moved_ = false;
	}

	//フラグをもとに戻す
	is_rotation_lookat_ = false;
	is_rotation_yaw_	= false;
	is_rotation_pitch_  = false;
	is_rotation_roll_	= false;
}

/*-----------------------------------------------------------------------------
/*　視線ベクトルの長さを更新
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateViewingVectorLength(void)
{
	D3DXVECTOR3 direction = eye_point_ - lookat_point_;
	viewing_vector_length_ = D3DXVec3Length(&direction);
}

/*-----------------------------------------------------------------------------
/*　カメラ座標の更新
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateCameraPosition(void)
{
	if (is_rotation_yaw_)   { this->ComputeRotationYaw(); }
	if (is_rotation_pitch_) { this->ComputeRotationPitch(); }
	if (is_rotation_roll_)	{ this->ComputeRotationRoll(); }
}

/*-----------------------------------------------------------------------------
/*　注視点座標の更新
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateLookatPosition(void)
{
	if (is_rotation_yaw_)   { this->ComputeRotationLookatYaw(); }
	if (is_rotation_pitch_) { this->ComputeRotationLookatPitch(); }
	if (is_rotation_roll_)	{ this->ComputeRotationLookatRoll(); }
}

/*-----------------------------------------------------------------------------
/*　カメラ座標中心の回転：Yaw
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationYaw(void)
{
	// 正規化視線ベクトルの作成
	D3DXVECTOR3 viewing_vector = lookat_point_ - eye_point_;
	D3DXVec3Normalize(&viewing_vector, &viewing_vector);

	// 視線ベクトルの回転
	const float radian = Math::ToRadian(degree_yaw_ - DEGREE_NORMALIZE_OFFSET);
	{
		viewing_vector.x = Math::Sin(radian);
		viewing_vector.y = 0.f;
		viewing_vector.z = Math::Cos(radian);
	}

	// 視線ベクトルを前ベクトルとして保存
	front_vector_ = viewing_vector;

	// Yaw軸回転のため、右ベクトルの算出：前ベクトルと上ベクトルの外積
	D3DXVec3Cross(&right_vector_, &front_vector_, &up_vector_);
	D3DXVec3Normalize(&right_vector_, &right_vector_);
	
	// カメラ座標：注視点に視線ベクトルを加算することで、カメラ座標を更新する
	eye_point_ = lookat_point_ + (viewing_vector * viewing_vector_length_); //視線ベクトルの長さ1 * 視線の長さN

	// カメラ座標中心の回転角度:Yawの正規化
	degree_yaw_ = Math::NormalizeDegree(degree_yaw_);
}

/*-----------------------------------------------------------------------------
/*　カメラ座標中心の回転：Pitch
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationPitch(void)
{
	// 正規化視線ベクトルの作成
	D3DXVECTOR3 viewing_vector = eye_point_ - lookat_point_;
	D3DXVec3Normalize(&viewing_vector, &viewing_vector);

	// 視線ベクトルの回転
	const float radian = Math::ToRadian(degree_pitch_ - DEGREE_NORMALIZE_OFFSET);
	{
		viewing_vector.x = 0.f;
		viewing_vector.y = Math::Sin(radian);
		viewing_vector.z = Math::Cos(radian);
	}

	// 視線ベクトルを前ベクトルとして保存
	front_vector_ = viewing_vector;

	// Pitch軸回転のため、上ベクトルの算出：右ベクトルと上ベクトルの外積
	D3DXVec3Cross(&up_vector_, &front_vector_, &right_vector_);
	D3DXVec3Normalize(&up_vector_, &up_vector_);

	// カメラ座標：注視点に視線ベクトルを加算することで、カメラ座標を更新する
	eye_point_ = lookat_point_ + (viewing_vector * viewing_vector_length_); //向きベクトルの長さ1 * 視線の長さN

	// カメラ座標中心の回転角度:Pitchの正規化
	degree_pitch_ = Math::NormalizeDegree(degree_pitch_);
}

/*-----------------------------------------------------------------------------
/*　カメラ座標中心の回転：Roll
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationRoll(void)
{
	// 視線ベクトルの回転
	const float radian = Math::ToRadian(degree_roll_ + degree_lookat_roll_);
	{
		D3DXMATRIX rotation_matrix;
		D3DXMatrixRotationAxis(&rotation_matrix, &front_vector_, radian);

		right_vector_.x	= rotation_matrix._11;
		right_vector_.y	= rotation_matrix._12;
		right_vector_.z	= rotation_matrix._13;

		up_vector_.x = rotation_matrix._21;
		up_vector_.y = rotation_matrix._22;
		up_vector_.z = rotation_matrix._23;
	}

	// カメラ座標：注視点に向きベクトルを加算することで、カメラ座標を更新する
	eye_point_ = lookat_point_ + (front_vector_ * viewing_vector_length_); //視線ベクトルの長さ1 * 視線の長さN

	// カメラ座標中心の回転角度:Rollの正規化
	degree_roll_ = Math::NormalizeDegree(degree_roll_);
}

/*-----------------------------------------------------------------------------
/*　注視点座標中心の回転：Yaw
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationLookatYaw(void)
{
	// 正規化視線ベクトルの作成
	D3DXVECTOR3 viewing_vector = eye_point_ - lookat_point_;
	D3DXVec3Normalize(&viewing_vector, &viewing_vector);

	// 視線ベクトルの回転
	const float radian = Math::ToRadian(degree_lookat_yaw_);
	{
		viewing_vector.x = Math::Sin(radian);
		viewing_vector.y = 0.f;
		viewing_vector.z = Math::Cos(radian);
	}

	// 視線ベクトルを前ベクトルとして保存
	front_vector_ = viewing_vector;

	// Yaw軸回転のため、右ベクトルの算出：前ベクトルと上ベクトルの外積
	D3DXVec3Cross(&right_vector_, &front_vector_, &up_vector_);
	D3DXVec3Normalize(&right_vector_, &right_vector_);

	// 注視点座標：カメラ座標に視線ベクトルを加算することで、注視点座標を更新する
	lookat_point_ = eye_point_  + (viewing_vector * viewing_vector_length_); //視線ベクトルの長さ1 * 視線の長さN

	// カメラ座標中心の回転角度:Yawの正規化
	degree_lookat_yaw_ = Math::NormalizeDegree(degree_lookat_yaw_);
}

/*-----------------------------------------------------------------------------
/*　注視点座標中心の回転：Pitch
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationLookatPitch(void)
{
	// 正規化視線ベクトルの作成
	D3DXVECTOR3 viewing_vector = eye_point_ - lookat_point_;
	D3DXVec3Normalize(&viewing_vector, &viewing_vector);

	// 視線ベクトルの回転
	const float radian = Math::ToRadian(degree_lookat_pitch_);
	{
		viewing_vector.x = 0.f;
		viewing_vector.y = Math::Sin(radian);
		viewing_vector.z = Math::Cos(radian);
	}

	// 視線ベクトルを前ベクトルとして保存
	front_vector_ = viewing_vector;

	// Pitch軸回転のため、上ベクトルの算出：右ベクトルと上ベクトルの外積
	D3DXVec3Cross(&up_vector_, &right_vector_, &front_vector_);
	D3DXVec3Normalize(&up_vector_, &up_vector_);

	// 注視点座標：カメラ座標に視線ベクトルを加算することで、注視点座標を更新する
	lookat_point_ = eye_point_ + (viewing_vector * viewing_vector_length_); //視線ベクトルの長さ1 * 視線の長さN

	// カメラ座標中心の回転角度:Pitchの正規化
	degree_lookat_pitch_ = Math::NormalizeDegree(degree_lookat_pitch_);
}

/*-----------------------------------------------------------------------------
/*　注視点座標中心の回転：Roll
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationLookatRoll(void)
{
	// 視線ベクトルの回転
	const float radian = Math::ToRadian(degree_roll_ + degree_lookat_roll_);
	{
		D3DXMATRIX rotation_matrix;
		D3DXMatrixRotationAxis(&rotation_matrix, &front_vector_, radian);

		right_vector_.x = rotation_matrix._11;
		right_vector_.y = rotation_matrix._12;
		right_vector_.z = rotation_matrix._13;

		up_vector_.x = rotation_matrix._21;
		up_vector_.y = rotation_matrix._22;
		up_vector_.z = rotation_matrix._23;
	}

	// カメラ座標：注視点に向きベクトルを加算することで、カメラ座標を更新する
	eye_point_ = lookat_point_ + (front_vector_ * viewing_vector_length_); //視線ベクトルの長さ1 * 視線の長さN

	// カメラ座標中心の回転角度:Rollの正規化
	degree_roll_ = Math::NormalizeDegree(degree_roll_);
}

/*-----------------------------------------------------------------------------
/*　ビュー行列の計算
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeViewMatrix(void)
{
	// ビュー行列作成
	{
		//
		//　ビュー行列の計算式
		//
		// view_matrix = rotation_matrixの逆行列 * translation_matrixの逆行列
		//


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

		//転置後の要素の中の、移動情報を削除
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