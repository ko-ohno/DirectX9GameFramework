/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputCheck.cpp] ���͏�񒆌p�N���X������
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�f�o�C�X�ɂ����͏��𒆌p����N���X������
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "InputCheck.h"
#include "InputDevice.h"
#include "InputDeviceKeyboard.h"
#include "InputDeviceMouse.h"
#include "../Math.h"

//�ÓI�ϐ��錾
InputDevice *InputCheck::input_device_;

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
InputCheck::InputCheck(void)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
InputCheck::~InputCheck(void)
{
}

/*-----------------------------------------------------------------------------
/* �f�o�C�X�̏�Ԃ��X�V
-----------------------------------------------------------------------------*/
void InputCheck::SetInputDeviceInstance(InputDevice * inputDevice)
{
	input_device_ = inputDevice;
}

/*-----------------------------------------------------------------------------
/* �{�^������������
-----------------------------------------------------------------------------*/
bool InputCheck::KeyPress(int dikKeynum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceKeyboard()->GetKeyboardPress(dikKeynum);
}

/*-----------------------------------------------------------------------------
/* �{�^�����������u��
-----------------------------------------------------------------------------*/
bool InputCheck::KeyTrigger(int dikKeynum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceKeyboard()->GetKeyboardTrigger(dikKeynum);
}

/*-----------------------------------------------------------------------------
/* �{�^�����������Ă�����
-----------------------------------------------------------------------------*/
bool InputCheck::KeyRepeat(int dikKeynum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceKeyboard()->GetKeyboardRepeat(dikKeynum);
}

/*-----------------------------------------------------------------------------
/* �{�^���J�����m����
-----------------------------------------------------------------------------*/
bool InputCheck::KeyRelease(int dikKeynum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceKeyboard()->GetKeyboardRelease(dikKeynum);
}

/*-----------------------------------------------------------------------------
/* �{�^������������
-----------------------------------------------------------------------------*/
bool InputCheck::MButtonPress(MibNum mibNum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceMouse()->GetMBPress((int)mibNum);
}

/*-----------------------------------------------------------------------------
/* �{�^�����������u��
-----------------------------------------------------------------------------*/
bool InputCheck::MButtonTrigger(MibNum mibNum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceMouse()->GetMBTrigger((int)mibNum);
}

/*-----------------------------------------------------------------------------
/* �{�^�������������Ă�����
-----------------------------------------------------------------------------*/
bool InputCheck::MButtonRepeat(MibNum mibNum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceMouse()->GetMBRepeat((int)mibNum);
}

/*-----------------------------------------------------------------------------
/* �{�^����������u��
-----------------------------------------------------------------------------*/
bool InputCheck::MButtonRelease(MibNum mibNum)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceMouse()->GetMBRelease((int)mibNum);
}

/*-----------------------------------------------------------------------------
/* �}�E�X�J�[�\���̈ʒu
-----------------------------------------------------------------------------*/
Vector2 InputCheck::MouseCursorPos(void)
{
	if (input_device_ == nullptr) { return Vector2(0.0f, 0.0f); }
	return input_device_->GetDeviceInstanceMouse()->GetMCursorPos();;
}

/*-----------------------------------------------------------------------------
/* �{�^������������
-----------------------------------------------------------------------------*/
bool InputCheck::XInputPress(PadIndex padIndex, XInputButton xibIndex)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceXInput()->GetXIBPress((int)padIndex, xibIndex);
}

/*-----------------------------------------------------------------------------
/* �{�^�����������u��
-----------------------------------------------------------------------------*/
bool InputCheck::XInputTrigger(PadIndex padIndex, XInputButton xibIndex)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceXInput()->GetXIBTrigger((int)padIndex, xibIndex);
}

/*-----------------------------------------------------------------------------
/* �{�^�������������Ă�����u��
-----------------------------------------------------------------------------*/
bool InputCheck::XInputRepeat(PadIndex padIndex, XInputButton xibIndex)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceXInput()->GetXIBRepeat((int)padIndex, xibIndex);
}

/*-----------------------------------------------------------------------------
/* �{�^����������u��
-----------------------------------------------------------------------------*/
bool InputCheck::XInputRelease(PadIndex padIndex, XInputButton xibIndex)
{
	if (input_device_ == nullptr) { return false; }
	return input_device_->GetDeviceInstanceXInput()->GetXIBRelease((int)padIndex, xibIndex);
}

/*-----------------------------------------------------------------------------
/* ���X�e�B�b�N�̎擾
-----------------------------------------------------------------------------*/
Vector2 InputCheck::XInputThumbLeft(PadIndex padIndex)
{
	if (input_device_ == nullptr) { return Vector2(0.0f, 0.0f); }
	//�f�[�^���擾
	Vector2 thumb_left;
	thumb_left.x_ = (float)input_device_->GetDeviceInstanceXInput()->GetThumbLX((int)padIndex);
	thumb_left.y_ = (float)input_device_->GetDeviceInstanceXInput()->GetThumbLY((int)padIndex);

	//�x�N�g���̐��K��
	D3DXVECTOR3 vec_thumb(thumb_left.x_, 0.0f, thumb_left.y_);
	D3DXVec3Normalize(&vec_thumb, &vec_thumb);

	//���H�ς݃f�[�^��ۑ�
	thumb_left.x_ = std::round(vec_thumb.x * 100) / 100;
	thumb_left.y_ = std::round(vec_thumb.z * 100) / 100;
	return thumb_left;
}

/*-----------------------------------------------------------------------------
/* �E�X�e�B�b�N�̎擾
-----------------------------------------------------------------------------*/
Vector2 InputCheck::XInputThumbRight(PadIndex padIndex)
{
	if (input_device_ == nullptr) { return Vector2( 0.0f, 0.0f); }
	//�f�[�^���擾
	Vector2 thumb_right;
	thumb_right.x_ = (float)input_device_->GetDeviceInstanceXInput()->GetThumbRX((int)padIndex);
	thumb_right.y_ = (float)input_device_->GetDeviceInstanceXInput()->GetThumbRY((int)padIndex);

	//�x�N�g���̐��K��
	D3DXVECTOR3 vec_thumb(thumb_right.x_, 0.0f, thumb_right.y_);
	D3DXVec3Normalize(&vec_thumb, &vec_thumb);

	//���H�ς݃f�[�^��ۑ�
	thumb_right.x_ = std::round(vec_thumb.x * 100) / 100;
	thumb_right.y_ = std::round(vec_thumb.z * 100) / 100;

	return thumb_right;
}

/*=============================================================================
/*		End of File
=============================================================================*/
