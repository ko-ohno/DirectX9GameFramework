/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Bullet.cpp] �o���b�g�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�o���b�g�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "Bullet.h"
#include "../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../Component/ColliderComponent/SphereColliderComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Bullet::Bullet(Game* game)
	: SandBox(game)
	, parent_front_vector_(0.f, 0.f, 0.f)
	, kill_timer_(3.f)
	, alive_time_(0.f)
	, move_speed_(30.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Bullet::~Bullet(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Bullet::Init(void)
{
	// �e�̎擾
	if (game_object_parent_ == nullptr)
	{
		auto game_objects = game_->GetGameObjects();

		// �������茟��
		for (auto game_object : game_objects)
		{
			auto game_object_id = game_object->GetType();

			//�v���C���[�����̃Q�[���I�u�W�F�N�g�̐e�ɐݒ�
			if (game_object_id == TypeID::Player)
			{
				game_object_parent_ = game_object;
			}
		}
	}

	// �o���b�g�̐������쐬
	{
		// �e�ۂ̃��b�V���\��
		bullet_mesh_ = NEW FFPMeshRendererComponent(this);
		bullet_mesh_->SetMesh(XFileMeshType::GreenBullet);

		const float scale = 1.f;

		// �e�ۂ̏Փ˔���̒ǉ�
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);

		// �e�ۂ̃M�Y���𐶐�
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
	}

	// �o���b�g�̎p����������
	{
		// �e�̎p�����擾
		TransformComponent* parent_transform;

		if (game_object_parent_ != nullptr)
		{
			parent_transform = game_object_parent_->GetTransform();

			// �O�x�N�g���̎擾�@�@
			parent_front_vector_ = *parent_transform->GetFrontVector();

			// ��]�̎p����ݒ�
			this->transform_component_->SetRotationMatrix(*parent_transform->GetRotationMatrix());
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Bullet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void Bullet::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Bullet::UpdateGameObject(float deltaTime)
{	
	// �p���̉�]�����ʕ�Ԃ����Ȃ�
	//bullet_transform->SetSlerpSpeed(100.f);

	this->transform_component_->IsSetExecuteSlerp(false);

	this->transform_component_->SetDirection(parent_front_vector_);
	{
		// �ړ�
		auto move_direction = (parent_front_vector_ * move_speed_ ) * deltaTime;

		// �ړ�
		this->transform_component_->AddTranslation(move_direction);
	}

	// �������Ԃւ̉��Z
	alive_time_ += deltaTime;

	// �������Ԃ��L���^�C�}�[����������
	if (alive_time_ >= kill_timer_)
	{
		this->SetState(State::Dead);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/