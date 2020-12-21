/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsRenderer.h] DirectX9�����_���[�N���X��`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FDirectX9�O���t�B�b�N�X�ɂ�郌���_���[�̓���N���X���`�B
=============================================================================*/
#ifndef DX9GRAPHICS_RENDERER_H_
#define	DX9GRAPHICS_RENDERER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/

/*-------------------------------------
/* DirectX9�����_���[�N���X
-------------------------------------*/
class DX9GraphicsRenderer
{
public:
	DX9GraphicsRenderer(void);
	~DX9GraphicsRenderer(void);

	void CreateRenderer(const LPDIRECT3DDEVICE9& lpd3dDevice);
	bool RenderingBegin(void);
	void RenderingEnd(void);

	void SetRenderEnable(void);

	void SetRenderStateDisable(void);

	void SetRenderAlphaBlendEnable(void);
	void SetRenderAlphaBlendDisable(void);

private:
	void Init(void);
	void Uninit(void);

	void InitRenderer();
	void InitRenderState();
	void InitRenderTarget();
	void InitTextureStageState();
	void InitSumplerState();

private:
	LPDIRECT3DDEVICE9 lpd3d_device_;
};


#endif //DX9GRAPHICS_RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/
