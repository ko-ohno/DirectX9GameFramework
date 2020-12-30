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
#include "../StdAfx.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/
class InputDeviceKeyboard;
class InputDeviceMouse;
class InputDeviceXInput;

/*-------------------------------------
/* 入力デバイス管理クラス
-------------------------------------*/
class InputDevice
{
public:
	InputDevice(void);
	~InputDevice(void);

	static InputDevice * Create(void);

	void CreateInputDevice(const HINSTANCE &hInstance, const HWND &wndHandle);

	void Update(const HWND &wndHandle);

	static InputDeviceKeyboard	*GetDeviceInstanceKeyboard(void);
	static InputDeviceMouse		*GetDeviceInstanceMouse(void);
	static InputDeviceXInput	*GetDeviceInstanceXInput(void);

private:
	void Init(void);
	void Uninit(void);

	HRESULT CreateDirectInputObject(const HINSTANCE &hInstance);

	void CreateDeviceKyeboard(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle);
	void CreateDeviceMouse(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle);
	void CreateDeviceXInput(void);

private:
	static InputDeviceKeyboard	* input_device_keyboard_;
	static InputDeviceMouse		* input_device_mouce_;
	static InputDeviceXInput	* input_device_xinput_;

	static LPDIRECTINPUT8		lpdinput_object_;		// DirectInputオブジェクトへのポインタ
};


#endif //INPUT_DEVICE_H_
/*=============================================================================
/*		End of File
=============================================================================*/