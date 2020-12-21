/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsRenderer.h] DirectX9レンダラークラス定義
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：DirectX9グラフィックスによるレンダラーの動作クラスを定義。
=============================================================================*/
#ifndef DX9GRAPHICS_RENDERER_H_
#define	DX9GRAPHICS_RENDERER_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/

/*-------------------------------------
/* DirectX9レンダラークラス
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
