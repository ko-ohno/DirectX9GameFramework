/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputDevice.cpp] ���̓f�o�C�X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���̓f�o�C�X�Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "InputDevice.h"
#include "InputDeviceKeyboard.h"
#include "InputDeviceMouse.h"
#include "InputDeviceXInput.h"

//�ÓI�ϐ��錾
InputDeviceKeyboard	* InputDevice::input_device_keyboard_;
InputDeviceMouse	* InputDevice::input_device_mouce_;
InputDeviceXInput	* InputDevice::input_device_xinput_;

// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECTINPUT8			InputDevice::lpdinput_object_;

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
InputDevice::InputDevice()
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
InputDevice::~InputDevice()
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
InputDevice * InputDevice::Create(void)
{
	return NEW InputDevice();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
void InputDevice::Init(void)
{
	//���̓I�u�W�F�N�g
	lpdinput_object_		= nullptr;

	//�e���̓f�o�C�X�ւ̃|�C���^
	input_device_mouce_		= nullptr;
	input_device_keyboard_	= nullptr;
	input_device_xinput_	= nullptr;
}

/*-----------------------------------------------------------------------------
/* �I������
-----------------------------------------------------------------------------*/
void InputDevice::Uninit(void)
{	
	// lpdinput_object_ptr_�I�u�W�F�N�g�̊J��
	SAFE_RELEASE_(lpdinput_object_);

	//�e�f�o�C�X�̔j��
	SAFE_DELETE_(input_device_keyboard_); 
	SAFE_DELETE_(input_device_mouce_); 
	SAFE_DELETE_(input_device_xinput_); 
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void InputDevice::Update(const HWND &wndHandle)
{
	//�e���̓f�o�C�X�̍X�V�@
	input_device_keyboard_->Update();
	input_device_mouce_->Update(wndHandle);
	input_device_xinput_->Update();
}

/*-----------------------------------------------------------------------------
/* �L�[�{�[�h�̃C���X�^���X���擾
-----------------------------------------------------------------------------*/
InputDeviceKeyboard * InputDevice::GetDeviceInstanceKeyboard(void)
{
	return input_device_keyboard_;
}

/*-----------------------------------------------------------------------------
/* �}�E�X�̃C���X�^���X���擾
-----------------------------------------------------------------------------*/
InputDeviceMouse * InputDevice::GetDeviceInstanceMouse(void)
{
	return input_device_mouce_;
}

/*-----------------------------------------------------------------------------
/* �R���g���[���[�̃C���X�^���X���擾
-----------------------------------------------------------------------------*/
InputDeviceXInput * InputDevice::GetDeviceInstanceXInput(void)
{
	return input_device_xinput_;
}

/*-----------------------------------------------------------------------------
/* ���̓f�o�C�X�̐���
-----------------------------------------------------------------------------*/
bool InputDevice::CreateInputDevice(const HINSTANCE &hInstance, const HWND &wndHandle)
{
	//���̓f�o�C�X�̐���
	{
		//DirectInput�C���^�[�t�F�[�X�I�u�W�F�N�g�̐���
		if (FAILED(CreateDirectInputObject(hInstance)))
		{
			return false;
		}

		//�L�[�{�[�h�̐���
		if (CreateDeviceKyeboard(lpdinput_object_, wndHandle) == false)
		{
			return false;
		}

		//�}�E�X�̓��͐���
		if (CreateDeviceMouse(lpdinput_object_, wndHandle) == false)
		{
			return false;
		}

		//�p�b�h�̓��͐���
		if (CreateDeviceXInput() == false)
		{
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* DirectInputObject�̐���
-----------------------------------------------------------------------------*/
HRESULT InputDevice::CreateDirectInputObject(const HINSTANCE &hInstance)
{
	if(hInstance == nullptr) { assert(!"DirectInuput�I�u�W�F�N�g�������ɁAhInstance��nullptr�ł����B"); }
	if (lpdinput_object_ == nullptr)
	{
		// Direct8Input�C���^�[�t�F�[�X�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&lpdinput_object_, nullptr)))
		{
			return S_FALSE;
		};
	}
	return S_OK;
}

/*-----------------------------------------------------------------------------
/* �L�[�{�[�h�p���̓f�o�C�X�̐���
-----------------------------------------------------------------------------*/
bool InputDevice::CreateDeviceKyeboard(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle)
{
	this->input_device_keyboard_ = NEW InputDeviceKeyboard();
	if (FAILED(input_device_keyboard_->CreateDeviceKeyboard(lpdinputObject, wndHandle)))
	{
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �}�E�X�p���̓f�o�C�X�̐���
-----------------------------------------------------------------------------*/
bool InputDevice::CreateDeviceMouse(const LPDIRECTINPUT8 &lpdinputObject, const HWND &wndHandle)
{
	this->input_device_mouce_ = NEW InputDeviceMouse();
	if (FAILED(input_device_mouce_->CrateInputDeviceMouse(lpdinputObject, wndHandle)))
	{
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* XInput�^�C�v�̃R���g���[���p���̓f�o�C�X�̐���
-----------------------------------------------------------------------------*/
bool InputDevice::CreateDeviceXInput(void)
{
	this->input_device_xinput_ = NEW InputDeviceXInput();
	{
		input_device_xinput_->Update();
	}
	return true;
}

/*==============================================================================
/*		End of file
==============================================================================*/
