/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PlayerMoveComponent.cpp] �v���C���[�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�v���C���[�̈ړ��R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "PlayerMoveComponent.h"
#include "../ColliderComponent/OBBColliderComponent.h"
#include "../RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../Input/InputCheck.h"
#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
PlayerMoveComponent::PlayerMoveComponent(GameObject* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
	, is_move_top_(false)
	, is_move_bottom_(false)
	, is_move_left_(false)
	, is_move_right_(false)
	, move_speed_(10.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
PlayerMoveComponent::~PlayerMoveComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool PlayerMoveComponent::Init(void)
{
	// �v���C���[�̃T���h�{�b�N�X��������
	{
		player_sandbox_ = NEW OBBColliderComponent(owner_);
		player_sandbox_->SetDirLength(5.f, AxisType::X);
		player_sandbox_->SetDirLength(3.f, AxisType::Y);
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void PlayerMoveComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void PlayerMoveComponent::Input(void)
{
}

/*-----------------------------------------------------------------------------
/*�@�X�V����
-----------------------------------------------------------------------------*/
void PlayerMoveComponent::Update(float deltaTime)
{
	// ���`���ʕۊǂ��s���t���O��ON��
	{
		owner_transform_->IsSetExecuteSlerp(true);
		owner_transform_->SetSlerpSpeed(1.2f);
	}

	// ���͂���ړ��̏�Ԃ��X�V
	Vector2 left_thumb = InputCheck::XInputThumbLeft(PadIndex::Pad1);
	{
		this->UpdateMovementState(left_thumb);
	}

	// �㉺���E�̈ړ�����
	D3DXVECTOR3 front_vector = *owner_transform_->GetFrontVector();
	{
		// �㉺�̈ړ�����
		{
			const float move_value = left_thumb.y_ * (front_vector.y * move_speed_);
			if (is_move_top_)
			{
				owner_transform_->SetRotationPitch(-30.f);
				owner_transform_->AddTranslationY(move_value * deltaTime);
			}

			if (is_move_bottom_)
			{
				owner_transform_->SetRotationPitch(30.f);
				owner_transform_->AddTranslationY(-move_value * deltaTime);
			}
		}
		
		// ���E�̈ړ�����
		{
			const float move_value = left_thumb.x_ * (front_vector.x * move_speed_);
			if (is_move_right_)
			{
				owner_transform_->SetRotationYaw(30.f);
				owner_transform_->SetRotationRoll(-15.f);
				owner_transform_->AddTranslationX(move_value * deltaTime);
			}

			if (is_move_left_)
			{
				owner_transform_->SetRotationYaw(-30.f);
				owner_transform_->SetRotationRoll(15.f);
				owner_transform_->AddTranslationX(-move_value * deltaTime);
			}
		}

		//�e��]���ɑ΂��ĂȂɂ����Ă��Ȃ����Ɏp�����X�V
		{
			const bool is_disable_yaw = !(is_move_left_ || is_move_right_);
			if (is_disable_yaw)
			{
				owner_transform_->SetRotationYaw(0.f);
				owner_transform_->SetRotationRoll(0.f);
			}

			const bool is_disable_pitch = !(is_move_top_ || is_move_bottom_);
			if (is_disable_pitch)
			{
				owner_transform_->SetRotationPitch(0.f);
				owner_transform_->SetRotationRoll(0.f);
			}
		}
	}

	// �v���C���[�̈ړ��͈͂𐧌�
	{
		// �ړ��͈͂̎擾
		float x_axis_sandbox_length = player_sandbox_->GetDirLength(AxisType::X);
		float y_axis_sandbox_length = player_sandbox_->GetDirLength(AxisType::Y);

		// �v���C���[�̈ʒu���̎擾
		D3DXVECTOR3 position = *owner_transform_->GetPosition();

		// �㉺�̈ړ�����
		{
			if (position.y >=  y_axis_sandbox_length)
			{
				owner_transform_->SetTranslation(*owner_transform_->GetOldPosition());
			}

			if (position.y <= -y_axis_sandbox_length)
			{
				owner_transform_->SetTranslation(*owner_transform_->GetOldPosition());
			}
		}

		// ���E�̈ړ�����
		{
			if (position.x >= x_axis_sandbox_length)
			{
				owner_transform_->SetTranslation(*owner_transform_->GetOldPosition());
			}

			if (position.x <= -x_axis_sandbox_length)
			{
				owner_transform_->SetTranslation(*owner_transform_->GetOldPosition());
			}
		}
	}
}

/*-----------------------------------------------------------------------------
/*�@�ړ��̏�ԍX�V����
-----------------------------------------------------------------------------*/
void PlayerMoveComponent::UpdateMovementState(Vector2& padThumb)
{
	// ��Ԃ̏�����
	is_move_top_	=
	is_move_bottom_	=
	is_move_left_	=
	is_move_right_	= false;

	float deadzone_yaw	 = 0.4f;
	float deadzone_pitch = 0.1f;


	// �㉺�ړ�
	{
		if (padThumb.y_ >=  deadzone_pitch)
		{
			is_move_top_ = true;
		}

		if (padThumb.y_ <= -deadzone_pitch)
		{
			is_move_bottom_ = true;
		}
	}

	// ���E�ړ�
	{
		if (padThumb.x_ <= -deadzone_yaw)
		{
			is_move_left_ = true;
		}

		if (padThumb.x_ >=  deadzone_yaw)
		{
			is_move_right_ = true;
		}
	}

	ImGui::Begin("TestThumb");
	ImGui::Text("Thumb_X:%f", padThumb.x_);
	ImGui::Text("Thumb_Y:%f", padThumb.y_);
	ImGui::Text("Top:%s", is_move_top_ ? "true" : "false");
	ImGui::Text("Bottom:%s", is_move_bottom_ ? "true" : "false");
	ImGui::Text("Left:%s", is_move_left_ ? "true" : "false");
	ImGui::Text("Right:%s", is_move_right_ ? "true" : "false");
	ImGui::End();

}

/*=============================================================================
/*		End of File
=============================================================================*/