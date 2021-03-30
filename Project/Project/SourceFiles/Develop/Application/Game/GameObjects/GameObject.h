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
#include "../../../StdAfx.h"
#include "Component/RendererComponent.h"

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

		, TestMesh
		, TestSprite
		, TestBillboard

		//UI
		, UI

		, HUD
		, PauseMenu
		, Result
		, Title

		, MAX		//�Q�[���I�u�W�F�N�g��ID�̍ő�l
	};

	//�Q�[���I�u�I�u�W�F�N�g�����L����^��ID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	//��������Q�[���I�u�W�F�N�g���H
		, Paused	//��~����Q�[���I�u�W�F�N�g���H
		, Dead		//�j������Q�[���I�u�W�F�N�g���H

		, MAX		//��Ԃ̍ő�l
	};

public:
	GameObject(class Game* game);
	virtual ~GameObject(void);

	bool Init(void);
	void Uninit(void);
	void Input(void); 
	virtual void InputGameObject(void);	//���override�ł���悤��
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateGameObject(float deltaTime);	//���override�ł���悤��

	//�p�����̍X�V
	void ComputeWorldTransform();

	//
	// �R���|�[�l���g�̑���
	//

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	//
	// �Q�[���I�u�W�F�N�g�̏��L�҂̎擾
	//
	
	class Game* GetGame(void) const { return game_; }

	//
	// �Q�[���I�u�W�F�N�g�̏��
	//

	void SetState(State state) { state_ = state; };
	State GetState(void) { return state_; }
	
	//�Q�[���I�u�W�F�N�g�̃��C���[�ɂ���

	void SetRendererLayerType(RendererLayerType rendererLayerType) { renderer_layer_type_ = rendererLayerType; }
	RendererLayerType GetRendererLayerType(void) { return renderer_layer_type_; }

	//�V�F�[�_�[�̃Z�b�g
	void SetShader(class Shader* shader) { shader_ = shader; } 


	//
	//�@�Q�[���I�u�W�F�N�g���J�����������ꍇ�̏����@
	//	�F��ŃT�u�N���X��override�ł���悤��virutal
	//

	virtual D3DXMATRIX* GetViewMatrix(void) { return nullptr; }
	virtual D3DXMATRIX* GetViewInverseMatrix(void) { return nullptr; }
	virtual D3DXMATRIX* GetProjection2DMatrix(void) { return nullptr; }
	virtual D3DXMATRIX* GetProjection3DMatrix(void) { return nullptr; }


	//�Q�[���I�u�W�F�N�g�̎p�����̎擾
	class TransformComponent* GetTransform(void) const { return transform_component_; }

	//�Q�[���I�u�W�F�N�g�̃R���|�[�l���g�̃R���e�i���擾
	const std::vector<class Component*>& GetComponents() const { return components_; }

	//�Q�[���I�u�W�F�N�g��ID�̎擾
	virtual TypeID GetType(void) const { return TypeID::GameObject; } //���override�ł���悤��

protected:
	//GameObject�̏��L��
	class Game*						game_;

	//GameObject�̏��
	State							state_;

	//�����_���[�̃��C���[�^���@
	RendererLayerType				renderer_layer_type_;

	//���L����V�F�[�_�[�I�u�W�F�N�g
	class Shader*					shader_;

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