/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshTest.cpp] ���b�V���e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���b�V���e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "_MeshTest.h"
#include "../../Component/RendererComponent/StdMeshRendererComponent.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
MeshTest::MeshTest(Game* game)
	: GameObject(game)
{
	//�Q�[�����C���[�ŕ`��
	this->renderer_layer_type_ = RendererLayerType::Game;

	std_mesh_renderer_component_ = NEW StdMeshRendererComponent(this);
	std_mesh_renderer_component_->SetMesh(XFileMeshType::Box);

	std_mesh_renderer_component_a = NEW StdMeshRendererComponent(this);
	std_mesh_renderer_component_a->SetMesh(XFileMeshType::BlueBullet);
	std_mesh_renderer_component_a->SetTranslationX(-5.f);


	std_mesh_renderer_component_b = NEW StdMeshRendererComponent(this);
	std_mesh_renderer_component_b->SetMesh(XFileMeshType::Cylinder);
	std_mesh_renderer_component_b->SetTranslationX(5.f);

	std_mesh_renderer_component_c = NEW StdMeshRendererComponent(this);
	std_mesh_renderer_component_c->SetMesh(XFileMeshType::AirPlane);
	std_mesh_renderer_component_c->SetTranslationY(-2.f);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
MeshTest::~MeshTest(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool MeshTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void MeshTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void MeshTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void MeshTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

/*=============================================================================
/*		End of File
=============================================================================*/