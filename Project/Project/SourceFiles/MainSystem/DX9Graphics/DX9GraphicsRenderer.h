/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsRenderer.h] DirectX9�����_���[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FDirectX9�O���t�B�b�N�X�ɂ�郌���_���[�N���X
=============================================================================*/
#ifndef DX9GRAPHICS_RENDERER_H_
#define	DX9GRAPHICS_RENDERER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"

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

	DX9GraphicsRenderer* Create();

	void CreateRenderer(const LPDIRECT3DDEVICE9& lpd3dDevice);

	//�����_�����O�̊J�n�ƏI��
	bool RenderingBegin(void);
	void RenderingEnd(void);

private:
	bool Init(void);
	void Uninit(void);

private:
	LPDIRECT3DDEVICE9 lpd3d_device_;
};


#endif //DX9GRAPHICS_RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/
