/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameObject.h] �Q�[���I�u�W�F�N�g�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���̃N���X����p���E�h�������ăQ�[���I�u�W�F�N�g���쐬����
=============================================================================*/
#ifndef GAME_OBJECT_H_
#define	GAME_OBJECT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �Q�[���I�u�W�F�N�g�̃x�[�X�N���X
-------------------------------------*/
class GameObject
{
public:
	enum class TypeID
	{
		None = -1
		//�������g
		, GameObject

		//�A�N�^�[(�Ɨ��������������Q�[���I�u�W�F�N�g)
		, Camera
		, Enemy
		, Player


		, MAX		//�Q�[���I�u�W�F�N�g��ID�̍ő�l
	};

	//�Q�[���I�u�I�u�W�F�N�g�����L����^��ID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	//��������Q�[���I�u�W�F�N�g���H
		, Paused	//��~����Q�[���I�u�W�F�N�g���H
		, Dead		//���ʃQ�[���I�u�W�F�N�g���H

		, MAX		//��Ԃ̍ő�l
	};

public:
	GameObject(class GameManager* gameManager);
	virtual ~GameObject(void);

	void Init(void);
	void Uninit(void);
	void Input(void); 
	virtual void InputGameObject(void);	//���override�ł���悤��
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateGameObject(float deltaTime);	//���override�ł���悤��

	//�p�����̍X�V
	void ComputeWorldTransform();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	void SetState(State state) { state_ = state; };
	State GetState(void) { return state_; }

	virtual TypeID GetType(void) const { return TypeID::GameObject; } //���override�ł���悤��

	const std::vector<class Component*>& GetComponents() const { return components_; }

	class GameManager* GetGameManager(void) { return game_manager_; }


private:
	//GameObject�̏��L��
	class GameManager*				game_manager_;

	//GameObject�̏��
	State							state_;

	//�p������R���|�[�l���g
	class TransformComponent*		transform_component_;

	//�p�������Čv�Z���邩
	bool							re_compute_transform_;

	//���L�R���|�[�l���g
	std::vector<class Component*>	components_;
};

#endif //GAME_OBJECT_H_
/*=============================================================================
/*		End of File
=============================================================================*/