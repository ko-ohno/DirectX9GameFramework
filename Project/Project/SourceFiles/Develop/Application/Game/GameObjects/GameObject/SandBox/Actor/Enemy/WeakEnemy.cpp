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
#include "../../Bullet/NormalBullet.h"
#include "../../../../../SandBoxManager/BulletManager.h"
#include "../../../../../CheckCollision.h"

// 移動コンポーネント
#include "../../../../Component/MoveComponent/EnemyMoveComponent/WeakEnemyMoveComponent.h"

// ボスAIコンポーネント
#include "../../../../Component/AIComponent/EnemyAIComponent/WeakEnemyAIComponent.h"

// メッシュコンポーネント
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"

// メッシュコンポーネント
#include "../../../../Component/RendererComponent/EffectRendererComponent.h"

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
	// 生成座標を初期化
	{
		this->transform_component_->SetTranslationY(-100.f);

		// テスト用生成座標
		//this->transform_component_->SetTranslationX(-3.f);
		//this->transform_component_->SetTranslationZ(8.f);
	}

	// 弱い敵のAIを生成 
	enemy_ai_ = NEW WeakEnemyAIComponent(this);

	// 弱い敵の移動コンポーネントを生成
	enemy_move_ = NEW WeakEnemyMoveComponent(this);

	// 生成座標を初期化
	{
		this->transform_component_->SetTranslationY(-100.f);
		this->enemy_move_->SetStartPositionY(-100.f);

		// テスト用生成座標
		//this->transform_component_->SetTranslationX(-3.f);
		//this->transform_component_->SetTranslationZ(8.f);
	}

	// 弱い敵のメッシュ生成
	{
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyWeak);
		actor_mesh_->SetScale(0.5f);
		actor_mesh_->SetTranslationY(-0.5f);
		actor_mesh_->SetEnableLighting(true);			// ライティングを有効にする
	}

	// 爆発エフェクトの生成
	{
		explosion_effect_ = NEW EffectRendererComponent(this);
		explosion_effect_->SetEffect(EffectType::ExplosionActor);
	}

	// ゲームマネージャへのポインタの取得
	{
		game_manager_ = this->FindGameObject(GameObject::TypeID::GameManager);
		if (game_manager_ == nullptr)
		{
			assert(!"WeakEnemy::Init()：ゲームマネージャへのポインタが取得できませんでした");
		}
	}

	// 弱い敵の状態を初期化
	{
		auto init_WeakEnemy_state = EnemyState::Idle;
		//init_WeakEnemy_state = EnemyState::MoveLoopLeftRight;

		// 敵の状態を初期化
		enemy_ai_->SetEnemyState(init_WeakEnemy_state);
		enemy_move_->SetEnemyState(init_WeakEnemy_state);
	}

	// 衝突判定関係
	{
		// 衝突判定の高さ　オフセット座標
		float collider_height_pos = 0.f;

		// 球
		{
			// 球の半径
			const float sphere_radius_size = 0.5f;

			// 衝突判定
			sphere_collider_ = NEW SphereColliderComponent(this);
			sphere_collider_->SetTranslationY(collider_height_pos);
			sphere_collider_->SetRadius(sphere_radius_size);

			// ギズモ
			sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
			sphere_gizmo_->SetTranslationY(collider_height_pos);
			sphere_gizmo_->SetScale(sphere_radius_size);
		}

		// 衝突判定の高さ　オフセット座標
		collider_height_pos = 0.f;

		// 箱
		{
			// 箱の高さ
			const float box_height_size = 1.f;

			// 箱の水平軸の大きさ
			const float box_scale = 1.f;

			// 衝突判定
			obb_collider_ = NEW OBBColliderComponent(this);
			obb_collider_->SetTranslationY(collider_height_pos);
			obb_collider_->SetDirLength(box_scale, AxisType::X);
			obb_collider_->SetDirLength(box_height_size, AxisType::Y);
			obb_collider_->SetDirLength(box_scale, AxisType::Z);

			// ギズモ
			obb_collider_gizmo_ = NEW BoxGizmoRendererComponent(this);
			obb_collider_gizmo_->SetVertexColor(0, 255, 255, 128);
			obb_collider_gizmo_->SetTranslationY(collider_height_pos);
			obb_collider_gizmo_->SetScaleX(box_scale);
			obb_collider_gizmo_->SetScaleY(box_height_size);
			obb_collider_gizmo_->SetScaleZ(box_scale);
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
	// AIコンポーネントに自身のHPを通知する
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

	if (true)
	{
		//
		// 本番環境スペース:値の伝達
		//

		// 始点座標の設定
		enemy_move_->SetStartPosition(position_start_);

		// 向きベクトルの設定
		enemy_move_->SetRotationMoveDirection(angle_yaw_, angle_pitch_, angle_roll_);

		// 移動ベクトルの長さを設定
		enemy_move_->SetMoveVectorLength(move_vector_length_);

		// 移動アクションの深さを設定
		enemy_move_->SetMoveActionMagnitude(move_action_magnitude_);

		// 最大の実行時間
		enemy_move_->SetMaxExecuteTime(max_execute_time_);
	}
	else
	{
		//
		// 実験スペース
		//

		switch (ai_state)
		{
		case EnemyState::MoveStraight:
			this->TestMoveStraight();
			break;

		case EnemyState::MoveStraightWaitOneTime:
			this->TestMoveStraightWaitOneTime();
			break;

		case EnemyState::MoveStraightWaitUpDown:
			this->TestMoveStraightWaitUpDown();
			break;

		case EnemyState::MoveRoundVertical:
			this->TestMoveRoundVertical();
			break;

		case EnemyState::MoveRoundHorizontal:
			this->TestMoveRoundHorizontal();
			break;

		case EnemyState::MoveLoopUpDown:
			this->TestMoveLoopUpDown();
			break;

		case EnemyState::MoveLoopLeftRight:
			this->TestMoveLoopLeftRight();
			break;

		case EnemyState::MoveShowOneTime:
			this->TestMoveShowOneTime();
			break;

		case EnemyState::Destroy:
			break;

		default:
			break;
		}
	}

	// WeakEnemyは必要なし
	//　自身のAIのステートから攻撃力を更新する
	//switch (ai_state)
	//{
	//case EnemyState::Idle:
	//	attack_ = 0.f;
	//	break;

	//case EnemyState::Shooting:
	//	attack_ = 0.f;
	//	break;

	//case EnemyState::Destroy:
	//	attack_ = 0.f;
	//	break;

	//default:
	//	attack_ = 10.f;
	//	break;
	//}

	// 自身を破壊されたら
	if (this->GetGameObjectState() == State::Destroy)
	{
		// 破壊状態での初期化を行う
		if (is_destroy_ == false)
		{
			// 爆発エフェクトを再生
			explosion_effect_->Play();

			// スコアへ加算する
			auto parameter_components = game_manager_->GetParameterComponents();
			for (auto parameter_component : parameter_components)
			{
				// スコアへの値コンポーネントへのポインタを取得
				auto parameter_component_type = parameter_component->GetParameterType();
				if (parameter_component_type == ParameterType::Score)
				{
					parameter_component->AddInt(10);
					break;
				}
			}

			actor_mesh_->IsSetDrawable(false);
			sphere_gizmo_->IsSetDrawable(false);

			// 破壊状態での初期化を行う
			is_destroy_ = true;
		}
		
		// 破壊までの時間
		destroy_interval_time_ += deltaTime;

		// 自身を破棄する
		const float MAX_DESTROY_INTERVAL_TIME = 1.f;
		if (destroy_interval_time_ >= MAX_DESTROY_INTERVAL_TIME)
		{
			// ゲームオブジェクトを破棄
			this->SetGameObjectState(State::Dead);
		}
		return;
	}

	// 衝突判定
	{	
		auto bullets = game_->GetBulletManager()->GetBulletGameObjectList();
		for (auto bullet : bullets)
		{
			// Bulletの所有者がPlayerかを調べる
			auto bullet_game_object = bullet->GetParentGameObject();
			if (bullet_game_object->GetType() != GameObject::TypeID::Player)
			{
				continue;
			}

			// プレイヤーのバレットの衝突判定を取得
			auto components = bullet->GetComponents();
			for (auto component : components)
			{
				auto component_type = component->GetComponentType();
				if (component_type == Component::TypeID::SphereColliderComponent)
				{
					if (CheckCollision::SphereVSSpghre(this->GetSphereCollider(), bullet->GetSphereCollider()))
					{
						// エネミーが破壊される
						this->SetGameObjectState(State::Destroy);

						// 衝突したバレットを破棄する
						bullet->SetGameObjectState(State::Dead);
						break;
					}
				}
			}
		}
	}
}

/*-----------------------------------------------------------------------------
/* 直線移動処理
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveStraight() 
{		
	// 始点座標の設定
	enemy_move_->SetStartPositionX(30.f);
	enemy_move_->SetStartPositionZ(10.f);

	// 向きベクトルの設定
	enemy_move_->SetRotationMoveDirectionYaw(-90);

	// 移動ベクトルの長さを設定
	enemy_move_->SetMoveVectorLength(60.f);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* 直線移動して一度待つ
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveStraightWaitOneTime()
{
	// 始点座標の設定
	enemy_move_->SetStartPositionX(30.f);
	enemy_move_->SetStartPositionZ(10.f);

	// 向きベクトルの設定
	enemy_move_->SetRotationMoveDirectionYaw(-90);

	// 移動ベクトルの長さを設定
	enemy_move_->SetMoveVectorLength(60.f);

	enemy_move_->SetMoveActionMagnitude(move_action_magnitude_);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* S字カーブ移動行動
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveStraightWaitUpDown()
{
	// 始点座標の設定
	enemy_move_->SetStartPositionX(15.f);
	enemy_move_->SetStartPositionZ(10.f);

	// 向きベクトルの設定
	enemy_move_->SetRotationMoveDirectionYaw(-90);

	// 移動ベクトルの長さを設定
	enemy_move_->SetMoveVectorLength(30.f);

	enemy_move_->SetMoveActionMagnitude(10.f);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* 垂直に半円を描く行動
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveRoundVertical()
{
	// 始点座標の設定
	//enemy_move_->SetStartPositionX(10.f);
	enemy_move_->SetStartPositionY( 5.f);
	enemy_move_->SetStartPositionZ(10.f);

	// 向きベクトルの設定
	enemy_move_->SetRotationMoveDirectionPitch(90);

	// 移動ベクトルの長さを設定
	enemy_move_->SetMoveVectorLength(10.f);

	enemy_move_->SetMoveActionMagnitude(10.f);

	enemy_move_->SetMaxExecuteTime(2.f);
}

/*-----------------------------------------------------------------------------
/* 水平に半円を描く行動
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveRoundHorizontal()
{
	// 始点座標の設定
	enemy_move_->SetStartPositionX(5.f);
	//enemy_move_->SetStartPositionY(5.f);
	enemy_move_->SetStartPositionZ(10.f);

	// 向きベクトルの設定
	enemy_move_->SetRotationMoveDirectionYaw(90);
	//enemy_move_->SetRotationMoveDirectionPitch(90);

	// 移動ベクトルの長さを設定
	enemy_move_->SetMoveVectorLength(-10.f);

	enemy_move_->SetMoveActionMagnitude(5.f);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* 上下ループ移動行動
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveLoopUpDown()
{
	// 始点座標の設定
	enemy_move_->SetStartPositionX(-30.f);
	enemy_move_->SetStartPositionZ(10.f);

	// 向きベクトルの設定
	enemy_move_->SetRotationMoveDirectionYaw(90);
	//enemy_move_->SetRotationMoveDirectionPitch(90);

	// 移動ベクトルの長さを設定
	enemy_move_->SetMoveVectorLength(60.f);

	enemy_move_->SetMoveActionMagnitude(5.f);

	enemy_move_->SetMaxExecuteTime(8.f);
}

/*-----------------------------------------------------------------------------
/* 左右ループ移動行動
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveLoopLeftRight()
{
	// 始点座標の設定
	enemy_move_->SetStartPositionY( 5.f);
	enemy_move_->SetStartPositionZ(10.f);

	// 向きベクトルの設定
	//enemy_move_->SetRotationMoveDirectionYaw(90);
	enemy_move_->SetRotationMoveDirectionPitch(90);

	// 移動ベクトルの長さを設定
	enemy_move_->SetMoveVectorLength(10.f);

	enemy_move_->SetMoveActionMagnitude(10.f);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* 画面端から顔出し行動
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveShowOneTime()
{
	// 始点座標の設定
	enemy_move_->SetStartPositionX(30.f);
	enemy_move_->SetStartPositionZ(10.f);

	// 向きベクトルの設定
	enemy_move_->SetRotationMoveDirectionYaw(-90);

	// 移動ベクトルの長さを設定
	enemy_move_->SetMoveVectorLength(60.f);

	enemy_move_->SetMoveActionMagnitude(move_action_magnitude_);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*=============================================================================
/*		End of File
=============================================================================*/