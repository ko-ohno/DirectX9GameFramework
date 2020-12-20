/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Win32APIWindow.cpp] ���W���[��
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "Win32APIWindow.h"
#include "../Generic/Math.h"

/*--- �֐��v���g�^�C�v ---*/
//WinAPI
//�ʏ�E�B���h�E�ƃt���X�N���[���E�B���h�E�̃R�[���o�b�N�֐������p�ɂ���(���������̂���)
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Win32APIWindow::Win32APIWindow(void)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Win32APIWindow::~Win32APIWindow(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
Win32APIWindow* Win32APIWindow::Create(void)
{
	return NEW Win32APIWindow();
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E��������
-----------------------------------------------------------------------------*/
HWND Win32APIWindow::CreateAppWindow(WindowStyle windowStyle)
{
	/*--- �E�B���h�E�N���X�̖��O�̒�` ---*/
	const char* WINDOW_CLASS_NAME = { "AppWindow" };
				
	/*------------------------------------
	// �E�B���h�E�N���X�o�^
	------------------------------------*/
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX)						//�\���̂ɕK�v�ȃo�C�g�����`
		, (CS_VREDRAW | CS_HREDRAW)				//�E�B���h�E�̃X�^�C��
		, WindowProcedure						//�R�[���o�b�N�֐��ւ̃|�C���^
		, 0										//�E�B���h�E�N���X�\���̂̌��Ɋ��蓖�Ă�⑫�̃o�C�g��
		, 0										//�E�B���h�E�C���X�^���̌��Ɋ��蓖�Ă�⑫�̃o�C�g��
		, windowStyle.hInstance					//���̃E�B���h�E�N���X�̂��߂̃E�C���h�E�v���V�[�W��������C���X�^���X�n���h��
		, windowStyle.hIcon						//�A�C�R���̃n���h��
		, LoadCursor(NULL, IDC_ARROW)			//�W���̃J�[�\����ǂݍ��ށB
		, (HBRUSH)(COLOR_WINDOW + 1)			//�N���C�A���g�̈�Ƀf�t�H���g�̐F���������ށB
		, NULL									//���j���[�n���h�����\���ɂ���B
		, WINDOW_CLASS_NAME						//�E�B���h�E�N���X���B
		, NULL									//�A�C�R���n���h���B
	};	

	//�E�B���h�E�N���X�̍ŏI�I�ȓo�^
	if (!RegisterClassEx(&wcex))
	{
		return nullptr;
	}

	/*--- �E�B���h�E�T�C�Y�̌v�Z ---*/
	//�E�B���h�E�̃X�^�C���Ǝw�肵���T�C�Y�ƃ��j���[�̐����̗L�����v�Z�B
	const Math::Vector2 true_window_size = CalculateWindowSize(windowStyle.dwWindowStyle, windowStyle.windowSize, FALSE);

	//�E�B���h�E�̒��S���W���f�X�N�g�b�v�̒��S���W�ɂȂ�悤�ɁA�f�X�N�g�b�v��ł̃E�B���h�E�̍��㐶�����W���v�Z�B
	const Math::Vector2 window_create_pos = CalculateWindowCreatePos(true_window_size);

	/*------------------------------------
	// �E�B���h�E�n���h���̍쐬
	------------------------------------*/
	HWND window_handle = CreateWindowEx(0										//�E�B���h�E�g���X�^�C��
									   , WINDOW_CLASS_NAME						//RegisterClassEx()�œo�^�����N���X�̖��O
									   , windowStyle.windowTitle.c_str()		//�^�C�g���o�[�ɕ\�����镶����
									   , windowStyle.dwWindowStyle				//�E�C���h�E�X�^�C��
									   , (int)window_create_pos.x_				//�E�C���h�E����x���W
									   , (int)window_create_pos.y_				//�E�C���h�E����y���W
									   , (int)true_window_size.x_				//�E�C���h�E�̕�
									   , (int)true_window_size.y_				//�E�C���h�E�̍���
									   , NULL									//�e�E�B���h�E�̃n���h��
									   , NULL									//���j���[�̃n���h��
									   , windowStyle.hInstance					//�E�C���h�E�Ȃǂ��쐬���郂�W���[���̃C���X�^���X�̃n���h��
									   , NULL);									//WM_CREATE��LPARAM�ɓn�������l
	

	//�E�B���h�E����
	ShowWindow(window_handle, windowStyle.nCmdShow);
	UpdateWindow(window_handle);

	return window_handle;
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E�T�C�Y�̌v�Z
-----------------------------------------------------------------------------*/
Math::Vector2 Win32APIWindow::CalculateWindowSize(const DWORD& dwWindowStyle, const Math::Vector2& windowSize, const BOOL isCreateSysMenu) const
{
	/*--- �E�B���h�E�T�C�Y�̎w�� ---*/
	RECT window_rect = { 0L, 0L, (LONG)windowSize.x_, (LONG)windowSize.y_ }; //�E�B���h�E�̃X�^�C���ɂ��T�C�Y�̌덷���v�Z
	AdjustWindowRect(&window_rect, dwWindowStyle, isCreateSysMenu);

	//�E�B���h�E�̔�N���C�A���g�̈�̕��ƍ������l�������N���C�A���g�̈�̌v�Z�B
	Math::Vector2 true_window_size;
	true_window_size.x_ = (float)window_rect.right - (float)window_rect.left;
	true_window_size.y_ = (float)window_rect.bottom - (float)window_rect.top;

	return true_window_size;
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E���W(�f�X�N�g�b�v��)�̌v�Z
-----------------------------------------------------------------------------*/
Math::Vector2 Win32APIWindow::CalculateWindowCreatePos(const Math::Vector2& windowSize) const
{
	Math::Vector2 create_window_pos;

	//�f�X�N�g�b�v�̃N���C�A���g�̈�̑傫��(��ʉ𑜓x)���擾����B
	RECT desk_top_clientsize;
	GetWindowRect(GetDesktopWindow(), &desk_top_clientsize);

	//�E�B���h�E�̒��S���W���f�X�N�g�b�v�̒��S���W�ɂȂ�悤�ɁA�f�X�N�g�b�v��ł̃E�B���h�E�̍��㐶�����W���v�Z�B
	create_window_pos.x_ = ((desk_top_clientsize.right - desk_top_clientsize.left) - windowSize.x_) / 2;
	create_window_pos.y_ = ((desk_top_clientsize.bottom - desk_top_clientsize.top) - windowSize.y_) / 2;

	return create_window_pos;
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E�T�C�Y�̐ݒ�
-----------------------------------------------------------------------------*/
void Win32APIWindow::SetWindowSize(const Math::Vector2& windowSize)
{
	window_size_ = windowSize;
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E�T�C�Y�̐ݒ�
-----------------------------------------------------------------------------*/
void Win32APIWindow::SetWindowSize(const float windowWidth, const float windowHeight)
{
	window_size_.x_ = windowWidth;
	window_size_.y_ = windowHeight;
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E�̎擾
-----------------------------------------------------------------------------*/
Math::Vector2 Win32APIWindow::GetWindowSize(void) const
{
	return window_size_;
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E�̃N���C�A���g�̈�T�C�Y�̎擾
-----------------------------------------------------------------------------*/
Math::Vector2 Win32APIWindow::GetWindowClientSize(const HWND& wndHandle) const
{
	Math::Vector2 true_client_size;
	RECT wnd_client_size;

	//�N���C�A���g�T�C�Y�̎擾
	GetClientRect(wndHandle, &wnd_client_size);

	//�N���C�A���g�̈�̕��ƍ����̌v�Z
	true_client_size.x_ = (float)wnd_client_size.right - (float)wnd_client_size.left;
	true_client_size.y_ = (float)wnd_client_size.bottom - (float)wnd_client_size.top;

	return true_client_size;
}

/*-----------------------------------------------------------------------------
/*	�E�B���h�E�v���V�[�W���\
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//#if defined(_DEBUG)||(DEBUG)
//	//ImGui�ɑ���𔽉f�����邽�߂̃E�B���h�E
//	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) { return true; }
//#else
//	ShowCursor(FALSE);//�J�[�\�����\����
//#endif //  _DEBUG


	//�E�B���h�E�̃��b�Z�[�W���[�v���I��������id
	int window_kill_id;

	switch (uMsg)
	{
	case WM_CREATE: //�E�B���h�E�������߂̎��s��
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: //Esc�L�[����

#if defined(_DEBUG)||(DEBUG)	//�f�o�b�O�r���h����Msgbox���\���ɂ���B
			DestroyWindow(hWnd);
#endif
			//�I�����b�Z�[�W�̕\��
			window_kill_id = MessageBox(hWnd, "�I�����܂����H", "�x��", (MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONWARNING));
			if (window_kill_id != IDCANCEL) { DestroyWindow(hWnd); }
			break;
		}
		break;

	default:
#if defined(_DEBUG)||(DEBUG)
		//imgui	
		//�f�o�C�X���X�g�����Ƃ��ɍs������
		//ImGui_ImplDX9_InvalidateDeviceObjects();
		//ImGui_ImplDX9_CreateDeviceObjects();
#endif //  _DEBUG
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*=============================================================================
/*		End of File
=============================================================================*/