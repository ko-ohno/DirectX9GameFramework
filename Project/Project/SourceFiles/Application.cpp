/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MainProcess.cpp] ���C���̎��s����
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���C���̎��s����
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "StdAfx.h"
#include "Application.h"
#include "ApplicationManager.h"
#include "Window/Win32APIWindow.h"
#include "Generic/Math.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Application::Application(void)
	:app_manager_(nullptr)
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
bool Application::StartUp(const HINSTANCE& hinstance, const int& nCmdShow)
{
#if defined(_DEBUG) || defined(DEBUG)
	OutputDebugString("�A�v���P�[�V�������N�����܂��B\n");
#endif

	//�ȉ��̃R�[�h�ƃ��\�[�X��g�ݍ��ނ��ƂŃA�C�R����ύX����
	//HICON hIcon = (HICON)LoadImage(hInstance_
	//	, MAKEINTRESOURCE(IDI_ICON1)
	//	, IMAGE_ICON
	//	, 64
	//	, 64
	//	, 0);

	//Math::Vector2 screen_size(0.f, 0.f);
	//BOOL is_windowed = TRUE;
	//bool is_init_success = false;

	//�E�B���h�E�̃C���X�^���X�쐬
	app_window_ = Win32APIWindow::Create();


	//�E�B���h�E�X�^�C���̎w��
	WindowStyle window_style;
	{
		window_style.hInstance	 = hinstance;
		window_style.nCmdShow	 = nCmdShow;
		window_style.windowTitle = "test";
		window_style.hIcon;
		window_style.windowSize  = {1280.f, 720.f};
		window_style.isWindowed  = TRUE;
	}
	app_window_->CreateAppWindow(window_style);

	////�����������ǂ���
	//Application::Init();
	//ApplicationManager::Init();

	return true;
}

/*-----------------------------------------------------------------------------
/* ���s����
-----------------------------------------------------------------------------*/
void Application::Run(void)
{ 
#if defined(_DEBUG) || defined(DEBUG)
	OutputDebugString("�A�v���P�[�V���������s���܂��B\n");
#endif

	MSG msg;
	DWORD execute_last_time			= 0UL;		//1�t���[���O�̏I������
	DWORD current_time				= 0UL;		//���݂̎���
	DWORD ticks_counts				= 0UL;		//1�t���[���̌o�ߎ���
	float delta_time				= 0.f;		//1�t���[���O�Ƃ̍����̕b��		
	const float maximum_delta_time	= 0.05f;	//deltaTime�̍ő吧���l

	timeBeginPeriod(1); //����\��ݒ�

	for(;;)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			//�E�B���h�E���b�Z�[�W���� 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//60fps��
			current_time = timeGetTime(); //���s���Ԃ��擾

			//1�t���[���O�Ƃ̍������擾
			ticks_counts = (current_time - execute_last_time);

			//�b���ɕϊ�
			delta_time = ((float)ticks_counts / 1000.f);

			if (delta_time >= (1 / 60))
			{
				//delta_time >= (1 / 60)
				//1�t���[���O�Ƃ̍�����0.016...�~���b�ȏゾ��������s����

				//delta_time�̐���
				//���s����u���[�N�|�C���g���s�����̗\�h�[�u
				if (delta_time >= maximum_delta_time)
				{
					delta_time = maximum_delta_time;
				}

				ApplicationManager::Input();
				ApplicationManager::Update(delta_time);
				ApplicationManager::GenerateOutput();

				//���݂̃t���[���̎��s�O���ԂɎ��s�㎞�Ԃ����B
				execute_last_time = current_time;
			}
		}
		if (msg.message == WM_QUIT) { break; }
	}

	timeEndPeriod(1); //����\������
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void Application::ShutDown(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	OutputDebugString("�A�v���P�[�V�������I�����܂��B\n");
#endif

	ApplicationManager::Uninit();
	Application::Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Application::Init(void)
{
	app_manager_ = app_manager_->Create();
	if (app_manager_ == nullptr) { return false; }
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Application::Uninit(void)
{
	delete app_manager_;
}

/*=============================================================================
/*		End of File
=============================================================================*/