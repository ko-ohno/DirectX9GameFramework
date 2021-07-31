/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyBlasterWeaponComponent.cpp] �G�̕���R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�̕���R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "EnemyBlasterWeaponComponent.h"
#include "../../GameObject.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../GameObject/SandBox/Bullet.h"
#include "../../../Game.h"
#include "../../GameObject/SandBox/Actor.h"
#include "../../../SandBoxManager/ActorManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EnemyBlasterWeaponComponent::EnemyBlasterWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, player_object_(nullptr)
	, muzzle_flash_(nullptr)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EnemyBlasterWeaponComponent::~EnemyBlasterWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool EnemyBlasterWeaponComponent::Init(void)
{
	// �e�̔��˃G�t�F�N�g
	{
		muzzle_flash_ = NEW EffectRendererComponent(owner_);
		muzzle_flash_->SetEffect(EffectType::MuzzluFrashBlue);

		// ���L�҂���̉e���𖳌���
		muzzle_flash_->IsSetOwnerTransfromOrder(false);
	}

	// �M�Y���̐���
	{
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(owner_);
		sphere_gizmo_->SetScale(0.5f);
		sphere_gizmo_->SetVertexColor(0, 255, 255);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void EnemyBlasterWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void EnemyBlasterWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void EnemyBlasterWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �v���C���[�̎擾����
	if (player_object_ == nullptr)
	{
		player_object_ = this->FindPlayerGameObject();
		if (player_object_ == nullptr)
		{
			assert(!"EnemyBlasterWeaponComponent::Update():�v���C���[�̃Q�[���I�u�W�F�N�g���擾�ł��܂���ł����I");
		}
	}

	// �M�Y���̍X�V
	{
		sphere_gizmo_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/*�@�G�̃^�[�Q�b�g(�v���C���[)�������鏈��
-----------------------------------------------------------------------------*/
Actor* EnemyBlasterWeaponComponent::FindPlayerGameObject(void)
{
	// �v���C���[�̎擾
	if (player_object_ == nullptr)
	{
		auto actor_list = owner_->GetGame()->GetActorManager()->GetActorGameObjectList();

		for (auto actor : actor_list)
		{
			if (actor->GetType() == GameObject::TypeID::Player)
			{
				return actor;
			}
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/*�@�e�̔��ˏ���
-----------------------------------------------------------------------------*/
void EnemyBlasterWeaponComponent::Fire(void)
{
	// ���s�ړ����̍쐬
	D3DXMATRIX translation_matrix;
	D3DXMatrixIdentity(&translation_matrix);
	{
		translation_matrix._41 = position_.x;
		translation_matrix._42 = position_.y;
		translation_matrix._43 = position_.z;

		// ���L�҂̎p�����ƍ�������
		translation_matrix = translation_matrix * *owner_transform_->GetWorldMatrix();
	}

	// �ړI�̌����x�N�g�����쐬
	D3DXVECTOR3 front_vector = { 0.f, 0.f, 0.f };
	if (player_object_ != nullptr)
	{
		// �v���C���[�̍��W���W
		D3DXVECTOR3 player_pos = *player_object_->GetTransform()->GetPosition();

		// ����̍��W
		D3DXVECTOR3 blaster_pos = { translation_matrix._41, translation_matrix._42, translation_matrix._43 };

		// �O�x�N�g���𐶐�
		front_vector = player_pos - blaster_pos;

		// �x�N�g���𒷂�1�ɂ���
		D3DXVec3Normalize(&front_vector, &front_vector);
	}

	// ���ˌ��G�t�F�N�g�̍Đ�
	{
		// �G�t�F�N�g�̎�ނ�ݒ�
		muzzle_flash_->SetEffect(EffectType::MuzzluFrashOrange);

		// ���ˌ��G�t�F�N�g�̍Đ�
		muzzle_flash_->Play(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}

	// �e�ۂ̐��� 
	{
		auto bullet = NEW Bullet(owner_->GetGame());
		bullet->SetParentGameObject(owner_);
		bullet->SetFrontVector(front_vector);
		bullet->SetCreatePosition(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/