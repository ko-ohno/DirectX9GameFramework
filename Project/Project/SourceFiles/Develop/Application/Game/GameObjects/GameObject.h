/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameObject.h] ゲームオブジェクトのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：このクラスから継承・派生させてゲームオブジェクトを作成する
=============================================================================*/
#ifndef GAME_OBJECT_H_
#define	GAME_OBJECT_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "Component/RendererComponent.h"
#include "Component/ParameterComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* ゲームオブジェクトのベースクラス
-------------------------------------*/
class GameObject
{
public:
	enum class TypeID
	{
		None = -1
		// 自分自身
		, GameObject
		// カメラ
		, Camera
		, GameCamera

		// UI
		, UI
		, Fade
		, HUD
		, PauseMenu
		, Result
		, Title

		// サンドボックス
		, SandBox
		, Bullet
		, ChargeBullet
		, Actor
		, Player
		, Enemy
		, WeakEnemy
		, StrongEnemy
		, Boss


		// 背景
		, BackGround
		, Planet
		, SkyBox

		// ゲームマネージャ
		, GameManager

		// テスト用のゲームオブジェクト
		, SpriteTest
		, BillboardTest
		, MeshTest
		, EffectTest
		, AudioTest
		, ColliderTest
		, CameraTest
		, SaveDataTest

		, MAX		//ゲームオブジェクトのIDの最大値
	};

	//ゲームオブオブジェクトが所有する型のID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	//活動するゲームオブジェクトか？
		, Paused	//停止するゲームオブジェクトか？
		, Dead		//破棄するゲームオブジェクトか？

		, MAX		//状態の最大値
	};

public:
	GameObject(class Game* game);
	virtual ~GameObject(void);

	bool Init(void);
	void Uninit(void);
	void Input(void); 
	virtual void InputGameObject(void);	//後でoverrideできるように
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateGameObject(float deltaTime);	//後でoverrideできるように

	//姿勢情報の更新
	void ComputeWorldTransform();

	//
	// コンポーネントの操作
	//

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	// 値コンポーネントの操作
	void AddParameterComponent(class ParameterComponent* component);
	void RemoveParameterComponent(class ParameterComponent* component);

	//
	// ゲームオブジェクトの所有者の取得
	//
	
	class Game* GetGame(void) const { return game_; }

	//
	// 自身の親のゲームオブジェクトの設定
	//
	void SetParentGameObject(class GameObject* parentGameObject) { game_object_parent_ = parentGameObject; };
	class GameObject* GetParentGameObject(void) { return game_object_parent_; }

	//
	// ゲームオブジェクトの状態
	//

	void SetGameObjectState(State state) { state_ = state; };
	State GetGameObjectState(void) { return state_; }
	
	//ゲームオブジェクトのレイヤーについて

	void SetRendererLayerType(RendererLayerType rendererLayerType) { renderer_layer_type_ = rendererLayerType; }
	RendererLayerType GetRendererLayerType(void) { return renderer_layer_type_; }

	// ゲームオブジェクトの検索処理
	class GameObject* FindGameObject(TypeID findTypeID);

	//ゲームオブジェクトの姿勢情報の取得
	class TransformComponent* GetTransform(void) const { return transform_component_; }

	//ゲームオブジェクトのコンポーネントのコンテナを取得
	const std::vector<class Component*>& GetComponents() const { return components_; }

	//ゲームオブジェクトのコンポーネントのコンテナを取得
	const std::vector<class ParameterComponent*>& GetParameterComponents() const { return parameter_components_; }

	//ゲームオブジェクトのIDの取得
	virtual TypeID GetType(void) const { return TypeID::GameObject; } //後でoverrideできるように

protected:
	// GameObjectの所有者
	class Game*						game_;

	// GameObjectの状態
	State							state_;

	// このGameObjectの親
	class GameObject*				game_object_parent_;

	//レンダラーのレイヤー型情報　
	RendererLayerType				renderer_layer_type_;

	// 姿勢制御コンポーネント
	class TransformComponent*		transform_component_;

	// 姿勢情報を再計算するか
	bool							re_compute_transform_;

	// 所有コンポーネント
	std::vector<class Component*>	components_;

	// 値コンポーネント
	std::vector<class ParameterComponent*>	parameter_components_;
};

#endif //GAME_OBJECT_H_
/*=============================================================================
/*		End of File
=============================================================================*/