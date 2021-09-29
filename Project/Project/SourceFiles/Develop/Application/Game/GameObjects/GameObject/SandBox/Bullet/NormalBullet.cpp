/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[NormalBullet.cpp] �o���b�g�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�o���b�g�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "NormalBullet.h"
#include "../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../Component/ColliderComponent/SphereColliderComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

#include "../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
NormalBullet::NormalBullet(Game* game)
	: Bullet(game)
	, bullet_mesh_(nullptr)
	, is_bullet_create_frame_(true)
	, is_set_front_vector_(false)
	, parent_front_vector_(0.f, 0.f, 0.f)
	, right_vector_(1.f, 0.f, 0.f)
	, up_vector_(0.f, 1.f, 0.f)
	, front_vector_(0.f, 0.f, 1.f)
	, kill_timer_(3.f)
	, alive_time_(0.f)
	, move_speed_(30.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
NormalBullet::~NormalBullet(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool NormalBullet::Init(void)
{
	// �o���b�g�̐������쐬
	{
		// �e�ۂ̃��b�V������
		bullet_mesh_ = NEW FFPMeshRendererComponent(this);
		bullet_mesh_->SetMesh(XFileMeshType::BlueBullet);

		// �X�P�[����������
		const float scale = 0.5f;

		// �e�ۂ̏Փ˔���̒ǉ�
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);

		// �e�ۂ̃M�Y���𐶐�
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
		//sphere_collider_gizmo_->IsSetDrawable(false);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void NormalBullet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void NormalBullet::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void NormalBullet::UpdateGameObject(float deltaTime)
{	
	// ���L�҂��Ȃ�������x���𔭍s
	if (game_object_parent_ == nullptr)
	{
		assert(!"Bullet::UpdateGameObject()�F�o���b�g�̏��L�҂��s���ł��I");
	}

	//���L�҂��s���������ꍇ
	const bool is_owner_type_unkown = (parent_game_object_type_ == GameObject::TypeID::None);
	if (is_owner_type_unkown)
	{
		// �e�Q�[���I�u�W�F�N�g�̎�ނ��L��
		parent_game_object_type_ = this->GetParentGameObject()->GetType();
	}

	// ���L�҂��v���C���[�������ꍇ
	if (game_object_parent_->GetType() == GameObject::TypeID::Player)
	{
		this->CombinePlayerTransform();
	}

	// �p���̉�]�����ʕ�Ԃ����Ȃ�(��ɕ�Ԃ̊����ς݂�)
	this->transform_component_->IsSetExecuteSlerpRotation(false);

	if (game_object_parent_ != nullptr)
	{
		auto game_object_parent_id = game_object_parent_->GetType();
		if (game_object_parent_id >= TypeID::Enemy)
		{
			bullet_mesh_->SetMesh(XFileMeshType::RedBullet);
		}
		else
		{
			bullet_mesh_->SetMesh(XFileMeshType::BlueBullet);
		}
	}

	// �o���b�g���p���̉�]���ł��Ă��Ȃ��̂Ō����x�N�g�������]�ł���悤�Ȍv�Z�����l����

	// �ړ�
	{
		D3DXVECTOR3 move_direction = { 0.f, 0.f, 0.f };

		if (is_set_front_vector_ == true)
		{
			// �p���x�N�g���̐���
			{
				D3DXVec3Normalize(&front_vector_, &front_vector_);
				D3DXVec3Normalize(&up_vector_, &up_vector_);
				D3DXVec3Cross(&right_vector_, &up_vector_, &front_vector_);
				D3DXVec3Normalize(&right_vector_, &right_vector_);
				D3DXVec3Cross(&up_vector_, &right_vector_, &front_vector_);
				D3DXVec3Normalize(&up_vector_, &up_vector_);
			}

			// ��]�s��̍쐬
			D3DXMATRIX rotation_matrix_;
			D3DXMatrixIdentity(&rotation_matrix_);
			memcpy(rotation_matrix_.m[0], &right_vector_, sizeof(D3DXVECTOR3));
			memcpy(rotation_matrix_.m[1], &up_vector_,	  sizeof(D3DXVECTOR3));
			memcpy(rotation_matrix_.m[2], &front_vector_, sizeof(D3DXVECTOR3));

			this->transform_component_->SetRotationMatrix(rotation_matrix_);
			
			// �ړ��������m��
			move_direction = (front_vector_ * move_speed_) * deltaTime;
		}
		else
		{
			this->transform_component_->SetDirection(parent_front_vector_);

			// �ړ��������m��
			move_direction = (parent_front_vector_ * move_speed_) * deltaTime;
		}

		this->transform_component_->AddTranslation(move_direction);
	}

	// �Փ˔���̍��W���X�V
	{
		// ���W���擾
		auto bullet_position = *this->transform_component_->GetPosition();

		// ���̏Փ˔���
		this->sphere_collider_->SetTranslation(bullet_position);
	}

	// �������Ԃւ̉��Z
	alive_time_ += deltaTime;

	// �������Ԃ��L���^�C�}�[����������
	if (alive_time_ >= kill_timer_)
	{
		this->SetGameObjectState(State::Dead);
	}
}

/*-----------------------------------------------------------------------------
/* �v���C���[�̎p��������
-----------------------------------------------------------------------------*/
void NormalBullet::CombinePlayerTransform(void)
{
	if (is_bullet_create_frame_)
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
		is_bullet_create_frame_ = false;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/