/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDevice.h] ���̓f�o�C�X�̋@�\���܂Ƃ߂��Ǘ��N���X��`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�L�[�{�[�h��A�Q�[���p�b�h�Ȃǂ̏������Ǘ�����N���X��`
=============================================================================*/
#ifndef INPUT_DEVICE_H_
#define	INPUT_DEVICE_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"

/*--- �\���̒�` ---*/



/*-------------------------------------
/* ���̓f�o�C�X�Ǘ��N���X
-------------------------------------*/
class InputDevice
{
public:
	InputDevice(void);
	~InputDevice(void);

	static InputDevice * Create(void);

	bool CreateInputDevice(const HINSTANCE &hInstance, const HWND &wndHandle);

	void Update(const HWND &wndHandle);

	static class InputDeviceKeyboard* GetDeviceInstanceKeyboard(void);
	static class InputDeviceMouse*	  GetDeviceInstanceMouse(void);
	static class InputDeviceXInput*	  GetDeviceInstanceXInput(void);

private:
	void Init(void);
	void Uninit(void);

	HRESULT CreateDirectInputObject(const HINSTANCE &hInstance);

	bool CreateDeviceKyeboard(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle);
	bool CreateDeviceMouse(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle);
	bool CreateDeviceXInput(void);

private:
	static class InputDeviceKeyboard* input_device_keyboard_;
	static class InputDeviceMouse*	  input_device_mouce_;
	static class InputDeviceXInput*	  input_device_xinput_;

	static LPDIRECTINPUT8 lpdinput_object_;		// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
};


#endif //INPUT_DEVICE_H_
/*=============================================================================
/*		End of File
=============================================================================*/