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

// 描画コンポーネント
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../../Component/RendererComponent/EffectRendererComponent.h"

// 音声コンポーネント
#include "../../../../Component/AudioComponent.h"

// 球の衝突判定
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// ボックスの衝突判定
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

// 敵の武器コンポーネント
#include "../../../../Component/WeaponComponent/EnemyBlasterWeaponComponent.h"
#include "../../../../Component/WeaponComponent/LaserCannonWeaponComponent.h"

// 値コンポーネント
#include "../../../../Component/ParameterComponent/FloatParameterComponent.h"

// 入力チェック
#include "../../../../../Input/InputCheck.h"

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"


#include "../../../../../Game.h"
#include "../../Bullet/NormalBullet.h"
#include "../../../../../SandBoxManager/ActorManager.h"
#include "../../../../../SandBoxManager/BulletManager.h"
#include "../../../../../CheckCollision.h"



/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Boss::Boss(Game* game)
	: Enemy(game)
	, enemy_state_old_(EnemyState::None)
	, motion_state_old_(EnemyMotionState::None)
	, effect_enemy_action_shoot_(nullptr)
	, effect_player_attack_hit_(nullptr)
	, enemy_damage_sound_effect_(nullptr)
	, max_hp_param_(nullptr)
	, hp_param_(nullptr)
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

	// 生成座標を初期化
	{
		this->transform_component_->SetTranslationY(-100.f);
		this->enemy_move_->SetStartPositionY(-100.f);

		// テスト用生成座標
		//this->transform_component_->SetTranslationZ(15.f);
	}

	// メッシュの生成
	{
		// ボスのメッシュ生成
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyBoss);
		//actor_mesh_->IsSetDrawable(false);
		actor_mesh_->SetEnableLighting(true);			// ライティングを有効にする
	}

	// エフェクトコンポーネントの生成
	{
		// 射撃行動通知エフェクト
		effect_enemy_action_shoot_ = NEW EffectRendererComponent(this);
		effect_enemy_action_shoot_->SetEffect(EffectType::EnemyActionGuide_Red);
		effect_enemy_action_shoot_->SetTranslationY(3.f);

		// ヒットエフェクト
		effect_player_attack_hit_ = NEW EffectRendererComponent(this);
		effect_player_attack_hit_->SetEffect(EffectType::HitEffect);
		effect_player_attack_hit_->SetTranslationY(3.f);

		// 爆発エフェクト
		effect_explosion_ = NEW EffectRendererComponent(this);
		effect_explosion_->SetEffect(EffectType::ExplosionBoss);
		effect_explosion_->SetTranslationY(3.f);
	}

	// 音声コンポーネントの生成
	{
		enemy_damage_sound_effect_ = NEW AudioComponent(this);
		enemy_damage_sound_effect_->SetSound(SoundType::DamageBoss);
		enemy_damage_sound_effect_->SetAudioVolume(1.f);
	}

	// ゲームマネージャへのポインタの取得
	{
		game_manager_ = this->FindGameObject(GameObject::TypeID::GameManager);
		if (game_manager_ == nullptr)
		{
			assert(!"StrongEnemy::Init()：ゲームマネージャへのポインタが取得できませんでした");
		}
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
		// 球
		{
			// 球の半径
			const float sphere_radius_size = 3.f;

			// 衝突判定
			sphere_collider_ = NEW SphereColliderComponent(this);
			sphere_collider_->SetOffsetTranslationY(COLLIDER_OFFSET_HEIGHT_POS);
			sphere_collider_->SetRadius(sphere_radius_size);

			// ギズモ
			sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
			sphere_gizmo_->SetTranslationY(COLLIDER_OFFSET_HEIGHT_POS);
			sphere_gizmo_->SetScale(sphere_radius_size);
			//sphere_gizmo_->IsSetDrawable(false);
		}

		// 箱
		{
			// 箱の高さ
			const float box_height_size = 1.f;

			// 箱の水平軸の大きさ
			const float box_size = 7.f;

			// 衝突判定
			obb_collider_ = NEW OBBColliderComponent(this);
			obb_collider_->SetOffsetTranslationY(COLLIDER_OFFSET_HEIGHT_POS);
			obb_collider_->SetDirLength(box_size, AxisType::X);
			obb_collider_->SetDirLength(box_height_size, AxisType::Y);
			obb_collider_->SetDirLength(box_size, AxisType::Z);

			// ギズモ
			obb_collider_gizmo_ = NEW BoxGizmoRendererComponent(this);
			obb_collider_gizmo_->SetTranslationY(COLLIDER_OFFSET_HEIGHT_POS);
			obb_collider_gizmo_->SetScaleX(box_size);
			obb_collider_gizmo_->SetScaleY(box_height_size);
			obb_collider_gizmo_->SetScaleZ(box_size);
			//obb_collider_gizmo_->IsSetDrawable(false);
		}
	}

	// 値コンポーネントの作成
	{
		// 最大HP
		max_hp_param_ = NEW FloatParameterComponent(this);
		max_hp_param_->SetParameterType(ParameterType::BossMaxHP);
		max_hp_param_->SetFloat(max_hit_point_);

		// HP
		hp_param_ = NEW FloatParameterComponent(this);
		hp_param_->SetParameterType(ParameterType::BossHP);
		hp_param_->SetFloat(hit_point_);
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

	// 射撃行動に入ることを通知する
	if (ai_state == EnemyState::Shooting)
	{
		if (ai_state != enemy_state_old_)
		{
			effect_enemy_action_shoot_->Play();
		}
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

	// 値コンポーネントの更新
	this->UpdateParameter(deltaTime);

	// 武器コンポーネントの更新
	{
		this->UpdateBlaster(deltaTime, ai_state, move_motion_state);

		// レーザー砲の更新
		this->UpdateLaserCannon(ai_state, move_motion_state);
	}

	// 衝突判定の更新
	this->UpdateCollision(deltaTime);

	// 1フレーム前の情報を更新
	enemy_state_old_ = ai_state;
	motion_state_old_ = move_motion_state;


	// 自身を破壊されたら
	if (this->GetGameObjectState() == State::Destroy)
	{
		// 破壊状態での初期化を行う
		if (is_destroy_ == false)
		{
			// 破壊される状態として記憶を行う
			is_destroy_ = true;

			// 爆発エフェクトを再生
			effect_explosion_->Play();

			// スコアへ加算する
			auto parameter_components = game_manager_->GetParameterComponents();
			for (auto parameter_component : parameter_components)
			{
				// スコアへの値コンポーネントへのポインタを取得
				auto parameter_component_type = parameter_component->GetParameterType();
				if (parameter_component_type == ParameterType::Score)
				{
					parameter_component->AddInt(100);
					break;
				}
			}

			sphere_gizmo_->IsSetDrawable(false);
		}

		// 破壊までの時間
		destroy_interval_time_ += deltaTime;

		// 自身を破棄する
		const float MAX_DESTROY_INTERVAL_TIME = 6.f;

		// メッシュの描画を無効に
		if (destroy_interval_time_ >= (MAX_DESTROY_INTERVAL_TIME * 0.6f))
		{
			actor_mesh_->IsSetDrawable(false);
		}

		// 自身を破棄
		if (destroy_interval_time_ >= MAX_DESTROY_INTERVAL_TIME)
		{
			// プレイヤーが破壊されたのでゲームオーバーにする
			game_->SetGameState(Game::GameState::GameFinishScene);

			this->SetGameObjectState(State::Dead);
		}
		return;
	}
}

/*-----------------------------------------------------------------------------
/* 値コンポーネントの更新処理
-----------------------------------------------------------------------------*/
void Boss::UpdateParameter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const bool is_nullptr_max_hp_param = (max_hp_param_ == nullptr);
	const bool is_nullptr_hp_param = (hp_param_ == nullptr);

	// 最大HPの値コンポーネントのnullチェック
	if (is_nullptr_max_hp_param)
	{
		assert(!"Boss::UpdateParameter():値コンポーネント:max_hp_param_ が”nullptr”でした");
		return;
	}

	// HPの値コンポーネントのnullチェック
	if (is_nullptr_hp_param)
	{
		assert(!"Boss::UpdateParameter():値コンポーネント:hp_param_ が”nullptr”でした");
		return;
	}

	// 最大HPの更新
	max_hp_param_->SetFloat(max_hit_point_);

	// 現在のHPの更新
	hp_param_->SetFloat(hit_point_);
}

/*-----------------------------------------------------------------------------
/* 光線銃の更新処理
-----------------------------------------------------------------------------*/
void Boss::UpdateBlaster(float deltaTime, EnemyState enemyState, EnemyMotionState motionState)
{
	// ゲームの状態が切り替わったら
	if (this->GetGameObjectState() == GameObject::State::Destroy) { return; }

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

/*-----------------------------------------------------------------------------
/* 衝突判定の更新処理
-----------------------------------------------------------------------------*/
void Boss::UpdateCollision(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (InputCheck::KeyTrigger(DIK_I))
	{
		hit_point_ = 100.f;
	}

	// HPの下限を設定
	if (hit_point_ <= 0.f)
	{
		// エネミーが破壊される状態へ
		this->SetGameObjectState(State::Destroy);
		hit_point_ = 0.f;
	}

	auto boss_state_ = this->enemy_ai_->GetEnemyState();
	auto boss_motion_state_ = this->enemy_move_->GetMotionState();

	const bool is_weakpoint_ready = ((boss_state_ == EnemyState::LaserCannon) || (boss_state_ == EnemyState::Shooting));
	const bool is_weakpoint_enable = ((boss_motion_state_ == EnemyMotionState::Attack) && is_weakpoint_ready);

	// 弱点が有効ではなかった場合
	if (is_weakpoint_enable == false) { return; }

	// バレットの衝突判定
	auto bullets = game_->GetBulletManager()->GetBulletGameObjectList();
	for (auto bullet : bullets)
	{
		// Bulletの親オブジェクトがPlayerかを調べる
		auto bullet_parent_game_object_type = bullet->GetParentGameObjectType();

		if (bullet_parent_game_object_type != GameObject::TypeID::Player)
		{
			continue;
		}

		// エネミーのバレットの衝突判定を取得
		if (CheckCollision::SphereVSSpghre(this->GetSphereCollider(), bullet->GetSphereCollider()))
		{
			// ダメージを受けた時のエフェクトを再生
			effect_player_attack_hit_->Play();

			// ダメージを受けたSEを再生
			enemy_damage_sound_effect_->Play();

			// ダメージをを受ける
			const float DAMAGE = -5.f;
			hit_point_ += DAMAGE;

			// 衝突したバレットを破棄する
			bullet->SetGameObjectState(State::Dead);
			break;
		}

	}
}

/*=============================================================================
/*		End of File
=============================================================================*/