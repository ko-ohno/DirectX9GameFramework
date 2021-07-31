/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBullet.cpp] チャージ弾のゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：チャージ弾のゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "ChargeBullet.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../Component/ColliderComponent/SphereColliderComponent.h"
#include "../../../../Math.h"
#include "../../../Input/InputCheck.h"
#include "../SandBox/Actor/Enemy.h"
#include "../../../SandBoxManager/EnemieManager.h"
#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ChargeBullet::ChargeBullet(Game* game)
	: SandBox(game)
	, sphere_collider_(nullptr)
	, sphere_collider_gizmo_(nullptr)
	, charge_bullet_state_(ChargeBulletState::None)
	, charge_bullet_state_old_(ChargeBulletState::None)
	, is_fire_(false)
	, is_hit_(false)
	, is_lockon_(false)
	, is_next_state_(false)
	, parent_front_vector_(0.f, 0.f, 1.f)
	, move_speed_(15.f)
	, position_(0.f, 0.f, -100.f)
	, src_position_(0.f, 0.f, 0.f)
	, dst_position_(0.f, 0.f, 0.f)
	, lerp_execute_time_(0.f)
	, kill_timer_(2.f)
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
	// 配列の初期化
	{
		// エフェクト番号の登録
		effect_type_[0] = EffectType::ChargeBulletState1Charge;
		effect_type_[1] = EffectType::ChargeBulletState2Hold;
		effect_type_[2] = EffectType::ChargeBulletState4Bullet;
		effect_type_[3] = EffectType::ChargeBulletState5Explosion;

		for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
		{
			effect_[i] = nullptr;
		}
	}

	// 弾丸の生成
	{
		for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
		{
			effect_[i] = nullptr;
			effect_[i] = NEW EffectRendererComponent(this);
			effect_[i]->SetEffect(effect_type_[i]);
			effect_[i]->SetScale(0.5f);
			effect_[i]->SetTranslationY(-100.f);
		}
	}

	// 衝突判定の作成
	{
		const float scale = 1.f;

		// 球の衝突判定
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);
		sphere_collider_->SetTranslationY(-100.f);

		// ギズモの描画コンポーネント
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
		sphere_collider_gizmo_->SetTranslationY(-100.f);
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
		// 移動
		lerp_execute_time_ += deltaTime;

		// ロックオンした相手まで飛んでいく
		const Vector3 src_pos(src_position_);
		const Vector3 dst_pos(dst_position_);

		// LerpとEasingで座標の補間
		auto bullet_pos = Vector3::Vector3lerp(src_pos, dst_pos, Easing::Linear(lerp_execute_time_));

		position_ = { bullet_pos.x_, bullet_pos.y_, bullet_pos.z_ };
	}
	else
	{
		// プレイヤーの前ベクトルへ移動
		position_ += (parent_front_vector_ * move_speed_) * deltaTime;
	}
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

	ImGui::Begin("BulletState");

	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		ImGui::Text("Charge"); // ボタンを長押ししている間
		if (state_time_ >= MAX_STATE_TIME_CHARGE)
		{
			is_next_state_ = true;
			state_time_ = 0;
		}
		break;

	case ChargeBulletState::Hold:
		ImGui::Text("Hold");
		state_time_ = 0;
		break;

	case ChargeBulletState::Fire:
		ImGui::Text("Fire");
		if (state_time_ >= MAX_STATE_TIME_FIRE)
		{
			charge_bullet_state_ = ChargeBulletState::Bullet;
			state_time_ = 0;
		}
		break;
	
	case ChargeBulletState::Bullet:
		ImGui::Text("Bullet");
		if (is_hit_)
		{
			charge_bullet_state_ = ChargeBulletState::Explosion;
			state_time_ = 0;
		}
		break;
	
	case ChargeBulletState::Explosion:
		ImGui::Text("Explosion");
		if (state_time_ >= MAX_STATE_TIME_EXPLOSION)
		{
			charge_bullet_state_ = ChargeBulletState::End;
			state_time_ = 0;
		}
		break;

	case ChargeBulletState::End:
		ImGui::Text("End");
		break;

	default:
		assert(!"ChargeBullet::UpdateChargeBullet():チャージ弾のゲームオブジェクトが不正な処理を起こしています！");
		break;
	}

	ImGui::End();
	
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

	// エフェクトの位置を更新
	for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
	{
		effect_[i]->SetTranslation(position_);
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
		break;

	case ChargeBulletState::Hold:
		effect_[EFFECT_HOLD]->Play();		// エフェクト再生：チャージを続けるエフェクト
		break;

	case ChargeBulletState::Fire:
		effect_[EFFECT_HOLD]->Stop();		// エフェクト停止：チャージを続けるエフェクト
		effect_[EFFECT_BULLET]->Play();		// エフェクト再生：チャージ弾のエフェクト
		break;

	case ChargeBulletState::Explosion:
		effect_[EFFECT_BULLET]->Stop();		// エフェクト停止：チャージ弾のエフェクト
		effect_[EFFECT_EXPLOSION]->Play();	// エフェクト再生：爆発のエフェクト
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

	// 衝突判定の位置の更新
	{
		sphere_collider_gizmo_->SetTranslation(position_);
		sphere_collider_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/* 弾の発射
-----------------------------------------------------------------------------*/
void ChargeBullet::Fire(void)
{
	charge_bullet_state_ = ChargeBulletState::Fire;
}

/*=============================================================================
/*		End of File
=============================================================================*/