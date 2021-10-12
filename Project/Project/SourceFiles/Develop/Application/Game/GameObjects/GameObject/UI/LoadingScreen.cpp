/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LoadingScreen.cpp] ���[�h��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���[�h��ʃN���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "LoadingScreen.h"
#include "../../../Game.h"

// �l�R���|�[�l���g
#include "../../Component/ParameterComponent/BoolParameterComponent.h"

// ����
#include "../../../Input/InputCheck.h"

// ImGui
#include "../../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
LoadingScreen::LoadingScreen(Game* game)
	: UI(game)
	, parameter_is_fade_execute_(nullptr)
	, parameter_is_fade_completed_(nullptr)
	, parameter_is_scene_changed_(nullptr)
	, parameter_is_show_game_screen_(nullptr)
	, loading_state_(LoadingState::None)
	, is_show_loading_screen_(false)
	, wait_time_(0.f)
	, text_index_(0)
	, text_tick_time_(0.f)
	, execute_time_(0.f)
	, progress_value_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
LoadingScreen::~LoadingScreen(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool LoadingScreen::Init(void)
{
	//
	// �ʐM��������̃Q�[���I�u�W�F�N�g����l�R���|�[�l���g�̎擾
	// 

	// �Q�[���I�u�W�F�N�g�̃��X�g���擾
	auto game_objects = game_->GetGameObjects();
	for (auto game_object : game_objects)
	{
		// �Q�[���I�u�W�F�N�g�̌^�𒲂ׂ�
		auto game_object_type = game_object->GetType();

		// ��ʐ؂�ւ��p�̒l�R���|�[�l���g�̎擾
		{
			// �t�F�[�h��ʃQ�[���I�u�W�F�N�g����l�R���|�[�l���g�̃|�C���^���擾
			if (game_object_type == GameObject::TypeID::Fade)
			{
				//�@�Q�[���I�u�W�F�N�g�����L����l�R���|�[�l���g�̃��X�g���擾
				auto parameter_components = game_object->GetParameterComponents();

				// �Q�[���I�u�W�F�N�g�����L����l�R���|�[�l���g�𒲂ׂ�
				for (auto parameter_component : parameter_components)
				{
					// �t�F�[�h�������������̒l�R���|�[�l���g�̎擾
					auto parameter_component_type = parameter_component->GetParameterType();
					if (parameter_component_type == ParameterType::IsFadeExecute)
					{
						this->parameter_is_fade_execute_ = parameter_component;
					}

					if (parameter_component_type == ParameterType::IsFadeCompleted)
					{
						this->parameter_is_fade_completed_ = parameter_component;
					}
				}
				break;
			}
		}
	}


	// �l�R���|�[�l���g�̍쐬
	{
		// ���[�h��ʂ�\�����邩
		parameter_is_scene_changed_ = NEW BoolParameterComponent(this);
		parameter_is_scene_changed_->SetParameterType(ParameterType::IsSceneChanged);

		// �Q�[����ʂ�\�����邩
		parameter_is_show_game_screen_ = NEW BoolParameterComponent(this);
		parameter_is_show_game_screen_->SetParameterType(ParameterType::IsShowGameScreen);
	}

	// �l�̏�����
	loading_state_ = LoadingState::Idle;
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void LoadingScreen::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void LoadingScreen::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void LoadingScreen::UpdateGameObject(float deltaTime)
{
	// �l�R���|�[�l���g��null�`�F�b�N
	if (parameter_is_scene_changed_ == nullptr)
	{
		assert(!"LoadingScreen::UpdateGameObject():�l�R���|�[�l���g:parameter_is_scene_changed_ ���hnullptr�h�ł����B");
		return;
	}

	// �l�R���|�[�l���g��null�`�F�b�N�@
	if (parameter_is_show_game_screen_ == nullptr)
	{
		assert(!"LoadingScreen::UpdateGameObject():�l�R���|�[�l���g:parameter_is_show_game_screen_ ���hnullptr�h�ł����B");
		return;
	}


	// 
	// �t�F�[�h�����������烍�[�h��ʂ�\��
	// 

	// ���[�h��ʂ�\�����邩
	const bool is_fade_completed = parameter_is_fade_completed_->GetBool();
	if (is_fade_completed == true)
	{
		// ���̃t�F�[�h�̃X�e�[�g�ɔ�����
		parameter_is_fade_completed_->SetBool(false);

		// ���[�h��ʂ̕\��
		is_show_loading_screen_ = true;

	}

	// ���[�h��ʂ�\�����邩�H
	if (is_show_loading_screen_ == false) { return; }

	// �������`
	switch (loading_state_)
	{
	case LoadingState::Idle:
		// ���[�h��ʂ�\��������ǂݍ��݊J�n
		loading_state_ = LoadingState::FirstHalf;
		break;

	case LoadingState::FirstHalf:
		this->UpdateProgressBarFirstHalf(deltaTime);
		break;

	case LoadingState::SecondHalf:
		this->UpdateProgressBarSecondHalf(deltaTime);
		break;

	case LoadingState::SceneChanged:
		// �Q�[����ʂ�\���������ʒm
		this->parameter_is_show_game_screen_->SetBool(false);
		this->parameter_is_scene_changed_->SetBool(true);
		loading_state_ = LoadingState::SecondHalf;
		break;

	default:
		break;
	}


	// ��ʂ̕��ƍ����̎擾
	const float screen_width  = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	// ��������ImGui�E�B���h�E�̕��ƍ����̐ݒ�
	const float window_width  = 400.f;
	const float window_height = 100.f;

	// ImGui�E�B���h�E�X�^�C���̐ݒ�
	bool is_window_opne = true;
	const ImGuiWindowFlags wf = (ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
	
	// ImGui�E�B���h�E�̐���
	ImGui::Begin("Progress Indicators", &is_window_opne, wf);
	{
		// ImGui�E�B���h�E�̑傫���ƈʒu�̐ݒ�
		ImGui::SetWindowSize(ImVec2(window_width, window_height));
		ImGui::SetWindowPos(ImVec2(screen_width - window_width, screen_height - window_height));

		// ImGui�̔z�F�̐ݒ�
		const ImU32 gui_color = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
		const ImU32 bg_color = ImGui::GetColorU32(ImGuiCol_Button);

		// Gui�̐���
		{
			// ��]����i���C���W�P�[�^�̕\��
			ImGui::Spinner("##spinner", 16, 6, gui_color);

			// �C���W�P�[�^�[�̉��Ƀe�L�X�g�̕\��
			ImGui::SameLine();
			this->UpdateLoadingText(deltaTime);

			// �o�b�t�@�̕\��
			ImGui::BufferingBar("##buffer_bar", progress_value_ / MAX_PROGRESS_VALUE_, ImVec2(400, 8), bg_color, gui_color);
		}
	}
	ImGui::End();
}

/*-----------------------------------------------------------------------------
/* �X�V�ǂݍ��ݒ��̃e�L�X�g�X�V��������
-----------------------------------------------------------------------------*/
void LoadingScreen::UpdateLoadingText(float deltaTime)
{
	// �e�L�X�g�̃`�b�N���v�Z
	text_tick_time_ += deltaTime;

	// �e�L�X�g�̃C���f�b�N�X���X�V
	const float max_tick_time = 0.5f;
	if (text_tick_time_ >= max_tick_time)
	{
		text_tick_time_ = 0.f;
		text_index_++;
	}

	// �ő�ɂȂ����烊�Z�b�g
	const int max_text_index = 4;
	if (text_index_ >= max_text_index)
	{
		text_index_ = 0;
	}

	// �e�L�X�g�̃��Z�b�g
	switch (text_index_)
	{
	case 0:
		ImGui::Text("Now Loading");
		break;
	case 1:
		ImGui::Text("Now Loading.");
		break;
	case 2:
		ImGui::Text("Now Loading..");
		break;
	case 3:
		ImGui::Text("Now Loading...");
		break;
	default:
		break;
	}
}

/*-----------------------------------------------------------------------------
/* �v���O���X�o�[�̑O���̐i���l�̍X�V����
-----------------------------------------------------------------------------*/
void LoadingScreen::UpdateProgressBarFirstHalf(float deltaTime)
{
	// �v���O���X�o�[�̎��s���Ԃ̍X�V
	execute_time_ += deltaTime;
	if (execute_time_ >= MAX_EXECUTE_TIME_ * 0.5f)
	{
		execute_time_ = MAX_EXECUTE_TIME_ * 0.5f;
	
		// ��ʂ�؂�ւ�
		loading_state_ = LoadingState::SceneChanged;
	}

	// �v���O���X�o�[�̐i�����̍X�V(�����܂�)
	progress_value_ = Easing::QuintIn(execute_time_, MAX_EXECUTE_TIME_ * 0.5f, 0.f, MAX_PROGRESS_VALUE_ * 0.5f);
	if (progress_value_ >= MAX_PROGRESS_VALUE_ * 0.5f)
	{
		progress_value_ = MAX_PROGRESS_VALUE_ * 0.5f;		
	}

	//if (progress_value_ >= MAX_PROGRESS_VALUE_)
	//{
	//	progress_value_ = MAX_PROGRESS_VALUE_;
	//}
}

/*-----------------------------------------------------------------------------
/* �v���O���X�o�[�̌㔼�̐i���l�̍X�V����
-----------------------------------------------------------------------------*/
void LoadingScreen::UpdateProgressBarSecondHalf(float deltaTime)
{
	if (parameter_is_show_game_screen_ == nullptr)
	{
		assert(!"LoadingScreen::UpdateProgressBarSecondHalf()�F�l�R���|�[�l���g");
	}

	// �҂����Ԃ��v�Z
	wait_time_ += deltaTime;

	// �ǂݍ��݂͏I���������1�b�҂�
	const float max_wait_time = 1.f;
	if (wait_time_ >= max_wait_time)
	{
		execute_time_ += deltaTime;
		if (execute_time_ >= MAX_EXECUTE_TIME_)
		{
			// ���s���Ԃ�������
			execute_time_ = 0.f;

			// �ǂݍ��݂̑҂����Ԃ�������
			wait_time_ = 0.f;

			// �ǂݍ��݂̃X�e�[�g��������
			loading_state_ = LoadingState::Idle;

			// ���[�h��ʂ�\�����Ȃ�
			is_show_loading_screen_ = false;

			// �t�F�[�h�C�������s����悤�ɗv��
			parameter_is_fade_execute_->SetBool(true);

			// �Q�[����ʂ�\���������ʒm
			parameter_is_show_game_screen_->SetBool(true);
		}

		// �v���O���X�o�[�̐i�����̍X�V
		progress_value_ = Easing::QuintIn(MAX_EXECUTE_TIME_ * 0.5f, MAX_EXECUTE_TIME_ * 0.5f, 0.f, MAX_PROGRESS_VALUE_ * 0.5f)
						+ Easing::QuintIn(execute_time_, MAX_EXECUTE_TIME_, 0.f, MAX_PROGRESS_VALUE_);
		if (progress_value_ >= MAX_PROGRESS_VALUE_)
		{
			progress_value_ = MAX_PROGRESS_VALUE_;
		}
	}

}

/*=============================================================================
/*		End of File
=============================================================================*/