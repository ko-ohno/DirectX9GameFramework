/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDeviceMouse.cpp] �}�E�X���̓N���X�̎�����
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�}�E�X���̓N���X�ɂ�铮����`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "InputDeviceMouse.h"
#include "../Math.h"

#define DIRECTINPUT_VERSION (0x0800) //DirectInput�̃o�[�W�������w��B

//�ÓI�ϐ��錾
LPDIRECTINPUTDEVICE8	InputDeviceMouse::lpdinput_device_mouse_;
POINT					InputDeviceMouse::mouse_cursor_pos_;

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
InputDeviceMouse::InputDeviceMouse(void)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
InputDeviceMouse::~InputDeviceMouse(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* �}�E�X�̏�����
-----------------------------------------------------------------------------*/
HRESULT InputDeviceMouse::CrateInputDeviceMouse(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle)
{
	// �C���^�[�t�F�[�X�I�u�W�F�N�g�̎擾
	if (lpdinputObject == nullptr)
	{
		MessageBox(wndHandle, "DirectInput�C���^�[�t�F�[�X�I�u�W�F�N�g���擾�ł��܂���ł���", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	// �}�E�X�p�̃f�o�C�X�̍쐬
	if (FAILED(lpdinputObject->CreateDevice(GUID_SysMouse, &lpdinput_device_mouse_, NULL)))
	{
		MessageBox(wndHandle, "�}�E�X���ڑ�����Ă��܂���", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(lpdinput_device_mouse_->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(wndHandle, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(lpdinput_device_mouse_->SetCooperativeLevel(wndHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))//��ʂ��t�H�A�O���E���h�̎��ɃC���v�b�g���󂯕t����B
	{
		MessageBox(wndHandle, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize		 = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj		 = 0;
	diprop.diph.dwHow		 = DIPH_DEVICE;
	diprop.dwData			 = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED(lpdinput_device_mouse_->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		MessageBox(wndHandle, "�}�E�X�ւ̃f�o�C�X�ݒ�Ɏ��s���܂����B", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}


	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	lpdinput_device_mouse_->Acquire();

	return S_OK;
}

/*-----------------------------------------------------------------------------
/* �}�E�X�̏�Ԏ擾����
-----------------------------------------------------------------------------*/
void InputDeviceMouse::UpdateMouseState(const HWND &wndHandle)
{
	//�P�t���[���O�̏��ƌ��݂̃t���[���̏����r���āA���͂����m����B
	// �ω����m�p�Ƀ}�E�X���ǎ�O�̒l��ۑ�
	dimouse_state_old_ = dimouse_state_;
	
	//�}�E�X�J�[�\���̈ʒu��ǂݎ��
	GetCursorPos(&mouse_cursor_pos_);
	ScreenToClient(wndHandle, &mouse_cursor_pos_);

	//���͔����0x80���g���Ă���̂�
	//�擾�����f�o�C�X�Ń{�^����������Ă���Ƃ���1�o�C�g�̍ŏ�ʃr�b�g��1�ƂȂ��Ă���

	// �}�E�X�̏�Ԃ��擾
	if (SUCCEEDED(lpdinput_device_mouse_->GetDeviceState(sizeof(DIMOUSESTATE), &dimouse_state_)))
	{
		for (int mb_count = 0; mb_count < NUM_MB_MAX; mb_count++)
		{

			//�g���K�[�̏�񐶐�
			//����1�F�����ꂽ
			//����2�F������Ă��Ȃ�
			//1��2��XOR
			//���݂̏��F�����ꂽ
			mb_state_trigger_[mb_count] =
				(dimouse_state_.rgbButtons[mb_count] ^ dimouse_state_old_.rgbButtons[mb_count]) & dimouse_state_.rgbButtons[mb_count];

			//�����[�X�̏�񐶐�
			//����1�F�����ꂽ
			//����2�F������Ă���
			//1��2��XOR
			//���݂̏����F������Ă��Ȃ�
			mb_state_release_[mb_count] =
				(dimouse_state_.rgbButtons[mb_count] ^ dimouse_state_old_.rgbButtons[mb_count]) & ~dimouse_state_.rgbButtons[mb_count];

			//���s�[�g
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
			//�v���X
			mb_state_[mb_count] = dimouse_state_.rgbButtons[mb_count];
		}
	}
	else
	{
		lpdinput_device_mouse_->Acquire();

		//���݂̃f�o�C�X�̏�Ԃ��擾
		lpdinput_device_mouse_->GetDeviceState(sizeof(DIMOUSESTATE), &dimouse_state_);
	}
}

/*-----------------------------------------------------------------------------
/* ����������
/*---------------------------------------------------------------------------*/
void InputDeviceMouse::Init(void)
{
	dimouse_state_ = {0};

	// �e���[�N�̃N���A
	ZeroMemory(mb_state_, sizeof(mb_state_));
	ZeroMemory(mb_state_trigger_, sizeof(mb_state_trigger_));
	ZeroMemory(mb_state_release_, sizeof(mb_state_release_));
	ZeroMemory(mb_state_repeat_, sizeof(mb_state_repeat_));
	ZeroMemory(mb_state_repeat_count_, sizeof(mb_state_repeat_count_));
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void InputDeviceMouse::Uninit(void)
{
	if (lpdinput_device_mouse_ != nullptr)
	{
		SAFE_RELEASE_(lpdinput_device_mouse_);
	}
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void InputDeviceMouse::Update(const HWND &wndHandle)
{
	this->UpdateMouseState(wndHandle);
}

/*-----------------------------------------------------------------------------
/* �{�^�����������u��
-----------------------------------------------------------------------------*/
bool InputDeviceMouse::GetMBPress(int mibNum)
{
	return (mb_state_[mibNum] & 0x80) ? true : false;
}

/*-----------------------------------------------------------------------------
/* �{�^�����������u��
-----------------------------------------------------------------------------*/
bool InputDeviceMouse::GetMBTrigger(int mibNum)
{
	return (mb_state_trigger_[mibNum] & 0x80) ? true : false;
}

/*-----------------------------------------------------------------------------
/* �{�^�������������Ă�����
-----------------------------------------------------------------------------*/
bool InputDeviceMouse::GetMBRepeat(int mibNum)
{
	return  (mb_state_repeat_[mibNum] & 0x80) ? true : false;;
}

/*-----------------------------------------------------------------------------
/* �{�^����������u��
-----------------------------------------------------------------------------*/
bool InputDeviceMouse::GetMBRelease(int mibNum)
{
	return (mb_state_release_[mibNum] & 0x80) ? true : false;
}

/*-----------------------------------------------------------------------------
/* �}�E�X�J�[�\���̍��W�擾
-----------------------------------------------------------------------------*/
Vector2 InputDeviceMouse::GetMCursorPos(void) const
{
	return Vector2((float)mouse_cursor_pos_.x, (float)mouse_cursor_pos_.y);
}

/*=============================================================================
/*		End of File
=============================================================================*/

