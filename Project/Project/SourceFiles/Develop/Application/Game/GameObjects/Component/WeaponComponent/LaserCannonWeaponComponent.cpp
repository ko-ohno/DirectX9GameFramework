/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Hoge.cpp] ���[�U�[�C����R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���[�U�[�C����R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "LaserCannonWeaponComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../GameObject/SandBox/Actor/Enemy.h"
#include "../../GameObject/SandBox/Bullet/LargeLaser.h"

#include "../RendererComponent/EffectRendererComponent.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
LaserCannonWeaponComponent::LaserCannonWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, enemy_motion_state_(EnemyMotionState::None)
	, large_laser_(nullptr)
	, is_fire_(false)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
LaserCannonWeaponComponent::~LaserCannonWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool LaserCannonWeaponComponent::Init(void)
{
	// ����̈ʒu��\������M�Y��
	{
		sphere_gizmo_ = NEW SphereGizmoRendererComponent(owner_);
		sphere_gizmo_->SetScale(2.f);
		sphere_gizmo_->SetVertexColor(0, 128, 255);
		//sphere_gizmo_->IsSetDrawable(false);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void LaserCannonWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void LaserCannonWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void LaserCannonWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (large_laser_ != nullptr)
	{
		if (enemy_motion_state_ == EnemyMotionState::Complete)
		{
			//�@���˂������̃t���O��������
			is_fire_ = false;

			//�@��ڂ��I�����Q�[���I�u�W�F�N�g�Ƃ���
			large_laser_->SetGameObjectState(GameObject::State::Dead);
		}
	}
}

/*-----------------------------------------------------------------------------
/*�@���[�U�[�̔��ˏ���
-----------------------------------------------------------------------------*/
void LaserCannonWeaponComponent::Shoot(void)
{
	// ���[�U�[�𔭎˂��Ă��Ȃ���
	if (is_fire_ == false)
	{
		// ���[�U�[�𐶐�
		auto game = owner_->GetGame();
		large_laser_ = NEW LargeLaser(game);
		large_laser_->SetTransfrom(owner_transform_);

		// ���˂������Ƃ��L��
		is_fire_ = true;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/