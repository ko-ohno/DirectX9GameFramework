/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreen.cpp] �X�v���b�V���X�N���[���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���b�V���X�N���[���N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "SplashScreen.h"
#include "MessageLoop.h"
#include "Win32APIWindow.h"
#include "../Generic/Math.h"
#include "../CodeDebug/DebugFunction.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SplashScreen::SplashScreen(void)
    : window_style_(WindowStyle())
    , message_loop_(nullptr)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SplashScreen::~SplashScreen(void)
{
}

/*-----------------------------------------------------------------------------
/* �N������
-----------------------------------------------------------------------------*/
bool SplashScreen::StartUp(const WindowStyle& windowStyle)
{
    std::string window_name     =  windowStyle.windowTitle;
    std::string window_sub_name = "�F�X�v���b�V���X�N���[��";

    //���[�J���ϐ��ɁA�X�v���b�V���X�N���[���̃E�B���h�E�̐ݒ菑������
    window_style_ = windowStyle;
    {
        //window_style.hInstance    = hinstance;    //Application.cpp�ł̐ݒ�������p��
        //window_style.nShowCmd     = nShowCmd;     //Application.cpp�ł̐ݒ�������p��
        //window_style.hIcon;                      //Application.cpp�ł̐ݒ�������p��
        window_style_.dwWindowStyle = WS_POPUPWINDOW;
        window_style_.windowTitle   = window_name + window_sub_name;
        window_style_.windowSize    = Vector2(500.f, 600.f);
    }

    //���b�Z�[�W���[�v�ɁA�X�v���b�V���X�N���[���̃}�l�[�W����o�^
    message_loop_ = MessageLoop::Create(MessageLoopType::SplashScreenWindow, window_style_);
    const bool is_success = message_loop_->StartUp();
    if (is_success == false)
    {
        std::string msg_str = OUTPUT_FORMAT_STRING("�X�v���b�V���X�N���[���̏��������ł��܂���ł����I");
        DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
        return false;
    }
    return true;
}

/*-----------------------------------------------------------------------------
/* ���s����
-----------------------------------------------------------------------------*/
void SplashScreen::Run(void)
{
    message_loop_->Run();
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void SplashScreen::ShutDown(void)
{
    message_loop_->ShutDown();
    SAFE_DELETE_(message_loop_);
}

/*-----------------------------------------------------------------------------
/* �I�������A�X�y�N�g�䗦�̎擾����
-----------------------------------------------------------------------------*/
Vector2* SplashScreen::GetSelectedAspectRatio(void)
{
    if (message_loop_ == nullptr) { return nullptr; }
    return message_loop_->GetSelectedAspectRatio();
}

/*-----------------------------------------------------------------------------
/* ��ʔ䗦
-----------------------------------------------------------------------------*/
float SplashScreen::GetScreenScaler(void)
{
    if (message_loop_ == nullptr) { return 1.0f; }
    return message_loop_->GetScreenScaler();
}

/*-----------------------------------------------------------------------------
/*  �A�v���P�[�V�������I�����邩
-----------------------------------------------------------------------------*/
bool SplashScreen::IsApplicationShutDown(void)
{
    if (message_loop_ == nullptr) { return false; }
    return message_loop_->IsShutDown();
}

/*=============================================================================
/*		End of File
=============================================================================*/