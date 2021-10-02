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
#include "../../GameObject.h"
#include "../../GameObject/UI/HUD.h"
#include "../../../Input/InputCheck.h"
#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
PlayerMoveComponent::PlayerMoveComponent(GameObject* owner, int updateOrder)
	: MoveComponent(owner, updateOrder)
	, position_(0.f, 0.f, 0.f)
	, position_animation_start_(0.f, 0.f, 0.f)
	, position_animation_finish_(0.f, 0.f, 0.f)
	, move_animation_time_(0.f)
	, is_move_top_(false)
	, is_move_bottom_(false)
	, is_move_left_(false)
	, is_move_right_(false)
	, move_speed_(12.f)
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

	//owner_transform_->SetTranslationZ(-30.f);

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
		owner_transform_->IsSetExecuteSlerpRotation(true);
		owner_transform_->SetSlerpSpeed(1.2f);
	}

	const bool is_animation_scene = ((owner_->GetGame()->GetGameState() == Game::GameState::GameStartScene)
									 || (owner_->GetGame()->GetGameState() == Game::GameState::GameFinishScene));
	if (is_animation_scene)
	{
		// �A�j���[�V�����̏�ʂ��������ꍇ�̍X�V����
		this->UpdateAnimationScene(deltaTime);
		return;
	}
	else
	{
		position_ = *owner_transform_->GetPosition();
		move_animation_time_ = 0.f;
	}

	// ���͂���ړ��̏�Ԃ��X�V
	Vector2 left_thumb = InputCheck::XInputThumbLeft(PadIndex::Pad1);
	{
		this->UpdateMovementState(left_thumb);
	}

	// �㉺���E�̈ړ�����
	D3DXVECTOR3 front_vector = *owner_transform_->GetFrontVector();
	const float default_move_value = 0.04f;
	{
		// �㉺�̈ړ�����
		{
			const float move_value_y = left_thumb.y_ * (front_vector.y * move_speed_);
			if (is_move_top_)
			{
				owner_transform_->SetRotationPitch(-30.f);
				owner_transform_->AddTranslationY((move_value_y * deltaTime) + default_move_value);
			}

			if (is_move_bottom_)
			{
				owner_transform_->SetRotationPitch(30.f);
				owner_transform_->AddTranslationY((-move_value_y * deltaTime) - default_move_value);
			}
		}
		
		// ���E�̈ړ�����
		{
			const float move_value_x = left_thumb.x_ * (front_vector.x * move_speed_);
			if (is_move_right_)
			{
				owner_transform_->SetRotationYaw(30.f);
				owner_transform_->SetRotationRoll(-15.f);
				owner_transform_->AddTranslationX((move_value_x * deltaTime) + default_move_value);;
			}

			if (is_move_left_)
			{
				owner_transform_->SetRotationYaw(-30.f);
				owner_transform_->SetRotationRoll(15.f);
				owner_transform_->AddTranslationX((-move_value_x * deltaTime) - default_move_value);;
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
				owner_transform_->SetTranslationY(owner_transform_->GetOldPosition()->y);
			}

			if (position.y <= -y_axis_sandbox_length)
			{
				owner_transform_->SetTranslationY(owner_transform_->GetOldPosition()->y);
			}
		}

		// ���E�̈ړ�����
		{
			if (position.x >= x_axis_sandbox_length)
			{
				owner_transform_->SetTranslationX(owner_transform_->GetOldPosition()->x);
			}

			if (position.x <= -x_axis_sandbox_length)
			{
				owner_transform_->SetTranslationX(owner_transform_->GetOldPosition()->x);
			}
		}
	}
}

/*-----------------------------------------------------------------------------
/*�@�ړ��̏�ԍX�V����
-----------------------------------------------------------------------------*/
void PlayerMoveComponent::UpdateAnimationScene(float deltaTime)
{
	// ���݂̃Q�[���̏󋵂��擾
	auto game_state = owner_->GetGame()->GetGameState();

	// ���݈ʒu
	D3DXVECTOR3 pos = { 0.f, 0.f, 0.f };

	// �J�n�ʒu���̐ݒ�
	position_animation_start_ = position_;

	// �A�j���[�V�����̎��Ԃ��v�Z
	move_animation_time_ += deltaTime;

	// �Q�[���̏�Ԃɂ���ăC�x���g�V�[�������肷��
	switch (game_state)
	{
	case Game::GameState::GameStartScene:
		//���W��ݒ�
		position_animation_start_ = { 0.f, 0.f, -100.f };

		// ���W����`���
		D3DXVec3Lerp(&pos
					, &position_animation_start_
					, &position_animation_finish_
					, Easing::SineIn(move_animation_time_, MAX_ANIMATION_TIME));

		// �p�����̋���
		owner_transform_->SetRotation(0.f, 0.f, 0.f);

		// �ړ����̐ݒ�
		owner_transform_->SetTranslation(pos);

		// �A�j���[�V�����̏�����Ԃ𐧌��ƃQ�[���̏�Ԃ̍X�V
		if (move_animation_time_ >= MAX_ANIMATION_TIME)
		{
			move_animation_time_ = MAX_ANIMATION_TIME;

			// �Q�[���̏�Ԃ̍X�V
			owner_->GetGame()->SetGameState(Game::GameState::Gameplay);
		}
		break;

	case Game::GameState::GameFinishScene:
		//���W��ݒ�
		position_animation_finish_ = { 0.f, 0.f, 100.f };

		// ���W����`���
		D3DXVec3Lerp(&pos
					, &position_animation_start_
					, &position_animation_finish_
					, Easing::SineIn(move_animation_time_, MAX_ANIMATION_TIME));

		// �p�����̋���
		owner_transform_->SetRotation(0.f, 0.f, 0.f);

		// �ړ����̐ݒ�
		owner_transform_->SetTranslation(pos);

		// �A�j���[�V�����̏�����Ԃ𐧌��ƃQ�[���̏�Ԃ̍X�V
		if (move_animation_time_ >= MAX_ANIMATION_TIME)
		{
			move_animation_time_ = MAX_ANIMATION_TIME;

			// �Q�[���̏�Ԃ̍X�V
			owner_->GetGame()->SetGameState(Game::GameState::GameClear);

			// �v���C���[��j������
			owner_->SetGameObjectState(GameObject::State::Dead);
		}
		break;

	default:
		assert(!"PlayerMoveComponent::UpdateAnimationScene()�F�ړ��A�j���[�V�����̏�Ԃ��s���ȏ�Ԃł����I");
		break;
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

#ifdef DEBUG_MODE_
	ImGui::Begin("TestThumb");
	ImGui::Text("Thumb_X:%f", padThumb.x_);
	ImGui::Text("Thumb_Y:%f", padThumb.y_);
	ImGui::Text("Top:%s", is_move_top_ ? "true" : "false");
	ImGui::Text("Bottom:%s", is_move_bottom_ ? "true" : "false");
	ImGui::Text("Left:%s", is_move_left_ ? "true" : "false");
	ImGui::Text("Right:%s", is_move_right_ ? "true" : "false");
	ImGui::End();
#endif
}

/*=============================================================================
/*		End of File
=============================================================================*/