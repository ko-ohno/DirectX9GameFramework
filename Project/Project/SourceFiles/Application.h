/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Application.h] �A�v���P�[�V�����N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�v���P�[�V�����N���X
=============================================================================*/
#ifndef APPLICATION_H_
#define	APPLICATION_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "MainSystem/Win32APIWindow.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �A�v���P�[�V�����N���X
-------------------------------------*/
class Application
{
public:
	Application(void);
	~Application(void);

public:
	bool StartUp(const HINSTANCE& hInstance, const int& nShowCmd);
	void Run(void);
	void ShutDown(void);

private:
	//�X�v���b�V���X�N���[���̎��s
	bool RunSplashScreen(void);

	HICON LoadAppIcon(const HINSTANCE& hInstance);

private:
	std::string			app_title_name_;
	WindowStyle			window_style_;
	class Vector2*		selected_screen_aspect_ratio_;
	class MessageLoop*	message_loop_;
	bool				is_shutdown_;
};

#endif //APPLICATION_H_
/*=============================================================================
/*		End of File
=============================================================================*/