/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDevice.cpp] 入力デバイス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：入力デバイス管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "InputDevice.h"
#include "InputDeviceKeyboard.h"
#include "InputDeviceMouse.h"
#include "InputDeviceXInput.h"

//静的変数宣言
InputDeviceKeyboard	* InputDevice::input_device_keyboard_;
InputDeviceMouse	* InputDevice::input_device_mouce_;
InputDeviceXInput	* InputDevice::input_device_xinput_;

// IDirectInput8インターフェースへのポインタ
LPDIRECTINPUT8			InputDevice::lpdinput_object_;

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
InputDevice::InputDevice()
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
InputDevice::~InputDevice()
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
InputDevice * InputDevice::Create(void)
{
	return NEW InputDevice();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
void InputDevice::Init(void)
{
	//入力オブジェクト
	lpdinput_object_		= nullptr;

	//各入力デバイスへのポインタ
	input_device_mouce_		= nullptr;
	input_device_keyboard_	= nullptr;
	input_device_xinput_	= nullptr;
}

/*-----------------------------------------------------------------------------
/* 終了処理
-----------------------------------------------------------------------------*/
void InputDevice::Uninit(void)
{	
	// lpdinput_object_ptr_オブジェクトの開放
	SAFE_RELEASE_(lpdinput_object_);

	//各デバイスの破棄
	SAFE_DELETE_(input_device_keyboard_); 
	SAFE_DELETE_(input_device_mouce_); 
	SAFE_DELETE_(input_device_xinput_); 
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void InputDevice::Update(const HWND &wndHandle)
{
	//各入力デバイスの更新　
	input_device_keyboard_->Update();
	input_device_mouce_->Update(wndHandle);
	input_device_xinput_->Update();
}

/*-----------------------------------------------------------------------------
/* キーボードのインスタンスを取得
-----------------------------------------------------------------------------*/
InputDeviceKeyboard * InputDevice::GetDeviceInstanceKeyboard(void)
{
	return input_device_keyboard_;
}

/*-----------------------------------------------------------------------------
/* マウスのインスタンスを取得
-----------------------------------------------------------------------------*/
InputDeviceMouse * InputDevice::GetDeviceInstanceMouse(void)
{
	return input_device_mouce_;
}

/*-----------------------------------------------------------------------------
/* コントローラーのインスタンスを取得
-----------------------------------------------------------------------------*/
InputDeviceXInput * InputDevice::GetDeviceInstanceXInput(void)
{
	return input_device_xinput_;
}

/*-----------------------------------------------------------------------------
/* 入力デバイスの生成
-----------------------------------------------------------------------------*/
bool InputDevice::CreateInputDevice(const HINSTANCE &hInstance, const HWND &wndHandle)
{
	//入力デバイスの生成
	{
		//DirectInputインターフェースオブジェクトの生成
		if (FAILED(CreateDirectInputObject(hInstance)))
		{
			return false;
		}

		//キーボードの生成
		if (CreateDeviceKyeboard(lpdinput_object_, wndHandle) == false)
		{
			return false;
		}

		//マウスの入力生成
		if (CreateDeviceMouse(lpdinput_object_, wndHandle) == false)
		{
			return false;
		}

		//パッドの入力生成
		if (CreateDeviceXInput() == false)
		{
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* DirectInputObjectの生成
-----------------------------------------------------------------------------*/
HRESULT InputDevice::CreateDirectInputObject(const HINSTANCE &hInstance)
{
	if(hInstance == nullptr) { assert(!"DirectInuputオブジェクト生成時に、hInstanceがnullptrでした。"); }
	if (lpdinput_object_ == nullptr)
	{
		// Direct8Inputインターフェースオブジェクトの作成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&lpdinput_object_, nullptr)))
		{
			return S_FALSE;
		};
	}
	return S_OK;
}

/*-----------------------------------------------------------------------------
/* キーボード用入力デバイスの生成
-----------------------------------------------------------------------------*/
bool InputDevice::CreateDeviceKyeboard(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle)
{
	this->input_device_keyboard_ = NEW InputDeviceKeyboard();
	if (FAILED(input_device_keyboard_->CreateDeviceKeyboard(lpdinputObject, wndHandle)))
	{
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* マウス用入力デバイスの生成
-----------------------------------------------------------------------------*/
bool InputDevice::CreateDeviceMouse(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle)
{
	this->input_device_mouce_ = NEW InputDeviceMouse();
	if (FAILED(input_device_mouce_->CrateInputDeviceMouse(lpdinputObject, wndHandle)))
	{
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* XInputタイプのコントローラ用入力デバイスの生成
-----------------------------------------------------------------------------*/
bool InputDevice::CreateDeviceXInput(void)
{
	this->input_device_xinput_ = NEW InputDeviceXInput();
	{
		input_device_xinput_->Update();
	}
	return true;
}

/*==============================================================================
/*		End of file
==============================================================================*/
