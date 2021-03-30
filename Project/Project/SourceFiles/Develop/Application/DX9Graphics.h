/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9Graphics.h] DirectX9グラフィックス管理クラス定義
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：レンダラーからデバイス生成などの処理クラスのまとめ役クラスの定義
=============================================================================*/
#ifndef DX9GRAPHICS_H_
#define	DX9GRAPHICS_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "Math.h"

/*--- 構造体定義 ---*/

/*-------------------------------------
/* DX9グラフィックス管理クラス
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

	//画面サイズの取得
	Vector2 GetScreenSize(void) { return screen_size_; }

private:
	void Init(void);
	void Uninit(void);

	LPDIRECT3DDEVICE9 CreateGraphicsDevice(const HWND& windowHandle, const class Vector2& screenSize);
	void CreateDX9Renderer(const LPDIRECT3DDEVICE9& lpd3dDevice);

private:
	static LPDIRECT3DDEVICE9		   lpd3d_device_;		//Direct3Dデバイス
	static class DX9GraphicsDevice*	   graphics_device_;	//デバイスクラス
	static class DX9GraphicsRenderer*  graphics_renderer_;	//レンダラークラス

private:
	Vector2 screen_size_;
};

#endif //DX9GRAPHICS_H_
/*=============================================================================
/*		End of File
=============================================================================*/
