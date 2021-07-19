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
#include "../../StdAfx.h"

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

	// 入力時間の設定
	void SetRepeatInputTime(float inputSeconds) { repeat_input_time_ = inputSeconds; }

private:
	// キーの最大上限数
	static constexpr int NUM_KEY_MAX = 256;

	// 最大FPS数
	static constexpr int MAX_FPS = 60;

	// 最大リピートフレーム数 
	int max_repeat_frame_count_;

	// 入力時間
	float repeat_input_time_;

	// 入力デバイス(キーボード)へのポインタ
	static LPDIRECTINPUTDEVICE8	lpdinput_device_keyboard_;	

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
