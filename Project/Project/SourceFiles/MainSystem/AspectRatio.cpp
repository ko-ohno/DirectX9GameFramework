/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AspectRatio.cpp] ���W���[��
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "AspectRatio.h"
#include "Win32APIWindow.h"

//�A�X�y�N�g�䗦��16�F9�̔䗦�����{�ɂ������̒l
//1920:1080��16�F9��120�{�ɂ����l


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
AspectRatio::AspectRatio(void)
{
	//
	Win32APIWindow window;
	DWORD window_style = WS_POPUPWINDOW; //�t���X�N���[���̍ۂ̐ݒ�
	Vector2 fullscreen_aspect = window.CalculateFullScreenWindowSize(window_style, false);

	RECT fullscreen_padding;
	fullscreen_padding.left		= 0.0f;
	fullscreen_padding.right	= 2.0f;
	fullscreen_padding.top		= 0.0f;
	fullscreen_padding.bottom	= 2.0f;


	const float screen_padding_width = static_cast<float>(fullscreen_padding.left - fullscreen_padding.right);
	const float screen_padding_height = static_cast<float>(fullscreen_padding.top - fullscreen_padding.bottom);

	Vector2 true_fullscreen_aspect = { fullscreen_aspect.x_ -screen_padding_width
									 , fullscreen_aspect.y_ -screen_padding_height };


	int a = GetSystemMetrics(SM_CXSCREEN);
	int b = GetSystemMetrics(SM_CYSCREEN);


}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
AspectRatio::~AspectRatio(void)
{
}

/*-----------------------------------------------------------------------------
/* �A�X�y�N�g�䗦�̌v�Z
-----------------------------------------------------------------------------*/
Vector2* AspectRatio::CaiculationAspectRatio(const DWORD& dwWindowStyle)
{
	DWORD winodw_style = WS_POPUPWINDOW;
	


	//��ʂ̃t���X�N���[���̃T�C�Y���擾

	//���̃T�C�Y��{��1.00�Ƃ��A���Ԃ�0.25���������l���������킹��

	std::unordered_map<std::string, int> a;
	std::vector<float> vec_array_float = {0.5f, 0.6f, 0.7f, 0.8f, 1.0f};
	
	auto iter = vec_array_float.begin();

	a.emplace(std::to_string(1), 999);

	return NEW Vector2();
}

/*-----------------------------------------------------------------------------
/* �t���X�N���[���̃E�B���h�E�T�C�Y�̎擾
-----------------------------------------------------------------------------*/
Vector2* AspectRatio::GetFullScreenWindowSize(const DWORD& dwWindowStyle)
{
	Win32APIWindow window;
	return NEW Vector2(window.CalculateFullScreenWindowSize(dwWindowStyle, false));
}

/*=============================================================================
/*		End of File
=============================================================================*/