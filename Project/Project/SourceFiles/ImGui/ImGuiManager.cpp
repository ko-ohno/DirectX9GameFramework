/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ImGuiManager.cpp] モジュール
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "ImGuiManager.h"
#include "../MainSystem/DX9Graphics.h"

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
void ImGuiManager::StartUp(DX9Graphics* dx9Graphics, const HWND& windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX9_Init(*dx9Graphics->GetLPD3DDevice());

	//ビルドの設定によってImGuiの.iniファイルを生成しないようにする　
#if defined(_DEBUG) || defined(DEBUG)
	io.IniFilename;				//生成
#else
	io.IniFilename = nullptr;	//非生成
#endif // 0

	//ImGuiの色を選択
	ImGuiManager::SetDefaultColor();
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
	case ImGuiColorStyle::None:
		assert("指定されたカラーはありません。");
		break;

	case ImGuiColorStyle::Dark:
		ImGui::StyleColorsDark();
		break;

	case ImGuiColorStyle::Classic:
		ImGui::StyleColorsClassic();
		break;

	case ImGuiColorStyle::Light:
		ImGui::StyleColorsLight();
		break;

	case ImGuiColorStyle::MAX:
		assert("指定されたカラーはありません。");
		break;

	default:
		assert("不正な処理を検知");
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
	ImGuiWindowFlags gui_window_style = (ImGuiWindowFlags_NoTitleBar
										//| ImGuiWindowFlags_NoMove
										| ImGuiWindowFlags_NoResize
										| ImGuiWindowFlags_NoCollapse);
	static bool is_open = true;
	//ImGui::SetNextWindowPos(ImVec2(-5.f, -5.f));
	ImGui::SetNextWindowSize(ImVec2(400.f, 100.f));
	ImGui::Begin("Framerate", &is_open, gui_window_style);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("deltaTime is : %.3f ms", deltaTime);
	ImGui::End();
}


/*-----------------------------------------------------------------------------
/* ImGuiのウィンドウ用のテクスチャ読み込み
-----------------------------------------------------------------------------*/
bool ImGuiManager::ImGuiLoadTexture(const char* fileName, LPDIRECT3DTEXTURE9* srcTexture, const Vector2* textureSize)
{
	////テクスチャ情報の取得
	//LPDIRECT3DTEXTURE9	lpd3d_texture;
	//D3DXIMAGE_INFO		image_info;
	//Vector2				image_size;

	//HRESULT hr = D3DXCreateTextureFromFile(*DX9Graphics::GetLPD3DDevice(), file_name, &lpd3d_texture);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, "スプラッシュスクリーン用のテクスチャ―が読み込めませんでした。", "警告", (MB_OK | MB_ICONWARNING));
	//	return false;
	//}

	//hr = D3DXGetImageInfoFromFile(file_name, &image_info);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, "スプラッシュスクリーン用のテクスチャ―の情報が取得できませんでした。", "警告", (MB_OK | MB_ICONWARNING));
	//	return false;
	//}

	//{//テクスチャ情報の保存
	//	image_size.x_ = (float)image_info.Width;
	//	image_size.y_ = (float)image_info.Height;

	//	textureSize = image_size;
	//	*srcTexture = lpd3d_texture;
	//}

	return true;
}


/*=============================================================================
/*		End of File
=============================================================================*/