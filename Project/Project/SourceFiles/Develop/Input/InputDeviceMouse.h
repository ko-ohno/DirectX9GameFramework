/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceMouse.h] マウス入力クラスの定義
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：マウス入力による動作クラスの定義
=============================================================================*/
#ifndef INPUT_DEVICE_MOUSE_H_
#define	INPUT_DEVICE_MOUSE_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/
class Vector2;

/*-------------------------------------
/* マウス入力クラス
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

	Vector2 GetMCursorPos(void) const;

private:
	void Init(void);
	void Uninit(void);

	void UpdateMouseState(const HWND &wndHandle);

private:
	static constexpr int LIMIT_COUNT_REPEAT = 20;
	static constexpr int NUM_MB_MAX = 4;

	//デバイス入力用
	static LPDIRECTINPUTDEVICE8	lpdinput_device_mouse_;		// 入力デバイス(マウス)へのポインタ
	static POINT mouse_cursor_pos_;
	DIMOUSESTATE dimouse_state_;
	DIMOUSESTATE dimouse_state_old_;

	BYTE mb_state_[NUM_MB_MAX];					// マウスの入力情報ワーク
	BYTE mb_state_trigger_[NUM_MB_MAX];			// マウスのトリガー情報ワーク
	BYTE mb_state_release_[NUM_MB_MAX];			// マウスのリリース情報ワーク
	BYTE mb_state_repeat_[NUM_MB_MAX];			// マウスのリピート情報ワーク
	int mb_state_repeat_count_[NUM_MB_MAX];		// マウスのリピートカウンタ
};



#endif //INPUT_DEVICE_MOUSE_H_
/*=============================================================================
/*		End of File
=============================================================================*/
