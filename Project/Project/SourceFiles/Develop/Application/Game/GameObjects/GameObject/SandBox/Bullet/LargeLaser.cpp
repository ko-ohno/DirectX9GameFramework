/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LargeLaser.cpp] ��^���[�U�[�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F��^���[�U�[�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "LargeLaser.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../Component/ColliderComponent/OBBColliderComponent.h"



/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
LargeLaser::LargeLaser(Game* game)
	: Bullet(game)
	, owner_transform_(nullptr)
	, large_laser_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
LargeLaser::~LargeLaser(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool LargeLaser::Init(void)
{
	// ���[�U�[�̃G�t�F�N�g
	{
		large_laser_ = NEW EffectRendererComponent(this);
		large_laser_->SetEffect(EffectType::RedLaser);

		D3DXMATRIX rot_mat;
		D3DXMatrixIdentity(&rot_mat);
		D3DXMatrixRotationX(&rot_mat, Math::ToRadian(90.f));
		large_laser_->SetRotationMatrix(rot_mat);
		large_laser_->SetScale(1.5f);
		large_laser_->Play();
	}

	// �Փ˔���̍쐬
	{
		// ���[�U�[�̔���̒���
		const float laser_length = 30.f;

		// ���[�U�[�̔���̊e�k��
		const float laser_scale  = 1.5f;

		obb_collider_ = NEW OBBColliderComponent(this);
		obb_collider_->SetDirLength(laser_scale, AxisType::X);
		obb_collider_->SetDirLength(laser_length, AxisType::Y);
		obb_collider_->SetDirLength(laser_scale, AxisType::Z);

		obb_collider_gizmo_ = NEW BoxGizmoRendererComponent(this);
		obb_collider_gizmo_->SetVertexColor(0, 255, 255, 128);
		obb_collider_gizmo_->SetScaleX(laser_scale);
		obb_collider_gizmo_->SetScaleY(laser_length);
		obb_collider_gizmo_->SetScaleZ(laser_scale);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void LargeLaser::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void LargeLaser::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void LargeLaser::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// ���L�҂̎p����ʒm����
	transform_component_ = owner_transform_;
}

/*=============================================================================
/*		End of File
=============================================================================*/