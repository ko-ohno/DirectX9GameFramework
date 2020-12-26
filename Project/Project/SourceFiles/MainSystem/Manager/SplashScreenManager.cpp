/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreenManager.cpp] スプラッシュスクリーン全体の処理の管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプラッシュスクリーンの全体の処理の管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "SplashScreenManager.h"
#include "../Win32APIWindow.h"
#include "../DX9Graphics.h"
#include "../../ImGui/ImGuiManager.h"
#include "../AspectRatio.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SplashScreenManager::SplashScreenManager(const WindowStyle& windowStyle)
	: splash_window_(nullptr)
	, window_handle_(nullptr)
	, dx9_graphics_(nullptr)
	, imgui_manager_(nullptr)
	, is_loop_break_(false)
	, is_shutdown_(false)
{
	splash_window_	= splash_window_->Create();
	window_handle_	= splash_window_->CreateNewWindow(windowStyle);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SplashScreenManager::~SplashScreenManager(void)
{
	ShowWindow(window_handle_, SW_HIDE); // このハンドラのウィンドウを非表示に
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SplashScreenManager::Init(void)
{
	//グラフィックスオブジェクトの生成。
	dx9_graphics_ = dx9_graphics_->Create();
	dx9_graphics_->CreateDX9Graphics(window_handle_, splash_window_->GetWindowClientSize(window_handle_));

	//ImGuiの起動
	imgui_manager_ = imgui_manager_->Create();
	imgui_manager_->StartUp(dx9_graphics_, window_handle_);

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SplashScreenManager::Uninit(void)
{
	imgui_manager_->ShutDown();

	SAFE_DELETE_(splash_window_);
	SAFE_DELETE_(imgui_manager_);
	SAFE_DELETE_(dx9_graphics_);
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void SplashScreenManager::Input(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void SplashScreenManager::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	imgui_manager_->UpdateBegin();
	{
		ImVec2 offset_size		  = { 5.f, 5.f };
		ImVec2 offset_draw_pos	  = { -offset_size.x, -offset_size.y };
		ImVec2 offset_screen_size = { splash_window_->GetWindowSize().x_ + offset_size.x
									, splash_window_->GetWindowSize().y_ + offset_size.y };

		ImGuiWindowFlags this_gui_window_flag = ( ImGuiWindowFlags_NoTitleBar
												| ImGuiWindowFlags_NoMove
												| ImGuiWindowFlags_NoResize
												| ImGuiWindowFlags_NoCollapse
												| ImGuiWindowFlags_NoScrollbar);

		//コンボボックスで選択中の要素
		static int combo_item_current = 2; //初期化値
		const char* combo_items[] = { "FullScreen(1920*1080)"
									, "1360*768"
									, "1280*720"
									, "720*480" };

		//コンボボックスが選択中の文字列をもとに画面画面サイズの定義を変更する
		//ScreenSize::UpdateScreenSizeSelect(combo_items[combo_item_current]);

		//オフセットした画面サイズとそのほかの設定
		{
			ImGui::SetNextWindowSize(offset_screen_size);
			ImGui::SetNextWindowPos(offset_draw_pos);

			//ウィンドウ描画
			ImGui::Begin("splash_screen", nullptr, this_gui_window_flag);
			{
				//画像の描画
				ImGui::BeginGroup();
				{
					//画像サイズの縮小して貼り付け
					//ImGui::Image((void*)texture_, ImVec2( texture_size_.x_ - offset_size.x
					//									, texture_size_.y_ - offset_size.y));
					ImGui::Text("0");
					ImGui::Text("1");
					ImGui::Text("2");
					ImGui::Text("3");
					ImGui::Text("4");
					ImGui::Text("5");
					ImGui::Text("6");
					ImGui::Text("7");
					ImGui::Text("8");
					ImGui::Text("9");
					ImGui::Text("1");
					ImGui::Text("2");
					ImGui::Text("3");
					ImGui::Text("4");
					ImGui::Text("5");
					ImGui::Text("6");
					ImGui::Text("7");
					ImGui::Text("8");
					ImGui::Text("9");
				}
				ImGui::EndGroup();

				//コンボボックス描画
				ImGui::BeginGroup();
				{
					ImGui::Text("ScreenSize:");
					ImGui::SameLine();
					ImGui::Combo("", &combo_item_current, combo_items, IM_ARRAYSIZE(combo_items));
					//ImGui::Text("combo_item_current:%d", combo_item_current);
				}
				ImGui::EndGroup();

				//改行
				ImGui::BeginGroup();
				{
					ImGui::Text("");	//コンボボックスとウィンドウのあいだの空間に余裕を持たせる
				}
				ImGui::EndGroup();

				//ボタン描画
				ImGui::BeginGroup();
				{
					ImGui::Text("GAME:");
					ImGui::SameLine();
					if (ImGui::Button("START", ImVec2(200.f, 20.f)))
					{
						is_loop_break_ = true;
					}
					ImGui::SameLine();
					if (ImGui::Button("QUIT", ImVec2(200.f, 20.f)))
					{
						is_shutdown_  = true;	//プログラムの停止命令を発行
					}
				}
				ImGui::EndGroup();
			}
			ImGui::End();
		}
	}
	imgui_manager_->UpdateEnd();
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void SplashScreenManager::GenerateOutput(void)
{
	dx9_graphics_->RenderingBegin();

	imgui_manager_->ImGuiRender();

	dx9_graphics_->RenderingEnd();
}

/*-----------------------------------------------------------------------------
/* アスペクト比率の取得
-----------------------------------------------------------------------------*/
Vector2* SplashScreenManager::GetSelectedAspectRatio(void)
{
	//return NEW Vector2(1920.f, 1080.f);
	return NEW Vector2(200.f, 200.f);
}

/*-----------------------------------------------------------------------------
/* メッセージループを脱出するか
-----------------------------------------------------------------------------*/
bool SplashScreenManager::IsLoopBreak(void)
{
	return is_loop_break_;
}

/*-----------------------------------------------------------------------------
/* シャットダウンをするか
-----------------------------------------------------------------------------*/
bool SplashScreenManager::IsShutDown(void)
{
	return is_shutdown_;
}

/*=============================================================================
/*		End of File
=============================================================================*/