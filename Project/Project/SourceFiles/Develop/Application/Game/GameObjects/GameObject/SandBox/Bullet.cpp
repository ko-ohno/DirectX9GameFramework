/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Bullet.cpp] バレットゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：バレットゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "Bullet.h"
#include "../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../Component/ColliderComponent/SphereColliderComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Bullet::Bullet(Game* game)
	: SandBox(game)
	, parent_front_vector_(0.f, 0.f, 0.f)
	, kill_timer_(3.f)
	, alive_time_(0.f)
	, move_speed_(30.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Bullet::~Bullet(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Bullet::Init(void)
{
	// 親の取得
	if (game_object_parent_ == nullptr)
	{
		auto game_objects = game_->GetGameObjects();

		// 総当たり検索
		for (auto game_object : game_objects)
		{
			auto game_object_id = game_object->GetType();

			//プレイヤーをこのゲームオブジェクトの親に設定
			if (game_object_id == TypeID::Player)
			{
				game_object_parent_ = game_object;
			}
		}
	}

	// バレットの性質を作成
	{
		// 弾丸のメッシュ表示
		bullet_mesh_ = NEW FFPMeshRendererComponent(this);
		bullet_mesh_->SetMesh(XFileMeshType::GreenBullet);

		const float scale = 1.f;

		// 弾丸の衝突判定の追加
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);

		// 弾丸のギズモを生成
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
	}

	// バレットの姿勢を初期化
	{
		// 親の姿勢を取得
		TransformComponent* parent_transform;

		if (game_object_parent_ != nullptr)
		{
			parent_transform = game_object_parent_->GetTransform();

			// 前ベクトルの取得　　
			parent_front_vector_ = *parent_transform->GetFrontVector();

			// 回転の姿勢を設定
			this->transform_component_->SetRotationMatrix(*parent_transform->GetRotationMatrix());
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Bullet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void Bullet::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Bullet::UpdateGameObject(float deltaTime)
{	
	// 姿勢の回転を球面補間をしない
	//bullet_transform->SetSlerpSpeed(100.f);

	this->transform_component_->IsSetExecuteSlerp(false);

	this->transform_component_->SetDirection(parent_front_vector_);
	{
		// 移動
		auto move_direction = (parent_front_vector_ * move_speed_ ) * deltaTime;

		// 移動
		this->transform_component_->AddTranslation(move_direction);
	}

	// 生存時間への加算
	alive_time_ += deltaTime;

	// 生存時間がキルタイマーを上回ったら
	if (alive_time_ >= kill_timer_)
	{
		this->SetState(State::Dead);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/