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
	, large_laser_(nullptr)
	, test_effect_(nullptr)
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
	test_effect_ = NEW EffectRendererComponent(owner_);
	test_effect_->SetEffect(EffectType::RedLaser);

	D3DXMATRIX rot_mat;
	D3DXMatrixIdentity(&rot_mat);
	D3DXMatrixRotationX(&rot_mat, Math::ToRadian(90.f));
	test_effect_->SetRotationMatrix(rot_mat);
	test_effect_->Play();


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



	/*if (large_laser_ == nullptr)
	{
		auto game = owner_->GetGame();
		large_laser_ = NEW LargeLaser(game);

	}*/
}

/*=============================================================================
/*		End of File
=============================================================================*/