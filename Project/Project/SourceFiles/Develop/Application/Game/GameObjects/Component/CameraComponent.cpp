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

#include "../../Input/InputCheck.h"
#include "../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
CameraComponent::CameraComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, is_need_update_(false)
	, is_camera_moved_(false)
	, is_camera_controlling_(true)
	, position_(0.f, 0.f, 0.f)
	, old_position_(0.f, 0.f, 0.f)
	, lookat_position_(0.f, 0.f, 0.f)
	, move_direction_(0.f, 0.f, 0.f)
	, front_vector_(0.f, 0.f, 1.f)
	, up_vector_(0.f, 1.f, 0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, move_speed_(10.f)
	, rotation_degree_(45.f)
	, viewing_vector_length_(0.f)
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

	position_	   = { 0.f, 0.f, -10.f };
	old_position_ = position_;
	lookat_position_  = { 0.f, 0.f,   0.f };

	//
	//	カメラの姿勢ベクトル
	//

	//前ベクトルを求める
	front_vector_ = lookat_position_ - position_;
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
				ImGui::Text("%f:lookat.x\n", lookat_position_.x);
				ImGui::Text("%f:lookat.y\n", lookat_position_.y);
				ImGui::Text("%f:lookat.z\n", lookat_position_.z);
				ImGui::TreePop();
			}

			ImGui::SetNextTreeNodeOpen(true);
			if (ImGui::TreeNode("eye_point"))
			{
				ImGui::Text("%f:eye.x\n", position_.x);
				ImGui::Text("%f:eye.y\n", position_.y);
				ImGui::Text("%f:eye.z\n", position_.z);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

	}
	ImGui::End();

	//視線ベクトルの長さの更新
	{
		this->UpdateViewingVectorLength();
	}

	//姿勢ベクトルの更新
	{
		this->UpdateTransform(deltaTime);
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
	old_position_ = position_;
}

/*-----------------------------------------------------------------------------
/*　カメラの状態更新処理
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateCameraState(void)
{
	//カメラが移動したか？
	if (old_position_ != position_)
	{
		is_camera_moved_ = true;
	}
	else
	{
		is_camera_moved_ = false;
	}
}

/*-----------------------------------------------------------------------------
/*　視線ベクトルの長さを更新
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateViewingVectorLength(void)
{
	D3DXVECTOR3 viewing_vector = position_ - lookat_position_;
	viewing_vector_length_ = D3DXVec3Length(&viewing_vector);
}

/*-----------------------------------------------------------------------------
/*　移動方向ベクトルの更新
-----------------------------------------------------------------------------*/
void CameraComponent::UpdateTransform(float deltaTime)
{
	//前ベクトルを算出。注視点からカメラの位置分を引く
	front_vector_ = lookat_position_ - position_;

	//姿勢ベクトルの更新
	{
		//前ベクトルを正規化
		D3DXVec3Normalize(&front_vector_, &front_vector_);

		//外積で右ベクトルを求める
		D3DXVec3Cross(&right_vector_, &up_vector_, &front_vector_);
		D3DXVec3Normalize(&right_vector_, &right_vector_);

		//外積で上ベクトルを求める
		D3DXVec3Cross(&up_vector_, &front_vector_, &right_vector_);
		D3DXVec3Normalize(&up_vector_, &up_vector_);
	}

	//カメラを操作するか
	if (is_camera_controlling_)
	{
		this->ComputeCameraMovement(deltaTime);
		this->ComputeRotationCameraPosition(deltaTime);
		this->ComputeRotationLookatPosition(deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/*　カメラの移動コントロール
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeCameraMovement(float deltaTime)
{
	const bool is_move_front = InputCheck::KeyPress(DIK_W);
	const bool is_move_back  = InputCheck::KeyPress(DIK_S);
	const bool is_move_left	 = InputCheck::KeyPress(DIK_A);
	const bool is_move_right = InputCheck::KeyPress(DIK_D);
	const bool is_move_up	 = InputCheck::KeyPress(DIK_Q);
	const bool is_move_down  = InputCheck::KeyPress(DIK_E);

	const bool is_moving = (is_move_front || is_move_back || is_move_left || is_move_right || is_move_up || is_move_down);

	if (is_moving)
	{
		//
		// 前後移動
		//

		if (is_move_front)
		{
			position_		 += (front_vector_ * move_speed_) * deltaTime;
			lookat_position_ += (front_vector_ * move_speed_) * deltaTime;
		}
		
		if (is_move_back) 
		{
			position_		 -= (front_vector_ * move_speed_) * deltaTime;
			lookat_position_ -= (front_vector_ * move_speed_) * deltaTime;
		}
		
		//
		// 左右移動
		//

		if (is_move_left)
		{
			position_		 += (right_vector_ * move_speed_) * deltaTime;
			lookat_position_ += (right_vector_ * move_speed_) * deltaTime;
		}
		
		if (is_move_right)
		{
			position_		 -= (right_vector_ * move_speed_) * deltaTime;
			lookat_position_ -= (right_vector_ * move_speed_) * deltaTime;
		}
		
		//
		// 上下移動
		//

		if (is_move_up)
		{
			position_		 += (up_vector_ * move_speed_) * deltaTime;
			lookat_position_ += (up_vector_ * move_speed_) * deltaTime;
		}
		
		if (is_move_down)
		{
			position_		 -= (up_vector_ * move_speed_) * deltaTime;
			lookat_position_ -= (up_vector_ * move_speed_) * deltaTime;
		}
	}
}

/*-----------------------------------------------------------------------------
/*　カメラ座標のコントロール
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationCameraPosition(float deltaTime)
{
	const bool is_rotation_up    = InputCheck::KeyPress(DIK_UPARROW);
	const bool is_rotation_down  = InputCheck::KeyPress(DIK_DOWNARROW);
	const bool is_rotation_right = InputCheck::KeyPress(DIK_RIGHTARROW);
	const bool is_rotation_left  = InputCheck::KeyPress(DIK_LEFTARROW);
	const bool is_rotation  = (is_rotation_up || is_rotation_down || is_rotation_right || is_rotation_left);

	if (is_rotation)
	{
		//回転の速度をラジアンに変換
		float radian = Math::ToRadian(rotation_degree_ * deltaTime);

		//回転情報
		D3DXMATRIX rotation_matrix;
		D3DXMatrixIdentity(&rotation_matrix);

		//向きベクトル
		D3DXVECTOR3 direction;

		/*--- カメラのワールド座標中心に回転 ---*/
		if (is_rotation_up)	   { D3DXMatrixRotationAxis(&rotation_matrix, &right_vector_,  radian); }
		if (is_rotation_down)  { D3DXMatrixRotationAxis(&rotation_matrix, &right_vector_, -radian); }
		if (is_rotation_right) { D3DXMatrixRotationAxis(&rotation_matrix, &up_vector_,	   radian); }
		if (is_rotation_left)  { D3DXMatrixRotationAxis(&rotation_matrix, &up_vector_,	  -radian); }

		//向きベクトルを作成
		direction = position_ - lookat_position_;
		D3DXVec3Normalize(&direction, &direction);

		//向きベクトルを回転
		D3DXVec3TransformNormal(&direction, &direction, &rotation_matrix);

		//カメラ座標の更新
		position_ = lookat_position_ + (direction * viewing_vector_length_);
	}
}

/*-----------------------------------------------------------------------------
/*　注視点座標のコントロール
-----------------------------------------------------------------------------*/
void CameraComponent::ComputeRotationLookatPosition(float deltaTime)
{
	const bool is_rotation_up    = InputCheck::KeyPress(DIK_T);
	const bool is_rotation_down  = InputCheck::KeyPress(DIK_G);
	const bool is_rotation_right = InputCheck::KeyPress(DIK_F);
	const bool is_rotation_left  = InputCheck::KeyPress(DIK_H);
	const bool is_rotation = (is_rotation_up || is_rotation_down || is_rotation_right || is_rotation_left);

	if (is_rotation)
	{
		//回転の速度をラジアンに変換
		float radian = Math::ToRadian(rotation_degree_ * deltaTime);

		//回転情報
		D3DXMATRIX rotation_matrix;
		D3DXMatrixIdentity(&rotation_matrix);

		//向きベクトル
		D3DXVECTOR3 direction;

		/*--- カメラのワールド座標中心に回転 ---*/
		if (is_rotation_up)		{ D3DXMatrixRotationAxis(&rotation_matrix, &right_vector_,  radian); }
		if (is_rotation_down)	{ D3DXMatrixRotationAxis(&rotation_matrix, &right_vector_, -radian); }
		if (is_rotation_right)	{ D3DXMatrixRotationAxis(&rotation_matrix, &up_vector_,		radian); }
		if (is_rotation_left)	{ D3DXMatrixRotationAxis(&rotation_matrix, &up_vector_,	   -radian); }

		//向きベクトルを作成
		direction = lookat_position_ - position_;
		D3DXVec3Normalize(&direction, &direction);

		//向きベクトルを回転
		D3DXVec3TransformNormal(&direction, &direction, &rotation_matrix);

		//カメラ座標の更新
		lookat_position_ = position_ + (direction * viewing_vector_length_);
	}
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
						  , &position_	 	// 視点
						  , &lookat_position_	// 注視点
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