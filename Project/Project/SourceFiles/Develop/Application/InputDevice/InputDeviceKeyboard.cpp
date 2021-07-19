/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceKeyboard.cpp] キーボード入力管理クラス動作定義
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：キーボードによる入力処理を管理するクラス定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "InputDeviceKeyboard.h"


//静的変数宣言
LPDIRECTINPUTDEVICE8 InputDeviceKeyboard::lpdinput_device_keyboard_;

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
InputDeviceKeyboard::InputDeviceKeyboard()
	: max_repeat_frame_count_(0)
	, repeat_input_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
InputDeviceKeyboard::~InputDeviceKeyboard()
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* キーボードの初期化
-----------------------------------------------------------------------------*/
HRESULT InputDeviceKeyboard::CreateDeviceKeyboard(const LPDIRECTINPUT8 &lpdinput_interface_object, const HWND &wndHandle)
{
	// インターフェースオブジェクトの取得
	if(lpdinput_interface_object == nullptr)
	{
		MessageBox(wndHandle, "DirectInputインターフェースオブジェクトが取得できませんでした", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	// キーボード用のデバイスの作成
	if(FAILED(lpdinput_interface_object->CreateDevice(GUID_SysKeyboard, &lpdinput_device_keyboard_, NULL)))
	{
		MessageBox(wndHandle, "キーボードが接続されていません", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if(FAILED(lpdinput_device_keyboard_->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(wndHandle, "キーボードのデータフォーマットを設定できませんでした。", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if(FAILED(lpdinput_device_keyboard_->SetCooperativeLevel(wndHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))//画面がフォアグラウンドの時にインプットを受け付ける。
	{ 
		MessageBox(wndHandle, "キーボードの協調モードを設定できませんでした。", "警告", MB_ICONWARNING);
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	lpdinput_device_keyboard_->Acquire();

	return S_OK;
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
void InputDeviceKeyboard::Init(void)
{
	//変数の初期化
	lpdinput_device_keyboard_ = nullptr;

	// 各ワークのクリア
	ZeroMemory(key_state_,				sizeof(key_state_));
	ZeroMemory(key_state_trigger_,		sizeof(key_state_trigger_));
	ZeroMemory(key_state_release_,		sizeof(key_state_release_));
	ZeroMemory(key_state_repeat_,		sizeof(key_state_repeat_));
	ZeroMemory(key_state_repeat_count_,	sizeof(key_state_repeat_count_));
}

/*-----------------------------------------------------------------------------
/* 終了処理
-----------------------------------------------------------------------------*/
void InputDeviceKeyboard::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	if (lpdinput_device_keyboard_ != nullptr)
	{
		// キーボードへのアクセス権を開放
		lpdinput_device_keyboard_->Unacquire();
		SAFE_RELEASE_(lpdinput_device_keyboard_);
	}
}

/*-----------------------------------------------------------------------------
/* キーボードの更新処理
-----------------------------------------------------------------------------*/
void InputDeviceKeyboard::Update(void)
{
	BYTE key_state[NUM_KEY_MAX];

	// リピートの最大入力時間の更新
	{
		// 1秒 * n倍をフレーム数として登録する
		max_repeat_frame_count_ = static_cast<int>(static_cast<float>(MAX_FPS) * repeat_input_time_);
	}

	// デバイスからデータを取得
	if (SUCCEEDED(lpdinput_device_keyboard_->GetDeviceState(sizeof(key_state), key_state)))
	{
		for (int key_count = 0; key_count < NUM_KEY_MAX; key_count++)
		{
			// キートリガー・リリース情報を生成
			key_state_trigger_[key_count] = (key_state_[key_count] ^ key_state[key_count]) & key_state[key_count];
			key_state_release_[key_count] = (key_state_[key_count] ^ key_state[key_count]) & ~key_state[key_count];

			// キーリピート情報を生成
			if (key_state[key_count])
			{
				if (key_state_repeat_count_[key_count] < max_repeat_frame_count_)
				{
					key_state_repeat_count_[key_count]++;
					
					// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
					if (/*(key_state_repeat_count_[key_count] == 1 )||*/( key_state_repeat_count_[key_count] >= max_repeat_frame_count_))
					{
						key_state_repeat_[key_count] = key_state[key_count];
					}
					else
					{
						key_state_repeat_[key_count] = 0;
					}
				}
			}
			else
			{
				key_state_repeat_count_[key_count] = 0;
				key_state_repeat_[key_count] = 0;
			}
			// キープレス情報を保存
			key_state_[key_count] = key_state[key_count];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		lpdinput_device_keyboard_->Acquire();
	}
}

/*-----------------------------------------------------------------------------
/* キーボードのプレス状態を取得
-----------------------------------------------------------------------------*/
bool InputDeviceKeyboard::GetKeyboardPress(int nKey)
{
 	return (key_state_[nKey] & 0x80) ? true: false;
}

/*-----------------------------------------------------------------------------
/* キーボードのトリガー状態を取得
-----------------------------------------------------------------------------*/
bool InputDeviceKeyboard::GetKeyboardTrigger(int nKey)
{
	return (key_state_trigger_[nKey] & 0x80) ? true: false;
}

/*-----------------------------------------------------------------------------
/* キーボードのリピート状態を取得
-----------------------------------------------------------------------------*/
bool InputDeviceKeyboard::GetKeyboardRepeat(int nKey)
{
	return (key_state_repeat_[nKey] & 0x80) ? true: false;
}

/*-----------------------------------------------------------------------------
/* キーボードのリリ－ス状態を取得
-----------------------------------------------------------------------------*/
bool InputDeviceKeyboard::GetKeyboardRelease(int nKey)
{
	return (key_state_release_[nKey] & 0x80) ? true: false;
}

/*==============================================================================
/*		End of file
==============================================================================*/
