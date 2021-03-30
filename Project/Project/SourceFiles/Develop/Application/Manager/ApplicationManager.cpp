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
#include "../InputDevice/InputDevice.h"
#include "../Game/Input/InputCheck.h"
#include "../ImGui/ImGuiManager.h"
#include "../../DebugCode/DebugFunction.h"

//�Q�[���̎��s��
#include "../Game/Game.h"

//�V�F�[�_�e�X�g
//#include "..Test/Shader/SpriteShader.h"
//#include "Test/GameObject/TestCamera.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ApplicationManager::ApplicationManager(const WindowStyle& windowStyle)
	: app_window_(nullptr)
	, window_handle_(nullptr)
	, dx9_graphics_(nullptr)
	, input_device_(nullptr)
	, imgui_manager_(nullptr)
	, window_style_(WindowStyle())
	, screen_scaler_(0.0f)
	, game_(nullptr)
	, sprite_shader_(nullptr)
	, test_camera_(nullptr)
{
	app_window_	   = app_window_->Create();
	window_handle_ = app_window_->CreateNewWindow(windowStyle, true);

	// �E�B���h�E�ɂ��Ă̏����擾�ł���悤��
	window_style_  = windowStyle;
	screen_scaler_ = window_style_.screen_scaler;	// ��ʂ̊g�k�{�����擾�ł���悤��
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

	//���̓f�o�C�X�̐���
	{
		input_device_ = input_device_->Create();
		const bool input_device_init = input_device_->CreateInputDevice(window_style_.hInstance, window_handle_);
		if (input_device_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("InputDevice�̏��������ł��܂���ł����I");
			DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());

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

	//�Q�[���̋N��
	{
		game_ = game_->Create();
		const bool game_init = game_->StartUp(dx9_graphics_);
		if (game_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("�Q�[���̏��������ł��܂���ł����I");
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
	//ImGui�̏I��
	{
		imgui_manager_->ShutDown();
		SAFE_DELETE_(imgui_manager_);
	}

	//�Q�[���̏I��
	{
		game_->ShutDown();
		SAFE_DELETE_(game_);
	}

	SAFE_DELETE_(app_window_);
	SAFE_DELETE_(input_device_);
	SAFE_DELETE_(dx9_graphics_);
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void ApplicationManager::Input(void)
{
	//���̓f�o�C�X�X�V����
	if (input_device_ != nullptr)
	{
		//�f�o�C�X�̍X�V
		input_device_->Update(window_handle_);

		//�f�o�C�X���͌��m�N���X�̍X�V
		InputCheck::SetInputDeviceState(input_device_);

		game_->Input();
	}
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void ApplicationManager::Update(float deltaTime)
{
	imgui_manager_->UpdateBegin();

	game_->Update(deltaTime);

	imgui_manager_->ShowFramerate(deltaTime);

	imgui_manager_->UpdateEnd();
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void ApplicationManager::GenerateOutput(void)
{
	dx9_graphics_->RenderingBegin();

	game_->GenerateOutput();

	imgui_manager_->ImGuiRender();

	dx9_graphics_->RenderingEnd();
}

/*=============================================================================
/*		End of File
=============================================================================*/