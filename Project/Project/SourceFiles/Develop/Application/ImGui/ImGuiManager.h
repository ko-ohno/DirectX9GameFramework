/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ImGuiManager.h] ImGuiの管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ImGuiの管理クラス
=============================================================================*/
#ifndef IMGUI_MANAGER_H_
#define	IMGUI_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "../Math.h"

/*--- ImGuiのライブラリをインクルード ---*/
#include "../../../External/ImGui/include/imgui.h"
#include "../../../External/ImGui/include/imgui_impl_dx9.h"
#include "../../../External/ImGui/include/imgui_impl_win32.h"


/*-------------------------------------
/* ImGuiのウィンドウカラースタイル
-------------------------------------*/
enum class ImGuiColorStyle
{
	None = -1
	, Dark
	, Classic
	, Light
	, MAX
};

/*-------------------------------------
/* ImGui管理クラス
-------------------------------------*/
class ImGuiManager
{
private:
	ImGuiManager(void);

public:
	~ImGuiManager(void);

	static ImGuiManager* Create(void);

	//ImGUIの管理
	bool StartUp(class DX9Graphics* dx9Graphics, const HWND& windowHandle);	//ImGuiの起動
	void ShutDown(void);													//ImGuiの停止								

	//デフォルト色を指定
	void SetDefaultColor(ImGuiColorStyle colorStyle = ImGuiColorStyle::Dark);	

	//ImGuiを更新管理
	void UpdateBegin(void);		//GUIの更新開始(更新命令の一番最初に呼び出す)
	void UpdateEnd(void);		//GUIの更新終了(更新命令の一番最後に呼び出す)

	//ImGuiの出力管理
	void ImGuiRender(void);		//描画開始処理(描画命令の一番最後に呼び出す)

private:
};

namespace ImGui
{
	//フレームレートの表示
	void ShowFPS(float deltaTime);

	//ImGui用のテクスチャ読み込み関数
	bool LoadTexture(const char* fileName
					, LPDIRECT3DTEXTURE9* srcTexture
					, class Vector2& textureSize);

	// 読み込みのプログレスバー
    bool BufferingBar(const char* label, float value, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);

	// 回転する進捗インジケータ
	bool Spinner(const char* label, float radius, int thickness, const ImU32& color);
};

#endif //IMGUI_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/