/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreen.h] �X�v���b�V���X�N���[���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���b�V���X�N���[���N���X
=============================================================================*/
#ifndef SPLASHSCREEN_H_
#define	SPLASHSCREEN_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "Win32APIWindow.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �X�v���b�V���X�N���[���N���X
-------------------------------------*/
class SplashScreen
{
public:
	SplashScreen(void);
	~SplashScreen(void);

public:
	bool StartUp(const WindowStyle& windowStyle);
	void Run(void);
	void ShutDown(void);

	class Vector2* GetSelectedAspectRatio(void);
	bool IsApplicationShutDown(void);
	
private:
	WindowStyle			  window_style_;
	class MessageLoop*	  message_loop_;
};

#endif //SPLASHSCREEN_H_
/*=============================================================================
/*		End of File
=============================================================================*/