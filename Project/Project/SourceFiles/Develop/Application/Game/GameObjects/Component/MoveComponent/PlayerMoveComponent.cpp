/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PlayerMoveComponent.cpp] プレイヤーの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：プレイヤーの移動コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "PlayerMoveComponent.h"
#include "../ColliderComponent/OBBColliderComponent.h"
#include "../RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../Input/InputCheck.h"
#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
PlayerMoveComponent::PlayerMoveComponent(GameObject* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
	, is_move_top_(false)
	, is_move_bottom_(false)
	, is_move_left_(false)
	, is_move_right_(false)
	, move_speed_(10.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
PlayerMoveComponent::~PlayerMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool PlayerMoveComponent::Init(void)
{
	// プレイヤーのサンドボックスを初期化
	{
		player_sandbox_ = NEW OBBColliderComponent(owner_);
		player_sandbox_->SetDirLength(5.f, AxisType::X);
		player_sandbox_->SetDirLength(3.f, AxisType::Y);
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void PlayerMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void PlayerMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void PlayerMoveComponent::Update(float deltaTime)
{
	// 線形球面保管を行うフラグをONに
	{
		owner_transform_->IsSetExecuteSlerp(true);
		owner_transform_->SetSlerpSpeed(1.2f);
	}

	// 入力から移動の状態を更新
	Vector2 left_thumb = InputCheck::XInputThumbLeft(PadIndex::Pad1);
	{
		this->UpdateMovementState(left_thumb);
	}

	// 上下左右の移動処理
	D3DXVECTOR3 front_vector = *owner_transform_->GetFrontVector();
	{
		// 上下の移動処理
		{
			const float move_value = left_thumb.y_ * (front_vector.y * move_speed_);
			if (is_move_top_)
			{
				owner_transform_->SetRotationPitch(-30.f);
				owner_transform_->AddTranslationY(move_value * deltaTime);
			}

			if (is_move_bottom_)
			{
				owner_transform_->SetRotationPitch(30.f);
				owner_transform_->AddTranslationY(-move_value * deltaTime);
			}
		}
		
		// 左右の移動処理
		{
			const float move_value = left_thumb.x_ * (front_vector.x * move_speed_);
			if (is_move_right_)
			{
				owner_transform_->SetRotationYaw(30.f);
				owner_transform_->SetRotationRoll(-15.f);
				owner_transform_->AddTranslationX(move_value * deltaTime);
			}

			if (is_move_left_)
			{
				owner_transform_->SetRotationYaw(-30.f);
				owner_transform_->SetRotationRoll(15.f);
				owner_transform_->AddTranslationX(-move_value * deltaTime);
			}
		}

		//各回転軸に対してなにもしていない時に姿勢を更新
		{
			const bool is_disable_yaw = !(is_move_left_ || is_move_right_);
			if (is_disable_yaw)
			{
				owner_transform_->SetRotationYaw(0.f);
				owner_transform_->SetRotationRoll(0.f);
			}

			const bool is_disable_pitch = !(is_move_top_ || is_move_bottom_);
			if (is_disable_pitch)
			{
				owner_transform_->SetRotationPitch(0.f);
				owner_transform_->SetRotationRoll(0.f);
			}
		}
	}

	// プレイヤーの移動範囲を制限
	{
		// 移動範囲の取得
		float x_axis_sandbox_length = player_sandbox_->GetDirLength(AxisType::X);
		float y_axis_sandbox_length = player_sandbox_->GetDirLength(AxisType::Y);

		// プレイヤーの位置情報の取得
		D3DXVECTOR3 position = *owner_transform_->GetPosition();

		// 上下の移動制限
		{
			if (position.y >=  y_axis_sandbox_length)
			{
				owner_transform_->SetTranslation(*owner_transform_->GetOldPosition());
			}

			if (position.y <= -y_axis_sandbox_length)
			{
				owner_transform_->SetTranslation(*owner_transform_->GetOldPosition());
			}
		}

		// 左右の移動制限
		{
			if (position.x >= x_axis_sandbox_length)
			{
				owner_transform_->SetTranslation(*owner_transform_->GetOldPosition());
			}

			if (position.x <= -x_axis_sandbox_length)
			{
				owner_transform_->SetTranslation(*owner_transform_->GetOldPosition());
			}
		}
	}
}

/*-----------------------------------------------------------------------------
/*　移動の状態更新処理
-----------------------------------------------------------------------------*/
void PlayerMoveComponent::UpdateMovementState(Vector2& padThumb)
{
	// 状態の初期化
	is_move_top_	=
	is_move_bottom_	=
	is_move_left_	=
	is_move_right_	= false;

	float deadzone_yaw	 = 0.4f;
	float deadzone_pitch = 0.1f;


	// 上下移動
	{
		if (padThumb.y_ >=  deadzone_pitch)
		{
			is_move_top_ = true;
		}

		if (padThumb.y_ <= -deadzone_pitch)
		{
			is_move_bottom_ = true;
		}
	}

	// 左右移動
	{
		if (padThumb.x_ <= -deadzone_yaw)
		{
			is_move_left_ = true;
		}

		if (padThumb.x_ >=  deadzone_yaw)
		{
			is_move_right_ = true;
		}
	}

	ImGui::Begin("TestThumb");
	ImGui::Text("Thumb_X:%f", padThumb.x_);
	ImGui::Text("Thumb_Y:%f", padThumb.y_);
	ImGui::Text("Top:%s", is_move_top_ ? "true" : "false");
	ImGui::Text("Bottom:%s", is_move_bottom_ ? "true" : "false");
	ImGui::Text("Left:%s", is_move_left_ ? "true" : "false");
	ImGui::Text("Right:%s", is_move_right_ ? "true" : "false");
	ImGui::End();

}

/*=============================================================================
/*		End of File
=============================================================================*/