/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BlasterComponent.cpp] �����e�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e�R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "BlasterComponent.h"
#include "../../GameObject.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../GameObject/SandBox/Bullet.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
BlasterComponent::BlasterComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, muzzle_flash_(nullptr)
{
	muzzle_flash_ = NEW EffectRendererComponent(owner);
	muzzle_flash_->SetEffect(EffectType::MuzzluFrashGreen);

	// ���L�҂���̉e���𖳌���
	muzzle_flash_->SetOwnerTransfromOrder(false);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
BlasterComponent::~BlasterComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool BlasterComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void BlasterComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void BlasterComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void BlasterComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*-----------------------------------------------------------------------------
/*�@���ˏ���
-----------------------------------------------------------------------------*/
void BlasterComponent::Fire(void)
{	
	// ���s�ړ����̍쐬
	D3DXMATRIX translation_matrix;
	D3DXMatrixIdentity(&translation_matrix);

	translation_matrix._41 = position_.x;
	translation_matrix._42 = position_.y;
	translation_matrix._43 = position_.z;

	// ���L�҂̎p�����ƍ�������
	translation_matrix = translation_matrix  * *owner_transform_->GetWorldMatrix();

	// ���ˌ��G�t�F�N�g�̍Đ�
	muzzle_flash_->Play(translation_matrix._41, translation_matrix._42, translation_matrix._43);

	//
	// �G�t�F�N�g�̍Đ����ɁA�������W���̂܂܂��ƁA��������c���Ă��܂��o�O������̂Œ���
	//
	//muzzle_flash_->Play(position_);

	// �e�ۂ̐���
	{
		auto bullet = NEW Bullet(owner_->GetGame());

		bullet->SetCreatePosition(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/