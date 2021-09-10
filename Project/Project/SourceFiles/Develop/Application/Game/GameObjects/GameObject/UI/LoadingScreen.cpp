/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LoadingScreen.cpp] ロード画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ロード画面クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "LoadingScreen.h"
#include "../../../Game.h"

#include "../../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
LoadingScreen::LoadingScreen(Game* game)
	: UI(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
LoadingScreen::~LoadingScreen(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool LoadingScreen::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void LoadingScreen::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void LoadingScreen::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void LoadingScreen::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 画面の幅と高さの取得
	const float screen_width  = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	// 生成するImGuiウィンドウの幅と高さの設定
	const float window_width  = 400.f;
	const float window_height = 100.f;

	// ImGuiウィンドウの設定
	bool is_window_opne = true;
	const ImGuiWindowFlags wf = (ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
	
	// ImGuiウィンドウの生成
	ImGui::Begin("Progress Indicators", &is_window_opne, wf);

	// ImGuiウィンドウの設定
	ImGui::SetWindowSize(ImVec2(window_width, window_height));
	ImGui::SetWindowPos(ImVec2(screen_width - window_width, screen_height - window_height));
	{
		static float time = 0.f;
		static float val = 0.f;
		static int	 text_index = 0;

		time += deltaTime;

		const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
		const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

		//const float div_num = 1000.f;
		const float div_num = 3.f;
		//ImGui::SliderFloat("##buffer_bar", &val, 0.0f, div_num);

		// 回転する進捗インジケータの表示
		ImGui::Spinner("##spinner", 16, 6, col);

		// テキストの表示
		ImGui::SameLine();
		{
			switch (text_index)
			{
			case 0:
				ImGui::Text("Now Loading");
				break;
			case 1:
				ImGui::Text("Now Loading.");
				break;
			case 2:
				ImGui::Text("Now Loading..");
				break;
			case 3:
				ImGui::Text("Now Loading...");
				break;
			default:
				break;
			}

			const float max_value = 3.f;
			if (val >= max_value)
			{
				val = max_value;
			}

			const float max_tick_time = 0.5f;
			if (time >= max_tick_time)
			{
				time = 0.f;
				text_index++;
			}

			const int max_text_index = 4;
			if (text_index >= max_text_index)
			{
				text_index = 0;
			}
		}

		// バッファの表示
		ImGui::BufferingBar("##buffer_bar", val / div_num, ImVec2(400, 8), bg, col);
	}
	ImGui::End();
}

/*=============================================================================
/*		End of File
=============================================================================*/