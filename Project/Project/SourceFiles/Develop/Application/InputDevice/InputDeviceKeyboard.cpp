/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceKeyboard.cpp] �L�[�{�[�h���͊Ǘ��N���X�����`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�L�[�{�[�h�ɂ����͏������Ǘ�����N���X��`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "InputDeviceKeyboard.h"


//�ÓI�ϐ��錾
LPDIRECTINPUTDEVICE8 InputDeviceKeyboard::lpdinput_device_keyboard_;

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
InputDeviceKeyboard::InputDeviceKeyboard()
	: max_repeat_frame_count_(0)
	, repeat_input_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
InputDeviceKeyboard::~InputDeviceKeyboard()
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* �L�[�{�[�h�̏�����
-----------------------------------------------------------------------------*/
HRESULT InputDeviceKeyboard::CreateDeviceKeyboard(const LPDIRECTINPUT8 &lpdinput_interface_object, const HWND &wndHandle)
{
	// �C���^�[�t�F�[�X�I�u�W�F�N�g�̎擾
	if(lpdinput_interface_object == nullptr)
	{
		MessageBox(wndHandle, "DirectInput�C���^�[�t�F�[�X�I�u�W�F�N�g���擾�ł��܂���ł���", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	// �L�[�{�[�h�p�̃f�o�C�X�̍쐬
	if(FAILED(lpdinput_interface_object->CreateDevice(GUID_SysKeyboard, &lpdinput_device_keyboard_, NULL)))
	{
		MessageBox(wndHandle, "�L�[�{�[�h���ڑ�����Ă��܂���", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(lpdinput_device_keyboard_->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(wndHandle, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if(FAILED(lpdinput_device_keyboard_->SetCooperativeLevel(wndHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))//��ʂ��t�H�A�O���E���h�̎��ɃC���v�b�g���󂯕t����B
	{ 
		MessageBox(wndHandle, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	lpdinput_device_keyboard_->Acquire();

	return S_OK;
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
void InputDeviceKeyboard::Init(void)
{
	//�ϐ��̏�����
	lpdinput_device_keyboard_ = nullptr;

	// �e���[�N�̃N���A
	ZeroMemory(key_state_,				sizeof(key_state_));
	ZeroMemory(key_state_trigger_,		sizeof(key_state_trigger_));
	ZeroMemory(key_state_release_,		sizeof(key_state_release_));
	ZeroMemory(key_state_repeat_,		sizeof(key_state_repeat_));
	ZeroMemory(key_state_repeat_count_,	sizeof(key_state_repeat_count_));
}

/*-----------------------------------------------------------------------------
/* �I������
-----------------------------------------------------------------------------*/
void InputDeviceKeyboard::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (lpdinput_device_keyboard_ != nullptr)
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��
		lpdinput_device_keyboard_->Unacquire();
		SAFE_RELEASE_(lpdinput_device_keyboard_);
	}
}

/*-----------------------------------------------------------------------------
/* �L�[�{�[�h�̍X�V����
-----------------------------------------------------------------------------*/
void InputDeviceKeyboard::Update(void)
{
	BYTE key_state[NUM_KEY_MAX];

	// ���s�[�g�̍ő���͎��Ԃ̍X�V
	{
		// 1�b * n�{���t���[�����Ƃ��ēo�^����
		max_repeat_frame_count_ = static_cast<int>(static_cast<float>(MAX_FPS) * repeat_input_time_);
	}

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(lpdinput_device_keyboard_->GetDeviceState(sizeof(key_state), key_state)))
	{
		for (int key_count = 0; key_count < NUM_KEY_MAX; key_count++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			key_state_trigger_[key_count] = (key_state_[key_count] ^ key_state[key_count]) & key_state[key_count];
			key_state_release_[key_count] = (key_state_[key_count] ^ key_state[key_count]) & ~key_state[key_count];

			// �L�[���s�[�g���𐶐�
			if (key_state[key_count])
			{
				if (key_state_repeat_count_[key_count] < max_repeat_frame_count_)
				{
					key_state_repeat_count_[key_count]++;
					
					// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂�����L�[���s�[�g���ON
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
			// �L�[�v���X����ۑ�
			key_state_[key_count] = key_state[key_count];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		lpdinput_device_keyboard_->Acquire();
	}
}

/*-----------------------------------------------------------------------------
/* �L�[�{�[�h�̃v���X��Ԃ��擾
-----------------------------------------------------------------------------*/
bool InputDeviceKeyboard::GetKeyboardPress(int nKey)
{
 	return (key_state_[nKey] & 0x80) ? true: false;
}

/*-----------------------------------------------------------------------------
/* �L�[�{�[�h�̃g���K�[��Ԃ��擾
-----------------------------------------------------------------------------*/
bool InputDeviceKeyboard::GetKeyboardTrigger(int nKey)
{
	return (key_state_trigger_[nKey] & 0x80) ? true: false;
}

/*-----------------------------------------------------------------------------
/* �L�[�{�[�h�̃��s�[�g��Ԃ��擾
-----------------------------------------------------------------------------*/
bool InputDeviceKeyboard::GetKeyboardRepeat(int nKey)
{
	return (key_state_repeat_[nKey] & 0x80) ? true: false;
}

/*-----------------------------------------------------------------------------
/* �L�[�{�[�h�̃����|�X��Ԃ��擾
-----------------------------------------------------------------------------*/
bool InputDeviceKeyboard::GetKeyboardRelease(int nKey)
{
	return (key_state_release_[nKey] & 0x80) ? true: false;
}

/*==============================================================================
/*		End of file
==============================================================================*/
