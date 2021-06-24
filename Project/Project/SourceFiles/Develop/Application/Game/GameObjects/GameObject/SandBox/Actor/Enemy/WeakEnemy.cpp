/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemy.cpp] 弱い敵のゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：弱い敵のゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../../StdAfx.h"
#include "WeakEnemy.h"

// 移動コンポーネント
#include "../../../../Component/MoveComponent/EnemyMoveComponent/WeakEnemyMoveComponent.h"

// ボスAIコンポーネント
#include "../../../../Component/AIComponent/EnemyAIComponent/WeakEnemyAIComponent.h"

// メッシュコンポーネント
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"

// 球の衝突判定
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// ボックスの衝突判定
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

// 入力チェック
#include "../../../../../Input/InputCheck.h"

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"


#include "../../../../../Game.h"
#include "../../../../../SandBoxManager/ActorManager.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
WeakEnemy::WeakEnemy(Game* game)
	: Enemy(game)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
WeakEnemy::~WeakEnemy(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool WeakEnemy::Init(void)
{
	// ボスのAIを生成 
	enemy_ai_ = NEW WeakEnemyAIComponent(this);

	// ボスの移動コンポーネントを生成
	enemy_move_ = NEW WeakEnemyMoveComponent(this);

	{
		// ボスのメッシュ生成
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyWeak);
		actor_mesh_->SetEnableLighting(true);			// ライティングを有効にする

		// 生成座標を調整
		this->transform_component_->SetTranslationZ(15.f);
	}

	// ボスの状態を初期化
	{
		auto init_WeakEnemy_state = EnemyState::Enter;

		// 敵の状態を初期化
		enemy_ai_->SetEnemyState(init_WeakEnemy_state);
		enemy_move_->SetEnemyState(init_WeakEnemy_state);
	}

	// 衝突判定関係
	{
		// 衝突判定の高さ　オフセット座標
		const float collider_height_pos = 3.f;

		// 球
		{
			// 球の半径
			const float sphere_radius_size = 6.f;

			// 衝突判定
			sphere_collider_ = NEW SphereColliderComponent(this);
			sphere_collider_->SetTranslationY(collider_height_pos);
			sphere_collider_->SetRadius(sphere_radius_size);

			// ギズモ
			sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
			sphere_gizmo_->SetTranslationY(collider_height_pos);
			sphere_gizmo_->SetScale(sphere_radius_size);
		}

		// 箱
		{
			// 箱の高さ
			const float box_height_size = 1.5f;

			// 箱の水平軸の大きさ
			const float box_size = 16.f;

			// 衝突判定
			obb_collider_ = NEW OBBColliderComponent(this);
			obb_collider_->SetTranslationY(collider_height_pos);
			obb_collider_->SetDirLength(box_size, AxisType::X);
			obb_collider_->SetDirLength(box_height_size, AxisType::Y);
			obb_collider_->SetDirLength(box_size, AxisType::Z);

			// ギズモ
			box_gizmo_ = NEW BoxGizmoRendererComponent(this);
			box_gizmo_->SetTranslationY(collider_height_pos);
			box_gizmo_->AddScaleX(box_size);
			box_gizmo_->AddScaleY(box_height_size);
			box_gizmo_->AddScaleZ(box_size);
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void WeakEnemy::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの入力処理
-----------------------------------------------------------------------------*/
void WeakEnemy::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* overrideで自分自身を更新
-----------------------------------------------------------------------------*/
void WeakEnemy::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// AIコンポーネントにボスのHPを通知する
	{
		enemy_ai_->SetHitPoint(this->GetHitPoint());
	}

	/*
	*			←		EnemyState		←
	*
	┏━━━━━━┓←┏━━━━━━┓←┏━━━━━━┓
	┃　　Move　　┃  ┃ WeakEnemy  ┃　┃　　AI　　　┃
	┗━━━━━━┛→┗━━━━━━┛→┗━━━━━━┛
	*
	*			→		MotionState		→
	*/

	// AIコンポーネントから敵AIの行動ステートを取得
	auto ai_state = enemy_ai_->GetEnemyState();
	{
		// 移動コンポーネントへ、敵AIの行動ステートを通知
		enemy_move_->SetEnemyState(ai_state);
	}

	// 移動コンポーネントから移動モーション状態を取得
	auto move_motion_state = enemy_move_->GetMotionState();
	{
		// AIコンポーネントへ移動モーション状態を通知
		enemy_ai_->SetMotionState(move_motion_state);
	}

	//　自身のAIのステートから攻撃力を更新する
	//switch (ai_state)
	//{
	//case EnemyState::BodyPress:
	//	attack_ = ATTACK_VALUE_BODY_PRESS;
	//	break;

	//case EnemyState::Shooting:
	//	attack_ = ATTACK_VALUE_SHOOT;
	//	break;

	//case EnemyState::LaserCannon:
	//	attack_ = ATTACK_VALUE_LASER_CANNON;
	//	break;

	//case EnemyState::Destroy:
	//	attack_ = 0.f;
	//	break;

	//default:
	//	break;
	//}

}

/*=============================================================================
/*		End of File
=============================================================================*/