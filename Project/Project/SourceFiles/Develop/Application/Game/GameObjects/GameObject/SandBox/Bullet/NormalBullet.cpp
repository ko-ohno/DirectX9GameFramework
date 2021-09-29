/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[NormalBullet.cpp] バレットゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：バレットゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "NormalBullet.h"
#include "../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../Component/ColliderComponent/SphereColliderComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
NormalBullet::NormalBullet(Game* game)
	: Bullet(game)
	, bullet_mesh_(nullptr)
	, is_bullet_create_frame_(true)
	, is_set_front_vector_(false)
	, parent_front_vector_(0.f, 0.f, 0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, up_vector_(0.f, 1.f, 0.f)
	, front_vector_(0.f, 0.f, 1.f)
	, kill_timer_(3.f)
	, alive_time_(0.f)
	, move_speed_(30.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
NormalBullet::~NormalBullet(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool NormalBullet::Init(void)
{
	// バレットの性質を作成
	{
		// 弾丸のメッシュ生成
		bullet_mesh_ = NEW FFPMeshRendererComponent(this);
		bullet_mesh_->SetMesh(XFileMeshType::BlueBullet);

		// スケールを初期化
		const float scale = 0.5f;

		// 弾丸の衝突判定の追加
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);

		// 弾丸のギズモを生成
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
		//sphere_collider_gizmo_->IsSetDrawable(false);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void NormalBullet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void NormalBullet::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void NormalBullet::UpdateGameObject(float deltaTime)
{	
	// 所有者がなかったら警告を発行
	if (game_object_parent_ == nullptr)
	{
		assert(!"Bullet::UpdateGameObject()：バレットの所有者が不明です！");
	}

	//所有者が不明だった場合
	const bool is_owner_type_unkown = (parent_game_object_type_ == GameObject::TypeID::None);
	if (is_owner_type_unkown)
	{
		// 親ゲームオブジェクトの種類を記憶
		parent_game_object_type_ = this->GetParentGameObject()->GetType();
	}

	// 所有者がプレイヤーだった場合
	if (game_object_parent_->GetType() == GameObject::TypeID::Player)
	{
		this->CombinePlayerTransform();
	}

	// 姿勢の回転を球面補間をしない(常に補間の完了済みに)
	this->transform_component_->IsSetExecuteSlerpRotation(false);

	if (game_object_parent_ != nullptr)
	{
		auto game_object_parent_id = game_object_parent_->GetType();
		if (game_object_parent_id >= TypeID::Enemy)
		{
			bullet_mesh_->SetMesh(XFileMeshType::RedBullet);
		}
		else
		{
			bullet_mesh_->SetMesh(XFileMeshType::BlueBullet);
		}
	}

	// バレットが姿勢の回転をできていないので向きベクトルから回転できるような計算式を考える

	// 移動
	{
		D3DXVECTOR3 move_direction = { 0.f, 0.f, 0.f };

		if (is_set_front_vector_ == true)
		{
			// 姿勢ベクトルの生成
			{
				D3DXVec3Normalize(&front_vector_, &front_vector_);
				D3DXVec3Normalize(&up_vector_, &up_vector_);
				D3DXVec3Cross(&right_vector_, &up_vector_, &front_vector_);
				D3DXVec3Normalize(&right_vector_, &right_vector_);
				D3DXVec3Cross(&up_vector_, &right_vector_, &front_vector_);
				D3DXVec3Normalize(&up_vector_, &up_vector_);
			}

			// 回転行列の作成
			D3DXMATRIX rotation_matrix_;
			D3DXMatrixIdentity(&rotation_matrix_);
			memcpy(rotation_matrix_.m[0], &right_vector_, sizeof(D3DXVECTOR3));
			memcpy(rotation_matrix_.m[1], &up_vector_,	  sizeof(D3DXVECTOR3));
			memcpy(rotation_matrix_.m[2], &front_vector_, sizeof(D3DXVECTOR3));

			this->transform_component_->SetRotationMatrix(rotation_matrix_);
			
			// 移動方向を確定
			move_direction = (front_vector_ * move_speed_) * deltaTime;
		}
		else
		{
			this->transform_component_->SetDirection(parent_front_vector_);

			// 移動方向を確定
			move_direction = (parent_front_vector_ * move_speed_) * deltaTime;
		}

		this->transform_component_->AddTranslation(move_direction);
	}

	// 衝突判定の座標を更新
	{
		// 座標を取得
		auto bullet_position = *this->transform_component_->GetPosition();

		// 球の衝突判定
		this->sphere_collider_->SetTranslation(bullet_position);
	}

	// 生存時間への加算
	alive_time_ += deltaTime;

	// 生存時間がキルタイマーを上回ったら
	if (alive_time_ >= kill_timer_)
	{
		this->SetGameObjectState(State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/* プレイヤーの姿勢を合成
-----------------------------------------------------------------------------*/
void NormalBullet::CombinePlayerTransform(void)
{
	if (is_bullet_create_frame_)
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
		is_bullet_create_frame_ = false;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/