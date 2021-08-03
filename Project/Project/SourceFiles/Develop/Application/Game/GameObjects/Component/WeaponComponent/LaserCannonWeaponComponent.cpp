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
#include "../../GameObject/SandBox/LargeLaser.h"

#include "../RendererComponent/EffectRendererComponent.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
LaserCannonWeaponComponent::LaserCannonWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, enemy_motion_state_(EnemyMotionState::None)
	, large_laser_(nullptr)
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
			SAFE_DELETE_(large_laser_);
		}
	}
}

/*-----------------------------------------------------------------------------
/*�@���[�U�[�̔��ˏ���
-----------------------------------------------------------------------------*/
void LaserCannonWeaponComponent::Shoot(void)
{
	if (large_laser_ == nullptr)
	{
		auto game = owner_->GetGame();
		large_laser_ = NEW LargeLaser(game);
		large_laser_->SetTransfrom(owner_transform_);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/