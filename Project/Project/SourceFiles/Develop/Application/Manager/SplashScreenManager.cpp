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
#include "../ImGui/ImGuiManager.h"
#include "../AspectRatio.h"
#include "../../DebugCode/DebugFunction.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SplashScreenManager::SplashScreenManager(const WindowStyle& windowStyle)
	: screen_scaler_(1.0f)
	, aspect_ratio_size_(Vector2())
	, texture_(nullptr)
	, splash_window_(nullptr)
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
	{
		dx9_graphics_ = dx9_graphics_->Create();
		const bool directx9_init = dx9_graphics_->CreateDX9Graphics(window_handle_, splash_window_->GetWindowClientSize(window_handle_));
		if (directx9_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("directx9の初期化ができませんでした！");
			DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
			return false;
		}
	}

	//ImGuiの起動
	{
		imgui_manager_ = imgui_manager_->Create();
		const bool imgui_init = imgui_manager_->StartUp(dx9_graphics_, window_handle_);
		if (imgui_init == false)
		{
			std::string msg_str = OUTPUT_FORMAT_STRING("ImGuiの初期化ができませんでした！");
			DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
			return false;
		}
	}

	//アスペクト比率のリストの作成
	this->MakeListAspectRatio();

	const char* filename = { "Assets/PackageImage/QR_code_to_my_github.png" };
	bool is_load_sucess = ImGui::LoadTexture(filename, &texture_, texture_size_);
	if (!is_load_sucess) { return false; }

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SplashScreenManager::Uninit(void)
{
	imgui_manager_->ShutDown();

	while (!aspect_ratio_size_array_.empty())
	{
		aspect_ratio_size_array_.pop_back();
	}

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
					ImGui::Image((void*)texture_
								, ImVec2( texture_size_.x_ - offset_size.x
										, texture_size_.y_ - offset_size.y));
				}
				ImGui::EndGroup();

				//コンボボックス
				{
					//スプラッシュスクリーン起動直後のコンボボックスの選択値
					static int combo_item_current = screen_scaler_array_.size() -1;

					//選択中の比率の更新
					aspect_ratio_size_ = aspect_ratio_size_array_.at(combo_item_current);
					screen_scaler_ = screen_scaler_array_.at(combo_item_current);

					//配列の中に格納
					std::vector<const char*> combo_items_;
					auto iter = aspact_ratio_string_array_.begin();
					for (iter; iter != aspact_ratio_string_array_.end(); ++iter)
					{
						combo_items_.push_back((*iter).c_str());
					}

					//コンボボックス描画
					ImGui::BeginGroup();
					{
						ImGui::Text("ScreenSize:");
						ImGui::SameLine();
						ImGui::Combo(""
									, &combo_item_current
									, combo_items_.data()
									, aspact_ratio_string_array_.size());
						//ImGui::Text("combo_item_current:%d", combo_item_current);
					}
					ImGui::EndGroup();
				}

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
						is_loop_break_ = true; // Applicationのウィンドウ生成命令を発行
					}
					ImGui::SameLine();
					if (ImGui::Button("QUIT", ImVec2(200.f, 20.f)))
					{
						is_shutdown_  = true;  // プログラムの停止命令を発行
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
/* アスペクト比率のリストの作成
-----------------------------------------------------------------------------*/
void SplashScreenManager::MakeListAspectRatio(void)
{
	auto aspect_ratio		= AspectRatio::Create(); 
	auto aspect_ratio_list  = aspect_ratio->GetAspectRatioList();

	auto iter = aspect_ratio_list.begin();
	for (iter; iter != aspect_ratio_list.end(); ++iter)
	{
		//リストの文字列を格納
		aspact_ratio_string_array_.push_back((*iter).first);

		aspect_ratio_size_array_.push_back((*iter).second);
	}

	screen_scaler_array_ = aspect_ratio->GetScreenScalerList();

	delete aspect_ratio;
}

/*-----------------------------------------------------------------------------
/* アスペクト比率の取得
-----------------------------------------------------------------------------*/
Vector2* SplashScreenManager::GetSelectedAspectRatio(void)
{
	return &aspect_ratio_size_;
}

/*-----------------------------------------------------------------------------
/* 画面の拡縮倍率の取得関数
-----------------------------------------------------------------------------*/
float SplashScreenManager::GetScreenScaler(void)
{
	return screen_scaler_;
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