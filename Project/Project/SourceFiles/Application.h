/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Application.h] ���C���̎��s����
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���C���̎��s����
=============================================================================*/
#ifndef APPLICATION_H_
#define	APPLICATION_H_

/*--- �C���N���[�h�t�@�C�� ---*/

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* ���C���̎��s�����N���X
-------------------------------------*/
class Application
{
public:
	Application(void);
	~Application(void);

public:
	bool StartUp(const HINSTANCE& hinstance, const int& nCmdShow);
	void Run(void);
	void ShutDown(void);

private:
	bool Init(void);
	void Uninit(void);

private:
	class ApplicationManager* app_manager_;

	std::string				window_title_;
	class Win32APIWindow*	app_window_;
	class DX9Graphics*		dx9_graphics_;
};


#endif //APPLICATION_H_
/*=============================================================================
/*		End of File
=============================================================================*/