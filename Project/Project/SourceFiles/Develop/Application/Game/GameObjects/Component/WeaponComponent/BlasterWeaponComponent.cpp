/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BlasterWeaponComponent.cpp] �����e����R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e����R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "BlasterWeaponComponent.h"
#include "../../GameObject.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../GameObject/SandBox/Bullet.h"
#include "../../../Game.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BlasterWeaponComponent::BlasterWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, muzzle_flash_(nullptr)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
BlasterWeaponComponent::~BlasterWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool BlasterWeaponComponent::Init(void)
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
void BlasterWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void BlasterWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void BlasterWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �M�Y���̍X�V
	{
		sphere_gizmo_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/*�@���ˏ���
-----------------------------------------------------------------------------*/
void BlasterWeaponComponent::Fire(void)
{	
	// ���s�ړ����̍쐬
	D3DXMATRIX translation_matrix;
	D3DXMatrixIdentity(&translation_matrix);

	translation_matrix._41 = position_.x;
	translation_matrix._42 = position_.y;
	translation_matrix._43 = position_.z;

	// ���L�҂̎p�����ƍ�������
	translation_matrix = translation_matrix  * *owner_transform_->GetWorldMatrix();

	// �G�t�F�N�g�̍Đ�
	{
		// �G�t�F�N�g�̎�ނ�ݒ�
		muzzle_flash_->SetEffect(EffectType::MuzzluFrashBlue);

		// ���ˌ��G�t�F�N�g�̍Đ�
		muzzle_flash_->Play(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}

	// �e�ۂ̐���
	{
		auto game = owner_->GetGame();
		auto bullet = NEW Bullet(game);
		bullet->SetParentGameObject(owner_);
		bullet->SetCreatePosition(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}
}
/*=============================================================================
/*		End of File
=============================================================================*/