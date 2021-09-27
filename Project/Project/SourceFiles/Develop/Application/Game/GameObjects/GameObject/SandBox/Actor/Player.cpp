/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Player.cpp] プレイヤーのゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：プレイヤーの処理を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "Player.h"
#include "../Bullet/ChargeBullet.h"
#include "../../../../CheckCollision.h"
#include "Enemy.h"
#include "../../../../SandBoxManager/EnemieManager.h"
#include "../Bullet/NormalBullet.h"
#include "../../../../SandBoxManager/BulletManager.h"

// 描画コンポーネント
#include "../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../../Component/RendererComponent/BillboardRendererComponent.h"

// 武器コンポーネント
#include "../../../Component/WeaponComponent/BlasterWeaponComponent.h"
#include "../../../Component/WeaponComponent/ChargeBlasterWeaponComponent.h"

// 移動コンポーネント
#include "../../../Component/MoveComponent/PlayerMoveComponent.h"

// 衝突判定コンポーネント
#include "../../../Component/ColliderComponent/OBBColliderComponent.h"
#include "../../../Component/ColliderComponent/SphereColliderComponent.h"

// 音声コンポーネント
#include "../../../Component/AudioComponent.h"

// ギズモコンポーネント
#include "../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

// 値コンポーネント
#include "../../../Component/ParameterComponent/FloatParameterComponent.h"

// 入力チェック
#include "../../../../Input/InputCheck.h"

// ImGUI
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Player::Player(Game* game)
	: Actor(game)
	, player_move_(nullptr)
	, effect_after_burner_(nullptr)
	, effect_enemy_attack_hit_(nullptr)
	, near_reticle_(nullptr)
	, far_reticle_(nullptr)
	, lockon_reticle_(nullptr)
	, left_blaster_(nullptr)
	, right_blaster_(nullptr)
	, charge_blaster_(nullptr)
	, player_damege_sound_effect_(nullptr)
	, max_hp_param_(nullptr)
	, hp_param_(nullptr)
	, is_blaster_fire_(false)
	, is_received_damage_(false)
	, damage_recieve_interval_time_(0.f)
	, boss_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Player::~Player(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Player::Init(void)
{
	// プレイヤーの移動コンポーネントの生成
	player_move_ = NEW  PlayerMoveComponent(this);

	// 描画コンポーネント
	{
		// 自機の表示
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::SpaceShip);
		actor_mesh_->SetEnableLighting(true);
		actor_mesh_->SetScale(0.5f);

		// エフェクトコンポーネント
		{
			// アフターバーナーの表示
			effect_after_burner_ = NEW EffectRendererComponent(this);
			effect_after_burner_->SetEffect(EffectType::AfterBurner);
			effect_after_burner_->Play();

			// アフターバーナーの表示
			effect_enemy_attack_hit_ = NEW EffectRendererComponent(this);
			effect_enemy_attack_hit_->SetEffect(EffectType::HitEffect);
		}

		// レティクルの設定
		{
			// 遠くのレティクル
			{
				far_reticle_ = NEW BillboardRendererComponent(this, 290);
				far_reticle_->SetTexture(TextureType::FarReticle);
				far_reticle_->SetVertexColor(0, 255, 0, 255);
				far_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// レティクルの性質の調整
				far_reticle_->SetScale(1.2f);
				far_reticle_->SetTranslationZ(10.f);
			}

			//　手前のレティクル
			{
				near_reticle_ = NEW BillboardRendererComponent(this, 290);
				near_reticle_->SetTexture(TextureType::NearReticle);
				near_reticle_->SetVertexColor(0, 255, 0, 255);
				near_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// レティクルの性質の調整
				near_reticle_->SetScale(1.4f);
				near_reticle_->SetTranslationZ(9.f);
			}

			//　ロックオンのレティクル
			{
				lockon_reticle_ = NEW BillboardRendererComponent(this, 290);
				lockon_reticle_->SetTexture(TextureType::NearReticle);
				lockon_reticle_->SetVertexColor(0, 255, 0, 255);
				lockon_reticle_->SetRendererLayerType(RendererLayerType::UI);

				// レティクルの性質の調整
				lockon_reticle_->SetScale(1.4f);
				lockon_reticle_->SetTranslationZ(9.f);
			}
		}
	}

	// 音声コンポーネント
	{
		player_damege_sound_effect_ = NEW AudioComponent(this);
		player_damege_sound_effect_->SetSound(SoundType::DamagePlayer);
		player_damege_sound_effect_->SetAudioVolume(1.f);
	}

	// 武器コンポーネント
	{
		// 左の光線銃
		left_blaster_ = NEW BlasterWeaponComponent(this);

		// 右の光線銃
		right_blaster_ = NEW BlasterWeaponComponent(this);

		// チャージ弾用の光線銃
		charge_blaster_ = NEW ChargeBlasterWeaponComponent(this);
	}

	//　衝突判定コンポーネント
	{
		// OBBの大きさ
		const float sphere_radius_scale = 0.5f;

		// 球の衝突判定
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(sphere_radius_scale);

		sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_gizmo_->SetScale(sphere_radius_scale);
		sphere_gizmo_->SetVertexColor(255, 255, 0, 255);


		// OBBの大きさ
		const float box_scale = 0.5f;

		// OBBの衝突判定
		obb_collider_ = NEW OBBColliderComponent(this);
		obb_collider_->SetDirLength(box_scale, AxisType::X);
		obb_collider_->SetDirLength(box_scale, AxisType::Y);
		obb_collider_->SetDirLength(box_scale, AxisType::Z);

		obb_collider_gizmo_ = NEW BoxGizmoRendererComponent(this);
		obb_collider_gizmo_->SetScale(box_scale);

		// ロックオンの箱の衝突判定
		{
			const float lockon_langth = 10.f;
			const float lockon_scale = 0.5f;

			lockon_collider_ = NEW OBBColliderComponent(this);
			lockon_collider_->SetDirLength(lockon_scale, AxisType::X);
			lockon_collider_->SetDirLength(lockon_scale, AxisType::Y);
			lockon_collider_->SetDirLength(lockon_langth, AxisType::Z);

			lockon_gizmo_ = NEW BoxGizmoRendererComponent(this);
			lockon_gizmo_->SetVertexColor(0, 255, 255, 128);
			lockon_gizmo_->SetScaleX(lockon_scale);
			lockon_gizmo_->SetScaleY(lockon_scale);
			lockon_gizmo_->SetScaleZ(lockon_langth);
		}
	}

	// 値コンポーネントの作成
	{
		// 最大HP
		max_hp_param_ = NEW FloatParameterComponent(this);
		max_hp_param_->SetParameterType(ParameterType::MaxHP);
		max_hp_param_->SetFloat(max_hit_point_);

		// HP
		hp_param_ = NEW FloatParameterComponent(this);
		hp_param_->SetParameterType(ParameterType::HP);
		hp_param_->SetFloat(hit_point_);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Player::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void Player::InputGameObject(void)
{
	// チャージ弾の武器コンポーネントの確認
	if(charge_blaster_ == nullptr)
	{
		assert(!"Player::InputGameObject()：チャージ弾の武器コンポーネントが、nullptrでした！");
	}

	// 弾を発射するか
	is_blaster_fire_ = InputCheck::XInputTrigger(PadIndex::Pad1, XInputButton::XIB_A);

	// ボタンを長押ししたら
	if (charge_blaster_->IsCheckChargeBulletInstance() == false)
	{
		if (InputCheck::XInputRepeat(PadIndex::Pad1, XInputButton::XIB_A, 2.f))
		{
			charge_blaster_->CreateChargeBullet();
		}
	}

	if (charge_blaster_->IsCheckChargeBulletInstance() == true)
	{
		// ボタンを離したら
		if (charge_blaster_->GetChargeBulletState() == ChargeBulletState::Hold)
		{
			if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_A) == false)
			{
				charge_blaster_->Fire();
			}
		}
	}
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Player::UpdateGameObject(float deltaTime)
{
	// チャージ弾の武器コンポーネントの確認
	if (charge_blaster_ == nullptr)
	{
		assert(!"Player::UpdateWeapon():チャージ弾の武器コンポーネントが、nullptrでした！");
	}

	ImGui::Begin("PlayerTransform");
	ImGui::Text("Yaw:%f", transform_component_->GetAngleYaw());
	ImGui::Text("Pitch:%f", transform_component_->GetAnglePitch());
	ImGui::Text("Roll:%f", transform_component_->GetAngleRoll());

	auto pos = *transform_component_->GetPosition();
	ImGui::Text("PosX:%f", pos.x);
	ImGui::Text("PosY:%f", pos.y);
	ImGui::Text("PosZ:%f", pos.z);
	ImGui::End();

	// 値コンポーネントの更新処理
	this->UpdateParameter(deltaTime);

	// 武器の更新処理
	this->UpdateWeapon(deltaTime);

	// エフェクトの更新処理
	this->UpdatePirticleEffect(deltaTime);

	// 当たり判定の更新
	this->UpdateCollision(deltaTime);
}

/*-----------------------------------------------------------------------------
/* 値コンポーネントの更新処理
-----------------------------------------------------------------------------*/
void Player::UpdateParameter(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const bool is_nullptr_max_hp_param	= (max_hp_param_ == nullptr);
	const bool is_nullptr_hp_param		= (hp_param_ == nullptr);

	// 最大HPの値コンポーネントのnullチェック
	if (is_nullptr_max_hp_param)
	{
		assert(!"Player::UpdateParameter():値コンポーネント:max_hp_param_ が”nullptr”でした");
		return;
	}

	// HPの値コンポーネントのnullチェック
	if (is_nullptr_hp_param)
	{
		assert(!"Player::UpdateParameter():値コンポーネント:hp_param_ が”nullptr”でした");
		return;
	}

	// 最大HPの更新
	max_hp_param_->SetFloat(max_hit_point_);

	// 現在のHPの更新
	hp_param_->SetFloat(hit_point_);
}

/*-----------------------------------------------------------------------------
/* 武器の更新処理
-----------------------------------------------------------------------------*/
void Player::UpdateWeapon(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 武器の位置を調整
	{
		left_blaster_->SetTranslation(-1.5f, 0.1f, 1.0f);
		right_blaster_->SetTranslation(1.5f, 0.1f, 1.0f);
		charge_blaster_->SetTranslation(0.f, 0.1f, 3.0f);
	}

	// 弾の発射
	if (is_blaster_fire_)
	{
		left_blaster_->Fire();
		right_blaster_->Fire();
		is_blaster_fire_ = false;
	}
}

/*-----------------------------------------------------------------------------
/* エフェクトの更新処理
-----------------------------------------------------------------------------*/
void Player::UpdatePirticleEffect(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// エフェクトの位置を調整
	{
		effect_after_burner_->SetTranslation(0.f, 0.1f, -1.1f);
	}
}


/*-----------------------------------------------------------------------------
/* 衝突判定の更新処理
-----------------------------------------------------------------------------*/
void Player::UpdateCollision(float deltaTime)
{
	if (InputCheck::KeyTrigger(DIK_O))
	{
		hit_point_ = 100.f;
	}

	// HPの下限を設定
	if (hit_point_ <= 0.f)
	{
		hit_point_ = 0.f;
	}

	// 次にプレイヤーがダメージを受けるまでの時間を計算
	if (damage_recieve_interval_time_ >= MAX_DAMAGE_RECIEVE_INTERVAL_TIME_)
	{
		// 数値を正規化
		damage_recieve_interval_time_ = MAX_DAMAGE_RECIEVE_INTERVAL_TIME_;

		// ダメージを受けられるように
		is_received_damage_ = true;
	}
	else
	{
		damage_recieve_interval_time_ += deltaTime;
	}

	// ダメージを受け付けるか？
	if (is_received_damage_ == false) { return; }

	// 衝突判定
	{
		// ボスへのポインタを取得
		if (boss_ == nullptr)
		{
			auto enemie_list = game_->GetEnemieManager()->GetEnemyGameObjectList();
			for (auto enemy : enemie_list)
			{
				// ボスじゃなかったらスキップ
				auto actor_type = enemy->GetType();
				if (actor_type != GameObject::TypeID::Boss) { continue; }

				// ボスへのポインタを取得
				boss_ = enemy;
			}
		}

		// ボスが生成されていたら
		if (boss_ != nullptr)
		{
			// バレットの衝突判定
			auto bullets = game_->GetBulletManager()->GetBulletGameObjectList();
			for (auto bullet : bullets)
			{
				// Bulletの所有者がPlayerかを調べる
				auto bullet_owner_game_object = bullet->GetParentGameObject();

				if (bullet_owner_game_object == nullptr) { continue; }

				// バレットの所有者を調べる
				const bool is_weak_enemy_shoot_bullet = (bullet_owner_game_object->GetType() == GameObject::TypeID::WeakEnemy);
				const bool is_strong_enemy_shoot_bullet = (bullet_owner_game_object->GetType() == GameObject::TypeID::StrongEnemy);
				const bool is_boss_shoot_bullet = (bullet_owner_game_object->GetType() == GameObject::TypeID::Boss);
				if (is_weak_enemy_shoot_bullet || is_strong_enemy_shoot_bullet || is_boss_shoot_bullet)
				{
					// エネミーのバレットの衝突判定を取得
					if (CheckCollision::SphereVSSpghre(this->GetSphereCollider(), bullet->GetSphereCollider()))
					{
						// ダメージを受けた時のエフェクトを再生
						effect_enemy_attack_hit_->Play();

						// ダメージを受けたSEを再生
						player_damege_sound_effect_->Play();

						// ダメージをを受ける
						hit_point_ += -10.f;

						// 衝突したバレットを破棄する
						bullet->SetGameObjectState(State::Dead);
	
						// 次にプレイヤーがダメージを受けるまでの時間と状態を初期化
						damage_recieve_interval_time_ = 0.f;
						is_received_damage_ = false;
						break;

					}
				}
			}

			// ボスの体当たりの衝突判定
			if (CheckCollision::ObbVSObb(this->GetOBBCollider(), boss_->GetOBBCollider()))
			{
				// ダメージを受けた時のエフェクトを再生
				effect_enemy_attack_hit_->Play();

				// ダメージを受けたSEを再生
				player_damege_sound_effect_->Play();

				// ダメージをを受ける
				hit_point_ += -10.f;

				// 次にプレイヤーがダメージを受けるまでの時間と状態を初期化
				damage_recieve_interval_time_ = 0.f;
				is_received_damage_ = false;
			}

			// ボスの大型レーザーの衝突判定
			{
				class Bullet* large_laser = nullptr;

				for (auto bullet : bullets)
				{
					// バレットの所有者を調べる
					const bool is_bullet_large_laser = (bullet->GetType() == GameObject::TypeID::LargeLaser);
					if (is_bullet_large_laser)
					{
						// 巨大レーザーを取得
						large_laser = bullet;
						break;
					}
				}

				// ボスの大型レーザーの衝突判定
				if (large_laser != nullptr)
				{
					if (CheckCollision::ObbVSObb(this->GetOBBCollider(), large_laser->GetOBBCollider()))
					{
						// ダメージを受けた時のエフェクトを再生
						effect_enemy_attack_hit_->Play();

						// ダメージを受けたSEを再生
						player_damege_sound_effect_->Play();

						// ダメージをを受ける
						hit_point_ += -10.f;

						// 次にプレイヤーがダメージを受けるまでの時間と状態を初期化
						damage_recieve_interval_time_ = 0.f;
						is_received_damage_ = false;
					}
				}
			}
		}
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/