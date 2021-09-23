/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBlasterWeaponComponent.cpp] �����e����R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e����R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "ChargeBlasterWeaponComponent.h"
#include "../../GameObject.h"
#include "../../Component/RendererComponent/BillboardRendererComponent.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../GameObject/SandBox/Bullet/ChargeBullet.h"
#include "../../../Game.h"
#include "../../GameObject/SandBox/Actor.h"
#include "../../../SandBoxManager/ActorManager.h"

#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ChargeBlasterWeaponComponent::ChargeBlasterWeaponComponent(GameObject* owner, int updateOrder)
	: WeaponComponent(owner, updateOrder)
	, is_lockon_(false)
	, is_fire_(false)
	, charge_bullet_(nullptr)
	, sphere_gizmo_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ChargeBlasterWeaponComponent::~ChargeBlasterWeaponComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool ChargeBlasterWeaponComponent::Init(void)
{
	// �e�̔��ˌ��̐���
	muzzle_flash_ = NEW EffectRendererComponent(owner_);
	muzzle_flash_->SetEffect(EffectType::ChargeBulletState3Fire);
	muzzle_flash_->SetScale(0.5f);

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
void ChargeBlasterWeaponComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (charge_bullet_ != nullptr)
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

		ImGui::Begin("BulletCreatePos");
		ImGui::Text("posX:%f", translation_matrix._41);
		ImGui::Text("posY:%f", translation_matrix._42);
		ImGui::Text("posZ:%f", translation_matrix._43);
		ImGui::End();

		if (charge_bullet_->GetChargeBulletState() <= ChargeBulletState::Hold)
		{
			// �e�̍��W���X�V
			charge_bullet_->SetTranslation(translation_matrix._41, translation_matrix._42, translation_matrix._43);
		}

		if (charge_bullet_->GetChargeBulletState() == ChargeBulletState::Fire)
		{
			if (is_fire_ == false)
			{	
				// �G�t�F�N�g�Đ����X�V
				muzzle_flash_->Play();
				is_fire_ = true;
			}
		}

		// �`���[�W�e�̏�Ԃ��m�F
		if (charge_bullet_->GetChargeBulletState() == ChargeBulletState::End)
		{
			charge_bullet_->SetGameObjectState(GameObject::State::Dead);
			is_fire_ = false;
		}
	}

	// �M�Y���̍X�V
	{
		sphere_gizmo_->SetTranslation(position_);
	}
}

/*-----------------------------------------------------------------------------
/*�@�`���[�W�e�̔��ˏ���
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::CreateChargeBullet(void)
{
	//// ���s�ړ����̍쐬
	D3DXMATRIX translation_matrix;
	D3DXMatrixIdentity(&translation_matrix);
	{
		translation_matrix._41 = position_.x;
		translation_matrix._42 = position_.y;
		translation_matrix._43 = position_.z;

		// ���L�҂̎p�����ƍ�������
		translation_matrix = translation_matrix * *owner_transform_->GetWorldMatrix();
	}

	// �e�ۂ̐���
	{
		if (charge_bullet_ != nullptr) { return; }
		auto game = owner_->GetGame();
		charge_bullet_ = NEW ChargeBullet(game);
		charge_bullet_->SetParentGameObject(owner_);
		charge_bullet_->SetTranslation(translation_matrix._41, translation_matrix._42, translation_matrix._43);
	}
}

/*-----------------------------------------------------------------------------
/*�@���ˏ���
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::Fire(void)
{	
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::ChargeBulletFire()�F�`���[�W�e�̃C���X�^���X����������Ă��܂���I");
	}
	charge_bullet_->Fire();	// �`���[�W�e�̔���
}

/*-----------------------------------------------------------------------------
/*�@�`���[�W�e�̃C���X�^���X�����邩�m�F
-----------------------------------------------------------------------------*/
bool ChargeBlasterWeaponComponent::IsCheckChargeBulletInstance(void)
{
	if (charge_bullet_ == nullptr) { return false; }
	return true;
}

/*-----------------------------------------------------------------------------
/*�@�`���[�W�e�̏�Ԃ̎擾����
-----------------------------------------------------------------------------*/
ChargeBulletState ChargeBlasterWeaponComponent::GetChargeBulletState(void)
{
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::GetChargeBulletState()�F�`���[�W�e�̃C���X�^���X����������Ă��܂���I");
	}
	return charge_bullet_->GetChargeBulletState();
}

/*-----------------------------------------------------------------------------
/*�@�`���[�W�e�̏�Ԃ̐ݒ菈��
-----------------------------------------------------------------------------*/
void ChargeBlasterWeaponComponent::SetChargeBulletState(ChargeBulletState chargeBulletState)
{
	if (charge_bullet_ == nullptr)
	{
		assert(!"ChargeBlasterWeaponComponent::SetChargeBulletState()�F�`���[�W�e�̃C���X�^���X����������Ă��܂���I");
	}
	charge_bullet_->SetChargeBulletState(chargeBulletState);
}

/*=============================================================================
/*		End of File
=============================================================================*/