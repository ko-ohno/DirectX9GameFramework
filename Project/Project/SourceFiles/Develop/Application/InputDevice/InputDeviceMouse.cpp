/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceMouse.cpp] マウス入力クラスの実装部
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：マウス入力クラスによる動作を定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "InputDeviceMouse.h"
#include "../Math.h"

#define DIRECTINPUT_VERSION (0x0800) //DirectInputのバージョンを指定。

//静的変数宣言
LPDIRECTINPUTDEVICE8	InputDeviceMouse::lpdinput_device_mouse_;
POINT					InputDeviceMouse::mouse_cursor_pos_;

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
InputDeviceMouse::InputDeviceMouse(void)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
InputDeviceMouse::~InputDeviceMouse(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* マウスの初期化
-----------------------------------------------------------------------------*/
HRESULT InputDeviceMouse::CrateInputDeviceMouse(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle)
{
	// インターフェースオブジェクトの取得
	if (lpdinputObject == nullptr)
	{
		MessageBox(wndHandle, "DirectInputインターフェースオブジェクトが取得できませんでした", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	// マウス用のデバイスの作成
	if (FAILED(lpdinputObject->CreateDevice(GUID_SysMouse, &lpdinput_device_mouse_, NULL)))
	{
		MessageBox(wndHandle, "マウスが接続されていません", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(lpdinput_device_mouse_->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(wndHandle, "マウスのデータフォーマットを設定できませんでした。", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(lpdinput_device_mouse_->SetCooperativeLevel(wndHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))//画面がフォアグラウンドの時にインプットを受け付ける。
	{
		MessageBox(wndHandle, "キーボードの協調モードを設定できませんでした。", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize		 = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj		 = 0;
	diprop.diph.dwHow		 = DIPH_DEVICE;
	diprop.dwData			 = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED(lpdinput_device_mouse_->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		MessageBox(wndHandle, "マウスへのデバイス設定に失敗しました。", "警告", MB_ICONWARNING);
		return E_FAIL;
	}


	// マウスへのアクセス権を獲得(入力制御開始)
	lpdinput_device_mouse_->Acquire();

	return S_OK;
}

/*-----------------------------------------------------------------------------
/* マウスの状態取得処理
-----------------------------------------------------------------------------*/
void InputDeviceMouse::UpdateMouseState(const HWND &wndHandle)
{
	//１フレーム前の情報と現在のフレームの情報を比較して、入力を検知する。
	// 変化検知用にマウス情報読取前の値を保存
	dimouse_state_old_ = dimouse_state_;
	
	//マウスカーソルの位置を読み取り
	GetCursorPos(&mouse_cursor_pos_);
	ScreenToClient(wndHandle, &mouse_cursor_pos_);

	//入力判定で0x80が使われているのは
	//取得したデバイスでボタンが押されているときに1バイトの最上位ビットが1となっている

	// マウスの状態を取得
	if (SUCCEEDED(lpdinput_device_mouse_->GetDeviceState(sizeof(DIMOUSESTATE), &dimouse_state_)))
	{
		for (int mb_count = 0; mb_count < NUM_MB_MAX; mb_count++)
		{

			//トリガーの情報生成
			//条件1：押された
			//条件2：押されていない
			//1と2でXOR
			//現在の情報：押された
			mb_state_trigger_[mb_count] =
				(dimouse_state_.rgbButtons[mb_count] ^ dimouse_state_old_.rgbButtons[mb_count]) & dimouse_state_.rgbButtons[mb_count];

			//リリースの情報生成
			//条件1：押された
			//条件2：押されていた
			//1と2でXOR
			//現在の条件：押されていない
			mb_state_release_[mb_count] =
				(dimouse_state_.rgbButtons[mb_count] ^ dimouse_state_old_.rgbButtons[mb_count]) & ~dimouse_state_.rgbButtons[mb_count];

			//リピート
			if (mb_state_[mb_count])
			{
				if (mb_state_repeat_count_[mb_count] < LIMIT_COUNT_REPEAT)
				{
					mb_state_repeat_count_[mb_count]++;

					if((mb_state_repeat_count_[mb_count] == 1) || (mb_state_repeat_count_[mb_count] >= LIMIT_COUNT_REPEAT))
					{
						mb_state_repeat_[mb_count] = mb_state_[mb_count];
					}
					else
					{
						mb_state_repeat_[mb_count] = 0;
					}
				}
			}
			else
			{
				mb_state_repeat_count_[mb_count] = 0;
				mb_state_repeat_[mb_count] = 0;
			}
			//プレス
			mb_state_[mb_count] = dimouse_state_.rgbButtons[mb_count];
		}
	}
	else
	{
		lpdinput_device_mouse_->Acquire();

		//現在のデバイスの状態を取得
		lpdinput_device_mouse_->GetDeviceState(sizeof(DIMOUSESTATE), &dimouse_state_);
	}
}

/*-----------------------------------------------------------------------------
/* 初期化処理
/*---------------------------------------------------------------------------*/
void InputDeviceMouse::Init(void)
{
	dimouse_state_ = {0};

	// 各ワークのクリア
	ZeroMemory(mb_state_, sizeof(mb_state_));
	ZeroMemory(mb_state_trigger_, sizeof(mb_state_trigger_));
	ZeroMemory(mb_state_release_, sizeof(mb_state_release_));
	ZeroMemory(mb_state_repeat_, sizeof(mb_state_repeat_));
	ZeroMemory(mb_state_repeat_count_, sizeof(mb_state_repeat_count_));
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void InputDeviceMouse::Uninit(void)
{
	if (lpdinput_device_mouse_ != nullptr)
	{
		SAFE_RELEASE_(lpdinput_device_mouse_);
	}
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void InputDeviceMouse::Update(const HWND &wndHandle)
{
	this->UpdateMouseState(wndHandle);
}

/*-----------------------------------------------------------------------------
/* ボタンを押した瞬間
-----------------------------------------------------------------------------*/
bool InputDeviceMouse::GetMBPress(int mibNum)
{
	return (mb_state_[mibNum] & 0x80) ? true : false;
}

/*-----------------------------------------------------------------------------
/* ボタンを押した瞬間
-----------------------------------------------------------------------------*/
bool InputDeviceMouse::GetMBTrigger(int mibNum)
{
	return (mb_state_trigger_[mibNum] & 0x80) ? true : false;
}

/*-----------------------------------------------------------------------------
/* ボタンを押し続けていたら
-----------------------------------------------------------------------------*/
bool InputDeviceMouse::GetMBRepeat(int mibNum)
{
	return  (mb_state_repeat_[mibNum] & 0x80) ? true : false;;
}

/*-----------------------------------------------------------------------------
/* ボタンを放した瞬間
-----------------------------------------------------------------------------*/
bool InputDeviceMouse::GetMBRelease(int mibNum)
{
	return (mb_state_release_[mibNum] & 0x80) ? true : false;
}

/*-----------------------------------------------------------------------------
/* マウスカーソルの座標取得
-----------------------------------------------------------------------------*/
Vector2 InputDeviceMouse::GetMCursorPos(void) const
{
	return Vector2((float)mouse_cursor_pos_.x, (float)mouse_cursor_pos_.y);
}

/*=============================================================================
/*		End of File
=============================================================================*/

