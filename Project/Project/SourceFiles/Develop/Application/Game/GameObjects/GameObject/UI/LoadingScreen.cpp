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

// 値コンポーネント
#include "../../Component/ParameterComponent/BoolParameterComponent.h"

// 入力
#include "../../../Input/InputCheck.h"

// ImGui
#include "../../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
LoadingScreen::LoadingScreen(Game* game)
	: UI(game)
	, parameter_is_fade_execute_(nullptr)
	, parameter_is_fade_completed_(nullptr)
	, parameter_is_scene_changed_(nullptr)
	, parameter_is_show_game_screen_(nullptr)
	, loading_state_(LoadingState::None)
	, is_show_loading_screen_(false)
	, wait_time_(0.f)
	, text_index_(0)
	, text_tick_time_(0.f)
	, execute_time_(0.f)
	, progress_value_(0.f)
{
	this->Init();
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
	//
	// 通信する既存のゲームオブジェクトから値コンポーネントの取得
	// 

	// ゲームオブジェクトのリストを取得
	auto game_objects = game_->GetGameObjects();
	for (auto game_object : game_objects)
	{
		// ゲームオブジェクトの型を調べる
		auto game_object_type = game_object->GetType();

		// 場面切り替え用の値コンポーネントの取得
		{
			// フェード画面ゲームオブジェクトから値コンポーネントのポインタを取得
			if (game_object_type == GameObject::TypeID::Fade)
			{
				//　ゲームオブジェクトが所有する値コンポーネントのリストを取得
				auto parameter_components = game_object->GetParameterComponents();

				// ゲームオブジェクトが所有する値コンポーネントを調べる
				for (auto parameter_component : parameter_components)
				{
					// フェードが完了したかの値コンポーネントの取得
					auto parameter_component_type = parameter_component->GetParameterType();
					if (parameter_component_type == ParameterType::IsFadeExecute)
					{
						this->parameter_is_fade_execute_ = parameter_component;
					}

					if (parameter_component_type == ParameterType::IsFadeCompleted)
					{
						this->parameter_is_fade_completed_ = parameter_component;
					}
				}
				break;
			}
		}
	}


	// 値コンポーネントの作成
	{
		// ロード画面を表示するか
		parameter_is_scene_changed_ = NEW BoolParameterComponent(this);
		parameter_is_scene_changed_->SetParameterType(ParameterType::IsSceneChanged);

		// ゲーム画面を表示するか
		parameter_is_show_game_screen_ = NEW BoolParameterComponent(this);
		parameter_is_show_game_screen_->SetParameterType(ParameterType::IsShowGameScreen);
	}

	// 値の初期化
	loading_state_ = LoadingState::Idle;
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
	// 値コンポーネントのnullチェック
	if (parameter_is_scene_changed_ == nullptr)
	{
		assert(!"LoadingScreen::UpdateGameObject():値コンポーネント:parameter_is_scene_changed_ が”nullptr”でした。");
		return;
	}

	// 値コンポーネントのnullチェック　
	if (parameter_is_show_game_screen_ == nullptr)
	{
		assert(!"LoadingScreen::UpdateGameObject():値コンポーネント:parameter_is_show_game_screen_ が”nullptr”でした。");
		return;
	}


	// 
	// フェードが完了したらロード画面を表示
	// 

	// ロード画面を表示するか
	const bool is_fade_completed = parameter_is_fade_completed_->GetBool();
	if (is_fade_completed == true)
	{
		// 次のフェードのステートに備える
		parameter_is_fade_completed_->SetBool(false);

		// ロード画面の表示
		is_show_loading_screen_ = true;

	}

	// ロード画面を表示するか？
	if (is_show_loading_screen_ == false) { return; }

	// 挙動を定義
	switch (loading_state_)
	{
	case LoadingState::Idle:
		// ロード画面を表示したら読み込み開始
		loading_state_ = LoadingState::FirstHalf;
		break;

	case LoadingState::FirstHalf:
		this->UpdateProgressBarFirstHalf(deltaTime);
		break;

	case LoadingState::SecondHalf:
		this->UpdateProgressBarSecondHalf(deltaTime);
		break;

	case LoadingState::SceneChanged:
		// ゲーム画面を表示する情報を通知
		this->parameter_is_show_game_screen_->SetBool(false);
		this->parameter_is_scene_changed_->SetBool(true);
		loading_state_ = LoadingState::SecondHalf;
		break;

	default:
		break;
	}


	// 画面の幅と高さの取得
	const float screen_width  = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	// 生成するImGuiウィンドウの幅と高さの設定
	const float window_width  = 400.f;
	const float window_height = 100.f;

	// ImGuiウィンドウスタイルの設定
	bool is_window_opne = true;
	const ImGuiWindowFlags wf = (ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
	
	// ImGuiウィンドウの生成
	ImGui::Begin("Progress Indicators", &is_window_opne, wf);
	{
		// ImGuiウィンドウの大きさと位置の設定
		ImGui::SetWindowSize(ImVec2(window_width, window_height));
		ImGui::SetWindowPos(ImVec2(screen_width - window_width, screen_height - window_height));

		// ImGuiの配色の設定
		const ImU32 gui_color = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
		const ImU32 bg_color = ImGui::GetColorU32(ImGuiCol_Button);

		// Guiの生成
		{
			// 回転する進捗インジケータの表示
			ImGui::Spinner("##spinner", 16, 6, gui_color);

			// インジケーターの横にテキストの表示
			ImGui::SameLine();
			this->UpdateLoadingText(deltaTime);

			// バッファの表示
			ImGui::BufferingBar("##buffer_bar", progress_value_ / MAX_PROGRESS_VALUE_, ImVec2(400, 8), bg_color, gui_color);
		}
	}
	ImGui::End();
}

/*-----------------------------------------------------------------------------
/* 更新読み込み中のテキスト更新処理処理
-----------------------------------------------------------------------------*/
void LoadingScreen::UpdateLoadingText(float deltaTime)
{
	// テキストのチックを計算
	text_tick_time_ += deltaTime;

	// テキストのインデックスを更新
	const float max_tick_time = 0.5f;
	if (text_tick_time_ >= max_tick_time)
	{
		text_tick_time_ = 0.f;
		text_index_++;
	}

	// 最大になったらリセット
	const int max_text_index = 4;
	if (text_index_ >= max_text_index)
	{
		text_index_ = 0;
	}

	// テキストのリセット
	switch (text_index_)
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
}

/*-----------------------------------------------------------------------------
/* プログレスバーの前半の進捗値の更新処理
-----------------------------------------------------------------------------*/
void LoadingScreen::UpdateProgressBarFirstHalf(float deltaTime)
{
	// プログレスバーの実行時間の更新
	execute_time_ += deltaTime;
	if (execute_time_ >= MAX_EXECUTE_TIME_ * 0.5f)
	{
		execute_time_ = MAX_EXECUTE_TIME_ * 0.5f;
	
		// 場面を切り替え
		loading_state_ = LoadingState::SceneChanged;
	}

	// プログレスバーの進捗情報の更新(半分まで)
	progress_value_ = Easing::QuintIn(execute_time_, MAX_EXECUTE_TIME_ * 0.5f, 0.f, MAX_PROGRESS_VALUE_ * 0.5f);
	if (progress_value_ >= MAX_PROGRESS_VALUE_ * 0.5f)
	{
		progress_value_ = MAX_PROGRESS_VALUE_ * 0.5f;		
	}

	//if (progress_value_ >= MAX_PROGRESS_VALUE_)
	//{
	//	progress_value_ = MAX_PROGRESS_VALUE_;
	//}
}

/*-----------------------------------------------------------------------------
/* プログレスバーの後半の進捗値の更新処理
-----------------------------------------------------------------------------*/
void LoadingScreen::UpdateProgressBarSecondHalf(float deltaTime)
{
	if (parameter_is_show_game_screen_ == nullptr)
	{
		assert(!"LoadingScreen::UpdateProgressBarSecondHalf()：値コンポーネント");
	}

	// 待ち時間を計算
	wait_time_ += deltaTime;

	// 読み込みは終わったあと1秒待つ
	const float max_wait_time = 1.f;
	if (wait_time_ >= max_wait_time)
	{
		execute_time_ += deltaTime;
		if (execute_time_ >= MAX_EXECUTE_TIME_)
		{
			// 実行時間を初期化
			execute_time_ = 0.f;

			// 読み込みの待ち時間を初期化
			wait_time_ = 0.f;

			// 読み込みのステートを初期化
			loading_state_ = LoadingState::Idle;

			// ロード画面を表示しない
			is_show_loading_screen_ = false;

			// フェードインを実行するように要請
			parameter_is_fade_execute_->SetBool(true);

			// ゲーム画面を表示する情報を通知
			parameter_is_show_game_screen_->SetBool(true);
		}

		// プログレスバーの進捗情報の更新
		progress_value_ = Easing::QuintIn(MAX_EXECUTE_TIME_ * 0.5f, MAX_EXECUTE_TIME_ * 0.5f, 0.f, MAX_PROGRESS_VALUE_ * 0.5f)
						+ Easing::QuintIn(execute_time_, MAX_EXECUTE_TIME_, 0.f, MAX_PROGRESS_VALUE_);
		if (progress_value_ >= MAX_PROGRESS_VALUE_)
		{
			progress_value_ = MAX_PROGRESS_VALUE_;
		}
	}

}

/*=============================================================================
/*		End of File
=============================================================================*/