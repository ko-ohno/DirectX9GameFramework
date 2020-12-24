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

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Application::Application(void)
	: app_title_name_("")
	, window_style_(WindowStyle())
	, message_loop_(nullptr)
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

	//�Q�[���p�E�B���h�E�̐ݒ�
	{
		window_style_.hInstance		= hInstance;
		window_style_.nShowCmd		= nShowCmd;
		window_style_.dwWindowStyle = WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME);
		window_style_.windowTitle	= app_title_name_;
		window_style_.hIcon			= LoadAppIcon(hInstance);
		//window_style_.windowSize	= Vector2(100.f, 100.f);
		window_style_.windowSize	= Vector2(1280.f, 720.f);
	}

	//���g�̏�����
	is_success = this->Init();
	if (is_success == false)
	{
		return false;	//�������̎��s
	}

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
	message_loop_->ShutDown();
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Application::Init(void)
{
	//�X�v���b�V���X�N���[���̎��s
	{
		SplashScreen splash_screen;
		const bool is_success = splash_screen.StartUp(window_style_);
		if (is_success)
		{
			splash_screen.Run();
		}
		else
		{
			return false;	//�X�v���b�V���X�N���[���̋N���Ɏ��s
		}
		splash_screen.ShutDown();
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Application::Uninit(void)
{
	SAFE_DELETE_(message_loop_);
}

/*-----------------------------------------------------------------------------
/* �A�C�R���̓ǂݍ��ݏ�������
-----------------------------------------------------------------------------*/
HICON Application::LoadAppIcon(const HINSTANCE& hInstance)
{
	//�ȉ��̃R�[�h�ƃ��\�[�X��g�ݍ��ނ��ƂŃA�C�R����ύX����
	//HICON hIcon = (HICON)LoadImage(hInstance_
	//								, MAKEINTRESOURCE(IDI_ICON1)
	//								, IMAGE_ICON
	//								, 64
	//								, 64
	//								, 0);

	return HICON();
}

/*=============================================================================
/*		End of File
=============================================================================*/