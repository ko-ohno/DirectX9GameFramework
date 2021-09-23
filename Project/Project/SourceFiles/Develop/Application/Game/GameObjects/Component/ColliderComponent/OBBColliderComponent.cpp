/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[OBBColliderComponent.cpp] OBB�R���C�_�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FOBB�R���C�_�R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "OBBColliderComponent.h"
#include "../../GameObject.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
OBBColliderComponent::OBBColliderComponent(GameObject* owner, int updateOrder)
	: ColliderComponent(owner, updateOrder)
	, position_(0.f, 0.f, 0.f)
	, offset_position_(0.f, 0.f, 0.f)
	, axis_element_{
		{ 1.f, 0.f, 0.f}
		, { 0.f, 1.f, 0.f}
		, { 0.f, 0.f, 1.f}
	  }
	, axis_length_{ 0.5f, 0.5f, 0.5f }
{
	position_.y_ = -100.f;
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
OBBColliderComponent::~OBBColliderComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void OBBColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �Փ˔���̈ʒu���̍X�V
	position_ = offset_position_ + *owner_->GetTransform()->GetPosition();

	// OBB�̎p���̍X�V
	auto rotate_matrix = *owner_->GetTransform()->GetRotationMatrix();
	this->SetDirElement(rotate_matrix);
}

/*=============================================================================
/*		End of File
=============================================================================*/