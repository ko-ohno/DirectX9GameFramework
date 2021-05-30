/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Component.cpp] コンポーネントのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：コンポーネントのベースクラスの処理を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "Component.h"
#include "GameObject.h"

//コンポーネントのリスト
const char* Component::ComponentTypeNames[static_cast<int>(TypeID::Max)] = {
	// 自分自身
	"Component"
	// AI
	, "AIComponent"
	, "EnemyAIComponent"
	// 音声
	, "AudioComponent"
	// カメラ
	, "CameraComponent"
	, "FollowCameraComponent"
	// 衝突判定
	, "ColliderComponent"
	, "CircleColliderComponent"
	, "RectangleColliderComponent"
	, "SphereColliderComponent"
	, "OBBColliderComponent"
	, "CapsuleColliderComponent"
	// 入力
	, "InputComponent"
	, "PlayerInputComponent"
	, "AutomaticInputComponent"
	// レンダリング(形として出力)するオブジェクト
	, "RenderComponent"
	, "SpriteRendererComponent"
	, "BillboardRendererComponent"
	, "FFPMeshRendererComponent"
	, "StdMeshRendererComponent"
	, "EffectRendererComponent"
	// ギズモとしてレンダリング(形として出力)するオブジェクト
	, "GizmoRendererComponent"
	, "GridGizmoRendererComponent"
	, "SphereGizmoRendererComponent"
	, "BoxGizmoRendererComponent"
	// 姿勢制御
	, "TransformComponent"
	// 移動コンポーネント
	, "MoveComponent"
	, "PlayerMoveComponent"
	// 武器コンポーネント
	, "WeaponComponent"
	, "BlasterComponent"
	, "ChargeShotBlasterComponent"

};

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Component::Component(GameObject* owner, int updateOrder)
	: owner_(owner)
	, update_order_(updateOrder)
{
	owner_->AddComponent(this);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Component::~Component(void)
{
	owner_->RemoveComponent(this);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Component::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Component::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void Component::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Component::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* コンポーネントの姿勢制御の更新
-----------------------------------------------------------------------------*/
void Component::OnUpdateWorldTransform()
{
}

/*-----------------------------------------------------------------------------
/* コンポーネントの状態の読み込み
-----------------------------------------------------------------------------*/
void Component::LoadProperties(void)
{
}

/*-----------------------------------------------------------------------------
/* コンポーネントの状態の保存
-----------------------------------------------------------------------------*/
void Component::SaveProperties(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/