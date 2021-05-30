/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Component.cpp] �R���|�[�l���g�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�R���|�[�l���g�̃x�[�X�N���X�̏������`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "Component.h"
#include "GameObject.h"

//�R���|�[�l���g�̃��X�g
const char* Component::ComponentTypeNames[static_cast<int>(TypeID::Max)] = {
	// �������g
	"Component"
	// AI
	, "AIComponent"
	, "EnemyAIComponent"
	// ����
	, "AudioComponent"
	// �J����
	, "CameraComponent"
	, "FollowCameraComponent"
	// �Փ˔���
	, "ColliderComponent"
	, "CircleColliderComponent"
	, "RectangleColliderComponent"
	, "SphereColliderComponent"
	, "OBBColliderComponent"
	, "CapsuleColliderComponent"
	// ����
	, "InputComponent"
	, "PlayerInputComponent"
	, "AutomaticInputComponent"
	// �����_�����O(�`�Ƃ��ďo��)����I�u�W�F�N�g
	, "RenderComponent"
	, "SpriteRendererComponent"
	, "BillboardRendererComponent"
	, "FFPMeshRendererComponent"
	, "StdMeshRendererComponent"
	, "EffectRendererComponent"
	// �M�Y���Ƃ��ă����_�����O(�`�Ƃ��ďo��)����I�u�W�F�N�g
	, "GizmoRendererComponent"
	, "GridGizmoRendererComponent"
	, "SphereGizmoRendererComponent"
	, "BoxGizmoRendererComponent"
	// �p������
	, "TransformComponent"
	// �ړ��R���|�[�l���g
	, "MoveComponent"
	, "PlayerMoveComponent"
	// ����R���|�[�l���g
	, "WeaponComponent"
	, "BlasterComponent"
	, "ChargeShotBlasterComponent"

};

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Component::Component(GameObject* owner, int updateOrder)
	: owner_(owner)
	, update_order_(updateOrder)
{
	owner_->AddComponent(this);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Component::~Component(void)
{
	owner_->RemoveComponent(this);
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Component::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Component::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void Component::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Component::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/* �R���|�[�l���g�̎p������̍X�V
-----------------------------------------------------------------------------*/
void Component::OnUpdateWorldTransform()
{
}

/*-----------------------------------------------------------------------------
/* �R���|�[�l���g�̏�Ԃ̓ǂݍ���
-----------------------------------------------------------------------------*/
void Component::LoadProperties(void)
{
}

/*-----------------------------------------------------------------------------
/* �R���|�[�l���g�̏�Ԃ̕ۑ�
-----------------------------------------------------------------------------*/
void Component::SaveProperties(void)
{
}

/*=============================================================================
/*		End of File
=============================================================================*/