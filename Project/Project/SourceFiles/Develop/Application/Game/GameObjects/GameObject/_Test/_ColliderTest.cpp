/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderTest.cpp] �Փ˔���e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Փ˔���e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "_ColliderTest.h"
#include "../../../ResourceManager/ColliderManager.h"

#include "../../Component/RendererComponent/GizmoRendererComponent/GridGizmoRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"

#include "../../Component/ColliderComponent/SphereColliderComponent.h"
#include "../../Component/ColliderComponent/OBBColliderComponent.h"

#include "../../../../Math.h"

#include "../../../CheckCollision.h"

#include "../../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ColliderTest::ColliderTest(Game* game)
	: GameObject(game)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

	game->GetColliderManager()->GetColliderComponentList();

	grid_gizmo_renderer_component_ = NEW GridGizmoRendererComponent(this);
	grid_gizmo_renderer_component_->SetVertexColor(255, 255, 255, 255);

	//OBB�̏Փ˔���̍쐬
	{
		obb_collider_component_ = NEW OBBColliderComponent(this);
		box_gizmo_renderer_component_ = NEW BoxGizmoRendererComponent(this);


		obb_collider_component_a_ = NEW OBBColliderComponent(this);
		box_gizmo_renderer_component_a_ = NEW BoxGizmoRendererComponent(this);
	}

	//�X�t�B�A�̗p�˔���̍쐬
	{
		sphere_collider_component_ = NEW SphereColliderComponent(this);
		sphere_gizmo_renderer_component_ = NEW SphereGizmoRendererComponent(this);

		sphere_collider_component_a_ = NEW SphereColliderComponent(this);
		sphere_gizmo_renderer_component_a_ = NEW SphereGizmoRendererComponent(this);
	}
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ColliderTest::~ColliderTest(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool ColliderTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void ColliderTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void ColliderTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void ColliderTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	static float rot_value = 0.f;
	static float box_val = 0.f;
	static float sphere_val = 0.f;

	rot_value += deltaTime;

	ImGui::Begin("ColliderTest");
	//ImGui::Text("RotatitonHit_obb", &rot_value);
	//ImGui::SliderFloat("##sphere_bar", &rot_value, 0.0f, 360.0f);

	ImGui::Text("TestHit_OBB", &box_val);
	ImGui::SliderFloat("##rot_obb_bar", &box_val, 0.0f, 2.0f);

	ImGui::Text("TestHit_Sphere", &sphere_val);
	ImGui::SliderFloat("##sphere_bar", &sphere_val, 0.0f, 2.0f);
	ImGui::End();


	D3DXVECTOR3 box_pos			= { 0.0f, 0.f, 0.f };
	D3DXVECTOR3 box_start_pos	= {-3.0f, 3.f, 0.f };
	D3DXVECTOR3 box_end_pos		= {-1.5f, 3.f, 0.f };

	D3DXVec3Lerp(&box_pos, &box_start_pos, &box_end_pos, box_val);

	D3DXMATRIX rot_matrix;
	D3DXMatrixIdentity(&rot_matrix);

	//��]
	D3DXMatrixRotationY(&rot_matrix, rot_value);

	//OBB�̏Փ˔���̍쐬
	{
		// �M�Y���̍X�V
		box_gizmo_renderer_component_->SetTranslation(box_pos);
		box_gizmo_renderer_component_->SetVertexColor(255, 255, 255, 255);

		//�M�Y���ɉ�]�𔽉f
		box_gizmo_renderer_component_->SetRotationMatrix(rot_matrix);

		// �Փ˔�����X�V
		obb_collider_component_->SetPosition(box_pos);

		//�Փ˔���ɉ�]�𔽉f
		obb_collider_component_->SetDirElement(rot_matrix);


		// �M�Y��A�̍X�V
		box_gizmo_renderer_component_a_->SetTranslation(box_end_pos);
		box_gizmo_renderer_component_a_->SetVertexColor(255, 255, 255, 255);

		// �Փ˔���A���X�V
		obb_collider_component_a_->SetPosition(box_end_pos);


	
		const bool isHit = CheckCollision::ObbVSObb(obb_collider_component_, obb_collider_component_a_);
		if (isHit)
		{
			box_gizmo_renderer_component_->SetVertexColor(255, 0, 0, 255);
			box_gizmo_renderer_component_a_->SetVertexColor(255, 0, 0, 255);
		}
	}


	D3DXVECTOR3 sphere_pos		 = { 0.0f, 0.f, 0.f };
	D3DXVECTOR3 sphere_start_pos = { 3.0f, 3.f, 0.f };
	D3DXVECTOR3 sphere_end_pos	 = { 1.5f, 3.f, 0.f };


	D3DXVec3Lerp(&sphere_pos, &sphere_start_pos, &sphere_end_pos, sphere_val);

	//�X�t�B�A�̏Փ˔���̍쐬
	{
		// �M�Y���̍X�V
		sphere_gizmo_renderer_component_->SetTranslation(sphere_pos);
		sphere_gizmo_renderer_component_->SetVertexColor(255, 255, 255, 255);

		// �Փ˔�����X�V
		sphere_collider_component_->SetPosition(sphere_pos);


		// �M�Y��A�̍X�V
		sphere_gizmo_renderer_component_a_->SetTranslation(sphere_end_pos);
		sphere_gizmo_renderer_component_a_->SetVertexColor(255, 255, 255, 255);

		// �Փ˔���A���X�V
		sphere_collider_component_a_->SetPosition(sphere_end_pos);

		const bool isHit = CheckCollision::SphereVSSpghre(sphere_collider_component_, sphere_collider_component_a_);
		if (isHit)
		{
			sphere_gizmo_renderer_component_->SetVertexColor(255, 0, 0, 255);
			sphere_gizmo_renderer_component_a_->SetVertexColor(255, 0, 0, 255);
		}

	}



	//D3DXVec3Lerp();

	//Math::Lerp(0.f, );

	//Easing::Linear(0.5f); 
}

/*=============================================================================
/*		End of File
=============================================================================*/