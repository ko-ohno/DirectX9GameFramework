/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemy.cpp] �����G�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����G�̃Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../../StdAfx.h"
#include "StrongEnemy.h"
#include "../../Bullet/NormalBullet.h"
#include "../../../../../SandBoxManager/BulletManager.h"
#include "../../../../../CheckCollision.h"

// �ړ��R���|�[�l���g
#include "../../../../Component/MoveComponent/EnemyMoveComponent/StrongEnemyMoveComponent.h"

// �{�XAI�R���|�[�l���g
#include "../../../../Component/AIComponent/EnemyAIComponent/StrongEnemyAIComponent.h"

// ���b�V���R���|�[�l���g
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"

// ���̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// �{�b�N�X�̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

// �G�̕���R���|�[�l���g
#include "../../../../Component/WeaponComponent/EnemyBlasterWeaponComponent.h"

// ���̓`�F�b�N
#include "../../../../../Input/InputCheck.h"

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"

// ���̂ق�
#include "../../../../../Game.h"
#include "../../../../../SandBoxManager/ActorManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemy::StrongEnemy(Game* game)
	: Enemy(game)
	, enemy_blaster_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
StrongEnemy::~StrongEnemy(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool StrongEnemy::Init(void)
{
	// �������W��������
	{
		this->transform_component_->SetTranslationY(-100.f);
	
		// �e�X�g�p�������W
		//this->transform_component_->SetTranslationX(3.f);
		//this->transform_component_->SetTranslationZ(8.f);
	}

	// �{�X��AI�𐶐� 
	enemy_ai_ = NEW StrongEnemyAIComponent(this);

	// �{�X�̈ړ��R���|�[�l���g�𐶐�
	enemy_move_ = NEW StrongEnemyMoveComponent(this);

	// �������W��������
	{
		this->transform_component_->SetTranslationY(-100.f);
		this->enemy_move_->SetStartPositionY(-100.f);

		// �e�X�g�p�������W
		//this->transform_component_->SetTranslationX(3.f);
		//this->transform_component_->SetTranslationZ(8.f);
	}

	// �{�X�̃��b�V������
	{
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyStrong);
		actor_mesh_->SetEnableLighting(true);			// ���C�e�B���O��L���ɂ���
	}

	// �{�X�̏�Ԃ�������
	{
		auto init_StrongEnemy_state = EnemyState::Idle;

		// �G�̏�Ԃ�������
		enemy_ai_->SetEnemyState(init_StrongEnemy_state);
		enemy_move_->SetEnemyState(init_StrongEnemy_state);
	}

	// ����̐���
	{
		enemy_blaster_ = NEW EnemyBlasterWeaponComponent(this);
	}

	// �Փ˔���֌W
	{
		// �Փ˔���̍����@�I�t�Z�b�g���W
		const float collider_height_pos = 0.f;

		// ��
		{
			// ���̔��a
			const float sphere_radius_size = 3.f;

			// �Փ˔���
			sphere_collider_ = NEW SphereColliderComponent(this);
			sphere_collider_->SetTranslationY(collider_height_pos);
			sphere_collider_->SetRadius(sphere_radius_size);

			// �M�Y��
			sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
			sphere_gizmo_->SetTranslationY(collider_height_pos);
			sphere_gizmo_->SetScale(sphere_radius_size);
		}

		// ��
		{
			// ���̍���
			const float box_height_size = 1.5f;

			// ���̐������̑傫��
			const float box_size = 3.f;

			// �Փ˔���
			obb_collider_ = NEW OBBColliderComponent(this);
			obb_collider_->SetTranslationY(collider_height_pos);
			obb_collider_->SetDirLength(box_size, AxisType::X);
			obb_collider_->SetDirLength(box_height_size, AxisType::Y);
			obb_collider_->SetDirLength(box_size, AxisType::Z);

			// �M�Y��
			obb_collider_gizmo_ = NEW BoxGizmoRendererComponent(this);
			obb_collider_gizmo_->SetVertexColor(0, 255, 255, 128);
			obb_collider_gizmo_->SetTranslationY(collider_height_pos);
			obb_collider_gizmo_->SetScaleX(box_size);
			obb_collider_gizmo_->SetScaleY(box_height_size);
			obb_collider_gizmo_->SetScaleZ(box_size);
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void StrongEnemy::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̓��͏���
-----------------------------------------------------------------------------*/
void StrongEnemy::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* override�Ŏ������g���X�V
-----------------------------------------------------------------------------*/
void StrongEnemy::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// AI�R���|�[�l���g�Ɏ��g��HP��ʒm����
	{
		enemy_ai_->SetHitPoint(this->GetHitPoint());
	}

	/*
	*			��		EnemyState		��
	*
	����������������������������������������������������
	���@�@Move�@�@��  �� StrongEnemy  ���@���@�@AI�@�@�@��
	����������������������������������������������������
	*
	*			��		MotionState		��
	*/

	// AI�R���|�[�l���g����GAI�̍s���X�e�[�g���擾
	auto ai_state = enemy_ai_->GetEnemyState();
	{
		// �ړ��R���|�[�l���g�ցA�GAI�̍s���X�e�[�g��ʒm
		enemy_move_->SetEnemyState(ai_state);
	}

	// �ړ��R���|�[�l���g����ړ����[�V������Ԃ��擾
	auto move_motion_state = enemy_move_->GetMotionState();
	{
		// AI�R���|�[�l���g�ֈړ����[�V������Ԃ�ʒm
		enemy_ai_->SetMotionState(move_motion_state);
	}

	// ���g��AI�̃X�e�[�g����U���͂��X�V����
	switch (ai_state)
	{
	case EnemyState::Idle:
		attack_ = 0.f;
		break;

	case EnemyState::Shooting:
		attack_ = ATTACK_VALUE_SHOOT;
		break;

	case EnemyState::Destroy:
		attack_ = 0.f;
		break;

	default:
		attack_ = 10.f;
		break;
	}


	// �Փ˔���̐ݒ�
	auto bullets = game_->GetBulletManager()->GetBulletGameObjectList();
	for (auto bullet : bullets)
	{
		// Bullet�̏��L�҂�Player���𒲂ׂ�
		auto bullet_game_object = bullet->GetParentGameObject();
		if (bullet_game_object->GetType() != GameObject::TypeID::Player)
		{
			continue;
		}

		// �v���C���[�̃o���b�g�̏Փ˔�����擾
		auto components = bullet->GetComponents();
		for (auto component : components)
		{
			auto component_type = component->GetComponentType();
			if (component_type == Component::TypeID::SphereColliderComponent)
			{
				if (CheckCollision::SphereVSSpghre(this->GetSphereCollider(), bullet->GetSphereCollider()))
				{
					// �G�l�~�[���j�󂳂��
					this->SetGameObjectState(State::Destroy);

					// �Փ˂����o���b�g��j������
					bullet->SetGameObjectState(State::Dead);
				}
			}
		}
	}

	if (this->GetGameObjectState() == State::Destroy)
	{
		// �X�R�A�։��Z����
	}
}
/*=============================================================================
/*		End of File
=============================================================================*/