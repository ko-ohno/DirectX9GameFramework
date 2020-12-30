/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceKeyboard.h] �L�[�{�[�h�ւ̓��͊Ǘ��N���X��`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�L�[���͂̍X�V�A�L�[�{�[�h�̏��������s���N���X��`�B
=============================================================================*/
#ifndef INPUT_DEVICE_KEYBOARD_H_
#define	INPUT_DEVICE_KEYBOARD_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "StdAfx.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �L�[�{�[�h���̓N���X
-------------------------------------*/
class InputDeviceKeyboard
{
public:
	InputDeviceKeyboard();
	~InputDeviceKeyboard();

	void Init(void);
	
	HRESULT CreateDeviceKeyboard(const LPDIRECTINPUT8 &lpdinput_interface_object, const HWND &wndHandle);
	void Uninit(void);
	void Update(void);

	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	bool GetKeyboardRepeat(int nKey);
	bool GetKeyboardRelease(int nKey);

private:
	static constexpr int LIMIT_COUNT_REPEAT = 20;
	static constexpr int NUM_KEY_MAX = 256;			//�L�[�̍ő�����

	static LPDIRECTINPUTDEVICE8	lpdinput_device_keyboard_;	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^

	BYTE key_state_[NUM_KEY_MAX];				// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE key_state_trigger_[NUM_KEY_MAX];		// �L�[�{�[�h�̃g���K�[��񃏁[�N
	BYTE key_state_release_[NUM_KEY_MAX];		// �L�[�{�[�h�̃����[�X��񃏁[�N
	BYTE key_state_repeat_[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
	int	 key_state_repeat_count_[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
};



#endif //INPUT_DEVICE_KEYBOARD_H_
/*==============================================================================
//		End of file
==============================================================================*/
