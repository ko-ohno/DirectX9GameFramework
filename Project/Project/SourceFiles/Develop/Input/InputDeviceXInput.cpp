/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceXInput.cpp] �Q�[���p�b�h(XInput)��Ԏ擾����
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FXInput�̃Q�[���p�b�h�p����̓��͂��`�F�b�N����N���X�̓����`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "InputDeviceXInput.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
InputDeviceXInput::InputDeviceXInput(void)
{
	Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
InputDeviceXInput::~InputDeviceXInput(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
void InputDeviceXInput::Init(void)
{
	// �e���[�N�̃N���A
	ZeroMemory(xinput_gamepad_, sizeof(xinput_gamepad_));
	ZeroMemory(xib_state_trigger_, sizeof(xib_state_trigger_));
	ZeroMemory(xib_state_release_, sizeof(xib_state_release_));
	ZeroMemory(xib_state_repeat_,  sizeof(xib_state_repeat_));
	ZeroMemory(xib_state_repeat_count_, sizeof(xib_state_repeat_count_));
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void InputDeviceXInput::Update(void)
{
	UpdateGamepadEntity();
	GamepadIdleState();
}

/*-----------------------------------------------------------------------------
/* XInput�R���g���[���̐ڑ��󋵂̍X�V����
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
/* �R���g���[���̏�Ԏ擾�֐�
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
			//�f�b�h�]�[����ݒ�
			SetBothThumbDeadZone(gamepad_count);

			//�g���K�[�{�^���̍X�V
			SetBothTriggerState(gamepad_count);

			//�p�b�h�̏�Ԃ�ۑ�
			WORD xib_state		= xinput_gamepad_[gamepad_count].pad_state_.Gamepad.wButtons;
			WORD xib_state_old  = xinput_gamepad_[gamepad_count].pad_state_old_.Gamepad.wButtons;
			xinput_gamepad_[gamepad_count].pad_state_old_ = xinput_gamepad_[gamepad_count].pad_state_;

			//�g���K�[���̐���
			//����1�F�����ꂽ
			//����2�F������Ă��Ȃ�
			//1��2��XOR
			//���݂̏��F�����ꂽ
			xib_state_trigger_[gamepad_count] = (xib_state ^ xib_state_old) & xib_state;

			//�����[�X�̏�񐶐�
			//����1�F�����ꂽ
			//����2�F������Ă���
			//1��2��XOR
			//���݂̏����F������Ă��Ȃ�
			xib_state_release_[gamepad_count] = (xib_state ^ xib_state_old) & ~xib_state;


			//���s�[�g�̏�񐶐�
			if (xib_state)
			{
				if (xib_state_repeat_count_[gamepad_count] < LIMIT_COUNT_REPEAT)
				{
					xib_state_repeat_count_[gamepad_count]++;

					// �{�^���������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂����烊�s�[�g���ON
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
			
			//�v���X�̏�񐶐�
			xib_state_press_[gamepad_count] = xib_state;
		}
	}	
}

/*-----------------------------------------------------------------------------
/* ���E�̗����̃X�e�B�b�N�̃f�b�h�]�[����ݒ�
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetBothThumbDeadZone(int padIndex)
{
	SetRightThumbDeadZone(padIndex);
	SetLeftThumbDeadZone(padIndex);
}

/*-----------------------------------------------------------------------------
/* ���X�e�B�b�N�̃f�b�h�]�[����ݒ�
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetLeftThumbDeadZone(int padIndex)
{
	//���X�e�B�b�N�̃f�b�h�]�[���ւ̃t���O
	const bool dead_zone_left_thumb =
		((xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLX <  INPUT_DEADZONE)  &&
		 (xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLX > -INPUT_DEADZONE)) &&
		((xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLY <  INPUT_DEADZONE)  &&
		 (xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLY > -INPUT_DEADZONE));

	//���A�i���O�X�e�B�b�N������
	if (dead_zone_left_thumb)
	{
		xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLX = 0;
		xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLY = 0;
	}
}

/*-----------------------------------------------------------------------------
/* �E�X�e�B�b�N�̃f�b�h�]�[����ݒ�
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetRightThumbDeadZone(int padIndex)
{
	//�E�X�e�B�b�N�̃f�b�h�]�[���ւ̃t���O
	const bool dead_zone_right_thumb =
		((xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRX <  INPUT_DEADZONE)  &&
		 (xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRX > -INPUT_DEADZONE)) &&
		((xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRY <  INPUT_DEADZONE)  &&
		 (xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRY > -INPUT_DEADZONE));


	//�E�A�i���O�X�e�B�b�N������
	if (dead_zone_right_thumb)
	{
		xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRX = 0;
		xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRY = 0;
	}
}

/*-----------------------------------------------------------------------------
/* LR�̗��g���K�[�{�^���̏�Ԑݒu
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetBothTriggerState(int padIndex)
{
	SetLTriggerState(padIndex);
	SetRTriggerState(padIndex);
}

/*-----------------------------------------------------------------------------
/* L�g���K�[�{�^���̏�Ԑݒu
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetLTriggerState(int padIndex)
{
	bool is_press = (xinput_gamepad_[padIndex].pad_state_.Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	if (is_press == false) { return; }
	xinput_gamepad_[padIndex].pad_state_.Gamepad.wButtons += (WORD)XInputButton::XIB_LEFT_TRIGGER;
}

/*-----------------------------------------------------------------------------
/* R�g���K�[�{�^���̏�Ԑݒu
-----------------------------------------------------------------------------*/
void InputDeviceXInput::SetRTriggerState(int padIndex)
{
	bool is_press = (xinput_gamepad_[padIndex].pad_state_.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	if (is_press == false) { return; }
	xinput_gamepad_[padIndex].pad_state_.Gamepad.wButtons += (WORD)XInputButton::XIB_RIGHT_TRIGGER;
}

/*-----------------------------------------------------------------------------
/* ���X�e�B�b�NX���̎擾
-----------------------------------------------------------------------------*/
double InputDeviceXInput::GetThumbLX(int padIndex)
{
	return xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLX;
}

/*-----------------------------------------------------------------------------
/* ���X�e�B�b�NY���̎擾
-----------------------------------------------------------------------------*/
double InputDeviceXInput::GetThumbLY(int padIndex)
{
	return xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbLY;
}

/*-----------------------------------------------------------------------------
/* �E�X�e�B�b�NX���̎擾
-----------------------------------------------------------------------------*/
double InputDeviceXInput::GetThumbRX(int padIndex)
{
	return xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRX;
}

/*-----------------------------------------------------------------------------
/* �E�X�e�B�b�NY���̎擾
-----------------------------------------------------------------------------*/
double InputDeviceXInput::GetThumbRY(int padIndex)
{
	return xinput_gamepad_[padIndex].pad_state_.Gamepad.sThumbRY;
}

/*-----------------------------------------------------------------------------
/* �{�^������������
-----------------------------------------------------------------------------*/
bool InputDeviceXInput::GetXIBPress(int padIndex, XInputButton xibIndex)
{
	return (xib_state_press_[padIndex] & (WORD)xibIndex) ? true : false;
}

/*-----------------------------------------------------------------------------
/* �{�^�����������u��
-----------------------------------------------------------------------------*/
bool InputDeviceXInput::GetXIBTrigger(int padIndex, XInputButton xibIndex)
{
	return (xib_state_trigger_[padIndex] & (WORD)xibIndex) ? true : false;
}

/*-----------------------------------------------------------------------------
/* �{�^���𗣂����u��
-----------------------------------------------------------------------------*/
bool InputDeviceXInput::GetXIBRelease(int padIndex, XInputButton xibIndex)
{
	return (xib_state_release_[padIndex] & (WORD)xibIndex) ? true : false;
}

/*-----------------------------------------------------------------------------
/* �{�^�������������Ă�����
-----------------------------------------------------------------------------*/
bool InputDeviceXInput::GetXIBRepeat(int padIndex, XInputButton xibIndex)
{
	return (xib_state_repeat_[padIndex] & (WORD)xibIndex) ? true : false;
}

/*=============================================================================
/*		End of File
=============================================================================*/


