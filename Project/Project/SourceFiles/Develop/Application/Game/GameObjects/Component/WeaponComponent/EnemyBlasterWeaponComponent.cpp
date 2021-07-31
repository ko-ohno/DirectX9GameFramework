/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyBlasterWeaponComponent.cpp] 敵の武器コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：敵の武器コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "EnemyBlasterWeaponComponent.h"
#include "../../GameObject.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../GameObject/SandBox/Bullet.h"
#include "../../../Game.h"
#include "../../GameObject/SandBox/Actor.h"
#include "../../../SandBoxManager/ActorManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EnemyBlasterWeaponComponent::EnemyBlasterWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, player_object_(nullptr)
	, muzzle_flash_(nullptr)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EnemyBlasterWeaponComponent::~EnemyBlasterWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool EnemyBlasterWeaponComponent::Init(void)
{
	// 弾の発射エフェクト
	{
		muzzle_flash_ = NEW EffectRendererComponent(owner_);
		muzzle_flash_->SetEffect(EffectType::MuzzluFrashBlue);

		// 所有者からの影響を無効に
		muzzle_flash_->IsSetOwnerTransfromOrder(false);
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
void EnemyBlasterWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void EnemyBlasterWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*　更新処理
-----------------------------------------------------------------------------*/
void EnemyBlasterWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// プレイヤーの取得処理
	if (player_object_ == nullptr)
	{
		player_object_ = this->FindPlayerGameObject();
		if (player_object_ == nullptr)
		{
			assert(!"EnemyBlasterWeaponComponent::Update():プレイヤーのゲームオブジェクトを取得できませんでした！");
		}
	}

	// ギズモの更新
	{
		sphere_gizmo_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/*　敵のターゲット(プレイヤー)を見つける処理
-----------------------------------------------------------------------------*/
Actor* EnemyBlasterWeaponComponent::FindPlayerGameObject(void)
{
	// プレイヤーの取得
	if (player_object_ == nullptr)
	{
		auto actor_list = owner_->GetGame()->GetActorManager()->GetActorGameObjectList();

		for (auto actor : actor_list)
		{
			if (actor->GetType() == GameObject::TypeID::Player)
			{
				return actor;
			}
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/*　弾の発射処理
-----------------------------------------------------------------------------*/
void EnemyBlasterWeaponComponent::Fire(void)
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

	// 目的の向きベクトルを作成
	D3DXVECTOR3 front_vector = { 0.f, 0.f, 0.f };
	if (player_object_ != nullptr)
	{
		// プレイヤーの座標座標
		D3DXVECTOR3 player_pos = *player_object_->GetTransform()->GetPosition();

		// 武器の座標
		D3DXVECTOR3 blaster_pos = { translation_matrix._41, translation_matrix._42, translation_matrix._43 };

		// 前ベクトルを生成
		front_vector = player_pos - blaster_pos;

		// ベクトルを長さ1にする
		D3DXVec3Normalize(&front_vector, &front_vector);
	}

	// 発射光エフェクトの再生
	{
		// エフェクトの種類を設定
		muzzle_flash_->SetEffect(EffectType::MuzzluFrashOrange);

		// 発射光エフェクトの再生
		muzzle_flash_->Play(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}

	// 弾丸の生成 
	{
		auto bullet = NEW Bullet(owner_->GetGame());
		bullet->SetParentGameObject(owner_);
		bullet->SetFrontVector(front_vector);
		bullet->SetCreatePosition(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/