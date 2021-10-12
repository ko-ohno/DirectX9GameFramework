/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Result.cpp] リザルト画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：リザルト画面の挙動を定義したクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "Result.h"
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/RendererComponent/SpriteDigitRendererComponent.h"
#include "../../Component/AudioComponent.h"
#include "../../../ResourceManager/SaveDataManager.h"
#include "../../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Result::Result(class Game* game)
	: UI(game)
	, result_(nullptr)
	, bg_(nullptr)
	, bgm_result_(nullptr)
	, se_(nullptr)
	, result_state_(ResultMenuState::None)
	, result_state_old_(ResultMenuState::None)
	, screen_width_(0)
	, screen_height_(0)
	, hud_animation_time_(0.f)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Result::~Result(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Result::Init(void)
{
	// 状態を初期化
	result_state_old_ = result_state_ = ResultMenuState::Wait;

	// セーブデータマネージャへのポインタを取得
	auto save_data_manager = game_->GetSaveDataManager();

	// セーブデータのリストの取得
	auto save_data_list = save_data_manager->GetSaveDataList();

	// 末尾の余分なセーブデータの削除
	if (save_data_list.size() >= MAX_SCORE_DATA +1)
	{
		save_data_manager->RemoveSaveData(save_data_list.back());
	}

	// リザルト画面のデータを作成
	{
		// 説明の表示
		go_next_ = NEW SpriteRendererComponent(this);
		go_next_->SetTexture(TextureType::GoNext);

		// タイトルの表示
		result_ = NEW SpriteRendererComponent(this);
		result_->SetTexture(TextureType::Result);
		result_->IsSetDrawingPositionToCenter(true);

		// 背景の表示
		bg_ = NEW SpriteRendererComponent(this, 150);
		bg_->SetTexture(TextureType::ScreenBG); 

		// スコア表示用データの生成
		for (int i = 0; i < MAX_SCORE_DATA; i++)
		{
			ranking_bg_[i] = nullptr;
			ranking_double_point_[i] = nullptr;
			ranking_new_[i] = nullptr;
			ranking_num_[i] = nullptr;
			ranking_score_digit_[i] = nullptr;

			// 背景の生成
			ranking_bg_[i] = NEW SpriteRendererComponent(this);
			ranking_bg_[i]->SetTexture(TextureType::Blank);
			ranking_bg_[i]->SetVertexColor(0, 255, 255, 128);
			ranking_bg_[i]->IsSetDrawingPositionToCenter(true);

			// ダブルコロンのスプライト生成
			ranking_double_point_[i] = NEW SpriteRendererComponent(this);
			ranking_double_point_[i]->SetTexture(TextureType::ScoreDoublePoint);
			ranking_double_point_[i]->IsSetDrawingPositionToCenter(true);

			// NEWのスプライト生成(新しい点数データかの明示)
			ranking_new_[i] = NEW SpriteRendererComponent(this, 250);
			ranking_new_[i]->SetTexture(TextureType::New);
			ranking_new_[i]->SetVertexColor(230, 180, 34);		// 金色に
			ranking_new_[i]->IsSetDrawingPositionToCenter(true);

			// ランキングの順位
			ranking_num_[i] = NEW SpriteDigitRendererComponent(this);
			ranking_num_[i]->SetTexture(TextureType::ScoreFontOrigin_0);
			ranking_num_[i]->IsSetDrawingPositionToCenter(true);
			ranking_num_[i]->SetDrawableDigitLength(1);
			ranking_num_[i]->SetIntData(i + 1);

			switch (i)
			{
			case 0:
				ranking_num_[i]->SetVertexColor(230, 180, 34);	// 金色に
				break;

			case 1:
				ranking_num_[i]->SetVertexColor(212, 212, 212); // 銀色に
				break;

			case 2:
				ranking_num_[i]->SetVertexColor(179,  140, 93);	// 銅色に
				break;

			default:
				break;
			}

			ranking_score_digit_[i] = NEW SpriteDigitRendererComponent(this);
			ranking_score_digit_[i]->SetTexture(TextureType::ScoreFontOrigin_0);
			ranking_score_digit_[i]->IsSetDrawingPositionToCenter(true);
			ranking_score_digit_[i]->SetDrawableDigitLength(3);
			ranking_score_digit_[i]->SetOffestWidth(30);

			// 点数の設定
			ranking_score_digit_[i]->SetIntData(save_data_list.at(i)->GetScore());
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Result::Uninit(void)
{
	// BGMの停止
	{
		bgm_result_->Stop();
	}

	// セーブデータの状態を更新
	{
		auto save_data_list = game_->GetSaveDataManager()->GetSaveDataList();
		for (auto save_data : save_data_list)
		{
			// 新しいデータとしての経歴を削除
			save_data->IsSetNewData(false);
		}
	}
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void Result::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Result::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 音声データの生成
	{
		// BGMの生成
		if (bgm_result_ == nullptr)
		{
			bgm_result_ = NEW AudioComponent(this);
			bgm_result_->SetSound(SoundType::Kemono);
			bgm_result_->PlayLoop();
		}
		
		// SEの生成
		if (se_ == nullptr)
		{
			se_ = NEW AudioComponent(this);
			se_->SetSound(SoundType::SelectSound);
		}
	}

	// 画面サイズの取得
	screen_width_  = game_->GetGraphics()->GetScreenSize().x_;
	screen_height_ = game_->GetGraphics()->GetScreenSize().y_;

	// メニューの更新
	this->UpdateMenu(deltaTime);

	// 表題のスプライトの更新
	this->UpdateResultSprite(deltaTime);

	// 背景の更新
	this->UpdateBackground(deltaTime);

	// ランキングデータの更新
	this->UpdateRankingData(deltaTime);

	// 入力された情報が1フレーム前と違ったら
	if (result_state_ != result_state_old_)
	{
		se_->Play();
	}

	// 1フレーム前の情報を更新
	result_state_old_ = result_state_;
}

/*-----------------------------------------------------------------------------
/* メニューの更新処理
-----------------------------------------------------------------------------*/
void Result::UpdateMenu(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// テクスチャのサイズを取得
	float texture_width  = static_cast<float>(go_next_->GetTextureImageInfo()->Width);
	float texture_height = static_cast<float>(go_next_->GetTextureImageInfo()->Height);

	// ポリゴンのサイズを更新
	go_next_->SetScaleX(texture_width);
	go_next_->SetScaleY(texture_height);

	// 描画座標の更新
	go_next_->SetTranslationX(screen_width_ - texture_width);
	go_next_->SetTranslationY(screen_height_ - texture_height);

}

/*-----------------------------------------------------------------------------
/* リザルトの表題の更新処理
-----------------------------------------------------------------------------*/
void Result::UpdateResultSprite(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 画面の拡縮値の取得
	float screen_scaler = game_->GetGraphics()->GetScreenScaler();

	// テクスチャのサイズを取得
	float texture_width  = static_cast<float>(result_->GetTextureImageInfo()->Width);
	float texture_height = static_cast<float>(result_->GetTextureImageInfo()->Height);

	// ポリゴンのサイズを更新
	result_->SetScaleX(texture_width * screen_scaler);
	result_->SetScaleY(texture_height * screen_scaler);

	// 描画座標の更新
	result_->SetTranslationX(screen_width_ / 2.f);
	result_->SetTranslationY(screen_height_ / 8.f);
}

/*-----------------------------------------------------------------------------
/* 背景の更新処理
-----------------------------------------------------------------------------*/
void Result::UpdateBackground(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 背景ポリゴンのサイズを更新
	bg_->SetScaleX(screen_width_);
	bg_->SetScaleY(screen_height_);

	// テクスチャの切り取りサイズを変更
	float texture_width  = static_cast<float>(bg_->GetTextureImageInfo()->Width);
	float texture_height = static_cast<float>(bg_->GetTextureImageInfo()->Height);

	// テクスチャの切り取り座標を初期化
	static float texture_cut_pos_x = 0.f;
	const float scroll_speed = 100.f;
	texture_cut_pos_x += scroll_speed * deltaTime;
	if (texture_cut_pos_x >= texture_width)
	{
		texture_cut_pos_x = 0.f;
	}

	// 背景をUVアニメーション
	bg_->SetUVAnimation(static_cast<int>(texture_cut_pos_x)
					   , 0
					   , static_cast<int>(screen_width_)
					   , static_cast<int>(texture_height));
}

/*-----------------------------------------------------------------------------
/* ランキングの更新処理
-----------------------------------------------------------------------------*/
void Result::UpdateRankingData(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// 画面の拡縮値の取得
	float screen_scaler = game_->GetGraphics()->GetScreenScaler();

	// セーブデータのリストを取得
	auto save_data_list = game_->GetSaveDataManager()->GetSaveDataList();

	// テクスチャのサイズを取得
	float digit_texture_width  = static_cast<float>(ranking_score_digit_[0]->GetFontWidth());
	float digit_texture_height = static_cast<float>(ranking_score_digit_[0]->GetFontHeight());

	for (int i = 0; i < MAX_SCORE_DATA; i++)
	{
		// ランキングの背景を更新
		{
			ranking_bg_[i]->SetScaleX((screen_width_ / 2.f));
			ranking_bg_[i]->SetScaleY((digit_texture_height));

			ranking_bg_[i]->SetTranslationX(screen_width_ / 2.f);
			ranking_bg_[i]->SetTranslationY((screen_height_ / 4.f) + ((digit_texture_height * 1.5f) * i));
		}
	
		// ランキングの順位を更新
		{
			ranking_num_[i]->SetScaleX(screen_scaler);
			ranking_num_[i]->SetScaleY(screen_scaler);

			ranking_num_[i]->SetTranslationX(screen_width_ / 3.5f);
			ranking_num_[i]->SetTranslationY((screen_height_ / 4.f) + ((digit_texture_height * 1.5f) * i));

			// ウィンドウサイズに合わせて拡縮
			ranking_double_point_[i]->SetScaleX((digit_texture_width  * 1.5f) * screen_scaler);
			ranking_double_point_[i]->SetScaleY((digit_texture_height * 1.5f) * screen_scaler);

			ranking_double_point_[i]->SetTranslationX(ranking_num_[i]->GetPosition()->x + digit_texture_width);
			ranking_double_point_[i]->SetTranslationY(ranking_num_[i]->GetPosition()->y);
		}

		// ランキングの新しいデータかを表示する
		{
			if (save_data_list.at(i)->IsGetNewData())
			{
				ranking_new_[i]->IsSetDrawable(true);
			}
			else
			{
				ranking_new_[i]->IsSetDrawable(false);
			}

			float new_texture_width = static_cast<float>(ranking_new_[0]->GetTextureImageInfo()->Width);
			float new_texture_height = static_cast<float>(ranking_new_[0]->GetTextureImageInfo()->Height);


			// HUDアニメーションの時間を計算
			hud_animation_time_ += deltaTime;
			if (hud_animation_time_ >= MAX_HUD_ANIMATION_TIME_)
			{
				hud_animation_time_ = 0.f;
			}

			// hudのカラーアニメーション(白色から金色への)
			int red		= static_cast<int>(Math::Lerp(255, 230, hud_animation_time_));
			int green	= static_cast<int>(Math::Lerp(255, 180, hud_animation_time_));
			int blue	= static_cast<int>(Math::Lerp(255,  34, hud_animation_time_));

			// 色の更新
			ranking_new_[i]->SetVertexColor(red, green, blue);

			// ポリゴンの大きさをテクスチャサイズに
			ranking_new_[i]->SetScaleX((new_texture_width * 2.f) * screen_scaler);
			ranking_new_[i]->SetScaleY((new_texture_height * 2.f) * screen_scaler);

			ranking_new_[i]->SetTranslationX(screen_width_ * 0.65f);
			ranking_new_[i]->SetTranslationY((screen_height_ / 4.f) + ((digit_texture_height * 1.5f) * i));
		}

		// ランキングのスコアを更新
		{
			auto digit_width = ranking_score_digit_[0]->GetMaxDrawableDigitWidth();

			ranking_score_digit_[i]->SetScaleX(screen_scaler);
			ranking_score_digit_[i]->SetScaleY(screen_scaler);

			ranking_score_digit_[i]->SetTranslationX((screen_width_ / 2.f)  - (((digit_width / 3.f) * 2.f)));
			ranking_score_digit_[i]->SetTranslationY((screen_height_ / 4.f) + (((digit_texture_height * 1.5f)))  * i);
		}
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/