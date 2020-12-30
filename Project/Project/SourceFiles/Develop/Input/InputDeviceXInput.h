/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceXInput.h] �Q�[���p�b�h(XInput)�̏�Ԏ擾�N���X��`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FXInput�̃Q�[���p�b�h�̏�Ԃ��擾����N���X��`
=============================================================================*/
#ifndef INPUT_DEVICE_XINPUT_H_
#define	INPUT_DEVICE_XINPUT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include <Xinput.h>

//XINPUT�R���g���[���̂��߂̃��C�u�����������N
#pragma comment(lib,"xinput.lib")	

/*--- �\���̌^��` ---*/
typedef struct
{
	XINPUT_STATE pad_state_;
	XINPUT_STATE pad_state_old_;
	bool is_pad_conected_;
}XinputController;

//�g���K�[�̔ԍ���Ǝ��ɒ�`
#define XINPUT_GAMEPAD_LEFT_TRIGGER  0x0400
#define XINPUT_GAMEPAD_RIGHT_TRIGGER 0x0800
#define XINPUT_GAMEPAD_BUTTON_MAX    (16)

/*--- �N���X�̑O���錾 ---*/

/*-------------------------------------
/* Xinput�Q�[���p�b�h�p
-------------------------------------*/
enum class XInputButton
{
	XIB_UP				= XINPUT_GAMEPAD_DPAD_UP,
	XIB_DOWN			= XINPUT_GAMEPAD_DPAD_DOWN,
	XIB_LEFT			= XINPUT_GAMEPAD_DPAD_LEFT,
	XIB_RIGHT			= XINPUT_GAMEPAD_DPAD_RIGHT,

	XIB_START			= XINPUT_GAMEPAD_START,
	XIB_BACK			= XINPUT_GAMEPAD_BACK,

	XIB_LEFT_THUMB		= XINPUT_GAMEPAD_LEFT_THUMB,
	XIB_RIGHT_THUMB		= XINPUT_GAMEPAD_RIGHT_THUMB,

	XIB_LEFT_SHOULDER	= XINPUT_GAMEPAD_LEFT_SHOULDER,
	XIB_RIGHT_SHOULDER	= XINPUT_GAMEPAD_RIGHT_SHOULDER,

	XIB_LEFT_TRIGGER	= XINPUT_GAMEPAD_LEFT_TRIGGER,
	XIB_RIGHT_TRIGGER	= XINPUT_GAMEPAD_RIGHT_TRIGGER,

	XIB_A = XINPUT_GAMEPAD_A,
	XIB_B = XINPUT_GAMEPAD_B,
	XIB_X = XINPUT_GAMEPAD_X,
	XIB_Y = XINPUT_GAMEPAD_Y,

	XIB_MAX = XINPUT_GAMEPAD_BUTTON_MAX,
};

/*-------------------------------------
/* Xinput�Q�[���p�b�h�N���X
-------------------------------------*/
class InputDeviceXInput
{
public:
	InputDeviceXInput(void);
	~InputDeviceXInput(void);

	void Init(void);
	void Update(void);

	//�X�e�B�b�N�̓��͂��擾
	double GetThumbLX(int padIndex);
	double GetThumbLY(int padIndex);
	double GetThumbRX(int padIndex);
	double GetThumbRY(int padIndex);

	//�p�b�h�̃{�^�����͂��擾
	bool GetXIBPress  (int padIndex, XInputButton xibIndex);
	bool GetXIBTrigger(int padIndex, XInputButton xibIndex);
	bool GetXIBRelease(int padIndex, XInputButton xibIndex);
	bool GetXIBRepeat (int padIndex, XInputButton xibIndex);

private:
	HRESULT UpdateGamepadEntity(void);
	void GamepadIdleState(void);

	void SetBothThumbDeadZone (int padIndex);
	void SetRightThumbDeadZone(int padIndex);
	void SetLeftThumbDeadZone (int padIndex);

	void SetBothTriggerState(int padIndex);
	void SetLTriggerState(int padIndex);
	void SetRTriggerState(int padIndex);

private:
	static constexpr int  MAX_GAMEPAD_CONNECTION = 4;
	XinputController xinput_gamepad_[MAX_GAMEPAD_CONNECTION];

	static constexpr WORD INPUT_DEADZONE = 7864;
	static constexpr int  LIMIT_COUNT_REPEAT = 20;

	WORD xib_state_press_  [MAX_GAMEPAD_CONNECTION];
	WORD xib_state_trigger_[MAX_GAMEPAD_CONNECTION];
	WORD xib_state_release_[MAX_GAMEPAD_CONNECTION];
	WORD xib_state_repeat_ [MAX_GAMEPAD_CONNECTION];
	int  xib_state_repeat_count_[MAX_GAMEPAD_CONNECTION]; // ���s�[�g�̃J�E���^

};


#endif //INPUT_DEVICE_XINPUT_H_
/*=============================================================================
/*		End of File
=============================================================================*/

