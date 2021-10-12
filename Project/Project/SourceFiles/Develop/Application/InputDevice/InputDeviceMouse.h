/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceMouse.h] �}�E�X���̓N���X�̒�`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�}�E�X���͂ɂ�铮��N���X�̒�`
=============================================================================*/
#ifndef INPUT_DEVICE_MOUSE_H_
#define	INPUT_DEVICE_MOUSE_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "../Math.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/

/*-------------------------------------
/* �}�E�X���̓N���X
-------------------------------------*/
class InputDeviceMouse
{
public:
	InputDeviceMouse(void);
	~InputDeviceMouse(void);

	HRESULT CrateInputDeviceMouse(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle);

	void Update(const HWND &wndHandle);
	
	bool GetMBPress  (int mibNum);
	bool GetMBTrigger(int mibNum);
	bool GetMBRepeat (int mibNum);
	bool GetMBRelease(int mibNum);

	class Vector2 GetMCursorPos(void) const;

	// ���͎��Ԃ̐ݒ�
	void SetRepeatInputTime(float inputSeconds) { repeat_input_time_ = inputSeconds; }

private:
	void Init(void);
	void Uninit(void);

	void UpdateMouseState(const HWND &wndHandle);

private:
	// �}�E�X�̃{�^���̐�
	static constexpr int NUM_MB_MAX = 4;

	// �ő�FPS��
	static constexpr int MAX_FPS = 60;

	// �ő僊�s�[�g�t���[���� 
	int max_repeat_frame_count_;

	// ���͎���
	float repeat_input_time_;

	//�f�o�C�X���͗p
	static LPDIRECTINPUTDEVICE8	lpdinput_device_mouse_;		// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^
	static POINT mouse_cursor_pos_;
	DIMOUSESTATE dimouse_state_;
	DIMOUSESTATE dimouse_state_old_;

	BYTE mb_state_[NUM_MB_MAX];					// �}�E�X�̓��͏�񃏁[�N
	BYTE mb_state_trigger_[NUM_MB_MAX];			// �}�E�X�̃g���K�[��񃏁[�N
	BYTE mb_state_release_[NUM_MB_MAX];			// �}�E�X�̃����[�X��񃏁[�N
	BYTE mb_state_repeat_[NUM_MB_MAX];			// �}�E�X�̃��s�[�g��񃏁[�N
	int mb_state_repeat_count_[NUM_MB_MAX];		// �}�E�X�̃��s�[�g�J�E���^
};



#endif //INPUT_DEVICE_MOUSE_H_
/*=============================================================================
/*		End of File
=============================================================================*/
