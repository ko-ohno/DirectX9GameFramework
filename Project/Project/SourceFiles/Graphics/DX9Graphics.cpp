/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9Graphics.cpp] DirectX9�O���t�B�b�N�X�̑������N���X�̓����`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����_�����O�Ɋւ��鏈�����e�N���X�ɓ`����N���X�̓����`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "DX9Graphics.h"
#include "DX9GraphicsDevice.h"
#include "DX9GraphicsRenderer.h"
#include "../Generic/Math.h"


//�ÓI�ϐ��錾
LPDIRECT3DDEVICE9		DX9Graphics::lpd3d_device_;			//Direct3D�f�o�C�X
DX9GraphicsDevice* DX9Graphics::graphics_device_;		//�f�o�C�X�N���X
DX9GraphicsRenderer* DX9Graphics::graphics_renderer_;	//�����_���[�N���X

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
DX9Graphics::DX9Graphics(void)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
DX9Graphics::~DX9Graphics(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* f�f�X�g���N�^�t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
DX9Graphics* DX9Graphics::Create()
{
	return NEW DX9Graphics();
}

/*-----------------------------------------------------------------------------
/* DirectX9�O���t�B�b�N�X�̐���
-----------------------------------------------------------------------------*/
void DX9Graphics::CreateDX9Graphics(const HWND& wndHandle, const Math::Vector2& screenSize)
{
	//�f�o�C�X�ƃ����_���[�̐���
	lpd3d_device_ = CreateDevice(wndHandle, screenSize);
	CreateRenderer(lpd3d_device_);
}

/*-----------------------------------------------------------------------------
/* �f�o�C�X�̎擾
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9* DX9Graphics::GetLPD3DDevice(void)
{
	return &lpd3d_device_;
}

/*-----------------------------------------------------------------------------
/* �O���t�B�b�N�X�̏�����
/*---------------------------------------------------------------------------*/
void DX9Graphics::Init(void)
{
	graphics_device_ = nullptr;
	graphics_renderer_ = nullptr;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void DX9Graphics::Uninit(void)
{
	SAFE_DELETE_(graphics_device_);
	SAFE_DELETE_(graphics_renderer_);
}

/*-----------------------------------------------------------------------------
/* �����_�����O�̊J�n
-----------------------------------------------------------------------------*/
bool DX9Graphics::RenderingBegin(void)
{
	return graphics_renderer_->RenderingBegin();
}

/*-----------------------------------------------------------------------------
/* �����_�����O�̏I��
-----------------------------------------------------------------------------*/
void DX9Graphics::RenderingEnd(void)
{
	graphics_renderer_->RenderingEnd();
}

/*-----------------------------------------------------------------------------
/* �O���t�B�b�N�f�o�C�X�̐�������
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9Graphics::CreateDevice(const HWND& wndHandle, const Math::Vector2& screenSize)
{
	graphics_device_ = NEW DX9GraphicsDevice();
	return graphics_device_->CreateGraphicsDevice(wndHandle, screenSize);
}

/*-----------------------------------------------------------------------------
/* �����_���[�̐�������
-----------------------------------------------------------------------------*/
void DX9Graphics::CreateRenderer(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	graphics_renderer_ = NEW DX9GraphicsRenderer();
	graphics_renderer_->CreateRenderer(lpd3d_device);
}

/*=============================================================================
/*		End of File
=============================================================================*/