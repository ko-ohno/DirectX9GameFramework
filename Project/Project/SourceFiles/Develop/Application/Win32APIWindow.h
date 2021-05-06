/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Win32APIWindow.h] Win32API�E�B���h�E�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FWin32API�E�B���h�E�Ǘ��N���X
=============================================================================*/
#ifndef WIN32API_WINDOW_H_
#define	WIN32API_WINDOW_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "Math.h"

/*-------------------------------------
/* �E�B���h�E�f�[�^�\����
-------------------------------------*/
struct WindowStyle
{
public:
	WindowStyle(void)
		: hInstance(nullptr)
		, nShowCmd(1)
		, dwWindowStyle(0UL)
		, hIcon(nullptr)
		, windowTitle("")
		, windowSize(Vector2())
		, screen_scaler(1.f)
	{}

	~WindowStyle(void) {}

public:
	HINSTANCE	  hInstance;		//�C���X�^���X�n���h��
	int			  nShowCmd;			//�E�B���h�E�̕\�����
	DWORD		  dwWindowStyle;	//�E�B���h�E�̕\������
	HICON		  hIcon;			//�A�C�R���ւ̃C���X�^���X
	std::string   windowTitle;		//�E�B���h�E�^�C�g��
	Vector2		  windowSize;		//�E�B���h�E�T�C�Y
	float		  screen_scaler;	//��ʂ̊g�k�{��
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

	HWND CreateNewWindow(WindowStyle windowStyle, bool isAppWindow = false);

public:
	Vector2 CalculateWindowSize(const DWORD& dwWindowStyle
							   , const Vector2& windowSize
							   , const BOOL isCreateSysMenu) const;

	Vector2 CalculateFullScreenWindowSize(const DWORD& dwWindowStyle, const BOOL isCreateSysMenu) const;

	Vector2 CalculateWindowCreatePos(const Vector2& windowSize) const;

	void SetWindowSize(const Vector2& windowSize);
	void SetWindowSize(const float windowWidth, const float windowHeight);

	Vector2 GetWindowSize(void) const;
	Vector2 GetWindowClientSize(const HWND& windowHandle) const;
	Vector2 GetFullScreenSize(void) const;

private:
	WNDCLASSEX  wcex_;
	std::string window_class_name_;
	Vector2	    window_size_;
	HWND	    window_handle_;
};

#endif //WIN32API_WINDOW_H_
/*=============================================================================
/*		End of File
=============================================================================*/