/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsRenderer.cpp] DirectX9�̃f�o�C�X�ɂ�郌���_���[�̓�����`�B
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FDirectX9�̃f�o�C�X�ɂ�郌���_���[�̓�����`�����N���X�B
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "DX9GraphicsRenderer.h"
#include "../../Generic/Math.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
DX9GraphicsRenderer::DX9GraphicsRenderer(void)
	: lpd3d_device_(nullptr)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
DX9GraphicsRenderer::~DX9GraphicsRenderer(void)
{
}

/*-----------------------------------------------------------------------------
/* �O���t�B�b�N�f�o�C�X�̎擾�ƃ����_���[�̐���
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::CreateRenderer(const LPDIRECT3DDEVICE9& lpd3dDevice)
{
	this->lpd3d_device_ = lpd3dDevice;
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �����_�����O�J�n����
-----------------------------------------------------------------------------*/
bool DX9GraphicsRenderer::RenderingBegin()
{

	//// �r���[�|�[�g�p�����[�^(��ʃN���A����͈�)
	//D3DVIEWPORT9 view_port;
	////Vector2 screen_split_size = Vector2(500.f, 600.f);
	//Vector2 screen_split_size = Vector2((1980.f), (1080.f));
	//Vector2 offset = Vector2(0.f, 0.f);

	//// �r���[�|�[�g�̍�����W
	//view_port.X = offset.x_;
	//view_port.Y = offset.y_;

	//// �r���[�|�[�g�̕�
	//view_port.Width = screen_split_size.x_;
	//// �r���[�|�[�g�̍���
	//view_port.Height = screen_split_size.y_;

	//// �r���[�|�[�g�[�x�ݒ�
	//view_port.MinZ = 0.0f;
	//view_port.MaxZ = 1.0f;

	//// �r���[�|�[�g�ݒ�
	//if (FAILED(lpd3d_device_->SetViewport(&view_port)))
	//{
	//	return false;
	//}


	/*--- ��ʂ̃N���A ---*/
	//D3DCOLOR_RGBA(...)�͉�ʃN���A�̐F
	if (FAILED(lpd3d_device_->Clear(
		(DWORD)0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(50, 50, 50, 255),
		1.0f,
		0)))
	{
		return false;
	}


	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(lpd3d_device_->BeginScene()))
	{
		return true;
	}


	return false;
}

/*-----------------------------------------------------------------------------
/* �����_�����O�I������
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::RenderingEnd(void)
{
	if (lpd3d_device_ == nullptr) { return; }

	//Direct3D�ɂ��`��̏I��
	lpd3d_device_->EndScene();
	lpd3d_device_->Present(NULL, NULL, NULL, NULL);
}

/*-----------------------------------------------------------------------------
/* �����_�����O�I������
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::SetRenderStateDisable(void)
{
	lpd3d_device_->SetRenderState(D3DRS_ZENABLE, false);
	lpd3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	lpd3d_device_->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
}

/*-----------------------------------------------------------------------------
/* �A���t�@�u�����h�̗L����
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::SetRenderAlphaBlendEnable(void)
{
	//lpd3d_device_->SetRenderState();
	//lpd3d_device_->SetRenderState();
	//lpd3d_device_->SetRenderState();
}

/*-----------------------------------------------------------------------------
/* �A���t�@�u�����h�̖�����
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::SetRenderAlphaBlendDisable(void)
{
	//lpd3d_device_->SetRenderState();
	//lpd3d_device_->SetRenderState();
	//lpd3d_device_->SetRenderState();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::Init(void)
{
	if (lpd3d_device_ == nullptr) { return; }

	this->InitRenderer();
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::Uninit(void)
{

}

/*-----------------------------------------------------------------------------
/* �����_���[�̏�����
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitRenderer()
{
	this->InitRenderTarget();
	this->InitRenderState();
	this->InitTextureStageState();
	this->InitSumplerState();
}

/*-----------------------------------------------------------------------------
/* �����_�����O�X�e�[�g�̏�����
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitRenderState()
{
	//�����_�[�X�e�[�g�p�����[�^�[�̐ݒ�
	lpd3d_device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //�w�ʃJ�����O�ɂ���

	//���u�����h���s��
	//SRC...������`�����́B�܂�|���S���Ƀe�N�X�`����\��������
	//DEST...���łɕ`�悳��Ă����ʂ̂��ƁB
	//SRC_RGB * SRC_�� + DEST_RGB * (1 - SRC_��);
	//lpd3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//lpd3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//lpd3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/*-----------------------------------------------------------------------------
/* �����_�����O�^�[�Q�b�g�̏�����
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitRenderTarget()
{
	return;	//�Ȃ�����Ȃ�
}

/*-----------------------------------------------------------------------------
/* �e�N�X�`���[�X�e�[�W�X�e�[�g�̏�����
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitTextureStageState()
{
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

/*-----------------------------------------------------------------------------
/* �T���v���[�̏�����
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::InitSumplerState()
{
	//�e�N�X�`����UV���W�ւ̌J��Ԃ��������s��Ȃ��B
	lpd3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�\������I�u�W�F�N�g�ɑ΂��āA�����Ƃ��߂��e�N�X�`���̃t�B���^�����O���s���B
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

/*=============================================================================
/*		End of File
=============================================================================*/