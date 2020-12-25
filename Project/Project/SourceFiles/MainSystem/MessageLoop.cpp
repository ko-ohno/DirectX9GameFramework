/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MessageLoop.cpp] ���b�Z�[�W���[�v�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���b�Z�[�W���[�v�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "MessageLoop.h"
#include "IManager.h"
#include "Manager/ApplicationManager.h"
#include "Manager/SplashScreenManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
MessageLoop::MessageLoop(IManager* iManager)
	: i_manager_(nullptr)
{
	i_manager_ = iManager;
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
MessageLoop::~MessageLoop()
{
	SAFE_DELETE_(i_manager_);
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
MessageLoop* MessageLoop::Create(MessageLoopType msgLoopTyep, const WindowStyle& windowStyle)
{
	switch (msgLoopTyep)
	{
	case MessageLoopType::SplashScreenWindow:
		return NEW MessageLoop(NEW SplashScreenManager(windowStyle));
	
	case MessageLoopType::ApplicationWindow:
		return NEW MessageLoop(NEW ApplicationManager(windowStyle));

	default:
		assert(!"�s���ȃ��b�Z�[�W���[�v�̐��������m!");
		break;
	}

	return nullptr;
}

/*-----------------------------------------------------------------------------
/* �N������
-----------------------------------------------------------------------------*/
bool MessageLoop::StartUp(void)
{
	if (i_manager_ == nullptr) { return false; }
	return i_manager_->Init();;
}

/*-----------------------------------------------------------------------------
/* ���s����
-----------------------------------------------------------------------------*/
void MessageLoop::Run(void)
{
	MSG	  msg;								//�E�B���h�E�v���V�[�W���ւ̃n���h��
	DWORD execute_last_time = 0UL;			//1�t���[���O�̏I������
	DWORD current_time		= 0UL;			//���݂̎���
	DWORD ticks_counts		= 0UL;			//1�t���[���̌o�ߎ���

	const float maximum_delta_time = 0.05f;	//deltaTime�̍ő吧���l
	float		delta_time		   = 0.f;	//1�t���[���O�Ƃ̍����̕b��		

	timeBeginPeriod(1); //����\��ݒ�

	for (;;)
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

				//null�`�F�b�N
				if (i_manager_ != nullptr)
				{
					i_manager_->Input();
					i_manager_->Update(delta_time);
					i_manager_->GenerateOutput();
				}

				//���݂̃t���[���̎��s�O���ԂɎ��s�㎞�Ԃ����B
				execute_last_time = current_time;
			}
		}
		const bool  lb = i_manager_->IsLoopBreak();
		const bool  sd = i_manager_->IsShutDown();

		if ((msg.message == WM_QUIT)|| lb || sd) { break; }
	}

	timeEndPeriod(1); //����\������
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void MessageLoop::ShutDown(void)
{
	i_manager_->Uninit();
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
Vector2* MessageLoop::GetSelectedAspectRatio(void)
{
	if (i_manager_ == nullptr) { return nullptr; }
	return i_manager_->GetSelectedAspectRatio();
}

/*-----------------------------------------------------------------------------
/* �V���b�g�_�E�������邩
-----------------------------------------------------------------------------*/
bool MessageLoop::IsShutDown(void)
{
	if (i_manager_ == nullptr) { return false; }
	return i_manager_->IsShutDown();
}

/*-----------------------------------------------------------------------------
/* ���[�v��E�o���邩
-----------------------------------------------------------------------------*/
bool MessageLoop::IsLoopBreak(void)
{
	if (i_manager_ == nullptr) { return false; }
	return i_manager_->IsLoopBreak();
}

/*=============================================================================
/*		End of File
=============================================================================*/