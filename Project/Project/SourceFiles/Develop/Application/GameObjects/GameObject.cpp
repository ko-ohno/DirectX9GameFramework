/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameObject.cpp] ゲームオブジェクトのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームオブジェクトの共有の処理を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "../GameManager.h"
#include "GameObject.h"
#include "Component.h"
#include "Component/TransformComponent.h"


//ゲームオブジェクトのリスト
const char* GameObject::GameObjectTypeNames[static_cast<int>(TypeID::MAX)] = {
	//自分自身
	"GameObject"

	//アクター(独立した役割を持つゲームオブジェクト)
	, "Camera"
	, "Enemy"
	, "Player"
};

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
GameObject::GameObject(class GameManager* gameManager)
	: game_manager_(gameManager)
	, state_(State::Active)
	, re_compute_transform_(true)
{
	//ゲームオブジェクトを管理先へ追加
	game_manager_->AddGameObject(this);

	//姿勢制御コンポーネントの追加
	transform_component_ = new TransformComponent(this);

	//ゲームオブジェクトの初期化
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
GameObject::~GameObject(void)
{
	this->Uninit();

	game_manager_->RemoveGameObject(this);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
void GameObject::Init(void)
{
	
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void GameObject::Uninit(void)
{
	//コンポーネントの破棄
	while (!components_.empty())
	{
		delete components_.back();
	}
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void GameObject::Input(void)
{
	//コンポーネントの入力処理

	if (state_ == State::Active)
	{
		for (auto component : components_)
		{
			component->Input();
		}
		InputGameObject(); //サブクラスが、挙動をoverrideできるように
	}
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの入力処理:サブクラスが、挙動をoverrideできるように
-----------------------------------------------------------------------------*/
void GameObject::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void GameObject::Update(float deltaTime)
{
	if (state_ == State::Active)
	{
		if (re_compute_transform_)
		{
			ComputeWorldTransform();
		}
		UpdateComponents(deltaTime);
		UpdateGameObject(deltaTime);	//サブクラスが、挙動をoverrideできるように
	}
}

/*-----------------------------------------------------------------------------
/* コンポーネントの更新処理
-----------------------------------------------------------------------------*/
void GameObject::UpdateComponents(float deltaTime)
{
	for (auto components : components_)
	{
		components->Update(deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/* ゲームオブジェクトの更新処理:サブクラスが、挙動をoverrideできるように
-----------------------------------------------------------------------------*/
void GameObject::UpdateGameObject(float deltaTime)
{
}

/*-----------------------------------------------------------------------------
/* 姿勢制御の更新
-----------------------------------------------------------------------------*/
void GameObject::ComputeWorldTransform()
{
	re_compute_transform_ = false;

	//拡縮・回転・平行移動の情報を格納

	for (auto components : components_)
	{
		components->OnUpdateWorldTransform();
	}
}

/*-----------------------------------------------------------------------------
/* コンポーネントの追加
-----------------------------------------------------------------------------*/
void GameObject::AddComponent(Component* component)
{
	int my_update_order = component->GetUpdateOrder();

	//現在から追加されるコンポーネントのUpdateOrderと
	//各コンポーネントのUpdateOrderとを比較
	//UpdateOrderが降順になるように適時追加していく。
	auto iter = components_.begin();
	for (;
		iter != components_.end();
		++iter)
	{
		if (my_update_order < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	components_.insert(iter, component);
}

/*-----------------------------------------------------------------------------
/* コンポーネントの削除
-----------------------------------------------------------------------------*/
void GameObject::RemoveComponent(Component* component)
{
	auto iter = std::find(components_.begin()
						, components_.end()
						, component);	//探す対象

	if (iter != components_.end())
	{
		components_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/