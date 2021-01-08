/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputCheck.h] デバイスからの入力状況を中継するクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：デバイスからの入力状況を中継するための仲介役クラス定義
=============================================================================*/
#ifndef INPUT_CHECK_H_
#define	INPUT_CHECK_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "../../InputDevice/InputDeviceXInput.h"

/*--- 構造体定義 ---*/


/*-------------------------------------
/* マウス入力用定数
-------------------------------------*/
enum class MibNum :int
{
	MIB_LEFT = 0,
	MIB_RIGHT,
	MIB_CENTER,
};

enum class PadIndex : int
{
	Pad1 = 0,
	Pad2,
	Pad3,
	Pad4
};


/*-------------------------------------
/* 入力中継クラス
-------------------------------------*/
class InputCheck
{
private:
	InputCheck(void);

public:
	~InputCheck(void);
	//Press		//ボタンを押したら
	//Trigger	//ボタンを押した瞬間
	//Repeat	//ボタンを押し続けていたら
	//Release	//ボタンを放した瞬間

	static void SetInputDeviceState(class InputDevice * inputDevice);

	static bool KeyPress(int dikKeynum);
	static bool KeyTrigger(int dikKeynum);
	static bool KeyRepeat(int dikKeynum);
	static bool KeyRelease(int dikKeynum);

	static bool MButtonPress(MibNum mibNum);
	static bool MButtonTrigger(MibNum mibNum);
	static bool MButtonRepeat(MibNum mibNum);
	static bool MButtonRelease(MibNum mibNum);
	static class Vector2 MouseCursorPos(void);

	static bool XInputPress(PadIndex padIndex, XInputButton xibIndex);
	static bool XInputTrigger(PadIndex padIndex, XInputButton xibIndex);
	static bool XInputRepeat(PadIndex padIndex, XInputButton xibIndex);
	static bool XInputRelease(PadIndex padIndex, XInputButton xibIndex);
	static class Vector2 XInputThumbLeft(PadIndex padIndex);
	static class Vector2 XInputThumbRight(PadIndex padIndex);

private:
	static class InputDevice *input_device_;
};

#endif //INPUT_CHECK_H_
/*=============================================================================
/*		End of File
=============================================================================*/
