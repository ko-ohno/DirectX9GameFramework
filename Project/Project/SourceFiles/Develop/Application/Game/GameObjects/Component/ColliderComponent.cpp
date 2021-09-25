/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderComponent.cpp] �R���C�_�R���|�[�l���g�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�R���C�_�R���|�[�l���g�ɋ��ʂ��鏈���̒�`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "ColliderComponent.h"
#include "../GameObject.h"
#include "../../Game.h"
#include "../../ResourceManager/ColliderManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ColliderComponent::ColliderComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, position_(0.f, 0.f, 0.f)
	, offset_position_(0.f, 0.f, 0.f)
{
	owner_->GetGame()->GetColliderManager()->AddColliderComponentAddress(this);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ColliderComponent::~ColliderComponent(void)
{
	owner_->GetGame()->GetColliderManager()->RemoveColliderComponentAddress(this);
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void ColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/