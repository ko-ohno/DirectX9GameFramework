/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Component.h] �R���|�[�l���g�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�R���|�[�l���g�̃x�[�X�N���X
=============================================================================*/
#ifndef COMPONENT_H_
#define	COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �R���|�[�l���g�̃x�[�X�N���X
-------------------------------------*/
class Component
{
public:
	enum class TypeID
	{
		None = -1
		//�x�[�X�N���X
		, Component

		//AI
		, AIComponent
		, EnemyAIComponent
		//����
		, AudioComponent
		//�J����
		, CameraComponent
		, FollowCameraComponent
		//�Փ˔���
		, ColliderComponent
		, SphereColliderComponent
		, CapsuleColliderComponent
		//����
		, InputComponent
		, PlayerInputComponent
		, AutomaticInputComponent
		//�����_�����O(�`�Ƃ��ďo��)����I�u�W�F�N�g
		, RenderComponent
		, SpriteComponent
		//�p������ƈړ�
		, TransformComponent
		, MoveComponent 
		
		//�R���|�[�l���g�̍ő�l
		, MAX
	};

	static const char* ComponentTypeNames[static_cast<int>(TypeID::MAX)];

public:
	Component(class GameObject* gameObject, int updateOrder = 100);
	Component(class UIObject* uiObject, int updateOrder = 100);
	virtual~Component(void);

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Input(void);
	virtual void Update(float deltaTime);

	virtual void OnUpdateWorldTransform();

	//��ŃT�u�N���X���������㏑���ł���悤�Ɂ@
	virtual void CallComponent(void) {};


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
	class GameObject*	owner_;				//����(�R���|�[�l���g)�̏��L��
	int					update_order_;		//�������g�̍X�V����
};

#endif //COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/
