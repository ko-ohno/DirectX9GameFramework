/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ApplicationManager.cpp] �A�v���S�̂̏����̊Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�v���S�̂̏����̊Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "ApplicationManager.h"
#include "../Win32APIWindow.h"
#include "../DX9Graphics.h"
#include "../../ImGui/ImGuiManager.h"
#include "../../CodeDebug/DebugFunction.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ApplicationManager::ApplicationManager(const WindowStyle& windowStyle)
	: app_window_(nullptr)
	, window_handle_(nullptr)
	, dx9_graphics_(nullptr)
	, imgui_manager_(nullptr)
	, screen_scaler_(0.0f)
{
	app_window_	   = app_window_->Create();
	window_handle_ = app_window_->CreateNewWindow(windowStyle, true);
	screen_scaler_ = windowStyle.screen_scaler;	// ��ʂ̊g�k�{�����擾�ł���悤��
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ApplicationManager::~ApplicationManager(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool ApplicationManager::Init(void)
{
	//�O���t�B�b�N�X�I�u�W�F�N�g�̐����B
	{
		dx9_graphics_ = dx9_graphics_->Create();
		const bool directx9_init = dx9_graphics_->CreateDX9Graphics(window_handle_, app_window_->GetWindowClientSize(window_handle_));
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
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void ApplicationManager::Uninit(void)
{
	imgui_manager_->ShutDown();

	SAFE_DELETE_(app_window_);
	SAFE_DELETE_(imgui_manager_);
	SAFE_DELETE_(dx9_graphics_);
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void ApplicationManager::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void ApplicationManager::Update(float deltaTime)
{
	imgui_manager_->UpdateBegin();

	imgui_manager_->ShowFramerate(deltaTime);

	imgui_manager_->UpdateEnd();
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void ApplicationManager::GenerateOutput(void)
{
	dx9_graphics_->RenderingBegin();

	imgui_manager_->ImGuiRender();

	dx9_graphics_->RenderingEnd();
}

/*=============================================================================
/*		End of File
=============================================================================*/