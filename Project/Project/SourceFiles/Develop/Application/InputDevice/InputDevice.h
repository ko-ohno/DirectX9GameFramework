/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDevice.h] 入力デバイスの機能をまとめた管理クラス定義
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：キーボードや、ゲームパッドなどの処理を管理するクラス定義
=============================================================================*/
#ifndef INPUT_DEVICE_H_
#define	INPUT_DEVICE_H_

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"

/*--- 構造体定義 ---*/



/*-------------------------------------
/* 入力デバイス管理クラス
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

	static LPDIRECTINPUT8 lpdinput_object_;		// DirectInputオブジェクトへのポインタ
};


#endif //INPUT_DEVICE_H_
/*=============================================================================
/*		End of File
=============================================================================*/