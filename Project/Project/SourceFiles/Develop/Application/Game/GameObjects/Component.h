/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Component.h] コンポーネントのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：コンポーネントのベースクラス
=============================================================================*/
#ifndef COMPONENT_H_
#define	COMPONENT_H_

/*--- インクルードファイル ---*/

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* コンポーネントのベースクラス
-------------------------------------*/
class Component
{
public:
	enum class TypeID
	{
		None = -1
		//ベースクラス
		, Component

		//AI
		, AIComponent
		, EnemyAIComponent
		//音声
		, AudioComponent
		//カメラ
		, CameraComponent
		, FollowCameraComponent
		//衝突判定
		, ColliderComponent
		, CircleColliderComponent
		, RectangleColliderComponent
		, SphereColliderComponent
		, OBBColliderComponent
		, CapsuleColliderComponent
		//入力
		, InputComponent
		, PlayerInputComponent
		, AutomaticInputComponent
		//レンダリング(形として出力)するオブジェクト
		, RendererComponent
		, SpriteRendererComponent
		, BillboardRendererComponent
		, StdMeshRendererComponent
		, EffectRendererComponent
		//姿勢制御と移動
		, TransformComponent
		, MoveComponent 
		
		//コンポーネントの最大値
		, Max
	};

	static const char* ComponentTypeNames[static_cast<int>(TypeID::Max)];

public:
	Component(class GameObject* gameObject, int updateOrder = 100);
	virtual~Component(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Input(void);
	virtual void Update(float deltaTime);

	virtual void OnUpdateWorldTransform();

	class GameObject* GetOwner(void) { return owner_; }
	int GetUpdateOrder(void) const	 { return update_order_; }

	virtual TypeID GetComponentType() const = 0;

	// Load/Save
	virtual void LoadProperties(void);
	virtual void SaveProperties(void);

	//virtual void LoadProperties(const rapidjson::Value& inObj);
	//virtual void SaveProperties(rapidjson::Document::AllocatorType& alloc,
	//	rapidjson::Value& inObj) const;

	// Create a component with specified properties
	//template <typename T>
	//static Component* Create(class GameObject* actor, const rapidjson::Value& inObj)
	//{
	//	// Dynamically allocate component of type T
	//	T* t = new T(actor);
	//	// Call LoadProperties on new component
	//	t->LoadProperties(inObj);
	//	return t;
	//}

protected:
	class GameObject*	owner_;				//自分(コンポーネント)の所有者
	int					update_order_;		//自分自身の更新順位
};

#endif //COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/
