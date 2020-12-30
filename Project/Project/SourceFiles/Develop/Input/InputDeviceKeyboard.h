/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceKeyboard.h] キーボードへの入力管理クラス定義
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：キー入力の更新、キーボードの初期化を行うクラス定義。
=============================================================================*/
#ifndef INPUT_DEVICE_KEYBOARD_H_
#define	INPUT_DEVICE_KEYBOARD_H_

/*--- インクルードファイル ---*/
#include "StdAfx.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* キーボード入力クラス
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
	static constexpr int NUM_KEY_MAX = 256;			//キーの最大上限数

	static LPDIRECTINPUTDEVICE8	lpdinput_device_keyboard_;	// 入力デバイス(キーボード)へのポインタ

	BYTE key_state_[NUM_KEY_MAX];				// キーボードの入力情報ワーク
	BYTE key_state_trigger_[NUM_KEY_MAX];		// キーボードのトリガー情報ワーク
	BYTE key_state_release_[NUM_KEY_MAX];		// キーボードのリリース情報ワーク
	BYTE key_state_repeat_[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
	int	 key_state_repeat_count_[NUM_KEY_MAX];	// キーボードのリピートカウンタ
};



#endif //INPUT_DEVICE_KEYBOARD_H_
/*==============================================================================
//		End of file
==============================================================================*/
