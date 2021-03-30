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
		//自分自身
		, GameObject

		//アクター(独立した役割を持つゲームオブジェクト)
		, Camera
		, Enemy
		, Player

		, TestMesh
		, TestSprite
		, TestBillboard

		//UI
		, UI

		, HUD
		, PauseMenu
		, Result
		, Title

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

	//
	// ゲームオブジェクトの所有者の取得
	//
	
	class Game* GetGame(void) const { return game_; }

	//
	// ゲームオブジェクトの状態
	//

	void SetState(State state) { state_ = state; };
	State GetState(void) { return state_; }
	
	//ゲームオブジェクトのレイヤーについて

	void SetRendererLayerType(RendererLayerType rendererLayerType) { renderer_layer_type_ = rendererLayerType; }
	RendererLayerType GetRendererLayerType(void) { return renderer_layer_type_; }

	//シェーダーのセット
	void SetShader(class Shader* shader) { shader_ = shader; } 


	//
	//　ゲームオブジェクトがカメラだった場合の処理　
	//	：後でサブクラスがoverrideできるようにvirutal
	//

	virtual D3DXMATRIX* GetViewMatrix(void) { return nullptr; }
	virtual D3DXMATRIX* GetViewInverseMatrix(void) { return nullptr; }
	virtual D3DXMATRIX* GetProjection2DMatrix(void) { return nullptr; }
	virtual D3DXMATRIX* GetProjection3DMatrix(void) { return nullptr; }


	//ゲームオブジェクトの姿勢情報の取得
	class TransformComponent* GetTransform(void) const { return transform_component_; }

	//ゲームオブジェクトのコンポーネントのコンテナを取得
	const std::vector<class Component*>& GetComponents() const { return components_; }

	//ゲームオブジェクトのIDの取得
	virtual TypeID GetType(void) const { return TypeID::GameObject; } //後でoverrideできるように

protected:
	//GameObjectの所有者
	class Game*						game_;

	//GameObjectの状態
	State							state_;

	//レンダラーのレイヤー型情報　
	RendererLayerType				renderer_layer_type_;

	//所有するシェーダーオブジェクト
	class Shader*					shader_;

	//姿勢制御コンポーネント
	class TransformComponent*		transform_component_;

	//姿勢情報を再計算するか
	bool							re_compute_transform_;

	//所有コンポーネント
	std::vector<class Component*>	components_;
};

#endif //GAME_OBJECT_H_
/*=============================================================================
/*		End of File
=============================================================================*/