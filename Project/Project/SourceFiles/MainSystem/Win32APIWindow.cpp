/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Win32APIWindow.cpp] Win32APIウィンドウ管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：Win32APIウィンドウ管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "Win32APIWindow.h"
#include "../ImGui/ImGuiManager.h"
#include "../Generic/Math.h"

/*--- 関数プロトタイプ ---*/
//Win32アプリケーションのメッセージハンドラー
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Win32APIWindow::Win32APIWindow(void)
	: window_size_(0.f, 0.f)
	, window_handle_(nullptr)
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
HWND Win32APIWindow::CreateNewWindow(WindowStyle windowStyle, bool isAppWindow)
{
	//ウィンドウクラスの名前定義
	std::string window_class_name = "";

	if (isAppWindow)
	{
		window_class_name = "AppWindow";
	}
	else
	{
		window_class_name = "SplashScreenWindow";
	}
				
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
		, LoadCursor(nullptr, IDC_ARROW)		//標準のカーソルを読み込む。
		, (HBRUSH)(COLOR_WINDOW + 1)			//クライアント領域にデフォルトの色を書き込む。
		, nullptr								//メニューハンドルを非表示にする。
		, window_class_name.c_str()				//ウィンドウクラス名。
		, nullptr								//アイコンハンドル。
	};	

	//ウィンドウクラスの最終的な登録
	if (!RegisterClassEx(&wcex))
	{
		assert(!"ウィンドウクラスの登録に失敗！！");
		return nullptr;
	}

	/*--- ウィンドウサイズの計算 ---*/
	//ウィンドウのスタイルと指定したサイズとメニューの生成の有無を計算。
	const Vector2 true_window_size = CalculateWindowSize(windowStyle.dwWindowStyle, windowStyle.windowSize, FALSE);

	//ウィンドウの中心座標がデスクトップの中心座標になるように、デスクトップ上でのウィンドウの左上生成座標を計算。
	const Vector2 window_create_pos = CalculateWindowCreatePos(true_window_size);

	/*------------------------------------
	// ウィンドウハンドルの作成
	------------------------------------*/
	window_handle_ = CreateWindowEx(0										//ウィンドウ拡張スタイル
								   , window_class_name.c_str()				//RegisterClassEx()で登録したクラスの名前
								   , windowStyle.windowTitle.c_str()		//タイトルバーに表示する文字列
								   , windowStyle.dwWindowStyle				//ウインドウスタイル
								   , (int)window_create_pos.x_				//ウインドウ左上x座標
								   , (int)window_create_pos.y_				//ウインドウ左上y座標
								   , (int)true_window_size.x_				//ウインドウの幅
								   , (int)true_window_size.y_				//ウインドウの高さ
								   , nullptr								//親ウィンドウのハンドル
								   , nullptr								//メニューのハンドル
								   , windowStyle.hInstance					//ウインドウなどを作成するモジュールのインスタンスのハンドル
								   , nullptr);								//WM_CREATEでLPARAMに渡したい値
								
	//ウィンドウ表示
	ShowWindow(window_handle_, windowStyle.nShowCmd);
	UpdateWindow(window_handle_);

	return window_handle_;
}

/*-----------------------------------------------------------------------------
/* ウィンドウサイズの計算
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::CalculateWindowSize(const DWORD& dwWindowStyle, const Vector2& windowSize, const BOOL isCreateSysMenu) const
{
	/*--- ウィンドウサイズの指定 ---*/
	RECT window_rect = { 0L, 0L, (LONG)windowSize.x_, (LONG)windowSize.y_ }; //ウィンドウのスタイルによるサイズの誤差を計算
	AdjustWindowRect(&window_rect, dwWindowStyle, isCreateSysMenu);

	//ウィンドウの非クライアント領域の幅と高さを考慮したクライアント領域の計算。
	Vector2 true_window_size;
	true_window_size.x_ = (float)window_rect.right - (float)window_rect.left;
	true_window_size.y_ = (float)window_rect.bottom - (float)window_rect.top;

	return true_window_size;
}

/*-----------------------------------------------------------------------------
/* フルスクリーンのウィンドウサイズの計算
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::CalculateFullScreenWindowSize(const DWORD& dwWindowStyle, const BOOL isCreateSysMenu) const
{
	//フルスクリーンの時
	//デスクトップのクライアント領域の大きさ(画面解像度)を取得する。
	RECT desk_top_clientsize;
	GetWindowRect(GetDesktopWindow(), &desk_top_clientsize);
	AdjustWindowRect(&desk_top_clientsize, dwWindowStyle, isCreateSysMenu);

	//画面解像度からフルスクリーンのサイズを計算する。
	Vector2 full_screen_window_size;
	full_screen_window_size.x_ = (float)(desk_top_clientsize.right - desk_top_clientsize.left);
	full_screen_window_size.y_ = (float)(desk_top_clientsize.bottom - desk_top_clientsize.top);

	return full_screen_window_size;
}

/*-----------------------------------------------------------------------------
/* ウィンドウ座標(デスクトップ上)の計算
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::CalculateWindowCreatePos(const Vector2& windowSize) const
{
	Vector2 create_window_pos;

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
void Win32APIWindow::SetWindowSize(const Vector2& windowSize)
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
Vector2 Win32APIWindow::GetWindowSize(void) const
{
	return window_size_;
}

/*-----------------------------------------------------------------------------
/* ウィンドウのクライアント領域サイズの取得
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::GetWindowClientSize(const HWND& windowHandle) const
{
	Vector2 true_client_size;
	RECT wnd_client_size;

	//クライアントサイズの取得
	GetClientRect(windowHandle, &wnd_client_size);

	//クライアント領域の幅と高さの計算
	true_client_size.x_ = (float)wnd_client_size.right - (float)wnd_client_size.left;
	true_client_size.y_ = (float)wnd_client_size.bottom - (float)wnd_client_size.top;

	return true_client_size;
}

/*-----------------------------------------------------------------------------
/* ウィンドウのIDごとのクライアント領域サイズの取得
-----------------------------------------------------------------------------*/
Vector2 Win32APIWindow::FindWindowSize(window_size_id id) const
{
	switch (id)
	{
	case window_size_id::None:
		break;

	case window_size_id::FULL_SCREEN:
		break;
	case window_size_id::MAX:
		break;
	default:
		break;
	}

	return Vector2();
}

//ImGuiのメッセージハンドラー
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*-----------------------------------------------------------------------------
/*	ウィンドウのメッセージハンドラー
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//ImGuiに操作を反映させるためのウィンドウプロシージャー
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) { return true; }

	//ウィンドウのメッセージループを終了させるid
	int window_kill_id;

	switch (uMsg)
	{
	case WM_CREATE: //ウィンドウ生成命令の実行先
		break;

	case WM_CLOSE:	//ウィンドウ×ボタン押下

#if defined(_DEBUG)||(DEBUG)	//デバッグビルド時にMsgboxを非表示にする。
		DestroyWindow(hWnd);
#endif
		//終了メッセージの表示
		window_kill_id = MessageBox(hWnd, "ゲームを終了しますか？", "警告", (MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONWARNING));
		if (window_kill_id != IDCANCEL) { DestroyWindow(hWnd); }
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
			window_kill_id = MessageBox(hWnd, "ゲームを終了しますか？", "警告", (MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONWARNING));
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