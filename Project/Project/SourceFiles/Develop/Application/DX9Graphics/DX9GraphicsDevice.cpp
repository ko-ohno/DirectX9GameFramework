/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DX9GraphicsDevice.cpp] DirectX9のグラフィックデバイス生成クラス動作定義
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：DirectX9のグラフィックデバイスを生成する動作定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "StdAfx.h"
#include "DX9GraphicsDevice.h"
#include "Math/Math.h"
#include "DebugCode/DebugFunction.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
DX9GraphicsDevice::DX9GraphicsDevice(void)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
DX9GraphicsDevice::~DX9GraphicsDevice(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
DX9GraphicsDevice* DX9GraphicsDevice::Create()
{
	return NEW DX9GraphicsDevice();
}

/*-----------------------------------------------------------------------------
/* DirectX9レンダラーデバイスの生成処理
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateGraphicsDevice(const HWND& windowHandle, const Vector2& screenSize)
{
	LPDIRECT3DDEVICE9		lpd3d_device;
	D3DPRESENT_PARAMETERS	d3dpp;

	lpd3d_interface_ = CreateD3DInterface();
	if (FAILED(lpd3d_interface_))
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("Direct3Dインターフェースの生成に失敗しました！");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return nullptr;
	}

	//ディスプレイモードの取得
	if (FAILED(GetDisplayMode()))
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("ディスプレイモードの取得に失敗しました！");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return nullptr;
	}

	//レンダリングデバイスのプレゼントパラメータの生成
	d3dpp = CreatePresentParam(screenSize, windowHandle, TRUE);

	//LPD3Dデバイスの生成
	lpd3d_device = CreateLPD3DDevice(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	return nullptr;
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
void DX9GraphicsDevice::Init(void)
{
	//変数の初期化
	lpd3d_interface_ = nullptr;
	d3d_display_mode_ = { 0 };
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void DX9GraphicsDevice::Uninit(void)
{
	SAFE_RELEASE_(lpd3d_interface_);//インターフェースの開放
}

/*-----------------------------------------------------------------------------
/* Direct3Dインターフェースの生成
-----------------------------------------------------------------------------*/
LPDIRECT3D9 DX9GraphicsDevice::CreateD3DInterface(void)
{
	//Direct3Dインターフェイスの作成
	LPDIRECT3D9 lpd3d_interface = Direct3DCreate9(D3D_SDK_VERSION);
	if (lpd3d_interface == nullptr) { return nullptr; }
	return lpd3d_interface;
}

/*-----------------------------------------------------------------------------
/* 現在のディスプレイモードの取得
-----------------------------------------------------------------------------*/
HRESULT DX9GraphicsDevice::GetDisplayMode(void)
{
	//現在のディスプレイモードを取得
	return lpd3d_interface_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3d_display_mode_);
}

/*-----------------------------------------------------------------------------
/* グラフィックデバイスのプレゼントパラメータ生成処理
-----------------------------------------------------------------------------*/
//TRUEでウィンドウモード/FALSEでフルスクリーンモード
D3DPRESENT_PARAMETERS DX9GraphicsDevice::CreatePresentParam(const Vector2& screenSize, const HWND& windowHandle, const BOOL& isWindowed)
{
	D3DPRESENT_PARAMETERS d3dpp;

	{//デバイスのプレゼンテーションパラメーターの設定
		ZeroMemory(&d3dpp, sizeof(&d3dpp));								//D3DPresentParamの初期化
		d3dpp.BackBufferWidth = (UINT)screenSize.x_;					//スクリーンのクライアント領域の幅
		d3dpp.BackBufferHeight = (UINT)screenSize.y_;					//スクリーンのクライアント領域の高さ
		d3dpp.BackBufferFormat = d3d_display_mode_.Format;				//GetAdapterDisplayMode()で取得した現在のディスプレイのモード
		d3dpp.BackBufferCount = 1;										//バックバッファの数
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;					//画像がきれいになるが、ハードが対応していない可能性があるから無効にしておく
		d3dpp.MultiSampleQuality = 0;									//マルチサンプルの品質。D3DMULTISAMPLE_NONEを指定したので0にする。
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//フロントバッファとバックバッファの切り替え方を定義
		d3dpp.hDeviceWindow = windowHandle;								//nullptrで自動で現在のウィンドウにフォーカスされる
		d3dpp.Windowed = isWindowed;									//TRUEでウィンドウモード/FALSEでフルスクリーンモード
		d3dpp.EnableAutoDepthStencil = TRUE;							//深度ステンシルバッファを設定、Zバッファなどの奥行を保持するかの設定
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//ステンシルバッファのフォーマット
		d3dpp.Flags = 0;												//バックバッファからフロントバッファへ転送するときの設定。
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//フルスクリーン/ウィンドウどちらのモードでもDEFAULTで大丈夫。
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//フレーム描画終了後の切り替わり方
	}

	return d3dpp;
}

/*-----------------------------------------------------------------------------
/* DirectX9レンダラーデバイス生成
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDevice(const HWND& windowHandle, const D3DPRESENT_PARAMETERS& d3dPP)
{
	if (windowHandle == nullptr) { return nullptr; }

	D3DPRESENT_PARAMETERS d3dpp = d3dPP;
	LPDIRECT3DDEVICE9 lpd3d_device;

	//描画処理とデバイス作成制御をハードウェアで行う。
	lpd3d_device = CreateLPD3DDeviceHALMode(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	//描画処理をハードウェアで、デバイス作成制御をソフトウェアで行う。
	lpd3d_device = CreateLPD3DDeviceLeastHALMode(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	//描画処理ソフトウェアで、デバイス作成制御をハードウェアで行う。
	lpd3d_device = CreateLPD3DDeviceREFMode(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	//描画処理とデバイス作成制御をソフトウェアで行う。
	lpd3d_device = CreateLPD3DDeviceLeastREFMode(windowHandle, d3dpp);
	if (lpd3d_device != nullptr) { return lpd3d_device; }

	//メッセージの表示
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("すべてのDirect3Dデバイスの作成に失敗しました。");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}

	return nullptr;
}

/*-----------------------------------------------------------------------------
/* HALモードによる高級なデバイスの生成処理
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDeviceHALMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp)
{
	LPDIRECT3DDEVICE9 lpd3d_device;

	//<描画>と<頂点処理>をハードウェアで行う
	//D3DDEVTYPE_HAL、パフォーマンスをハードウェアに依存する設定
	if (SUCCEEDED(lpd3d_interface_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,//ハードウェア頂点処理
		&d3dpp, &lpd3d_device)))
	{
		return lpd3d_device;
	}

	//上記の処理が失敗した場合に、下記のメッセージボックスを表示。
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("HALモードによるDirect3Dデバイスが作成できませんでした。\nHALモードによる最低限のデバイス作成制御で再試行します。");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* HALモードによる低級なデバイスの生成処理
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDeviceLeastHALMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp)
{
	LPDIRECT3DDEVICE9 lpd3d_device;

	//<描画>をハードウェアで、<頂点処理>をソフトウェアで行う
	//D3DDEVTYPE_HAL、パフォーマンスをハードウェアに依存する設定
	if (SUCCEEDED(lpd3d_interface_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandle,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &lpd3d_device)))
	{
		return lpd3d_device;
	}

	//上記の処理が失敗した場合に、下記のメッセージボックスを表示。
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("HALモードによる最低限のデバイス作成制御でDirect3Dデバイスが作成できませんでした。\nをREFモードによるデバイス作成制御で再試行します。");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* REFモードによる高級なデバイスの生成処理
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDeviceREFMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp)
{
	LPDIRECT3DDEVICE9 lpd3d_device;

	//<描画>をソフトウェアで、<頂点処理>をハードウェアで行う
	//D3DDEVTYPE_REF、パフォーマンスをソフトウェアに依存する設定
	if (SUCCEEDED(lpd3d_interface_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_REF,
		windowHandle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &lpd3d_device)))
	{
		return lpd3d_device;
	}

	//上記の処理が失敗した場合に、下記のメッセージボックスを表示。
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("REFモードによるデバイス作成制御でDirect3Dデバイスが作成できませんでした。REFモードによる最低限のデバイス作成制御で再試行します。");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* REFモードによる低級なデバイスの生成処理
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 DX9GraphicsDevice::CreateLPD3DDeviceLeastREFMode(const HWND& windowHandle, D3DPRESENT_PARAMETERS& d3dpp)
{
	LPDIRECT3DDEVICE9 lpd3d_device;

	//<描画>と<頂点処理>をソフトウェアで行う
	//D3DDEVTYPE_REF、パフォーマンスをソフトウェアに依存する設定
	if (SUCCEEDED(lpd3d_interface_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_REF,
		windowHandle,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &lpd3d_device)))
	{
		return lpd3d_device;
	}

	//上記の処理が失敗した場合に、下記のメッセージボックスを表示。
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("REFモードによる最低限のデバイス作成制御でDirect3Dデバイスが作成できませんでした。");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
	}
	return nullptr;
}

/*=============================================================================
/*		End of File
=============================================================================*/