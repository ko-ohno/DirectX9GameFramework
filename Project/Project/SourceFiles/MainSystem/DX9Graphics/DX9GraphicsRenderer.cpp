/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsRenderer.cpp] DirectX9�����_���[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FDirectX9�O���t�B�b�N�X�ɂ�郌���_���[�N���X
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
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
DX9GraphicsRenderer* DX9GraphicsRenderer::Create()
{
	return NEW DX9GraphicsRenderer();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool DX9GraphicsRenderer::Init(void)
{
	if (lpd3d_device_ == nullptr) { return false; }

	//�����_�����O�p�C�v���C���̏�����
	lpd3d_device_->SetPixelShader(nullptr);
	lpd3d_device_->SetVertexShader(nullptr);

	//�����_�[�X�e�[�g�̏�����
	//lpd3d_device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //�w�ʃJ�����O�ɂ��Ȃ�
	lpd3d_device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //�w�ʃJ�����O�ɂ���

	//���C�e�B���O��������
	lpd3d_device_->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�[�x�o�b�t�@�̐ݒ��������
	lpd3d_device_->SetRenderState(D3DRS_ZENABLE, FALSE);

	//�A���t�@������L����
	lpd3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	//�A���t�@�e�X�g�̎g�p�𖳌���
	lpd3d_device_->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�A���t�@�����̐ݒ�̏�����
	lpd3d_device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	lpd3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpd3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�N���C�A���g�̈�̔�`�敔���Ƀs�N�Z�����������܂Ȃ��悤�ɐݒ�
	lpd3d_device_->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);

	//�v���~�e�B�u�̓h��Ԃ����@��������
	lpd3d_device_->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	//�t�H�O��K�p���邩�̐ݒ�𖳌��ɂ��ď�����
	lpd3d_device_->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//�F�̍����̐ݒ�̏�����
	lpd3d_device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	//�A���t�@�����̐ݒ�̏�����
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	lpd3d_device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//�\������I�u�W�F�N�g�ɑ΂��āA�����Ƃ��߂��e�N�X�`���̃t�B���^�����O���s���B
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//�e�N�X�`����UV���W�ւ̌J��Ԃ��������s��Ȃ��B
	lpd3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	lpd3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void DX9GraphicsRenderer::Uninit(void)
{
	//���ׂĂ̐ݒ��߂�
	this->Init();
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
	/*--- ��ʂ̃N���A ---*/
	//D3DCOLOR_RGBA(...)�͉�ʃN���A�̐F
	if (FAILED(lpd3d_device_->Clear(0UL
								   , nullptr
								   , (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER)
								   , D3DCOLOR_RGBA(50, 50, 50, 255)
								   , 1.0f
								   , 0UL)))
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

/*=============================================================================
/*		End of File
=============================================================================*/