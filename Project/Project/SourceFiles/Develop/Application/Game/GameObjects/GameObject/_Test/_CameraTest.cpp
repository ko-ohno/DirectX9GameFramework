/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CameraTest.cpp] カメラテスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カメラテスト用ゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "_CameraTest.h"
#include "../../Component/CameraComponent.h"

#include "../../../Input/InputCheck.h"
#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
CameraTest::CameraTest(Game* game)
	: Camera(game)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
CameraTest::~CameraTest(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool CameraTest::Init(void)
{
	// カメラ座標の初期化
	camera_component_->SetCameraTranslation(0.f, 0.f, -15.f);

	// 注視点座標の初期化
	camera_component_->SetLookAtTranslation(0.f, 0.f,   0.f);
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void CameraTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void CameraTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void CameraTest::UpdateGameObject(float deltaTime)
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

		if (ImGui::Button("CameraTransformReset"))
		{
			camera_component_->SetCameraTransformReset();
		}
		ImGui::TreePop();
	}
	ImGui::End();

}

/*=============================================================================
/*		End of File
=============================================================================*/