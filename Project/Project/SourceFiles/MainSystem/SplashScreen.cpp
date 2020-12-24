/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreen.cpp] ���W���[��
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "SplashScreen.h"
#include "MessageLoop.h"
#include "Win32APIWindow.h"
#include "../Generic/Math.h"

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
    std::string window_sub_name = ":�X�v���b�V���X�N���[��";

    //���[�J���ϐ��ɁA�X�v���b�V���X�N���[���̃E�B���h�E�̐ݒ菑������
    window_style_ = windowStyle;
    {
        //window_style.hInstance    = hinstance;    //Application.cpp�ł̐ݒ�������p��
        //window_style.nCmdShow     = nShowCmd;     //Application.cpp�ł̐ݒ�������p��
        window_style_.dwWindowStyle = WS_POPUPWINDOW;
        window_style_.windowTitle   = window_name + window_sub_name;
        //window_style.hIcon;                       //Application.cpp�ł̐ݒ�������p��
        window_style_.windowSize    = Vector2(500.f, 600.f);
    }

    //���b�Z�[�W���[�v�ɁA�X�v���b�V���X�N���[���̃}�l�[�W����o�^
    message_loop_ = MessageLoop::Create(MessageLoopType::SplashScreenWindow, window_style_);
    const bool is_success = message_loop_->StartUp();
    if (is_success == false)
    {
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

/*=============================================================================
/*		End of File
=============================================================================*/