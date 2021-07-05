/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameCamera.cpp] カメラゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カメラゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "GameCamera.h"
#include "../../Component/CameraComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"

#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
GameCamera::GameCamera(Game* game)
	: Camera(game)
	, lookat_point_gizmo_(nullptr)
	, vertical_camera_shake_(0.f)
	, is_move_top_(true)
	, is_move_bottom_(false)
	, is_value_over_(false)
	, is_value_under_(false)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
GameCamera::~GameCamera(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool GameCamera::Init(void)
{
	// カメラ座標の初期化
	{
		camera_component_->SetLookAtTranslationX(0.f);
		camera_component_->SetLookAtTranslationY(0.f);

		camera_component_->SetCameraTranslationX(0.f);
		camera_component_->SetCameraTranslationY(0.f);
		camera_component_->SetCameraTranslationZ(-12.f);
	}

	// 注視点座標のギズモを表示
	lookat_point_gizmo_ = NEW BoxGizmoRendererComponent(this);
	lookat_point_gizmo_->SetScale(0.1f);
	lookat_point_gizmo_->SetVertexColor(255, 0, 0);

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void GameCamera::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void GameCamera::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void GameCamera::UpdateGameObject(float deltaTime)
{
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

	if (is_camera_controlling != true)
	{
		// このカメラゲームオブジェクトの親のとしてプレイヤーを取得
		if (game_object_parent_ == nullptr)
		{
			//ゲームオブジェクトのリストを総検索
			auto game_objects = game_->GetGameObjects();
			for (auto game_object : game_objects)
			{
				// プレイヤーの取得
				auto game_object_id = game_object->GetType();
				if (game_object_id == TypeID::Player)
				{
					game_object_parent_ = game_object;
					break;
				}
			}
		}

		// ゲームのカメラ用にプレイヤー姿勢を取得
		if (game_object_parent_ != nullptr)
		{
			// 注視点をプレイヤー座標に設定
			static D3DXVECTOR3 lookat_position = {0.f, 0.f, 0.f};
			static D3DXVECTOR3 camera_position = *camera_component_->GetPosition();

			// 注視点となるプレイヤーの位置情報の取得
			D3DXVECTOR3 lookat_target = *game_object_parent_->GetTransform()->GetPosition();

			// 垂直のカメラ揺れを作成
			static constexpr float camera_shake_range = 0.004f;
			static constexpr float camera_shake_value = 0.005f * 2;
			{
				// 条件式の代入により、注視点の上昇と下降のon/offが切り替わる
				is_value_over_  = (vertical_camera_shake_ >=  camera_shake_range);
				is_value_under_ = (vertical_camera_shake_ <= -camera_shake_range);
				{
					if (is_value_over_)
					{
						is_move_top_ = false;
						is_move_bottom_ = true;
					}

					if (is_value_under_)
					{
						is_move_top_ = true;
						is_move_bottom_ = false;
					}

					if (is_move_top_)
					{
						vertical_camera_shake_ += camera_shake_value * deltaTime;
					}

					if (is_move_bottom_)
					{
						vertical_camera_shake_ -= camera_shake_value * deltaTime;
					}
				}
			}
			
			ImGui::Begin("CameraShake");
			ImGui::Text("Shake:%f", vertical_camera_shake_);
			ImGui::End();

			// カメラの値を補間するための強度
			static constexpr float smooth_time = 0.5f;

			// 注視点座標を補間
			lookat_target.x = Math::Lerp(lookat_position.x, lookat_target.x, Easing::QuintInOut(smooth_time));
			lookat_target.y = Math::Lerp(lookat_position.y, lookat_target.y, Easing::QuintInOut(smooth_time));

			// カメラ座標を補間
			camera_position.x = Math::Lerp(camera_position.x, lookat_target.x, Easing::QuintInOut(smooth_time));
			camera_position.y = Math::Lerp(camera_position.y, lookat_target.y, Easing::QuintInOut(smooth_time));

			// プレイヤー座標に垂直揺れを加算した座標
			lookat_target.y = lookat_target.y + vertical_camera_shake_;
		
			// カメラの更新
			{
				// 注視点座標の更新
				camera_component_->SetLookAtTranslation(lookat_target);

				// カメラ座標の更新
				camera_component_->SetCameraTranslation(camera_position);
			}

			lookat_point_gizmo_->SetTranslation(lookat_target);
		}
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/