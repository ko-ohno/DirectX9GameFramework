/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreenManager.cpp] �X�v���b�V���X�N���[���S�̂̏����̊Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���b�V���X�N���[���̑S�̂̏����̊Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "SplashScreenManager.h"
#include "../Win32APIWindow.h"
#include "../DX9Graphics.h"
#include "../ImGui/ImGuiManager.h"
#include "../AspectRatio.h"
#include "../../DebugCode/DebugFunction.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SplashScreenManager::SplashScreenManager(const WindowStyle& windowStyle)
	: screen_scaler_(1.0f)
	, aspect_ratio_size_(Vector2())
	, texture_(nullptr)
	, splash_window_(nullptr)
	, window_handle_(nullptr)
	, dx9_graphics_(nullptr)
	, imgui_manager_(nullptr)
	, is_loop_break_(false)
	, is_shutdown_(false)
{
	splash_window_	= splash_window_->Create();
	window_handle_	= splash_window_->CreateNewWindow(windowStyle);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SplashScreenManager::~SplashScreenManager(void)
{
	ShowWindow(window_handle_, SW_HIDE); // ���̃n���h���̃E�B���h�E���\����
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SplashScreenManager::Init(void)
{
	//�O���t�B�b�N�X�I�u�W�F�N�g�̐����B
	{
		dx9_graphics_ = dx9_graphics_->Create();
		const bool directx9_init = dx9_graphics_->CreateDX9Graphics(window_handle_, splash_window_->GetWindowClientSize(window_handle_));
		if (directx9_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("directx9�̏��������ł��܂���ł����I");
			DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
			return false;
		}
	}

	//ImGui�̋N��
	{
		imgui_manager_ = imgui_manager_->Create();
		const bool imgui_init = imgui_manager_->StartUp(dx9_graphics_, window_handle_);
		if (imgui_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("ImGui�̏��������ł��܂���ł����I");
			DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
			return false;
		}
	}

	//�A�X�y�N�g�䗦�̃��X�g�̍쐬
	this->MakeListAspectRatio();

	const char* filename = { "Assets/PackageImage/QR_code_to_my_github.png" };
	bool is_load_sucess = ImGui::LoadTexture(filename, &texture_, texture_size_);
	if (!is_load_sucess) { return false; }

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SplashScreenManager::Uninit(void)
{
	imgui_manager_->ShutDown();

	while (!aspect_ratio_size_array_.empty())
	{
		aspect_ratio_size_array_.pop_back();
	}

	SAFE_DELETE_(splash_window_);
	SAFE_DELETE_(imgui_manager_);
	SAFE_DELETE_(dx9_graphics_);
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
	UNREFERENCED_PARAMETER(deltaTime);

	imgui_manager_->UpdateBegin();
	{
		ImVec2 offset_size		  = { 5.f, 5.f };
		ImVec2 offset_draw_pos	  = { -offset_size.x, -offset_size.y };
		ImVec2 offset_screen_size = { splash_window_->GetWindowSize().x_ + offset_size.x
									, splash_window_->GetWindowSize().y_ + offset_size.y };

		ImGuiWindowFlags this_gui_window_flag = ( ImGuiWindowFlags_NoTitleBar
												| ImGuiWindowFlags_NoMove
												| ImGuiWindowFlags_NoResize
												| ImGuiWindowFlags_NoCollapse
												| ImGuiWindowFlags_NoScrollbar);

		//�I�t�Z�b�g������ʃT�C�Y�Ƃ��̂ق��̐ݒ�
		{
			ImGui::SetNextWindowSize(offset_screen_size);
			ImGui::SetNextWindowPos(offset_draw_pos);

			//�E�B���h�E�`��
			ImGui::Begin("splash_screen", nullptr, this_gui_window_flag);
			{
				//�摜�̕`��
				ImGui::BeginGroup();
				{
					//�摜�T�C�Y�̏k�����ē\��t��
					ImGui::Image((void*)texture_
								, ImVec2( texture_size_.x_ - offset_size.x
										, texture_size_.y_ - offset_size.y));
				}
				ImGui::EndGroup();

				//�R���{�{�b�N�X
				{
					//�X�v���b�V���X�N���[���N������̃R���{�{�b�N�X�̑I��l
					static int combo_item_current = screen_scaler_array_.size() -1;

					//�I�𒆂̔䗦�̍X�V
					aspect_ratio_size_ = aspect_ratio_size_array_.at(combo_item_current);
					screen_scaler_ = screen_scaler_array_.at(combo_item_current);

					//�z��̒��Ɋi�[
					std::vector<const char*> combo_items_;
					auto iter = aspact_ratio_string_array_.begin();
					for (iter; iter != aspact_ratio_string_array_.end(); ++iter)
					{
						combo_items_.push_back((*iter).c_str());
					}

					//�R���{�{�b�N�X�`��
					ImGui::BeginGroup();
					{
						ImGui::Text("ScreenSize:");
						ImGui::SameLine();
						ImGui::Combo(""
									, &combo_item_current
									, combo_items_.data()
									, aspact_ratio_string_array_.size());
						//ImGui::Text("combo_item_current:%d", combo_item_current);
					}
					ImGui::EndGroup();
				}

				//���s
				ImGui::BeginGroup();
				{
					ImGui::Text("");	//�R���{�{�b�N�X�ƃE�B���h�E�̂������̋�Ԃɗ]�T����������
				}
				ImGui::EndGroup();

				//�{�^���`��
				ImGui::BeginGroup();
				{
					ImGui::Text("GAME:");
					ImGui::SameLine();
					if (ImGui::Button("START", ImVec2(200.f, 20.f)))
					{
						is_loop_break_ = true; // Application�̃E�B���h�E�������߂𔭍s
					}
					ImGui::SameLine();
					if (ImGui::Button("QUIT", ImVec2(200.f, 20.f)))
					{
						is_shutdown_  = true;  // �v���O�����̒�~���߂𔭍s
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

/*-----------------------------------------------------------------------------
/* �A�X�y�N�g�䗦�̃��X�g�̍쐬
-----------------------------------------------------------------------------*/
void SplashScreenManager::MakeListAspectRatio(void)
{
	auto aspect_ratio		= AspectRatio::Create(); 
	auto aspect_ratio_list  = aspect_ratio->GetAspectRatioList();

	auto iter = aspect_ratio_list.begin();
	for (iter; iter != aspect_ratio_list.end(); ++iter)
	{
		//���X�g�̕�������i�[
		aspact_ratio_string_array_.push_back((*iter).first);

		aspect_ratio_size_array_.push_back((*iter).second);
	}

	screen_scaler_array_ = aspect_ratio->GetScreenScalerList();

	delete aspect_ratio;
}

/*-----------------------------------------------------------------------------
/* �A�X�y�N�g�䗦�̎擾
-----------------------------------------------------------------------------*/
Vector2* SplashScreenManager::GetSelectedAspectRatio(void)
{
	return &aspect_ratio_size_;
}

/*-----------------------------------------------------------------------------
/* ��ʂ̊g�k�{���̎擾�֐�
-----------------------------------------------------------------------------*/
float SplashScreenManager::GetScreenScaler(void)
{
	return screen_scaler_;
}

/*-----------------------------------------------------------------------------
/* ���b�Z�[�W���[�v��E�o���邩
-----------------------------------------------------------------------------*/
bool SplashScreenManager::IsLoopBreak(void)
{
	return is_loop_break_;
}

/*-----------------------------------------------------------------------------
/* �V���b�g�_�E�������邩
-----------------------------------------------------------------------------*/
bool SplashScreenManager::IsShutDown(void)
{
	return is_shutdown_;
}

/*=============================================================================
/*		End of File
=============================================================================*/