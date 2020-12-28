/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Application.cpp] �A�v���P�[�V�����N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�v���P�[�V�����N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "StdAfx.h"
#include "Application.h"
#include "MainSystem/SplashScreen.h"
#include "MainSystem/MessageLoop.h"
#include "Generic/Math.h"
#include "Icon/resource.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Application::Application(void)
	: app_title_name_("")
	, window_style_(WindowStyle())
	, selected_screen_aspect_ratio_(Vector2())
	, message_loop_(nullptr)
	, is_shutdown_(false)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Application::~Application(void)
{
}

/*-----------------------------------------------------------------------------
/* �N������
-----------------------------------------------------------------------------*/
bool Application::StartUp(const HINSTANCE& hInstance, const int& nShowCmd)
{
	bool is_success;
	app_title_name_ = "�Q�[���^�C�g��";

	//�A�v���P�[�V�����p�E�B���h�E�̐ݒ�
	{
		window_style_.hInstance		= hInstance;
		window_style_.nShowCmd		= nShowCmd;
		window_style_.dwWindowStyle = WS_POPUPWINDOW;
		window_style_.hIcon			= this->LoadAppIcon(hInstance, Vector2(256.f, 256.f));
		window_style_.windowTitle	= app_title_name_;
		window_style_.windowSize	= Vector2(200.f,200.f);
	}

	//�X�v���b�V���X�N���[���̎��s
	const bool is_shutdown = this->RunSplashScreen();
	if (is_shutdown)
	{
		return false;
	}

	//�A�X�y�N�g�䗦�����j�^�[�̔䗦�ƈ�v���Ă邩�`�F�b�N
	const bool is_full_screen = (selected_screen_aspect_ratio_ == Win32APIWindow().GetFullScreenSize());
	if (is_full_screen)
	{
		window_style_.dwWindowStyle = WS_POPUPWINDOW;
	}
	else
	{
		window_style_.dwWindowStyle = WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME);
	}

	//�E�B���h�E�T�C�Y�̊m��
	window_style_.windowSize = selected_screen_aspect_ratio_;

	//�������Ɏ��s������
	//���b�Z�[�W���[�v�ɁA�A�v���P�[�V�����̃}�l�[�W����o�^
	{
		message_loop_ = MessageLoop::Create(MessageLoopType::ApplicationWindow, window_style_);
		is_success = message_loop_->StartUp();
		if (is_success == false)
		{
			return false;	//���b�Z�[�W���[�v�̋N���Ɏ��s
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ���s����
-----------------------------------------------------------------------------*/
void Application::Run(void)
{ 
	message_loop_->Run();
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void Application::ShutDown(void)
{
	if (message_loop_ != nullptr)
	{
		message_loop_->ShutDown();
		SAFE_DELETE_(message_loop_);
	}
}

/*-----------------------------------------------------------------------------
/* �X�v���b�V���X�N���[���̎��s����
-----------------------------------------------------------------------------*/
bool Application::RunSplashScreen(void)
{
	SplashScreen splash_screen;
	bool		 is_shutdown = false;

	const bool   is_success	 = splash_screen.StartUp(window_style_);
	if (is_success)
	{
		splash_screen.Run();

		selected_screen_aspect_ratio_ = *splash_screen.GetSelectedAspectRatio();

		is_shutdown = splash_screen.IsApplicationShutDown();
	}
	splash_screen.ShutDown();
	return is_shutdown;
}

/*-----------------------------------------------------------------------------
/* �A�C�R���̓ǂݍ��ݏ�������
-----------------------------------------------------------------------------*/
HICON Application::LoadAppIcon(const HINSTANCE& hInstance, const Vector2& iconSize)
{
	//�ȉ��̃R�[�h�ƃ��\�[�X��g�ݍ��ނ��ƂŃA�C�R����ύX����
	HICON hIcon = (HICON)LoadImage(hInstance
								  , MAKEINTRESOURCE(IDI_ICON1)
								  , IMAGE_ICON
								  , static_cast<int>(iconSize.x_)
								  , static_cast<int>(iconSize.y_)
								  , 0);
	return hIcon;
}

/*=============================================================================
/*		End of File
=============================================================================*/