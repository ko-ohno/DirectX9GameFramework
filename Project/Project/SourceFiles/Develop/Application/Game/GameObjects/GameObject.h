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
#include "../StdAfx.h"

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


		, MAX		//ゲームオブジェクトのIDの最大値
	};

	//ゲームオブオブジェクトが所有する型のID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	//活動するゲームオブジェクトか？
		, Paused	//停止するゲームオブジェクトか？
		, Dead		//死ぬゲームオブジェクトか？

		, MAX		//状態の最大値
	};

public:
	GameObject(class GameManager* gameManager);
	virtual ~GameObject(void);

	void Init(void);
	void Uninit(void);
	void Input(void); 
	virtual void InputGameObject(void);	//後でoverrideできるように
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateGameObject(float deltaTime);	//後でoverrideできるように

	//姿勢情報の更新
	void ComputeWorldTransform();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	void SetState(State state) { state_ = state; };
	State GetState(void) { return state_; }

	virtual TypeID GetType(void) const { return TypeID::GameObject; } //後でoverrideできるように

	const std::vector<class Component*>& GetComponents() const { return components_; }

	class GameManager* GetGameManager(void) { return game_manager_; }


private:
	//GameObjectの所有者
	class GameManager*				game_manager_;

	//GameObjectの状態
	State							state_;

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