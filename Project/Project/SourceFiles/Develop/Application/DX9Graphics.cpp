/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9Graphics.cpp] DirectX9�O���t�B�b�N�X�̑������N���X�̓����`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����_�����O�Ɋւ��鏈�����e�N���X�ɓ`����N���X�̓����`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "DX9Graphics.h"
#include "DX9Graphics/DX9GraphicsDevice.h"
#include "DX9Graphics/DX9GraphicsRenderer.h"
#include "Math.h"
#include "../DebugCode/DebugFunction.h"


//�ÓI�ϐ��錾
LPDIRECT3DDEVICE9	  DX9Graphics::lpd3d_device_;		//Direct3D�f�o�C�X
DX9GraphicsDevice*	  DX9Graphics::graphics_device_;	//�f�o�C�X�N���X
DX9GraphicsRenderer*  DX9Graphics::graphics_renderer_;	//�����_���[�N���X

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
DX9Graphics::DX9Graphics(void)
	: screen_size_(0.f, 0.f)
	, screen_scaler_(1.f)
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
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
DX9Graphics* DX9Graphics::Create()
{
	return NEW DX9Graphics();
}

/*-----------------------------------------------------------------------------
/* DirectX9�O���t�B�b�N�X�̐���
-----------------------------------------------------------------------------*/
bool DX9Graphics::CreateDX9Graphics(const HWND& windowHandle, const Vector2& screenSize)
{
	//��ʃT�C�Y���擾
	screen_size_ = screenSize;

	//�f�o�C�X�ƃ����_���[�̐���
	lpd3d_device_ = CreateGraphicsDevice(windowHandle, screenSize);
	if (lpd3d_device_ == nullptr)
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("�O���t�B�b�N�X�̃f�o�C�X���쐬�ł��܂���ł����I");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return false;
	}

	//�����_���[���쐬
	CreateDX9Renderer(lpd3d_device_);
	return true;
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
	lpd3d_device_ = nullptr;
	graphics_device_ = nullptr;
	graphics_renderer_ = nullptr;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void DX9Graphics::Uninit(void)
{
	SAFE_RELEASE_(lpd3d_device_);
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
LPDIRECT3DDEVICE9 DX9Graphics::CreateGraphicsDevice(const HWND& windowHandle, const Vector2& screenSize)
{
	graphics_device_ = graphics_device_->Create();
	return graphics_device_->CreateGraphicsDevice(windowHandle, screenSize);
}

/*-----------------------------------------------------------------------------
/* �����_���[�̐�������
-----------------------------------------------------------------------------*/
void DX9Graphics::CreateDX9Renderer(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	graphics_renderer_ = graphics_renderer_->Create();
	graphics_renderer_->CreateRenderer(lpd3d_device);
}

/*=============================================================================
/*		End of File
=============================================================================*/