/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Win32APIWindow.cpp] モジュール
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "Win32APIWindow.h"
#include "../Generic/Math.h"

/*--- 関数プロトタイプ ---*/
//WinAPI
//通常ウィンドウとフルスクリーンウィンドウのコールバック関数を共用にする(同じ処理のため)
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Win32APIWindow::Win32APIWindow(void)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Win32APIWindow::~Win32APIWindow(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
Win32APIWindow* Win32APIWindow::Create(void)
{
	return NEW Win32APIWindow();
}

/*-----------------------------------------------------------------------------
/* ウィンドウ生成処理
-----------------------------------------------------------------------------*/
HWND Win32APIWindow::CreateAppWindow(WindowStyle windowStyle)
{
	/*--- ウィンドウクラスの名前の定義 ---*/
	const char* WINDOW_CLASS_NAME = { "AppWindow" };
				
	/*------------------------------------
	// ウィンドウクラス登録
	------------------------------------*/
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX)						//構造体に必要なバイト数を定義
		, (CS_VREDRAW | CS_HREDRAW)				//ウィンドウのスタイル
		, WindowProcedure						//コールバック関数へのポインタ
		, 0										//ウィンドウクラス構造体の後ろに割り当てる補足のバイト数
		, 0										//ウィンドウインスタンの後ろに割り当てる補足のバイト数
		, windowStyle.hInstance					//このウィンドウクラスのためのウインドウプロシージャがあるインスタンスハンドル
		, windowStyle.hIcon						//アイコンのハンドル
		, LoadCursor(NULL, IDC_ARROW)			//標準のカーソルを読み込む。
		, (HBRUSH)(COLOR_WINDOW + 1)			//クライアント領域にデフォルトの色を書き込む。
		, NULL									//メニューハンドルを非表示にする。
		, WINDOW_CLASS_NAME						//ウィンドウクラス名。
		, NULL									//アイコンハンドル。
	};	

	//ウィンドウクラスの最終的な登録
	if (!RegisterClassEx(&wcex))
	{
		return nullptr;
	}

	/*--- ウィンドウサイズの計算 ---*/
	//ウィンドウのスタイルと指定したサイズとメニューの生成の有無を計算。
	const Math::Vector2 true_window_size = CalculateWindowSize(windowStyle.dwWindowStyle, windowStyle.windowSize, FALSE);

	//ウィンドウの中心座標がデスクトップの中心座標になるように、デスクトップ上でのウィンドウの左上生成座標を計算。
	const Math::Vector2 window_create_pos = CalculateWindowCreatePos(true_window_size);

	/*------------------------------------
	// ウィンドウハンドルの作成
	------------------------------------*/
	HWND window_handle = CreateWindowEx(0										//ウィンドウ拡張スタイル
									   , WINDOW_CLASS_NAME						//RegisterClassEx()で登録したクラスの名前
									   , windowStyle.windowTitle.c_str()		//タイトルバーに表示する文字列
									   , windowStyle.dwWindowStyle				//ウインドウスタイル
									   , (int)window_create_pos.x_				//ウインドウ左上x座標
									   , (int)window_create_pos.y_				//ウインドウ左上y座標
									   , (int)true_window_size.x_				//ウインドウの幅
									   , (int)true_window_size.y_				//ウインドウの高さ
									   , NULL									//親ウィンドウのハンドル
									   , NULL									//メニューのハンドル
									   , windowStyle.hInstance					//ウインドウなどを作成するモジュールのインスタンスのハンドル
									   , NULL);									//WM_CREATEでLPARAMに渡したい値
	

	//ウィンドウ生成
	ShowWindow(window_handle, windowStyle.nCmdShow);
	UpdateWindow(window_handle);

	return window_handle;
}

/*-----------------------------------------------------------------------------
/* ウィンドウサイズの計算
-----------------------------------------------------------------------------*/
Math::Vector2 Win32APIWindow::CalculateWindowSize(const DWORD& dwWindowStyle, const Math::Vector2& windowSize, const BOOL isCreateSysMenu) const
{
	/*--- ウィンドウサイズの指定 ---*/
	RECT window_rect = { 0L, 0L, (LONG)windowSize.x_, (LONG)windowSize.y_ }; //ウィンドウのスタイルによるサイズの誤差を計算
	AdjustWindowRect(&window_rect, dwWindowStyle, isCreateSysMenu);

	//ウィンドウの非クライアント領域の幅と高さを考慮したクライアント領域の計算。
	Math::Vector2 true_window_size;
	true_window_size.x_ = (float)window_rect.right - (float)window_rect.left;
	true_window_size.y_ = (float)window_rect.bottom - (float)window_rect.top;

	return true_window_size;
}

/*-----------------------------------------------------------------------------
/* ウィンドウ座標(デスクトップ上)の計算
-----------------------------------------------------------------------------*/
Math::Vector2 Win32APIWindow::CalculateWindowCreatePos(const Math::Vector2& windowSize) const
{
	Math::Vector2 create_window_pos;

	//デスクトップのクライアント領域の大きさ(画面解像度)を取得する。
	RECT desk_top_clientsize;
	GetWindowRect(GetDesktopWindow(), &desk_top_clientsize);

	//ウィンドウの中心座標がデスクトップの中心座標になるように、デスクトップ上でのウィンドウの左上生成座標を計算。
	create_window_pos.x_ = ((desk_top_clientsize.right - desk_top_clientsize.left) - windowSize.x_) / 2;
	create_window_pos.y_ = ((desk_top_clientsize.bottom - desk_top_clientsize.top) - windowSize.y_) / 2;

	return create_window_pos;
}

/*-----------------------------------------------------------------------------
/* ウィンドウサイズの設定
-----------------------------------------------------------------------------*/
void Win32APIWindow::SetWindowSize(const Math::Vector2& windowSize)
{
	window_size_ = windowSize;
}

/*-----------------------------------------------------------------------------
/* ウィンドウサイズの設定
-----------------------------------------------------------------------------*/
void Win32APIWindow::SetWindowSize(const float windowWidth, const float windowHeight)
{
	window_size_.x_ = windowWidth;
	window_size_.y_ = windowHeight;
}

/*-----------------------------------------------------------------------------
/* ウィンドウの取得
-----------------------------------------------------------------------------*/
Math::Vector2 Win32APIWindow::GetWindowSize(void) const
{
	return window_size_;
}

/*-----------------------------------------------------------------------------
/* ウィンドウのクライアント領域サイズの取得
-----------------------------------------------------------------------------*/
Math::Vector2 Win32APIWindow::GetWindowClientSize(const HWND& wndHandle) const
{
	Math::Vector2 true_client_size;
	RECT wnd_client_size;

	//クライアントサイズの取得
	GetClientRect(wndHandle, &wnd_client_size);

	//クライアント領域の幅と高さの計算
	true_client_size.x_ = (float)wnd_client_size.right - (float)wnd_client_size.left;
	true_client_size.y_ = (float)wnd_client_size.bottom - (float)wnd_client_size.top;

	return true_client_size;
}

/*-----------------------------------------------------------------------------
/*	ウィンドウプロシージャ―
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
//#if defined(_DEBUG)||(DEBUG)
//	//ImGuiに操作を反映させるためのウィンドウ
//	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) { return true; }
//#else
//	ShowCursor(FALSE);//カーソルを非表示に
//#endif //  _DEBUG


	//ウィンドウのメッセージループを終了させるid
	int window_kill_id;

	switch (uMsg)
	{
	case WM_CREATE: //ウィンドウ生成命令の実行先
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: //Escキー入力

#if defined(_DEBUG)||(DEBUG)	//デバッグビルド時にMsgboxを非表示にする。
			DestroyWindow(hWnd);
#endif
			//終了メッセージの表示
			window_kill_id = MessageBox(hWnd, "終了しますか？", "警告", (MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONWARNING));
			if (window_kill_id != IDCANCEL) { DestroyWindow(hWnd); }
			break;
		}
		break;

	default:
#if defined(_DEBUG)||(DEBUG)
		//imgui	
		//デバイスロストしたときに行う処理
		//ImGui_ImplDX9_InvalidateDeviceObjects();
		//ImGui_ImplDX9_CreateDeviceObjects();
#endif //  _DEBUG
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*=============================================================================
/*		End of File
=============================================================================*/