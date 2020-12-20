/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Win32APIWindow.h] �E�B���h�E�����Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�E�B���h�E�����Ǘ��N���X
=============================================================================*/
#ifndef WIN32API_WINDOW_H_
#define	WIN32API_WINDOW_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "../Generic/Math.h"

/*-------------------------------------
/* �E�B���h�E�f�[�^�\����
-------------------------------------*/
struct WindowStyle
{
public:
	WindowStyle(void)
		: hInstance(nullptr)
		, nCmdShow(1)
		, dwWindowStyle(0UL)
		, hIcon(nullptr)
		, windowTitle("")
		, windowSize(Math::Vector2())
		, isWindowed(TRUE)
	{}

	~WindowStyle(void) {}

public:
	HINSTANCE	  hInstance;		//�C���X�^���X�n���h��
	int			  nCmdShow;			//�E�B���h�E�̕\�����
	DWORD		  dwWindowStyle;		//�E�B���h�E�̕\������
	HICON		  hIcon;			//�A�C�R���ւ̃C���X�^���X
	std::string   windowTitle;		//�E�B���h�E�^�C�g��
	Math::Vector2 windowSize;		//�E�B���h�E�T�C�Y
	BOOL		  isWindowed;		//�E�B���h�E�\�����邩�H
};


/*-------------------------------------
/* �E�B���h�E�����Ǘ��N���X
-------------------------------------*/
class Win32APIWindow
{
public:
	Win32APIWindow(void);
	~Win32APIWindow(void);

	static Win32APIWindow* Create();
	HWND CreateAppWindow(WindowStyle windowStyle);

public:
	Math::Vector2 CalculateWindowSize(const DWORD& dwWindowStyle
								     , const Math::Vector2& windowSize
								     , const BOOL isCreateSysMenu) const;

	Math::Vector2 CalculateWindowCreatePos(const Math::Vector2& windowSize) const;

	void SetWindowSize(const Math::Vector2& windowSize);
	void SetWindowSize(const float windowWidth, const float windowHeight);

	Math::Vector2 GetWindowSize(void) const;
	Math::Vector2 GetWindowClientSize(const HWND& wndHandle) const;

private:
	Math::Vector2 window_size_;
};

#endif //WIN32API_WINDOW_H_
/*=============================================================================
/*		End of File
=============================================================================*/