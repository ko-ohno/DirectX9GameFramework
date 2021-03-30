/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ImGuiManager.cpp] ImGui管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ImGui管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "ImGuiManager.h"
#include "../DX9Graphics.h"
#include "../Math.h"
#include "../../DebugCode/DebugFunction.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ImGuiManager::ImGuiManager(void)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
ImGuiManager::~ImGuiManager(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
ImGuiManager* ImGuiManager::Create(void)
{
	return NEW ImGuiManager();
}

/*-----------------------------------------------------------------------------
/* ImGuiの起動処理
-----------------------------------------------------------------------------*/
bool ImGuiManager::StartUp(DX9Graphics* dx9Graphics, const HWND& windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//ImGuiの実行環境がWindowsAPIであることの初期化
	const bool imgui_environment_init = ImGui_ImplWin32_Init(windowHandle);
	if (imgui_environment_init == false)
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("ImGuiの実行環境の初期化ができませんでした！");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return false;
	}
	
	//ImGuiのレンダラーにDirectX9のグラフィックスデバイスを渡して初期化
	const bool imgui_renderer_init = ImGui_ImplDX9_Init(*dx9Graphics->GetLPD3DDevice());
	if (imgui_renderer_init == false)
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("ImGuiのレンダラーの初期化ができませんでした！");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return false;
	}

	//ビルドの設定によってImGuiの.iniファイルを生成しないようにする　
#if defined(_DEBUG) || defined(DEBUG)
	io.IniFilename;				//生成
#else
	io.IniFilename = nullptr;	//非生成
#endif // RELEASE

	//ImGuiの色を選択
	ImGuiManager::SetDefaultColor();

	return true;
}

/*-----------------------------------------------------------------------------
/* ImGuiの停止処理
-----------------------------------------------------------------------------*/
void ImGuiManager::ShutDown(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

/*-----------------------------------------------------------------------------
/* ImGuiの色彩設定呼び出し
-----------------------------------------------------------------------------*/
void ImGuiManager::SetDefaultColor(ImGuiColorStyle colorStyle)
{
	// 色のスタイルを設定
	switch (colorStyle)
	{
	case ImGuiColorStyle::Dark:
		ImGui::StyleColorsDark();
		break;

	case ImGuiColorStyle::Classic:
		ImGui::StyleColorsClassic();
		break;

	case ImGuiColorStyle::Light:
		ImGui::StyleColorsLight();
		break;

	default:
		std::string msg_str = OUTPUT_FORMAT_STRING("ImGuiは指定されたカラースタイルがありません！");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		break;
	}
}

/*-----------------------------------------------------------------------------
/* ImGuiのフレームの更新開始ハンドラ
-----------------------------------------------------------------------------*/
void ImGuiManager::UpdateBegin(void)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

/*-----------------------------------------------------------------------------
/* ImGuiのフレームの更新終了ハンドラ
-----------------------------------------------------------------------------*/
void ImGuiManager::UpdateEnd(void)
{
	ImGui::EndFrame();
}

/*-----------------------------------------------------------------------------
/* ImGuiのフレームの更新終了ハンドラ
-----------------------------------------------------------------------------*/
void ImGuiManager::ImGuiRender(void)
{
	ImGui::Render();//ImGuiの描画はじめに
	//ImGui_ImplDX9_set
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

/*-----------------------------------------------------------------------------
/* ImGuiのフレームの更新終了ハンドラ
-----------------------------------------------------------------------------*/
void ImGuiManager::ShowFramerate(float deltaTime)
{
	ImGuiWindowFlags gui_window_style = (ImGuiWindowFlags_NoMove);
	static bool is_open = false;
	ImGui::SetNextWindowPos(ImVec2(-5.f, -5.f));
	ImGui::SetNextWindowSize(ImVec2(400.f, 100.f));
	ImGui::Begin("DebugWindow", &is_open, gui_window_style);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("deltaTime is : %.3f ms", deltaTime);
	ImGui::End();
}


/*-----------------------------------------------------------------------------
/* ImGuiのウィンドウ用のテクスチャ読み込み
-----------------------------------------------------------------------------*/
bool ImGuiManager::ImGuiLoadTexture(const char* fileName, LPDIRECT3DTEXTURE9* srcTexture, Vector2& textureSize)
{
	//テクスチャ情報の取得
	LPDIRECT3DTEXTURE9	lpd3d_texture;
	D3DXIMAGE_INFO		image_info;
	Vector2				image_size;

	HRESULT hr = D3DXCreateTextureFromFile(*DX9Graphics::GetLPD3DDevice(), fileName, &lpd3d_texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, "スプラッシュスクリーン用のテクスチャ―が読み込めませんでした。", "警告", (MB_OK | MB_ICONWARNING));
		return false;
	}

	hr = D3DXGetImageInfoFromFile(fileName, &image_info);
	if (FAILED(hr))
	{
		MessageBox(NULL, "スプラッシュスクリーン用のテクスチャ―の情報が取得できませんでした。", "警告", (MB_OK | MB_ICONWARNING));
		return false;
	}

	//テクスチャ情報の保存
	{
		image_size.x_ = (float)image_info.Width;
		image_size.y_ = (float)image_info.Height;

		textureSize = image_size;
		*srcTexture = lpd3d_texture;
	}
	return true;
}


/*=============================================================================
/*		End of File
=============================================================================*/