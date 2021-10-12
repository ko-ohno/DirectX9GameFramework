/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBlasterWeaponComponent.cpp] 光線銃武器コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：光線銃武器コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "ChargeBlasterWeaponComponent.h"
#include "../../../Game.h"

// 描画コンポーネント
#include "../../Component/RendererComponent/BillboardRendererComponent.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"

// 衝突判定コンポーネント
#include "../../Component/AudioComponent.h"

// 衝突判定コンポーネント
#include "../../Component/ColliderComponent/OBBColliderComponent.h"

// ギズモコンポーネント
#include "../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

// ゲームオブジェクト関連
#include "../../GameObject.h"
#include "../../GameObject/SandBox/Bullet/ChargeBullet.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"
#include "../../../SandBoxManager/EnemieManager.h"

//衝突判定系
#include "../../../CheckCollision.h"

// 入力系
#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ChargeBlasterWeaponComponent::ChargeBlasterWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, is_bullet_created_(false)
	, is_fire_(false)
	, target_enemy_(nullptr)
	, is_enable_lockon_(false)
	, lockon_release_time_(0.f)
	, lockon_reticle_animation_time_(0.f)
	, lockon_reticle_hud_animation_time_(0.f)
	, lockon_reticle_src_pos_(0.f, 0.f, 0.f)
	, lockon_reticle_dst_pos_(0.f, 0.f, 0.f)
	, charge_bullet_(nullptr)
	, muzzle_flash_(nullptr)
	, lockon_reticle_(nullptr)
	, lockon_reticle_owner_transform_order_(nullptr)
	, lockon_alert_se_(nullptr)
	, lockon_collider_(nullptr)
	, lockon_gizmo_(nullptr)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
ChargeBlasterWeaponComponent::~ChargeBlasterWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool ChargeBlasterWeaponComponent::Init(void)
{
	// 描画コンポーネントの生成
	{
		
		// 銃の発射光の生成
		{
			muzzle_flash_ = NEW EffectRendererComponent(owner_);
			muzzle_flash_->SetEffect(EffectType::ChargeBulletState3Fire);
			muzzle_flash_->SetScale(0.5f);
		}

		//　ロックオンのレティクルの生成
		{
			lockon_reticle_ = NEW BillboardRendererComponent(owner_, 290);
			lockon_reticle_->SetTexture(TextureType::NearReticle);
			lockon_reticle_->SetVertexColor(0, 255, 0, 255);
			lockon_reticle_->SetRendererLayerType(RendererLayerType::UI);
			lockon_reticle_->IsSetDrawable(false);

			// レティクルの性質の調整
			lockon_reticle_->SetScaleX(1.4f);
			lockon_reticle_->SetScaleY(1.4f);
			lockon_reticle_->SetTranslationZ(9.f);
		}

		// 所有者の姿勢の影響を受けるロックオンのレティクルの生成
		{
			// 透明として描画する
			lockon_reticle_owner_transform_order_ = NEW BillboardRendererComponent(owner_, 290);
			lockon_reticle_owner_transform_order_->SetTexture(TextureType::NearReticle);
			lockon_reticle_->SetVertexColor(0, 0, 0, 0);
			lockon_reticle_owner_transform_order_->SetRendererLayerType(RendererLayerType::UI);

			// レティクルの性質の調整
			lockon_reticle_owner_transform_order_->SetScale(1.4f);
			lockon_reticle_owner_transform_order_->SetTranslationZ(9.f);

			// 描画しないように設定
			lockon_reticle_owner_transform_order_->IsSetDrawable(false);
		}
	}

	// 音声コンポーネントの生成
	{
		lockon_alert_se_ = NEW AudioComponent(owner_);
		lockon_alert_se_->SetSound(SoundType::LockonAlert);
	}

	// ロックオンの箱の衝突判定
	{
		const float lockon_langth = 20.f;
		const float lockon_scale = 0.5f;

		lockon_collider_ = NEW OBBColliderComponent(owner_);
		lockon_collider_->SetDirLength(lockon_scale, AxisType::X);
		lockon_collider_->SetDirLength(lockon_scale, AxisType::Y);
		lockon_collider_->SetDirLength(lockon_langth, AxisType::Z);

		lockon_gizmo_ = NEW BoxGizmoRendererComponent(owner_);
		lockon_gizmo_->SetVertexColor(0, 255, 255, 128);
		lockon_gizmo_->SetScaleX(lockon_scale);
		lockon_gizmo_->SetScaleY(lockon_scale);
		lockon_gizmo_->SetScaleZ(lockon_langth);
	}

	// ギズモの生成
	{
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(owner_);
		sphere_gizmo_->SetScale(0.5f);
		sphere_gizmo_->SetVertexColor(0, 255, 255);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//　レティクルを描画するか？
	{
		bool is_draw_reticle = false;

		auto game_state = owner_->GetGame()->GetGameState();
		if (game_state == Game::GameState::Gameplay)
		{
			is_draw_reticle = true;
		}
		lockon_reticle_->IsSetDrawable(is_draw_reticle);
	}


	if (charge_bullet_ != nullptr)
	{
		// 平行移動情報の作成
		D3DXMATRIX translation_matrix;
		D3DXMatrixIdentity(&translation_matrix);
		{
			translation_matrix._41 = position_.x;
			translation_matrix._42 = position_.y;
			translation_matrix._43 = position_.z;

			// 所有者の姿勢情報と合成する
			translation_matrix = translation_matrix * *owner_transform_->GetWorldMatrix();
		}


#ifdef DEBUG_MODE_
		ImGui::Begin("BulletCreatePos");
		ImGui::Text("posX:%f", translation_matrix._41);
		ImGui::Text("posY:%f", translation_matrix._42);
		ImGui::Text("posZ:%f", translation_matrix._43);
		ImGui::End();
#endif

		if (charge_bullet_->GetChargeBulletState() <= ChargeBulletState::Hold)
		{
			// 弾の座標を更新
			charge_bullet_->SetTranslation(translation_matrix._41, translation_matrix._42, translation_matrix._43);
		}

		if (charge_bullet_->GetChargeBulletState() == ChargeBulletState::Fire)
		{
			if (is_fire_ == false)
			{	
				// エフェクト再生を更新
				muzzle_flash_->Play();
				is_fire_ = true;
			}
		}

		// チャージ弾の状態を確認
		if (charge_bullet_->GetChargeBulletState() == ChargeBulletState::End)
		{
			charge_bullet_->SetGameObjectState(GameObject::State::Dead);

			// バレットを生成した記憶を初期化
			is_bullet_created_ = false;

			// バレットのポインタを初期化
			charge_bullet_ = nullptr;

			// バレットを発射した記憶を初期化
			is_fire_ = false;
		}
	}

	// ロックオンの標的を更新
	this->UpdateLockonTarget(deltaTime);

	// ギズモの更新
	{
		sphere_gizmo_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/*　チャージ弾の発射処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::CreateChargeBullet(void)
{
	//// 平行移動情報の作成
	D3DXMATRIX translation_matrix;
	D3DXMatrixIdentity(&translation_matrix);
	{
		translation_matrix._41 = position_.x;
		translation_matrix._42 = position_.y;
		translation_matrix._43 = position_.z;

		// 所有者の姿勢情報と合成する
		translation_matrix = translation_matrix * *owner_transform_->GetWorldMatrix();
	}

	// 弾丸の生成
	{
		if (is_bullet_created_ == true) { return; }
		
		// バレットの生成処理
		charge_bullet_ = NEW ChargeBullet(owner_->GetGame());
		charge_bullet_->SetParentGameObject(owner_);
		charge_bullet_->SetTranslation(translation_matrix._41, translation_matrix._42, translation_matrix._43);

		// バレットを生成したことを記憶
		is_bullet_created_ = true;
	}
}

/*-----------------------------------------------------------------------------
/*　発射処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Fire(void)
{	
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::ChargeBulletFire()：チャージ弾のインスタンスが生成されていません！");
	}
	charge_bullet_->Fire();	// チャージ弾の発射
}

/*-----------------------------------------------------------------------------
/*　ロックオンの標的を更新
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::UpdateLockonTarget(float deltaTime)
{
	//　標的の状態を確認
	if (target_enemy_ != nullptr)
	{
		// 破壊されたゲームオブジェクトかを確認
		auto target_enemy_game_object_state = target_enemy_->GetGameObjectState();
		const bool is_destroyed = ((target_enemy_game_object_state == GameObject::State::Destroy)
								  || (target_enemy_game_object_state == GameObject::State::Dead));

		if (is_destroyed == true)
		{
			// ターゲットから外す
			target_enemy_ = nullptr;
		}
	}

	// ロックオンの衝突判定
	{
		// チャージ弾のインスタンスがあるか？
		if (charge_bullet_ != nullptr)
		{
			// チャージ弾を発射したらほかのターゲットをロックオンしない
			auto charge_bullet_state = charge_bullet_->GetChargeBulletState();
			if (charge_bullet_state >= ChargeBulletState::Bullet)
			{
				// 発射したらレティクルの色を赤に指定
				lockon_reticle_->SetVertexColor(255, 0, 0);
				lockon_reticle_->SetScale(1.f);
				return;
			}

			// エネミーのリストを取得
			auto enemy_list = owner_->GetGame()->GetEnemieManager()->GetEnemyGameObjectList();
			for (auto enemy : enemy_list)
			{
				// エネミーの状態を取得
				auto enemy_game_object_state = enemy->GetGameObjectState();

				// 破壊中や死亡中だったら衝突判定をしない
				if (enemy_game_object_state == GameObject::State::Destroy) { continue; }
				if (enemy_game_object_state == GameObject::State::Dead) { continue; }

				// ロックオンの衝突判定
				if (CheckCollision::ObbVSObb(this->lockon_collider_, enemy->GetOBBCollider()))
				{
					// ロックオンを解除するまでの時間をリセット
					lockon_release_time_ = 0.f;

					// ロックオン有効化
					is_enable_lockon_ = true;

					// ロックオンしたターゲットのインスタンスが現在の標的と違う場合
					if (target_enemy_ != enemy)
					{
						lockon_alert_se_->Play();
					}

					// 標的へのポインタを取得
					target_enemy_ = enemy;
					break;
				}
				else
				{
					// ロックオンを解除するまでの時間を計算
					lockon_release_time_ += deltaTime;
					if (lockon_release_time_ >= MAX_LOCKON_RELEASE_TIME_)
					{
						// 現在のインターバルの上限を設定
						lockon_release_time_ = MAX_LOCKON_RELEASE_TIME_;

						// ロックオン無効化
						is_enable_lockon_ = false;
					}
				}
			}
		}
		else
		{
			// ロックオン無効化
			is_enable_lockon_ = false;
		}
	}

	// ロックオン中か？
	if (is_enable_lockon_)
	{
		 // プレイヤーの姿勢の影響を常時受けているレティクルから、補間の始点座標を取得
		lockon_reticle_src_pos_ = *lockon_reticle_owner_transform_order_->GetPosition() + *owner_->GetTransform()->GetPosition();

		// 補間の終点座標の更新
		if (target_enemy_ != nullptr)
		{
			auto enemy_game_object_state = target_enemy_->GetGameObjectState();
			const bool is_not_state_destroy = (enemy_game_object_state != GameObject::State::Destroy);
			const bool is_not_state_dead	= (enemy_game_object_state != GameObject::State::Dead);
			if (is_not_state_destroy || is_not_state_dead)
			{
				auto game_object_type = target_enemy_->GetType();;
				if (game_object_type == GameObject::TypeID::Boss)
				{
					// ボスのモデルが原点ズレを起こしているため、目的地座標をオフセットして設定
					lockon_reticle_dst_pos_ = *target_enemy_->GetTransform()->GetPosition();

					// Y座標をオフセット
					lockon_reticle_dst_pos_.y += 1.f;
				}
				else
				{
					// 目的地座標を設定
					lockon_reticle_dst_pos_ = *target_enemy_->GetTransform()->GetPosition();
				}
			}
		}
		else
		{
			lockon_reticle_dst_pos_ = { 0.f, 0.f, 0.f };
		}

		// レティクルの状態を設定
		{
			// レティクルの位置情報を
			D3DXVECTOR3 reticle_position = { 0.f, 0.f, 0.f };
			D3DXVec3Lerp(&reticle_position, &lockon_reticle_src_pos_, &lockon_reticle_dst_pos_, Easing::SineInOut(lockon_reticle_animation_time_, MAX_LOCKON_RETICLE_ANIMATION_TIME_));

			// ロックオンのアニメーション時間の計算
			lockon_reticle_animation_time_ += deltaTime;
			if (lockon_reticle_animation_time_ >= MAX_LOCKON_RETICLE_ANIMATION_TIME_)
			{
				lockon_reticle_animation_time_ = MAX_LOCKON_RETICLE_ANIMATION_TIME_;
			}

			// ロックオンのHUDのアニメーション時間の計算
			lockon_reticle_hud_animation_time_ += deltaTime;
			if (lockon_reticle_hud_animation_time_ >= MAX_LOCKON_RETICLE_HUD_ANIMATION_TIME_)
			{
				lockon_reticle_hud_animation_time_ = 0.f;
			}

			// ロックオンのHUDが拡縮するアニメーション
			float scale = Math::Lerp(1.9f, 1.4f, lockon_reticle_hud_animation_time_);
			lockon_reticle_->SetScale(scale);

			// ロックオンのレティクルの色を更新
			const int red   = static_cast<int>(Math::Lerp(255.f, 255.f, Easing::SineInOut(lockon_reticle_hud_animation_time_)));
			const int green = static_cast<int>(Math::Lerp(255.f,   0.f, Easing::SineInOut(lockon_reticle_hud_animation_time_)));
			const int bule  = static_cast<int>(Math::Lerp(  0.f,   0.f, Easing::SineInOut(lockon_reticle_hud_animation_time_)));
			lockon_reticle_->SetVertexColor(red, green, bule);															  

			// コンポーネントの所有者の姿勢制御の影響を受けないように設定
			lockon_reticle_->IsSetOwnerTransfromOrder(false);

			// ロックオンのレティクルの位置情報を更新
			lockon_reticle_->SetTranslation(reticle_position);
		}

		// チャージ弾の状態を設定
		if (charge_bullet_ != nullptr)
		{
			// ロックオンのターゲットをチャージ弾に通知
			charge_bullet_->SetLockonTargetEnemy(target_enemy_);

			// ロックオンしたことを通知
			charge_bullet_->IsSetLockon(true);
		}
	}
	else
	{
		// レティクルの状態を設定
		{
			// ロックオンのレティクルの色を更新
			lockon_reticle_->SetVertexColor(0, 255, 0);
		
			// コンポーネントの所有者の姿勢制御の影響を受けるように設定
			lockon_reticle_->IsSetOwnerTransfromOrder(true);

			// 拡縮値を初期化
			lockon_reticle_->SetScale(1.4f);

			// ロックオンのレティクルの位置情報を更新
			lockon_reticle_->SetTranslation(0.f, 0.f, 9.f);

			// レティクルのアニメーション時間を再初期化
			lockon_reticle_animation_time_ = 0.f;
		}

		// チャージ弾の状態を設定
		if (charge_bullet_ != nullptr)
		{
			// ロックオンしたことを通知
			charge_bullet_->IsSetLockon(false);
		}
	}
}

/*-----------------------------------------------------------------------------
/*　チャージ弾のインスタンスがあるか確認
-----------------------------------------------------------------------------*/
bool ChargeBlasterWeaponComponent::IsCheckChargeBulletInstance(void)
{
	if (charge_bullet_ == nullptr) { return false; }
	return true;
}

/*-----------------------------------------------------------------------------
/*　チャージ弾の状態の取得処理
-----------------------------------------------------------------------------*/
ChargeBulletState ChargeBlasterWeaponComponent::GetChargeBulletState(void)
{
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::GetChargeBulletState()：チャージ弾のインスタンスが生成されていません！");
	}
	return charge_bullet_->GetChargeBulletState();
}

/*-----------------------------------------------------------------------------
/*　チャージ弾の状態の設定処理
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::SetChargeBulletState(ChargeBulletState chargeBulletState)
{
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::SetChargeBulletState()：チャージ弾のインスタンスが生成されていません！");
	}
	charge_bullet_->SetChargeBulletState(chargeBulletState);
}

/*=============================================================================
/*		End of File
=============================================================================*/