/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsDevice.cpp] DirectX9�̃O���t�B�b�N�f�o�C�X�����N���X�����`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FDirectX9�̃O���t�B�b�N�f�o�C�X�𐶐����铮���`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "StdAfx.h"
#include "DX9GraphicsDevice.h"
#include "Math/Math.h"
#include "DebugCode/DebugFunction.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
DX9GraphicsDevice::DX9GraphicsDevice(void)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
DX9GraphicsDevice::~DX9GraphicsDevice(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
DX9GraphicsDevice* DX9GraphicsDevice::Create()
{
	return NEW DX9GraphicsDevice();
}

/*-----------------------------------------------------------------------------
/* DirectX9�����_���[�f�o�C�X�̐�������
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateGraphicsDevice(const HWND& windowHandle, const Vector2& screenSize)
{
	LPDIRECT3DDEVICE9		lpd3d_device;
	D3DPRESENT_PARAMETERS	d3dpp;

	lpd3d_interface_ = CreateD3DInterface();
	if (FAILED(lpd3d_interface_))
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("Direct3D�C���^�[�t�F�[�X�̐����Ɏ��s���܂����I");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return nullptr;
	}

	//�f�B�X�v���C���[�h�̎擾
	if (FAILED(GetDisplayMode()))
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂����I");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return nullptr;
	}

	//�����_�����O�f�o�C�X�̃v���[���g�p�����[�^�̐���
	d3dpp = CreatePresentParam(screenSize, windowHandle, TRUE);

	//LPD3D�f�o�C�X�̐���
	lpd3d_device = CreateLPD3DDevice(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	return nullptr;
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
void DX9GraphicsDevice::Init(void)
{
	//�ϐ��̏�����
	lpd3d_interface_ = nullptr;
	d3d_display_mode_ = { 0 };
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void DX9GraphicsDevice::Uninit(void)
{
	SAFE_RELEASE_(lpd3d_interface_);//�C���^�[�t�F�[�X�̊J��
}

/*-----------------------------------------------------------------------------
/* Direct3D�C���^�[�t�F�[�X�̐���
-----------------------------------------------------------------------------*/
LPDIRECT3D9 DX9GraphicsDevice::CreateD3DInterface(void)
{
	//Direct3D�C���^�[�t�F�C�X�̍쐬
	LPDIRECT3D9 lpd3d_interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (lpd3d_interface == nullptr) { return nullptr; }
	return lpd3d_interface;
}

/*-----------------------------------------------------------------------------
/* ���݂̃f�B�X�v���C���[�h�̎擾
-----------------------------------------------------------------------------*/
HRESULT DX9GraphicsDevice::GetDisplayMode(void)
{
	//���݂̃f�B�X�v���C���[�h���擾
	return lpd3d_interface_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3d_display_mode_);
}

/*-----------------------------------------------------------------------------
/* �O���t�B�b�N�f�o�C�X�̃v���[���g�p�����[�^��������
-----------------------------------------------------------------------------*/
//TRUE�ŃE�B���h�E���[�h/FALSE�Ńt���X�N���[�����[�h
D3DPRESENT_PARAMETERS DX9GraphicsDevice::CreatePresentParam(const Vector2& screenSize, const HWND& windowHandle, const BOOL& isWindowed)
{
	D3DPRESENT_PARAMETERS d3dpp;

	{//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�[�̐ݒ�
		ZeroMemory(&d3dpp, sizeof(&d3dpp));								//D3DPresentParam�̏�����
		d3dpp.BackBufferWidth = (UINT)screenSize.x_;					//�X�N���[���̃N���C�A���g�̈�̕�
		d3dpp.BackBufferHeight = (UINT)screenSize.y_;					//�X�N���[���̃N���C�A���g�̈�̍���
		d3dpp.BackBufferFormat = d3d_display_mode_.Format;				//GetAdapterDisplayMode()�Ŏ擾�������݂̃f�B�X�v���C�̃��[�h
		d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;					//�摜�����ꂢ�ɂȂ邪�A�n�[�h���Ή����Ă��Ȃ��\�������邩�疳���ɂ��Ă���
		d3dpp.MultiSampleQuality = 0;									//�}���`�T���v���̕i���BD3DMULTISAMPLE_NONE���w�肵���̂�0�ɂ���B
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̐؂�ւ������`
		d3dpp.hDeviceWindow = windowHandle;								//nullptr�Ŏ����Ō��݂̃E�B���h�E�Ƀt�H�[�J�X�����
		d3dpp.Windowed = isWindowed;									//TRUE�ŃE�B���h�E���[�h/FALSE�Ńt���X�N���[�����[�h
		d3dpp.EnableAutoDepthStencil = TRUE;							//�[�x�X�e���V���o�b�t�@��ݒ�AZ�o�b�t�@�Ȃǂ̉��s��ێ����邩�̐ݒ�
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�X�e���V���o�b�t�@�̃t�H�[�}�b�g
		d3dpp.Flags = 0;												//�o�b�N�o�b�t�@����t�����g�o�b�t�@�֓]������Ƃ��̐ݒ�B
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//�t���X�N���[��/�E�B���h�E�ǂ���̃��[�h�ł�DEFAULT�ő��v�B
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�t���[���`��I����̐؂�ւ���
	}

	return d3dpp;
}

/*-----------------------------------------------------------------------------
/* DirectX9�����_���[�f�o�C�X����
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDevice(const HWND& windowHandle, const D3DPRESENT_PARAMETERS& d3dPP)
{
	if (windowHandle == nullptr) { return nullptr; }

	D3DPRESENT_PARAMETERS d3dpp = d3dPP;
	LPDIRECT3DDEVICE9 lpd3d_device;

	//�`�揈���ƃf�o�C�X�쐬������n�[�h�E�F�A�ōs���B
	lpd3d_device = CreateLPD3DDeviceHALMode(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	//�`�揈�����n�[�h�E�F�A�ŁA�f�o�C�X�쐬������\�t�g�E�F�A�ōs���B
	lpd3d_device = CreateLPD3DDeviceLeastHALMode(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	//�`�揈���\�t�g�E�F�A�ŁA�f�o�C�X�쐬������n�[�h�E�F�A�ōs���B
	lpd3d_device = CreateLPD3DDeviceREFMode(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	//�`�揈���ƃf�o�C�X�쐬������\�t�g�E�F�A�ōs���B
	lpd3d_device = CreateLPD3DDeviceLeastREFMode(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	//���b�Z�[�W�̕\��
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("���ׂĂ�Direct3D�f�o�C�X�̍쐬�Ɏ��s���܂����B");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}

	return nullptr;
}

/*-----------------------------------------------------------------------------
/* HAL���[�h�ɂ�鍂���ȃf�o�C�X�̐�������
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDeviceHALMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp)
{
	LPDIRECT3DDEVICE9 lpd3d_device;

	//<�`��>��<���_����>���n�[�h�E�F�A�ōs��
	//D3DDEVTYPE_HAL�A�p�t�H�[�}���X���n�[�h�E�F�A�Ɉˑ�����ݒ�
	if (SUCCEEDED(lpd3d_interface_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,//�n�[�h�E�F�A���_����
		&d3dpp, &lpd3d_device)))
	{
		return lpd3d_device;
	}

	//��L�̏��������s�����ꍇ�ɁA���L�̃��b�Z�[�W�{�b�N�X��\���B
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("HAL���[�h�ɂ��Direct3D�f�o�C�X���쐬�ł��܂���ł����B\nHAL���[�h�ɂ��Œ���̃f�o�C�X�쐬����ōĎ��s���܂��B");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* HAL���[�h�ɂ��ዉ�ȃf�o�C�X�̐�������
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDeviceLeastHALMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp)
{
	LPDIRECT3DDEVICE9 lpd3d_device;

	//<�`��>���n�[�h�E�F�A�ŁA<���_����>���\�t�g�E�F�A�ōs��
	//D3DDEVTYPE_HAL�A�p�t�H�[�}���X���n�[�h�E�F�A�Ɉˑ�����ݒ�
	if (SUCCEEDED(lpd3d_interface_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandle,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &lpd3d_device)))
	{
		return lpd3d_device;
	}

	//��L�̏��������s�����ꍇ�ɁA���L�̃��b�Z�[�W�{�b�N�X��\���B
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("HAL���[�h�ɂ��Œ���̃f�o�C�X�쐬�����Direct3D�f�o�C�X���쐬�ł��܂���ł����B\n��REF���[�h�ɂ��f�o�C�X�쐬����ōĎ��s���܂��B");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* REF���[�h�ɂ�鍂���ȃf�o�C�X�̐�������
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDeviceREFMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp)
{
	LPDIRECT3DDEVICE9 lpd3d_device;

	//<�`��>���\�t�g�E�F�A�ŁA<���_����>���n�[�h�E�F�A�ōs��
	//D3DDEVTYPE_REF�A�p�t�H�[�}���X���\�t�g�E�F�A�Ɉˑ�����ݒ�
	if (SUCCEEDED(lpd3d_interface_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_REF,
		windowHandle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &lpd3d_device)))
	{
		return lpd3d_device;
	}

	//��L�̏��������s�����ꍇ�ɁA���L�̃��b�Z�[�W�{�b�N�X��\���B
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("REF���[�h�ɂ��f�o�C�X�쐬�����Direct3D�f�o�C�X���쐬�ł��܂���ł����BREF���[�h�ɂ��Œ���̃f�o�C�X�쐬����ōĎ��s���܂��B");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* REF���[�h�ɂ��ዉ�ȃf�o�C�X�̐�������
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDeviceLeastREFMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp)
{
	LPDIRECT3DDEVICE9 lpd3d_device;

	//<�`��>��<���_����>���\�t�g�E�F�A�ōs��
	//D3DDEVTYPE_REF�A�p�t�H�[�}���X���\�t�g�E�F�A�Ɉˑ�����ݒ�
	if (SUCCEEDED(lpd3d_interface_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_REF,
		windowHandle,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &lpd3d_device)))
	{
		return lpd3d_device;
	}

	//��L�̏��������s�����ꍇ�ɁA���L�̃��b�Z�[�W�{�b�N�X��\���B
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("REF���[�h�ɂ��Œ���̃f�o�C�X�쐬�����Direct3D�f�o�C�X���쐬�ł��܂���ł����B");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}
	return nullptr;
}

/*=============================================================================
/*		End of File
=============================================================================*/