/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Camera.cpp] カメラクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カメラクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "Camera.h"
#include "../../../Math.h"
#include "../Component/CameraComponent.h"
#include "../../Renderer.h"

#include "../../Input/InputCheck.h"
#include "../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Camera::Camera(class Game* game)
	: GameObject(game)
	, game_(game)
	, is_moved_(false)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

	camera_component_ = NEW CameraComponent(this);

	game_->GetRenderer()->AddCameraGameObjectAddress(this);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Camera::~Camera(void)
{
	game_->GetRenderer()->AddCameraGameObjectAddress(this);
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
Camera* Camera::Create(class Game* game)
{
	return NEW Camera(game);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Camera::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Camera::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの入力処理
-----------------------------------------------------------------------------*/
void Camera::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの更新処理
-----------------------------------------------------------------------------*/
void Camera::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//カメラを操作するか
	const bool is_camera_controlling = camera_component_->IsGetCameraControlling();

	ImGui::Begin("camera");
	ImGui::SetNextTreeNodeOpen(true);
	if (ImGui::TreeNode("CameraControll"))
	{
		if (is_camera_controlling)
		{
			if (ImGui::Button("OFF"))
			{
				camera_component_->IsSetCameraControlling(false);
			}
		}
		else
		{
			if (ImGui::Button("ON"))
			{
				camera_component_->IsSetCameraControlling(true);
			}
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

/*-----------------------------------------------------------------------------
/* ビュー行列の取得
-----------------------------------------------------------------------------*/
D3DXMATRIX* Camera::GetViewMatrix(void)
{
	return camera_component_->GetViewMatrix();
}

/*-----------------------------------------------------------------------------
/* 逆ビュー行列の取得
-----------------------------------------------------------------------------*/
D3DXMATRIX* Camera::GetViewInverseMatrix(void)
{
	return camera_component_->GetViewInverseMatrix();
}

/*-----------------------------------------------------------------------------
/* 2Dプロジェクション行列の取得
-----------------------------------------------------------------------------*/
D3DXMATRIX* Camera::GetProjection2DMatrix(void)
{
	return camera_component_->GetProjection2DMatrix();
}

/*-----------------------------------------------------------------------------
/* 3Dプロジェクション行列の取得
-----------------------------------------------------------------------------*/
D3DXMATRIX* Camera::GetProjection3DMatrix(void)
{
	return camera_component_->GetProjection3DMatrix();
}

/*-----------------------------------------------------------------------------
/* カメラが移動したかのフラグ
-----------------------------------------------------------------------------*/
bool Camera::IsGetCameraMoved(void) const
{
	return camera_component_->IsGetCameraMoved();
}

/*=============================================================================
/*		End of File
=============================================================================*/