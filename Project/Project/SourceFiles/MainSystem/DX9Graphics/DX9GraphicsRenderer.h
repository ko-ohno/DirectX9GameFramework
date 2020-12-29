/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsRenderer.h] DirectX9レンダラークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：DirectX9グラフィックスによるレンダラークラス
=============================================================================*/
#ifndef DX9GRAPHICS_RENDERER_H_
#define	DX9GRAPHICS_RENDERER_H_

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"

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

	DX9GraphicsRenderer* Create();

	void CreateRenderer(const LPDIRECT3DDEVICE9& lpd3dDevice);

	//レンダリングの開始と終了
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
