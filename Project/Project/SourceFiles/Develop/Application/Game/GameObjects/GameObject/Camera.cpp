/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Camera.cpp] �J�����N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�����N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "Camera.h"
#include "../../../Math.h"
#include "../Component/CameraComponent.h"
#include "../../Renderer.h"

#include "../../Input/InputCheck.h"
#include "../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Camera::Camera(class Game* game)
	: GameObject(game)
	, game_(game)
	, is_moved_(false)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

	camera_component_ = NEW CameraComponent(this);

	game_->GetRenderer()->AddCameraGameObjectAddress(this);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Camera::~Camera(void)
{
	game_->GetRenderer()->AddCameraGameObjectAddress(this);
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
Camera* Camera::Create(class Game* game)
{
	return NEW Camera(game);
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Camera::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Camera::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̓��͏���
-----------------------------------------------------------------------------*/
void Camera::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̍X�V����
-----------------------------------------------------------------------------*/
void Camera::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//�J�����𑀍삷�邩
	const bool is_camera_controlling = camera_component_->IsGetCameraControlling();

	ImGui::Begin("camera");
	ImGui::SetNextTreeNodeOpen(true);
	if (ImGui::TreeNode("CameraControll"))
	{
		if (is_camera_controlling)
		{
			if (ImGui::Button("OFF"))
			{
				camera_component_->IsSetCameraControlling(false);
			}
		}
		else
		{
			if (ImGui::Button("ON"))
			{
				camera_component_->IsSetCameraControlling(true);
			}
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

/*-----------------------------------------------------------------------------
/* �r���[�s��̎擾
-----------------------------------------------------------------------------*/
D3DXMATRIX* Camera::GetViewMatrix(void)
{
	return camera_component_->GetViewMatrix();
}

/*-----------------------------------------------------------------------------
/* �t�r���[�s��̎擾
-----------------------------------------------------------------------------*/
D3DXMATRIX* Camera::GetViewInverseMatrix(void)
{
	return camera_component_->GetViewInverseMatrix();
}

/*-----------------------------------------------------------------------------
/* 2D�v���W�F�N�V�����s��̎擾
-----------------------------------------------------------------------------*/
D3DXMATRIX* Camera::GetProjection2DMatrix(void)
{
	return camera_component_->GetProjection2DMatrix();
}

/*-----------------------------------------------------------------------------
/* 3D�v���W�F�N�V�����s��̎擾
-----------------------------------------------------------------------------*/
D3DXMATRIX* Camera::GetProjection3DMatrix(void)
{
	return camera_component_->GetProjection3DMatrix();
}

/*-----------------------------------------------------------------------------
/* �J�������ړ��������̃t���O
-----------------------------------------------------------------------------*/
bool Camera::IsGetCameraMoved(void) const
{
	return camera_component_->IsGetCameraMoved();
}

/*=============================================================================
/*		End of File
=============================================================================*/