/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameObject.cpp] �Q�[���I�u�W�F�N�g�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���I�u�W�F�N�g�̋��L�̏������`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "../game.h"
#include "GameObject.h"
#include "Component/TransformComponent.h"

//�Q�[���I�u�W�F�N�g�̃��X�g(�Z�[�u�p�̎��  �e�L�X�g�f�[�^)
const char* GameObject::GameObjectTypeNames[static_cast<int>(TypeID::MAX)] = {
	//�������g
	"GameObject"

	// �J����
	, "Camera"
	, "GameCamera"

	// UI
	, "UI"
	, "Fade"
	, "HUD"
	, "PauseMenu"
	, "Result"
	, "Title"

	// �A�N�^�[
	, "Actor"
	, "Player"
	, "Enemy"

	// �w�i
	, "BackGround"
	, "Planet"
	, "SkyBox"

	// �Q�[���}�l�[�W��
	, "GameManager"

	// �e�X�g�p�̃Q�[���I�u�W�F�N�g
	, "SpriteTest"
	, "BillboardTest"
	, "MeshTest"
	, "EffectTest"
	, "AudioTest"
	, "ColliderTest"
	, "CameraTest"
	, "SaveDataTest"

};

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
GameObject::GameObject(class Game* game)
	: game_(game)
	, state_(State::Active)
	, renderer_layer_type_(RendererLayerType::None)
	, transform_component_(nullptr)
	, re_compute_transform_(true)
{
	//�Q�[���I�u�W�F�N�g���Ǘ���֒ǉ�
	game_->AddGameObject(this);

	//�Q�[���I�u�W�F�N�g�̏�����
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
GameObject::~GameObject(void)
{
	this->Uninit();

	game_->RemoveGameObject(this);
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool GameObject::Init(void)
{
	//�p���R���|�[�l���g�̍쐬
	{
		transform_component_ = NEW TransformComponent(this);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void GameObject::Uninit(void)
{
	//�R���|�[�l���g�̔j��
	while (!components_.empty())
	{
		delete components_.back();
	}
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void GameObject::Input(void)
{
	//�R���|�[�l���g�̓��͏���
	if (state_ == State::Active)
	{
		for (auto component : components_)
		{
			component->Input();
		}
		this->InputGameObject(); //�T�u�N���X���A������override�ł���悤��
	}
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̓��͏���:�T�u�N���X���A������override�ł���悤��
-----------------------------------------------------------------------------*/
void GameObject::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void GameObject::Update(float deltaTime)
{
	if (state_ == State::Active)
	{
		if (this->GetRendererLayerType() == RendererLayerType::None)
		{
			assert(!"�Q�[���I�u�W�F�N�g�̃����_���[�̃��C���[���I������Ă��܂���I");
		}

		if (re_compute_transform_)
		{
			this->ComputeWorldTransform();
		}
		this->UpdateComponents(deltaTime);
		this->UpdateGameObject(deltaTime);	//�T�u�N���X���A������override�ł���悤��
	}
}

/*-----------------------------------------------------------------------------
/* �R���|�[�l���g�̍X�V����
-----------------------------------------------------------------------------*/
void GameObject::UpdateComponents(float deltaTime)
{
	for (auto components : components_)
	{
		components->Update(deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̍X�V����:�T�u�N���X���A������override�ł���悤��
-----------------------------------------------------------------------------*/
void GameObject::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �p������̍X�V
-----------------------------------------------------------------------------*/
void GameObject::ComputeWorldTransform()
{
	re_compute_transform_ = false;

	//�g�k�E��]�E���s�ړ��̏����i�[

	for (auto components : components_)
	{
		components->OnUpdateWorldTransform();
	}
}

/*-----------------------------------------------------------------------------
/* �R���|�[�l���g�̒ǉ�
-----------------------------------------------------------------------------*/
void GameObject::AddComponent(Component* component)
{
	int my_update_order = component->GetUpdateOrder();

	//���݂���ǉ������R���|�[�l���g��UpdateOrder��
	//�e�R���|�[�l���g��UpdateOrder�Ƃ��r
	//UpdateOrder���~���ɂȂ�悤�ɓK���ǉ����Ă����B
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
/* �R���|�[�l���g�̍폜
-----------------------------------------------------------------------------*/
void GameObject::RemoveComponent(Component* component)
{
	auto iter = std::find(components_.begin()
						 , components_.end()
						 , component);	//�T���Ώ�

	if (iter != components_.end())
	{
		components_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/