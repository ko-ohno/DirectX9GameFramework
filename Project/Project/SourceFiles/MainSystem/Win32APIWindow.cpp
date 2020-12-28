/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Win32APIWindow.cpp] Win32API�E�B���h�E�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FWin32API�E�B���h�E�Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "Win32APIWindow.h"
#include "../ImGui/ImGuiManager.h"
#include "../Generic/Math.h"

/*--- �֐��v���g�^�C�v ---*/
//Win32�A�v���P�[�V�����̃��b�Z�[�W�n���h���[
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Win32APIWindow::Win32APIWindow(void)
	: wcex_(WNDCLASSEX())
	, window_class_name_("")
	, window_size_(0.f, 0.f)
	, window_handle_(nullptr)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Win32APIWindow::~Win32APIWindow(void)
{
	//�o�^�����E�B���h�E�N���X�̓o�^����
	UnregisterClass(wcex_.lpszClassName, wcex_.hInstance);
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
HWND Win32APIWindow::CreateNewWindow(WindowStyle windowStyle, bool isAppWindow)
{
	//�E�B���h�E�N���X�̖��O��`				
	if (isAppWindow)
	{
		window_class_name_ = "AppWindow";
	}
	else
	{
		window_class_name_ = "SplashScreenWindow";
	}


	/*------------------------------------
	// �E�B���h�E�N���X�o�^
	------------------------------------*/
	wcex_ = {
		sizeof(WNDCLASSEX)						//�\���̂ɕK�v�ȃo�C�g�����`
		, (CS_VREDRAW | CS_HREDRAW)				//�E�B���h�E�̃X�^�C��
		, WindowProcedure						//�R�[���o�b�N�֐��ւ̃|�C���^
		, 0										//�E�B���h�E�N���X�\���̂̌��Ɋ��蓖�Ă�⑫�̃o�C�g��
		, 0										//�E�B���h�E�C���X�^���̌��Ɋ��蓖�Ă�⑫�̃o�C�g��
		, windowStyle.hInstance					//���̃E�B���h�E�N���X�̂��߂̃E�C���h�E�v���V�[�W��������C���X�^���X�n���h��
		, windowStyle.hIcon						//�A�C�R���̃n���h��
		, LoadCursor(nullptr, IDC_ARROW)		//�W���̃J�[�\����ǂݍ��ށB
		, (HBRUSH)(COLOR_WINDOW + 1)			//�N���C�A���g�̈�Ƀf�t�H���g�̐F���������ށB
		, nullptr								//���j���[�n���h�����\���ɂ���B
		, window_class_name_.c_str()			//�E�B���h�E�N���X���B
		, nullptr								//�A�C�R���n���h���B
	};	

	//�E�B���h�E�N���X�̍ŏI�I�ȓo�^
	if (!RegisterClassEx(&wcex_))
	{
		assert(!"�E�B���h�E�N���X�̓o�^�Ɏ��s�I�I");
		return nullptr;
	}

	/*--- �E�B���h�E�T�C�Y�̌v�Z ---*/
	Vector2 true_window_size;

	//�t���X�N���[���ł��邩
	const bool is_full_screen = ((windowStyle.dwWindowStyle == WS_POPUPWINDOW)
								 && (windowStyle.windowSize == this->GetFullScreenSize()));

	if (is_full_screen)
	{	
		//�t���X�N���[���Ƃ��Ă��̂܂܃T�C�Y����
		true_window_size = windowStyle.windowSize;
	}
	else
	{
		//�E�B���h�E�̃X�^�C���Ǝw�肵���T�C�Y�ƃ��j���[�̐����̗L�����v�Z�B
		true_window_size = CalculateWindowSize(windowStyle.dwWindowStyle, windowStyle.windowSize, FALSE);
	}

	//�E�B���h�E�T�C�Y�̓o�^
	this->SetWindowSize(true_window_size);

	//�E�B���h�E�̒��S���W���f�X�N�g�b�v�̒��S���W�ɂȂ�悤�ɁA�f�X�N�g�b�v��ł̃E�B���h�E�̍��㐶�����W���v�Z�B
	const Vector2 window_create_pos = CalculateWindowCreatePos(true_window_size);

	/*------------------------------------
	// �E�B���h�E�n���h���̍쐬
	------------------------------------*/
	window_handle_ = CreateWindowEx(0										//�E�B���h�E�g���X�^�C��
								   , window_class_name_.c_str()				//RegisterClassEx()�œo�^�����N���X�̖��O
								   , windowStyle.windowTitle.c_str()		//�^�C�g���o�[�ɕ\�����镶����
								   , windowStyle.dwWindowStyle				//�E�C���h�E�X�^�C��
								   , (int)window_create_pos.x_				//�E�C���h�E����x���W
								   , (int)window_create_pos.y_				//�E�C���h�E����y���W
								   , (int)true_window_size.x_				//�E�C���h�E�̕�
								   , (int)true_window_size.y_				//�E�C���h�E�̍���
								   , nullptr								//�e�E�B���h�E�̃n���h��
								   , nullptr								//���j���[�̃n���h��
								   , windowStyle.hInstance					//�E�C���h�E�Ȃǂ��쐬���郂�W���[���̃C���X�^���X�̃n���h��
								   , nullptr);								//WM_CREATE��LPARAM�ɓn�������l
								
	//�E�B���h�E�\��
	ShowWindow(window_handle_, windowStyle.nShowCmd);
	UpdateWindow(window_handle_);

	return window_handle_;
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E�T�C�Y�̌v�Z
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::CalculateWindowSize(const DWORD& dwWindowStyle, const Vector2& windowSize, const BOOL isCreateSysMenu) const
{
	/*--- �E�B���h�E�T�C�Y�̎w�� ---*/
	RECT window_rect = { 0L, 0L, (LONG)windowSize.x_, (LONG)windowSize.y_ }; //�E�B���h�E�̃X�^�C���ɂ��T�C�Y�̌덷���v�Z
	AdjustWindowRect(&window_rect, dwWindowStyle, isCreateSysMenu);

	//�E�B���h�E�̔�N���C�A���g�̈�̕��ƍ������l�������N���C�A���g�̈�̌v�Z�B
	Vector2 true_window_size;
	true_window_size.x_ = (float)window_rect.right - (float)window_rect.left;
	true_window_size.y_ = (float)window_rect.bottom - (float)window_rect.top;

	return true_window_size;
}

/*-----------------------------------------------------------------------------
/* �t���X�N���[���̃E�B���h�E�T�C�Y�̌v�Z
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::CalculateFullScreenWindowSize(const DWORD& dwWindowStyle, const BOOL isCreateSysMenu) const
{
	//�t���X�N���[���̎�
	//�f�X�N�g�b�v�̃N���C�A���g�̈�̑傫��(��ʉ𑜓x)���擾����B
	RECT desk_top_clientsize;
	GetWindowRect(GetDesktopWindow(), &desk_top_clientsize);
	AdjustWindowRect(&desk_top_clientsize, dwWindowStyle, isCreateSysMenu);

	//��ʉ𑜓x����t���X�N���[���̃T�C�Y���v�Z����B
	Vector2 full_screen_window_size;
	full_screen_window_size.x_ = (float)(desk_top_clientsize.right - desk_top_clientsize.left);
	full_screen_window_size.y_ = (float)(desk_top_clientsize.bottom - desk_top_clientsize.top);

	return full_screen_window_size;
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E���W(�f�X�N�g�b�v��)�̌v�Z
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::CalculateWindowCreatePos(const Vector2& windowSize) const
{
	Vector2 create_window_pos;

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
void Win32APIWindow::SetWindowSize(const Vector2& windowSize)
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
Vector2 Win32APIWindow::GetWindowSize(void) const
{
	return window_size_;
}

/*-----------------------------------------------------------------------------
/* �E�B���h�E�̃N���C�A���g�̈�T�C�Y�̎擾
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::GetWindowClientSize(const HWND& windowHandle) const
{
	Vector2 true_client_size;
	RECT wnd_client_size;

	//�N���C�A���g�T�C�Y�̎擾
	GetClientRect(windowHandle, &wnd_client_size);

	//�N���C�A���g�̈�̕��ƍ����̌v�Z
	true_client_size.x_ = (float)wnd_client_size.right - (float)wnd_client_size.left;
	true_client_size.y_ = (float)wnd_client_size.bottom - (float)wnd_client_size.top;

	return true_client_size;
}

/*-----------------------------------------------------------------------------
/* �t���X�N���[���̉�ʃT�C�Y���擾
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::GetFullScreenSize(void) const
{
	int desktop_width  = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);
	return Vector2(static_cast<const float>(desktop_width)
				  , static_cast<const float>(desktop_height));
}

//ImGui�̃��b�Z�[�W�n���h���[
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*-----------------------------------------------------------------------------
/*	�E�B���h�E�̃��b�Z�[�W�n���h���[
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//ImGui�ɑ���𔽉f�����邽�߂̃E�B���h�E�v���V�[�W���[
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) { return true; }

	//�E�B���h�E�̃��b�Z�[�W���[�v���I��������id
	int window_kill_id;

	switch (uMsg)
	{
	case WM_CREATE: //�E�B���h�E�������߂̎��s��
		break;

	case WM_CLOSE:	//�E�B���h�E�~�{�^������

#if defined(_DEBUG)||(DEBUG)	//�f�o�b�O�r���h����Msgbox���\���ɂ���B
		DestroyWindow(hWnd);
#endif
		//�I�����b�Z�[�W�̕\��
		window_kill_id = MessageBox(hWnd, "�Q�[�����I�����܂����H", "�x��", (MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONWARNING));
		if (window_kill_id != IDCANCEL) { DestroyWindow(hWnd); }
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
			window_kill_id = MessageBox(hWnd, "�Q�[�����I�����܂����H", "�x��", (MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONWARNING));
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