/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreenManager.cpp] �A�v���S�̂̏����̊Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�v���S�̂̏����̊Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "SplashScreenManager.h"
#include "../Win32APIWindow.h"
#include "../DX9Graphics.h"
#include "../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SplashScreenManager::SplashScreenManager(const WindowStyle& windowStyle)
	: splash_window_(nullptr)
	, window_handle_(nullptr)
	, dx9_graphics_(nullptr)
	, imgui_manager_(nullptr)
{
	splash_window_	= splash_window_->Create();
	window_handle_	= splash_window_->CreateNewWindow(windowStyle);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SplashScreenManager::~SplashScreenManager(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SplashScreenManager::Init(void)
{
	//�O���t�B�b�N�X�I�u�W�F�N�g�̐����B
	dx9_graphics_ = dx9_graphics_->Create();
	dx9_graphics_->CreateDX9Graphics(window_handle_, splash_window_->GetWindowClientSize(window_handle_));

	imgui_manager_->Create();
	imgui_manager_->StartUp(dx9_graphics_, window_handle_);


	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SplashScreenManager::Uninit(void)
{
	imgui_manager_->ShutDown();

	SAFE_DELETE_(splash_window_);
	SAFE_DELETE_(dx9_graphics_);
	SAFE_DELETE_(imgui_manager_);
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void SplashScreenManager::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void SplashScreenManager::Update(float deltaTime)
{
	imgui_manager_->UpdateBegin();

	imgui_manager_->ShowFramerate(deltaTime);

	{
		ImVec2 offset_size = { 5, 5 };
		ImVec2 offset_draw_pos = { -offset_size.x, -offset_size.y };
		//ImVec2 offset_screen_size = {
		//	screen_size_->x_ + offset_size.x
		//	, screen_size_->y_ + offset_size.y };

		ImGuiWindowFlags this_gui_window_flag = (
			ImGuiWindowFlags_NoTitleBar
			//| ImGuiWindowFlags_NoMove
			//| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar);

		//�R���{�{�b�N�X�őI�𒆂̗v�f
		static int combo_item_current = 2; //�������l
		const char* combo_items[] = {
			"FullScreen(1920*1080)"
			, "1360*768"
			, "1280*720"
			, "720*480" };

		//�R���{�{�b�N�X���I�𒆂̕���������Ƃɉ�ʉ�ʃT�C�Y�̒�`��ύX����
		//ScreenSize::UpdateScreenSizeSelect(combo_items[combo_item_current]);

		{//�I�t�Z�b�g������ʃT�C�Y�Ƃ��̂ق��̐ݒ�
			//ImGui::SetNextWindowSize(offset_screen_size);
			//ImGui::SetNextWindowPos(5);
			ImGui::SetNextWindowPos(offset_draw_pos);

			//�E�B���h�E�`��
			ImGui::Begin("splash_screen", nullptr, this_gui_window_flag);
			{
				//�摜�̕`��
				ImGui::BeginGroup();
				{
					////�摜�T�C�Y�̏k�����ē\��t��
					//ImGui::Image((void*)texture_
					//	, ImVec2(texture_size_.x_ - offset_size.x
					//		, texture_size_.y_ - offset_size.y));
				}
				ImGui::EndGroup();

				//�R���{�{�b�N�X�`��
				ImGui::BeginGroup();
				{
					ImGui::Text("ScreenSize:");
					ImGui::SameLine();
					ImGui::Combo("", &combo_item_current, combo_items, IM_ARRAYSIZE(combo_items));
					//ImGui::Text("combo_item_current:%d", combo_item_current);
				}
				ImGui::EndGroup();

				//���s
				ImGui::BeginGroup();
				{
					ImGui::Text("");
				}
				ImGui::EndGroup();

				//�{�^���`��
				ImGui::BeginGroup();
				{
					ImGui::Text("GAME:");
					ImGui::SameLine();
					if (ImGui::Button("START", ImVec2(200.f, 20.f)))
					{
					}
					ImGui::SameLine();
					if (ImGui::Button("QUIT", ImVec2(200.f, 20.f)))
					{
						//SystemDefinition::SetProgramRunningState(ProgramRunningState::QUIT);
					}
				}
				ImGui::EndGroup();
			}
			ImGui::End();
		}
	}
	imgui_manager_->UpdateEnd();
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void SplashScreenManager::GenerateOutput(void)
{
	dx9_graphics_->RenderingBegin();


	imgui_manager_->ImGuiRender();

	dx9_graphics_->RenderingEnd();
}

/*=============================================================================
/*		End of File
=============================================================================*/