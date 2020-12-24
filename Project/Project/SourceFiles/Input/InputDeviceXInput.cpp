/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceXInput.cpp] ゲームパッド(XInput)状態取得処理
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：XInputのゲームパッド用からの入力をチェックするクラスの動作定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "InputDeviceXInput.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
InputDeviceXInput::InputDeviceXInput(void)
{
	Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
InputDeviceXInput::~InputDeviceXInput(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
void InputDeviceXInput::Init(void)
{
	// 各ワークのクリア
	ZeroMemory(xinput_gamepad_, sizeof(xinput_gamepad_));
	ZeroMemory(xib_state_trigger_, sizeof(xib_state_trigger_));
	ZeroMemory(xib_state_release_, sizeof(xib_state_release_));
	ZeroMemory(xib_state_repeat_,  sizeof(xib_state_repeat_));
	ZeroMemory(xib_state_repeat_count_, sizeof(xib_state_repeat_count_));
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void InputDeviceXInput::Update(void)
{
	UpdateGamepadEntity();
	GamepadIdleState();
}

/*-----------------------------------------------------------------------------
/* XInputコントローラの接続状況の更新処理
-----------------------------------------------------------------------------*/
HRESULT InputDeviceXInput::UpdateGamepadEntity(void)
{
	DWORD result;
	for (int i = 0; i < MAX_GAMEPAD_CONNECTION; i++)
	{
		result = XInputGetState(i, &xinput_gamepad_[i].pad_state_);

		const bool is_gamepad_entity = (result == ERROR_SUCCESS);

		if (is_gamepad_entity)
		{
			xinput_gamepad_[i].is_pad_conected_ = true;
		}
		else
		{
			xinput_gamepad_[i].is_pad_conected_ = false;
		}
	}

	return S_OK;
}

/*-----------------------------------------------------------------------------
/* コントローラの状態取得関数
-----------------------------------------------------------------------------*/
void InputDeviceXInput::GamepadIdleState(void)
{
	for (int gamepad_count = 0; gamepad_count < MAX_GAMEPAD_CONNECTION; gamepad_count++)
	{
		if (xinput_gamepad_[gamepad_count].is_pad_conected_ == false)
		{
			break;
		}
		else
		{
			//デッドゾーンを設定
			SetBothThumbDeadZone(gamepad_count);

			//トリガーボタンの更新
			SetBothTriggerState(gamepad_count);

			//パッドの状態を保存
			WORD xib_state		= xinput_gamepad_[gamepad_count].pad_state_.Gamepad.wButtons;
			WORD xib_state_old  = xinput_gamepad_[gamepad_count].pad_state_old_.Gamepad.wButtons;
			xinput_gamepad_[gamepad_count].pad_state_old_ = xinput_gamepad_[gamepad_count].pad_state_;

			//トリガー情報の生成
			//条件1：押された
			//条件2：押されていない
			//1と2でXOR
			//現在の情報：押された
			xib_state_trigger_[gamepad_count] = (xib_state ^ xib_state_old) & xib_state;

			//リリースの情報生成
			//条件1：押された
			//条件2：押されていた
			//1と2でXOR
			//現在の条件：押されていない
			xib_state_release_[gamepad_count] = (xib_state ^ xib_state_old) & ~xib_state;


			//リピートの情報生成
			if (xib_state)
			{
				if (xib_state_repeat_count_[gamepad_count] < LIMIT_COUNT_REPEAT)
				{
					xib_state_repeat_count_[gamepad_count]++;

					// ボタンを押し始めた最初のフレーム、または一定時間経過したらリピート情報ON
					if ((xib_state_repeat_count_[gamepad_count] == 1) || (xib_state_repeat_count_[gamepad_count] >= LIMIT_COUNT_REPEAT))
					{
						xib_state_repeat_ [gamepad_count] = xib_state;
					}
					else
					{
						xib_state_repeat_[gamepad_count] = 0;
					}
				}
			}
			else
			{
				xib_state_repeat_count_[gamepad_count] = 0;
				xib_state_repeat_[gamepad_count] = 0;
			}
			
			//プレスの情報生成
			xib_state_press_[gamepad_count] = xib_state;
		}
	}	
}

/*-----------------------------------------------------------------------------
/* 左右の両方のスティックのデッドゾーンを設定
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetBothThumbDeadZone(int padIndex)
{
	SetRightThumbDeadZone(padIndex);
	SetLeftThumbDeadZone(padIndex);
}

/*-----------------------------------------------------------------------------
/* 左スティックのデッドゾーンを設定
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetLeftThumbDeadZone(int padIndex)
{
	//左スティックのデッドゾーンへのフラグ
	const bool dead_zone_left_thumb =
		((xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLX <  INPUT_DEADZONE)  &&
		 (xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLX > -INPUT_DEADZONE)) &&
		((xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLY <  INPUT_DEADZONE)  &&
		 (xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLY > -INPUT_DEADZONE));

	//左アナログスティック初期化
	if (dead_zone_left_thumb)
	{
		xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLX = 0;
		xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLY = 0;
	}
}

/*-----------------------------------------------------------------------------
/* 右スティックのデッドゾーンを設定
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetRightThumbDeadZone(int padIndex)
{
	//右スティックのデッドゾーンへのフラグ
	const bool dead_zone_right_thumb =
		((xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRX <  INPUT_DEADZONE)  &&
		 (xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRX > -INPUT_DEADZONE)) &&
		((xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRY <  INPUT_DEADZONE)  &&
		 (xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRY > -INPUT_DEADZONE));


	//右アナログスティック初期化
	if (dead_zone_right_thumb)
	{
		xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRX = 0;
		xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRY = 0;
	}
}

/*-----------------------------------------------------------------------------
/* LRの両トリガーボタンの状態設置
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetBothTriggerState(int padIndex)
{
	SetLTriggerState(padIndex);
	SetRTriggerState(padIndex);
}

/*-----------------------------------------------------------------------------
/* Lトリガーボタンの状態設置
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetLTriggerState(int padIndex)
{
	bool is_press = (xinput_gamepad_[padIndex].pad_state_.Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	if (is_press == false) { return; }
	xinput_gamepad_[padIndex].pad_state_.Gamepad.wButtons += (WORD)XInputButton::XIB_LEFT_TRIGGER;
}

/*-----------------------------------------------------------------------------
/* Rトリガーボタンの状態設置
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetRTriggerState(int padIndex)
{
	bool is_press = (xinput_gamepad_[padIndex].pad_state_.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	if (is_press == false) { return; }
	xinput_gamepad_[padIndex].pad_state_.Gamepad.wButtons += (WORD)XInputButton::XIB_RIGHT_TRIGGER;
}

/*-----------------------------------------------------------------------------
/* 左スティックX軸の取得
-----------------------------------------------------------------------------*/
double InputDeviceXInput::GetThumbLX(int padIndex)
{
	return xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLX;
}

/*-----------------------------------------------------------------------------
/* 左スティックY軸の取得
-----------------------------------------------------------------------------*/
double InputDeviceXInput::GetThumbLY(int padIndex)
{
	return xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLY;
}

/*-----------------------------------------------------------------------------
/* 右スティックX軸の取得
-----------------------------------------------------------------------------*/
double InputDeviceXInput::GetThumbRX(int padIndex)
{
	return xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRX;
}

/*-----------------------------------------------------------------------------
/* 右スティックY軸の取得
-----------------------------------------------------------------------------*/
double InputDeviceXInput::GetThumbRY(int padIndex)
{
	return xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRY;
}

/*-----------------------------------------------------------------------------
/* ボタンを押したら
-----------------------------------------------------------------------------*/
bool InputDeviceXInput::GetXIBPress(int padIndex, XInputButton xibIndex)
{
	return (xib_state_press_[padIndex] & (WORD)xibIndex) ? true : false;
}

/*-----------------------------------------------------------------------------
/* ボタンを押した瞬間
-----------------------------------------------------------------------------*/
bool InputDeviceXInput::GetXIBTrigger(int padIndex, XInputButton xibIndex)
{
	return (xib_state_trigger_[padIndex] & (WORD)xibIndex) ? true : false;
}

/*-----------------------------------------------------------------------------
/* ボタンを離した瞬間
-----------------------------------------------------------------------------*/
bool InputDeviceXInput::GetXIBRelease(int padIndex, XInputButton xibIndex)
{
	return (xib_state_release_[padIndex] & (WORD)xibIndex) ? true : false;
}

/*-----------------------------------------------------------------------------
/* ボタンを押し続けていたら
-----------------------------------------------------------------------------*/
bool InputDeviceXInput::GetXIBRepeat(int padIndex, XInputButton xibIndex)
{
	return (xib_state_repeat_[padIndex] & (WORD)xibIndex) ? true : false;
}

/*=============================================================================
/*		End of File
=============================================================================*/


