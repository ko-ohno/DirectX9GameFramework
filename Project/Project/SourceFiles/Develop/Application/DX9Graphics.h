/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9Graphics.h] DirectX9�O���t�B�b�N�X�Ǘ��N���X��`
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����_���[����f�o�C�X�����Ȃǂ̏����N���X�̂܂Ƃߖ��N���X�̒�`
=============================================================================*/
#ifndef DX9GRAPHICS_H_
#define	DX9GRAPHICS_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "Math.h"

/*--- �\���̒�` ---*/

/*-------------------------------------
/* DX9�O���t�B�b�N�X�Ǘ��N���X
-------------------------------------*/
class DX9Graphics
{
public:
	DX9Graphics(void);
	~DX9Graphics(void);

	static DX9Graphics* Create();

	bool CreateDX9Graphics(const HWND& windowHandle, const class Vector2& screenSize);

	static LPDIRECT3DDEVICE9* GetLPD3DDevice(void);

	bool RenderingBegin(void);
	void RenderingEnd(void);

	//��ʃT�C�Y�̎擾
	Vector2 GetScreenSize(void) { return screen_size_; }

private:
	void Init(void);
	void Uninit(void);

	LPDIRECT3DDEVICE9 CreateGraphicsDevice(const HWND& windowHandle, const class Vector2& screenSize);
	void CreateDX9Renderer(const LPDIRECT3DDEVICE9& lpd3dDevice);

private:
	static LPDIRECT3DDEVICE9		   lpd3d_device_;		//Direct3D�f�o�C�X
	static class DX9GraphicsDevice*	   graphics_device_;	//�f�o�C�X�N���X
	static class DX9GraphicsRenderer*  graphics_renderer_;	//�����_���[�N���X

private:
	Vector2 screen_size_;
};

#endif //DX9GRAPHICS_H_
/*=============================================================================
/*		End of File
=============================================================================*/
