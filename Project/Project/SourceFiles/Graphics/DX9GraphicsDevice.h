/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsDevice.h] DirectX9のグラフィックデバイス生成クラス定義
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：DirectX9のグラフィックデバイス生成するためのクラス定義
=============================================================================*/
#ifndef DX9GRAPHICS_DEVICE_H_
#define DX9GRAPHICS_DEVICE_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "../Generic/Math.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/

/*-------------------------------------
/* グラフィックデバイスの生成クラス
-------------------------------------*/
class DX9GraphicsDevice
{
public:
	DX9GraphicsDevice(void);
	~DX9GraphicsDevice(void);

	//Direct3Dデバイスの生成処理
	LPDIRECT3DDEVICE9 CreateGraphicsDevice(const HWND& wndHandle, const Math::Vector2& screenSize);

	//プレゼントパラメータ生成処理
	D3DPRESENT_PARAMETERS CreatePresentParam(const Math::Vector2& screenSize, const HWND& wndHandle, const BOOL& isWindowed);

private:
	void Init(void);
	void Uninit(void);

	//インターフェースの取得
	LPDIRECT3D9 CreateD3DInterface(void);
	//ディスプレイモードの取得
	HRESULT GetDisplayMode(void);

	//デバイス生成処理
	LPDIRECT3DDEVICE9 CreateLPD3DDevice(const HWND& wndHandle, const D3DPRESENT_PARAMETERS& d3dpp);
	LPDIRECT3DDEVICE9 CreateLPD3DDeviceHALMode(const HWND& wndHandle, D3DPRESENT_PARAMETERS& d3dpp);
	LPDIRECT3DDEVICE9 CreateLPD3DDeviceLeastHALMode(const HWND& wndHandle, D3DPRESENT_PARAMETERS& d3dpp);
	LPDIRECT3DDEVICE9 CreateLPD3DDeviceREFMode(const HWND& wndHandle, D3DPRESENT_PARAMETERS& d3dpp);
	LPDIRECT3DDEVICE9 CreateLPD3DDeviceLeastREFMode(const HWND& wndHandle, D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9					lpd3d_interface_;	//DIRECT3Dインターフェイス
	D3DDISPLAYMODE				d3d_display_mode_;	//ディスプレイモード
};

#endif //DX9GRAPHICS_DEVICE_H_
/*=============================================================================
/*		End of File
=============================================================================*/