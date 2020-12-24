/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsDevice.h] DirectX9�̃O���t�B�b�N�f�o�C�X�����N���X��`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FDirectX9�̃O���t�B�b�N�f�o�C�X�������邽�߂̃N���X��`
=============================================================================*/
#ifndef DX9GRAPHICS_DEVICE_H_
#define DX9GRAPHICS_DEVICE_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "../../Generic/Math.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/

/*-------------------------------------
/* �O���t�B�b�N�f�o�C�X�̐����N���X
-------------------------------------*/
class DX9GraphicsDevice
{
public:
	DX9GraphicsDevice(void);
	~DX9GraphicsDevice(void);

	//Direct3D�f�o�C�X�̐�������
	LPDIRECT3DDEVICE9 CreateGraphicsDevice(const HWND& windowHandle, const Vector2& screenSize);

	//�v���[���g�p�����[�^��������
	D3DPRESENT_PARAMETERS CreatePresentParam(const Vector2& screenSize, const HWND& windowHandle, const BOOL& isWindowed);

private:
	void Init(void);
	void Uninit(void);

	//�C���^�[�t�F�[�X�̎擾
	LPDIRECT3D9 CreateD3DInterface(void);
	//�f�B�X�v���C���[�h�̎擾
	HRESULT GetDisplayMode(void);

	//�f�o�C�X��������
	LPDIRECT3DDEVICE9 CreateLPD3DDevice(const HWND& windowHandle, const D3DPRESENT_PARAMETERS& d3dpp);
	LPDIRECT3DDEVICE9 CreateLPD3DDeviceHALMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp);
	LPDIRECT3DDEVICE9 CreateLPD3DDeviceLeastHALMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp);
	LPDIRECT3DDEVICE9 CreateLPD3DDeviceREFMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp);
	LPDIRECT3DDEVICE9 CreateLPD3DDeviceLeastREFMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9					lpd3d_interface_;	//DIRECT3D�C���^�[�t�F�C�X
	D3DDISPLAYMODE				d3d_display_mode_;	//�f�B�X�v���C���[�h
};

#endif //DX9GRAPHICS_DEVICE_H_
/*=============================================================================
/*		End of File
=============================================================================*/