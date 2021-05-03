/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderTest.cpp] �Փ˔���e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Փ˔���e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "_ColliderTest.h"
#include "../../Manager/ColliderManager.h"

#include "../Component/RendererComponent/GizmoRendererComponent/GridGizmoRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ColliderTest::ColliderTest(Game* game)
	: GameObject(game)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

	game->GetColliderManager()->GetColliderComponentList();

	grid_gizmo_renderer_component_ = NEW GridGizmoRendererComponent(this);

	box_gizmo_renderer_component_ = NEW BoxGizmoRendererComponent(this);

	sphere_gizmo_renderer_component_ = NEW SphereGizmoRendererComponent(this);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ColliderTest::~ColliderTest(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
ColliderTest* ColliderTest::Create(Game* game)
{
	return NEW ColliderTest(game);
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

	box_gizmo_renderer_component_->SetTranslationY( 3.f);
	box_gizmo_renderer_component_->SetTranslationX(-1.5f);
	box_gizmo_renderer_component_->SetVertexColor(255, 0, 0, 255);

	sphere_gizmo_renderer_component_->SetTranslationY(3.f);
	sphere_gizmo_renderer_component_->SetTranslationX(1.5f);
	sphere_gizmo_renderer_component_->SetVertexColor(0, 0, 255, 255);


	grid_gizmo_renderer_component_->SetTranslation(0.f, 0.f, 0.f);
	grid_gizmo_renderer_component_->SetVertexColor();


}

/*=============================================================================
/*		End of File
=============================================================================*/