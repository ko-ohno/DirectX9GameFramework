/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Boss.cpp] �{�X�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../../StdAfx.h"
#include "Boss.h"

// ���b�V���R���|�[�l���g
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../../Component/MoveComponent/BossMoveComponent.h"

// ���̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// �{�b�N�X�̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Boss::Boss(Game* game)
	: Enemy(game)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Boss::~Boss(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Boss::Init(void)
{
	// �{�X�̈ړ��R���|�[�l���g�𐶐�
	actor_move_ = NEW BossMoveComponent(this);

	{
		// �{�X�̃��b�V������
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyBoss);
		actor_mesh_->SetEnableLighting(true);			// ���C�e�B���O��L���ɂ���


	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Boss::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̓��͏���
-----------------------------------------------------------------------------*/
void Boss::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* override�Ŏ������g���X�V
-----------------------------------------------------------------------------*/
void Boss::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	static float value = 0.f;
	ImGui::Begin("Boss");
	ImGui::SliderFloat("##vertical", &value , -180.f, 180.0f);
	ImGui::End();

	this->transform_component_->SetRotationPitch(value);

}

/*=============================================================================
/*		End of File
=============================================================================*/