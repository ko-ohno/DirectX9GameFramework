/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputCheck.cpp] 入力情報中継クラス実装部
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：デバイスによる入力情報を中継するクラス実装部
=============================================================================*/

/*--- インクルードファイル ---*/
#include "InputCheck.h"
#include "InputDevice.h"
#include "InputDeviceKeyboard.h"
#include "InputDeviceMouse.h"
#include "../Math.h"

//静的変数宣言
InputDevice *InputCheck::input_device_;

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
InputCheck::InputCheck(void)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
InputCheck::~InputCheck(void)
{
}

/*-----------------------------------------------------------------------------
/* デバイスの状態を更新
-----------------------------------------------------------------------------*/
void InputCheck::SetInputDeviceInstance(InputDevice * inputDevice)
{
	input_device_ = inputDevice;
}

/*-----------------------------------------------------------------------------
/* ボタンを押したら
-----------------------------------------------------------------------------*/
bool InputCheck::KeyPress(int dikKeynum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceKeyboard()->GetKeyboardPress(dikKeynum);
}

/*-----------------------------------------------------------------------------
/* ボタンを押した瞬間
-----------------------------------------------------------------------------*/
bool InputCheck::KeyTrigger(int dikKeynum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceKeyboard()->GetKeyboardTrigger(dikKeynum);
}

/*-----------------------------------------------------------------------------
/* ボタン押し続けていたら
-----------------------------------------------------------------------------*/
bool InputCheck::KeyRepeat(int dikKeynum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceKeyboard()->GetKeyboardRepeat(dikKeynum);
}

/*-----------------------------------------------------------------------------
/* ボタン開放検知処理
-----------------------------------------------------------------------------*/
bool InputCheck::KeyRelease(int dikKeynum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceKeyboard()->GetKeyboardRelease(dikKeynum);
}

/*-----------------------------------------------------------------------------
/* ボタンを押したら
-----------------------------------------------------------------------------*/
bool InputCheck::MButtonPress(MibNum mibNum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceMouse()->GetMBPress((int)mibNum);
}

/*-----------------------------------------------------------------------------
/* ボタンを押した瞬間
-----------------------------------------------------------------------------*/
bool InputCheck::MButtonTrigger(MibNum mibNum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceMouse()->GetMBTrigger((int)mibNum);
}

/*-----------------------------------------------------------------------------
/* ボタンを押し続けていたら
-----------------------------------------------------------------------------*/
bool InputCheck::MButtonRepeat(MibNum mibNum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceMouse()->GetMBRepeat((int)mibNum);
}

/*-----------------------------------------------------------------------------
/* ボタンを放した瞬間
-----------------------------------------------------------------------------*/
bool InputCheck::MButtonRelease(MibNum mibNum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceMouse()->GetMBRelease((int)mibNum);
}

/*-----------------------------------------------------------------------------
/* マウスカーソルの位置
-----------------------------------------------------------------------------*/
Vector2 InputCheck::MouseCursorPos(void)
{
	if (input_device_ == nullptr) { return Vector2(0.0f, 0.0f); }
	return input_device_->GetDeviceInstanceMouse()->GetMCursorPos();;
}

/*-----------------------------------------------------------------------------
/* ボタンを押したら
-----------------------------------------------------------------------------*/
bool InputCheck::XInputPress(PadIndex padIndex, XInputButton xibIndex)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceXInput()->GetXIBPress((int)padIndex, xibIndex);
}

/*-----------------------------------------------------------------------------
/* ボタンを押した瞬間
-----------------------------------------------------------------------------*/
bool InputCheck::XInputTrigger(PadIndex padIndex, XInputButton xibIndex)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceXInput()->GetXIBTrigger((int)padIndex, xibIndex);
}

/*-----------------------------------------------------------------------------
/* ボタンを押し続けていたら瞬間
-----------------------------------------------------------------------------*/
bool InputCheck::XInputRepeat(PadIndex padIndex, XInputButton xibIndex)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceXInput()->GetXIBRepeat((int)padIndex, xibIndex);
}

/*-----------------------------------------------------------------------------
/* ボタンを放した瞬間
-----------------------------------------------------------------------------*/
bool InputCheck::XInputRelease(PadIndex padIndex, XInputButton xibIndex)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceXInput()->GetXIBRelease((int)padIndex, xibIndex);
}

/*-----------------------------------------------------------------------------
/* 左スティックの取得
-----------------------------------------------------------------------------*/
Vector2 InputCheck::XInputThumbLeft(PadIndex padIndex)
{
	if (input_device_ == nullptr) { return Vector2(0.0f, 0.0f); }
	//データを取得
	Vector2 thumb_left;
	thumb_left.x_ = (float)input_device_->GetDeviceInstanceXInput()->GetThumbLX((int)padIndex);
	thumb_left.y_ = (float)input_device_->GetDeviceInstanceXInput()->GetThumbLY((int)padIndex);

	//ベクトルの正規化
	D3DXVECTOR3 vec_thumb(thumb_left.x_, 0.0f, thumb_left.y_);
	D3DXVec3Normalize(&vec_thumb, &vec_thumb);

	//加工済みデータを保存
	thumb_left.x_ = std::round(vec_thumb.x * 100) / 100;
	thumb_left.y_ = std::round(vec_thumb.z * 100) / 100;
	return thumb_left;
}

/*-----------------------------------------------------------------------------
/* 右スティックの取得
-----------------------------------------------------------------------------*/
Vector2 InputCheck::XInputThumbRight(PadIndex padIndex)
{
	if (input_device_ == nullptr) { return Vector2( 0.0f, 0.0f); }
	//データを取得
	Vector2 thumb_right;
	thumb_right.x_ = (float)input_device_->GetDeviceInstanceXInput()->GetThumbRX((int)padIndex);
	thumb_right.y_ = (float)input_device_->GetDeviceInstanceXInput()->GetThumbRY((int)padIndex);

	//ベクトルの正規化
	D3DXVECTOR3 vec_thumb(thumb_right.x_, 0.0f, thumb_right.y_);
	D3DXVec3Normalize(&vec_thumb, &vec_thumb);

	//加工済みデータを保存
	thumb_right.x_ = std::round(vec_thumb.x * 100) / 100;
	thumb_right.y_ = std::round(vec_thumb.z * 100) / 100;

	return thumb_right;
}

/*=============================================================================
/*		End of File
=============================================================================*/
