/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameCamera.cpp] �J�����Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�����Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "GameCamera.h"
#include "../../Component/CameraComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"

#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
GameCamera::GameCamera(Game* game)
	: Camera(game)
	, lookat_point_gizmo_(nullptr)
	, vertical_camera_shake_(0.f)
	, is_move_top_(true)
	, is_move_bottom_(false)
	, is_value_over_(false)
	, is_value_under_(false)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
GameCamera::~GameCamera(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool GameCamera::Init(void)
{
	// �J�������W�̏�����
	{
		camera_component_->SetLookAtTranslationX(0.f);
		camera_component_->SetLookAtTranslationY(0.f);

		camera_component_->SetCameraTranslationX(0.f);
		camera_component_->SetCameraTranslationY(0.f);
		camera_component_->SetCameraTranslationZ(-12.f);
	}

	// �����_���W�̃M�Y����\��
	lookat_point_gizmo_ = NEW BoxGizmoRendererComponent(this);
	lookat_point_gizmo_->SetScale(0.1f);
	lookat_point_gizmo_->SetVertexColor(255, 0, 0);

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void GameCamera::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void GameCamera::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void GameCamera::UpdateGameObject(float deltaTime)
{
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

		if (ImGui::Button("CameraTransformReset"))
		{
			camera_component_->SetCameraTransformReset();
		}
		ImGui::TreePop();
	}
	ImGui::End();

	if (is_camera_controlling != true)
	{
		// ���̃J�����Q�[���I�u�W�F�N�g�̐e�̂Ƃ��ăv���C���[���擾
		if (game_object_parent_ == nullptr)
		{
			//�Q�[���I�u�W�F�N�g�̃��X�g�𑍌���
			auto game_objects = game_->GetGameObjects();
			for (auto game_object : game_objects)
			{
				// �v���C���[�̎擾
				auto game_object_id = game_object->GetType();
				if (game_object_id == TypeID::Player)
				{
					game_object_parent_ = game_object;
					break;
				}
			}
		}

		// �Q�[���̃J�����p�Ƀv���C���[�p�����擾
		if (game_object_parent_ != nullptr)
		{
			// �����_���v���C���[���W�ɐݒ�
			static D3DXVECTOR3 lookat_position = {0.f, 0.f, 0.f};
			static D3DXVECTOR3 camera_position = *camera_component_->GetPosition();

			// �����_�ƂȂ�v���C���[�̈ʒu���̎擾
			D3DXVECTOR3 lookat_target = *game_object_parent_->GetTransform()->GetPosition();

			// �����̃J�����h����쐬
			static constexpr float camera_shake_range = 0.004f;
			static constexpr float camera_shake_value = 0.005f * 2;
			{
				// �������̑���ɂ��A�����_�̏㏸�Ɖ��~��on/off���؂�ւ��
				is_value_over_  = (vertical_camera_shake_ >=  camera_shake_range);
				is_value_under_ = (vertical_camera_shake_ <= -camera_shake_range);
				{
					if (is_value_over_)
					{
						is_move_top_ = false;
						is_move_bottom_ = true;
					}

					if (is_value_under_)
					{
						is_move_top_ = true;
						is_move_bottom_ = false;
					}

					if (is_move_top_)
					{
						vertical_camera_shake_ += camera_shake_value * deltaTime;
					}

					if (is_move_bottom_)
					{
						vertical_camera_shake_ -= camera_shake_value * deltaTime;
					}
				}
			}
			
			ImGui::Begin("CameraShake");
			ImGui::Text("Shake:%f", vertical_camera_shake_);
			ImGui::End();

			// �J�����̒l���Ԃ��邽�߂̋��x
			static constexpr float smooth_time = 0.5f;

			// �����_���W����
			lookat_target.x = Math::Lerp(lookat_position.x, lookat_target.x, Easing::QuintInOut(smooth_time));
			lookat_target.y = Math::Lerp(lookat_position.y, lookat_target.y, Easing::QuintInOut(smooth_time));

			// �J�������W����
			camera_position.x = Math::Lerp(camera_position.x, lookat_target.x, Easing::QuintInOut(smooth_time));
			camera_position.y = Math::Lerp(camera_position.y, lookat_target.y, Easing::QuintInOut(smooth_time));

			// �v���C���[���W�ɐ����h������Z�������W
			lookat_target.y = lookat_target.y + vertical_camera_shake_;
		
			// �J�����̍X�V
			{
				// �����_���W�̍X�V
				camera_component_->SetLookAtTranslation(lookat_target);

				// �J�������W�̍X�V
				camera_component_->SetCameraTranslation(camera_position);
			}

			lookat_point_gizmo_->SetTranslation(lookat_target);
		}
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/