/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBullet.cpp] チャージ弾のゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：チャージ弾のゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "ChargeBullet.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../Component/ColliderComponent/SphereColliderComponent.h"
#include "../../../Component/AudioComponent.h"
#include "../../../../../Math.h"
#include "../../SandBox/Actor/Enemy.h"
#include "../../../../SandBoxManager/EnemieManager.h"
#include "../../../../CheckCollision.h"
#include "../../../../Input/InputCheck.h"
#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ChargeBullet::ChargeBullet(Game* game)
	: Bullet(game)
	, bullet_charge_se_(nullptr)
	, bullet_fire_se_(nullptr)
	, bullet_explosion_se_(nullptr)
	, charge_bullet_state_(ChargeBulletState::None)
	, charge_bullet_state_old_(ChargeBulletState::None)
	, is_fire_(false)
	, is_hit_(false)
	, is_lockon_(false)
	, is_next_state_(false)
	, parent_front_vector_(0.f, 0.f, 1.f)
	, move_speed_(0.f)
	, position_(0.f, 0.f, 0.f)
	, src_position_(0.f, 0.f, 0.f)
	, dst_position_(0.f, 0.f, 0.f)
	, lerp_execute_time_(0.f)
	, kill_timer_(0.f)
	, alive_time_(0.f)
	, state_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
ChargeBullet::~ChargeBullet(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool ChargeBullet::Init(void)
{
	// 値の設定
	move_speed_ = 15.f;
	kill_timer_ = 2.f;


	// 配列の初期化
	{
		// エフェクト番号の登録
		effect_type_[0] = EffectType::ChargeBulletState1Charge;
		effect_type_[1] = EffectType::ChargeBulletState2Hold;
		effect_type_[2] = EffectType::ChargeBulletState4Bullet;
		effect_type_[3] = EffectType::ChargeBulletState5Explosion;

		for (int i = 0; i < MAX_CHARGE_BULLET_STATE_; i++)
		{
			effect_[i] = nullptr;
		}
	}

	const float init_axis_y_pos = -100.f;

	// 弾丸の生成
	{
		for (int i = 0; i < MAX_CHARGE_BULLET_STATE_; i++)
		{
			effect_[i] = nullptr;
			effect_[i] = NEW EffectRendererComponent(this);
			effect_[i]->SetEffect(effect_type_[i]);
			//effect_[i]->SetScale(0.5f);
			effect_[i]->SetTranslationY(init_axis_y_pos);
		}
	}

	// 音声コンポーネントの生成
	{
		bullet_charge_se_ = NEW AudioComponent(this);
		bullet_charge_se_->SetSound(SoundType::ChargeBulletCharge);
		bullet_charge_se_->SetAudioVolume(0.8f);

		bullet_fire_se_ = NEW AudioComponent(this);
		bullet_fire_se_->SetSound(SoundType::ChargeBulletFire);
		bullet_fire_se_->SetAudioVolume(0.8f);

		bullet_explosion_se_ = NEW AudioComponent(this);
		bullet_explosion_se_->SetSound(SoundType::ChargeBulletExplosion);
		bullet_explosion_se_->SetAudioVolume(0.8f);
	}

	// 衝突判定の作成
	{
		const float scale = 1.f;

		// 球の衝突判定
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);

		// ギズモの描画コンポーネント
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
		//sphere_collider_gizmo_->IsSetDrawable(false);
	}

	// チャージ弾の起動
	{
		charge_bullet_state_ = ChargeBulletState::Charge;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void ChargeBullet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void ChargeBullet::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateGameObject(float deltaTime)
{
	//所有者が不明だった場合
	const bool is_owner_type_unkown = (parent_game_object_type_ == GameObject::TypeID::None);
	if (is_owner_type_unkown)
	{
		// 親ゲームオブジェクトの種類を記憶
		parent_game_object_type_ = this->GetParentGameObject()->GetType();
	}

	if ((charge_bullet_state_ == ChargeBulletState::Fire) && (is_fire_ == false))
	{
		// プレイヤーの前ベクトルへ移動する
		if (game_object_parent_ == nullptr)
		{
			assert(!"ChargeBullet::UpdateChargeBullet():このゲームオブジェクトの所有者が不明です！");
		}

		// 発射していることを証明
		is_fire_ = true;

		// 親のゲームオブジェクトの前ベクトルを取得
		parent_front_vector_ = *game_object_parent_->GetTransform()->GetFrontVector();

		// 発射座標を記録
		src_position_ = position_;
	}

	if (charge_bullet_state_ == ChargeBulletState::Bullet)
	{
		// 移動の更新
		this->UpdateMovement(deltaTime);

		// 生存時間の計算
		alive_time_ += deltaTime;

		//// 生存時間が制限時間を超えたら
		if (alive_time_ >= kill_timer_)
		{
			this->SetChargeBulletState(ChargeBulletState::End);
			alive_time_ = 0.f;
		}
	}

	// チャージ弾の更新
	this->UpdateChargeBulletState(deltaTime);

	// Particleエフェクトの更新
	this->UpdateParticleEffect();

	// 衝突判定の更新
	this->UpdateColilision(charge_bullet_state_);

	// 1フレーム前の情報を更新
	charge_bullet_state_old_ = charge_bullet_state_;
}

/*-----------------------------------------------------------------------------
/* チャージ弾の移動の更新処理
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateMovement(float deltaTime)
{
	if (is_lockon_ == true)
	{
		// 座標を補間して、ロックオンした相手まで飛んでいく
		D3DXVec3Lerp(&position_, &src_position_, &dst_position_, Easing::Linear(lerp_execute_time_, MAX_LERP_EXECUTE_TIME_));

		// 移動
		lerp_execute_time_ += deltaTime;
		if (lerp_execute_time_ >= MAX_LERP_EXECUTE_TIME_)
		{
			lerp_execute_time_ = MAX_LERP_EXECUTE_TIME_;
		}
	}
	else
	{
		// プレイヤーの前ベクトルへ移動
		position_ += (parent_front_vector_ * move_speed_) * deltaTime;
	}

	// 座標の更新
	this->transform_component_->SetTranslation(position_);
}

/*-----------------------------------------------------------------------------
/* チャージ弾の状態の更新処理
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateChargeBulletState(float deltaTime)
{
	const float MAX_STATE_TIME_CHARGE		= 3.0f;
	const float MAX_STATE_TIME_FIRE			= 0.05f;
	const float MAX_STATE_TIME_EXPLOSION	= 1.5f;

	// チャージ弾の生存時間
	state_time_ += deltaTime;

	if (is_next_state_)
	{
		charge_bullet_state_ = ChargeBulletState::Hold;
		is_next_state_ = false;
	}

#ifdef DEBUG_MODE_
	ImGui::Begin("BulletState");
	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		ImGui::Text("Charge"); // ボタンを長押ししている間
		break;

	case ChargeBulletState::Hold:
		ImGui::Text("Hold");
		break;

	case ChargeBulletState::Fire:
		ImGui::Text("Fire");
		break;

	case ChargeBulletState::Bullet:
		ImGui::Text("Bullet");
		break;

	case ChargeBulletState::Explosion:
		ImGui::Text("Explosion");
		break;

	case ChargeBulletState::End:
		ImGui::Text("End");
		break;

	default:
		break;
	}
	ImGui::End();
#endif

	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		if (state_time_ >= MAX_STATE_TIME_CHARGE)
		{
			is_next_state_ = true;
			state_time_ = 0;
		}
		break;

	case ChargeBulletState::Hold:
		state_time_ = 0;
		break;

	case ChargeBulletState::Fire:
		if (state_time_ >= MAX_STATE_TIME_FIRE)
		{
			charge_bullet_state_ = ChargeBulletState::Bullet;
			state_time_ = 0;
		}
		break;
	
	case ChargeBulletState::Bullet:
		if (is_hit_)
		{
			charge_bullet_state_ = ChargeBulletState::Explosion;
			state_time_ = 0;
		}
		break;
	
	case ChargeBulletState::Explosion:
		if (state_time_ >= MAX_STATE_TIME_EXPLOSION)
		{
			charge_bullet_state_ = ChargeBulletState::End;
			state_time_ = 0;
		}
		break;

	case ChargeBulletState::End:
		break;

	default:
		assert(!"ChargeBullet::UpdateChargeBullet():チャージ弾のゲームオブジェクトが不正な処理を起こしています！");
		break;
	}
}

/*-----------------------------------------------------------------------------
/* エフェクトの更新処理
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateParticleEffect(void)
{
	// ステートが切り替わった瞬間だけ再生されるように
	if (charge_bullet_state_ != charge_bullet_state_old_)
	{
		this->UpdateParticleEffectPlayState(charge_bullet_state_);
	}

	// バレットの状態を更新
	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		effect_[0]->SetTranslation(position_);
		break;

	case ChargeBulletState::Hold:
		effect_[1]->SetTranslation(position_);
		break;

	case ChargeBulletState::Bullet:
		effect_[2]->IsSetOwnerTransfromOrder(false);
		effect_[2]->SetTranslation(position_);
		break;

	case ChargeBulletState::Explosion:
		effect_[3]->IsSetOwnerTransfromOrder(false);
		effect_[3]->SetTranslation(position_);
		break;

	default:
		break;
	}
}

/*-----------------------------------------------------------------------------
/* エフェクトの再生状況の更新処理
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateParticleEffectPlayState(ChargeBulletState chargeBulletState)
{
	const int EFFECT_CHARGE		= 0;
	const int EFFECT_HOLD		= 1;
	const int EFFECT_BULLET		= 2;
	const int EFFECT_EXPLOSION	= 3;

	switch (chargeBulletState)
	{
	case ChargeBulletState::Charge:
		effect_[EFFECT_CHARGE]->Play();		// エフェクト再生：チャージを開始するエフェクト
		bullet_charge_se_->Play();			// 音声再生:チャージ音声
		break;

	case ChargeBulletState::Hold:
		effect_[EFFECT_HOLD]->Play();		// エフェクト再生：チャージを続けるエフェクト
		break;

	case ChargeBulletState::Fire:
		effect_[EFFECT_HOLD]->Stop();		// エフェクト停止：チャージを続けるエフェクト
		effect_[EFFECT_BULLET]->Play();		// エフェクト再生：チャージ弾のエフェクト
		bullet_fire_se_->Play();			// 音声再生:発射音声
		break;

	case ChargeBulletState::Explosion:
		effect_[EFFECT_BULLET]->Stop();		// エフェクト停止：チャージ弾のエフェクト
		effect_[EFFECT_EXPLOSION]->Play();	// エフェクト再生：爆発のエフェクト
		bullet_explosion_se_->Play();		// 音声再生:爆発音声
		break;

	default:
		break;
	}
}

/*-----------------------------------------------------------------------------
/* 衝突判定の更新
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateColilision(ChargeBulletState chargeBulletState)
{
	// 衝突判定の大きさを更新
	{
		const float colider_scale_ = 1.f;

		switch (chargeBulletState)
		{
		case ChargeBulletState::Bullet:
			// 弾の判定の大きさは1倍
			sphere_collider_->SetRadius(colider_scale_);
			sphere_collider_gizmo_->SetScale(colider_scale_);
			break;

		case ChargeBulletState::Explosion:
			// 爆発したら判定の大きさを4倍に設定
			sphere_collider_->SetRadius(colider_scale_ * 4.f);
			sphere_collider_gizmo_->SetScale(colider_scale_ * 4.f);
			break;

		default:
			break;
		}
	}

	// 敵の衝突判定を取得
	auto enemy_list_ = game_->GetEnemieManager()->GetEnemyGameObjectList();
	for (auto enemy : enemy_list_)
	{
		auto game_object_state = enemy->GetGameObjectState();
		if (game_object_state == GameObject::State::Destroy) { continue; }
		if (game_object_state == GameObject::State::Dead) { continue; }

		if (CheckCollision::SphereVSSpghre(this->GetSphereCollider(), enemy->GetSphereCollider()))
		{
			// ゲームオブジェクトの型を調べる
			auto enemy_game_object_type = enemy->GetType();
			if (enemy_game_object_type != GameObject::TypeID::Boss)
			{
				// ボスじゃなかったらエネミーを破壊する
				enemy->SetGameObjectState(GameObject::State::Destroy);
			}

			// 衝突したことを記憶
			is_hit_ = true;

			// チャージ弾の状態を爆発状態へ
			chargeBulletState = ChargeBulletState::Explosion;
			break;
		}
	}
}

/*-----------------------------------------------------------------------------
/* 弾の発射
-----------------------------------------------------------------------------*/
void ChargeBullet::Fire(void)
{
	charge_bullet_state_ = ChargeBulletState::Fire;
}

/*-----------------------------------------------------------------------------
/* ターゲットの敵へのポインタを設定
-----------------------------------------------------------------------------*/
void ChargeBullet::SetLockonTargetEnemy(Enemy* enemy)
{
	if (enemy == nullptr) { return; }

	auto game_object_type = enemy->GetType();
	if (game_object_type == GameObject::TypeID::Boss)
	{
		// ボスのモデルが原点ズレを起こしているため、目的地座標をオフセットして設定
		dst_position_ = *enemy->GetTransform()->GetPosition();

		// Y座標をオフセット
		dst_position_.y += 1.f;
	}
	else
	{
		// 目的地座標を設定
		dst_position_ = *enemy->GetTransform()->GetPosition();
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/