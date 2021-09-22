/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Boss.cpp] ボスゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../../StdAfx.h"
#include "Boss.h"

// 移動コンポーネント
#include "../../../../Component/MoveComponent/EnemyMoveComponent/BossMoveComponent.h"

// ボスAIコンポーネント
#include "../../../../Component/AIComponent/EnemyAIComponent/BossAIComponent.h"

// メッシュコンポーネント
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"

// 球の衝突判定
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// ボックスの衝突判定
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

// 敵の武器コンポーネント
#include "../../../../Component/WeaponComponent/EnemyBlasterWeaponComponent.h"
#include "../../../../Component/WeaponComponent/LaserCannonWeaponComponent.h"

// 入力チェック
#include "../../../../../Input/InputCheck.h"

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"


#include "../../../../../Game.h"
#include "../../../../../SandBoxManager/ActorManager.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Boss::Boss(Game* game)
	: Enemy(game)
	, enemy_state_old_(EnemyState::None)
	, motion_state_old_(EnemyMotionState::None)
	, is_fire_(false)
	, blaster_index_(0)
	, switch_time_(0.f)
	, laser_cannon_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Boss::~Boss(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Boss::Init(void)
{
	// ボスのAIを生成 
	enemy_ai_ = NEW BossAIComponent(this);

	// ボスの移動コンポーネントを生成
	enemy_move_ = NEW BossMoveComponent(this);

	// メッシュの生成
	{
		// ボスのメッシュ生成
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyBoss);
		actor_mesh_->SetEnableLighting(true);			// ライティングを有効にする

		// 生成座標を調整
		this->transform_component_->SetTranslationY(-100.f);
		this->transform_component_->SetTranslationZ(15.f);
	}

	// ボスの状態を初期化
	{
		auto init_boss_state = EnemyState::Enter;

		// 敵の状態を初期化
		enemy_ai_->SetEnemyState(init_boss_state);
		enemy_move_->SetEnemyState(init_boss_state);
	}

	// 武器の生成
	{
		for (int i = 0; i < MAX_WEAPON_COUNT; i++)
		{
			enemy_blaster_[i] = nullptr;
			enemy_blaster_[i] = NEW EnemyBlasterWeaponComponent(this);
		}
	
		laser_cannon_ = NEW LaserCannonWeaponComponent(this);
		laser_cannon_->SetTranslationY(-0.5f);
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
			obb_collider_->SetDirLength(box_size	   , AxisType::X);
			obb_collider_->SetDirLength(box_height_size, AxisType::Y);
			obb_collider_->SetDirLength(box_size	   , AxisType::Z);

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
void Boss::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの入力処理
-----------------------------------------------------------------------------*/
void Boss::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* overrideで自分自身を更新
-----------------------------------------------------------------------------*/
void Boss::UpdateGameObject(float deltaTime)
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
	┃　　Move　　┃  ┃　　Boss 　 ┃　┃　　AI　　　┃
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
	switch (ai_state)
	{
	case EnemyState::BodyPress:
		attack_ = ATTACK_VALUE_BODY_PRESS;
		break;

	case EnemyState::Shooting:
		attack_ = ATTACK_VALUE_SHOOT;
		break;

	case EnemyState::LaserCannon:
		attack_ = ATTACK_VALUE_LASER_CANNON;
		break;

	case EnemyState::Destroy:
		attack_ = 0.f;
		break;

	default:
		break;
	}

	//　武器コンポーネントの更新
	{
		this->UpdateBlaster(deltaTime, ai_state, move_motion_state);

		// レーザー砲の更新
		this->UpdateLaserCannon(ai_state, move_motion_state);
	}

	// 1フレーム前の情報を更新
	enemy_state_old_ = ai_state;
	motion_state_old_ = move_motion_state;
}

/*-----------------------------------------------------------------------------
/* 光線銃の更新処理
-----------------------------------------------------------------------------*/
void Boss::UpdateBlaster(float deltaTime, EnemyState enemyState, EnemyMotionState motionState)
{
	// 座標の更新
	{
		// それぞれの座標の一時保管先
		D3DXVECTOR3 pos;

		// 角度を三分割
		const float degree = 360.f / 3.f;

		// 半径
		const float radius = 5.0f;

		for (int i = 0; i < MAX_WEAPON_COUNT; i++)
		{
			// 角度をradian に変換
			const float radian = Math::ToRadian(degree * i);
			pos.x = cosf(radian) * radius;
			pos.y = 1.0f;
			pos.z = sinf(radian) * radius;

			// 座標の計算
			enemy_blaster_[i]->SetTranslation(pos);
		}
	}

	// 攻撃を行うかの判定
	if (enemyState != EnemyState::Shooting) { return; }
	if (motionState != EnemyMotionState::Attack) { return; }

	if (blaster_index_ >= MAX_WEAPON_COUNT)
	{
		blaster_index_ = 0;
	}

	// 切り替わり時間を計算
	switch_time_ += deltaTime;

	const float SWITCH_TIME_LIMIT = 0.3f;
	if (switch_time_ >= SWITCH_TIME_LIMIT)
	{
		switch_time_ = 0.f;
		is_fire_ = true;
	}

	if (is_fire_ == true)
	{
		enemy_blaster_[blaster_index_]->Fire();
		blaster_index_++;
		is_fire_ = false;
	}
}

/*-----------------------------------------------------------------------------
/* レーザー砲の更新処理
-----------------------------------------------------------------------------*/
void Boss::UpdateLaserCannon(EnemyState enemyState, EnemyMotionState motionState)
{
	if (enemyState != EnemyState::LaserCannon) { return; }

	// ボスのモーション状態を通知
	laser_cannon_->SetEnemyMotionState(motionState);

	// ステートが切り替わった瞬間とる
	if (enemy_state_old_ != enemyState)
	{
		is_fire_ = true;
	}

	if ((is_fire_ == true)
		&& (motionState == EnemyMotionState::Relay))
	{
		// レーザーを砲の発射
		laser_cannon_->Shoot();
		is_fire_ = false;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/