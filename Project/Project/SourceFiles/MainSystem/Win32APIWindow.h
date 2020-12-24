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
#include "../Generic/Math.h"

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
	{}

	~WindowStyle(void) {}

public:
	HINSTANCE	  hInstance;		//�C���X�^���X�n���h��
	int			  nShowCmd;			//�E�B���h�E�̕\�����
	DWORD		  dwWindowStyle;	//�E�B���h�E�̕\������
	HICON		  hIcon;			//�A�C�R���ւ̃C���X�^���X
	std::string   windowTitle;		//�E�B���h�E�^�C�g��
	Vector2		  windowSize;		//�E�B���h�E�T�C�Y
};


/*-------------------------------------
/* �E�B���h�E�T�C�Y��ID
-------------------------------------*/
enum class window_size_id
{
	None = -1
	, SPLASH_SCREEN_500x600
	, _1280x_720 
	, _1920x1080
	, FULL_SCREEN
	, MAX
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

	Vector2 FindWindowSize(window_size_id id) const;

	void SetWindowSize(const Vector2& windowSize);
	void SetWindowSize(const float windowWidth, const float windowHeight);

	Vector2 GetWindowSize(void) const;
	Vector2 GetWindowClientSize(const HWND& windowHandle) const;

private:
	Vector2 window_size_;
	HWND	window_handle_;
};

#endif //WIN32API_WINDOW_H_
/*=============================================================================
/*		End of File
=============================================================================*/