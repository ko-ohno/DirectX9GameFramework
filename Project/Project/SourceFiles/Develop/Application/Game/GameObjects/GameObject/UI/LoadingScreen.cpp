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

#include "../../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
LoadingScreen::LoadingScreen(Game* game)
	: UI(game)
{
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
	UNREFERENCED_PARAMETER(deltaTime);

	// ��ʂ̕��ƍ����̎擾
	const float screen_width  = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	// ��������ImGui�E�B���h�E�̕��ƍ����̐ݒ�
	const float window_width  = 400.f;
	const float window_height = 100.f;

	// ImGui�E�B���h�E�̐ݒ�
	bool is_window_opne = true;
	const ImGuiWindowFlags wf = (ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
	
	// ImGui�E�B���h�E�̐���
	ImGui::Begin("Progress Indicators", &is_window_opne, wf);

	// ImGui�E�B���h�E�̐ݒ�
	ImGui::SetWindowSize(ImVec2(window_width, window_height));
	ImGui::SetWindowPos(ImVec2(screen_width - window_width, screen_height - window_height));
	{
		static float time = 0.f;
		static float val = 0.f;
		static int	 text_index = 0;

		time += deltaTime;

		const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
		const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

		//const float div_num = 1000.f;
		const float div_num = 3.f;
		//ImGui::SliderFloat("##buffer_bar", &val, 0.0f, div_num);

		// ��]����i���C���W�P�[�^�̕\��
		ImGui::Spinner("##spinner", 16, 6, col);

		// �e�L�X�g�̕\��
		ImGui::SameLine();
		{
			switch (text_index)
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

			const float max_value = 3.f;
			if (val >= max_value)
			{
				val = max_value;
			}

			const float max_tick_time = 0.5f;
			if (time >= max_tick_time)
			{
				time = 0.f;
				text_index++;
			}

			const int max_text_index = 4;
			if (text_index >= max_text_index)
			{
				text_index = 0;
			}
		}

		// �o�b�t�@�̕\��
		ImGui::BufferingBar("##buffer_bar", val / div_num, ImVec2(400, 8), bg, col);
	}
	ImGui::End();
}

/*=============================================================================
/*		End of File
=============================================================================*/