/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossHUD.cpp] ボスのHUDクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボスのHUDクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "BossHUD.h"
#include "../../../Game.h"
#include "../../../../DX9Graphics.h"
#include "../SandBox/Actor/Enemy.h"

// 描画コンポーネント
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/RendererComponent/BillboardRendererComponent.h"

// 音声コンポーネント
#include "../../Component/AudioComponent.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BossHUD::BossHUD(Game* game)
	: UI(game)
	, game_manager_(nullptr)
	, boss_(nullptr)
	, boss_state_(EnemyState::None)
	, health_bar_(nullptr)
	, health_bar_blank_(nullptr)
	, health_bar_bg_(nullptr)
	, hp_value_(0.f)
	, max_hp_value_(0.f)
	, hp_rate_(0.f)
	, weak_point_(nullptr)
	, is_alert_(false)
	, alert_execute_time_(0.f)
	, alert_time_(0.f)
	, alert_exclamation_(nullptr)
	, alert_bg_(nullptr)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
BossHUD::~BossHUD(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BossHUD::Init(void)
{
	// 値の初期化
	{
		hp_value_		= 100;
		max_hp_value_	= 100;
		hp_rate_ = 1.f;
	}

	// 体力の表示
	{
		health_bar_ = NEW SpriteRendererComponent(this, 240);
		health_bar_->SetTexture(TextureType::Blank);
		health_bar_->SetVertexColor(0, 255, 0, 255); // 緑
		health_bar_->IsSetDrawingPositionToCenter(true);

		health_bar_blank_ = NEW SpriteRendererComponent(this, 230);
		health_bar_blank_->SetTexture(TextureType::Blank);
		health_bar_blank_->SetVertexColor(0, 0, 0, 255); // 黒
		health_bar_blank_->IsSetDrawingPositionToCenter(true);

		health_bar_bg_ = NEW SpriteRendererComponent(this);
		health_bar_bg_->SetTexture(TextureType::Blank);
		health_bar_bg_->SetVertexColor(255, 128, 128, 128); // 赤色
		health_bar_bg_->IsSetDrawingPositionToCenter(true);
	}

	// 弱点の表示
	{
		weak_point_ = NEW BillboardRendererComponent(this);
		weak_point_->SetTexture(TextureType::WeakPoint);
		weak_point_->SetScale(2.f);
		weak_point_->IsSetDrawable(false);
	}

	// アラート用コンポーネントの生成
	{
		// ビックリマーク
		alert_exclamation_ = NEW BillboardRendererComponent(this);
		alert_exclamation_->SetTexture(TextureType::Exclamation);
		alert_exclamation_->SetScale(2.f);

		// 背景
		alert_bg_ = NEW BillboardRendererComponent(this);
		alert_bg_->SetTexture(TextureType::Blank);
	}

	// 音声コンポーネントの生成
	{
		alert_se_ = NEW AudioComponent(this);
		alert_se_->SetSound(SoundType::DangerAlert);
	}

	boss_state_ = EnemyState::BodyPress;

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void BossHUD::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void BossHUD::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void BossHUD::UpdateGameObject(float deltaTime)
{
	// 体力バーの更新
	this->UpdateHealthBarHUD(deltaTime);

	// アラートのステート
	{
		switch (boss_state_)
		{
		case EnemyState::Idle:
			break;
		
		case EnemyState::BodyPress:
			// 水平攻撃アラートの更新
			this->UpdateHorizontalAlertHUD(deltaTime);
			break;
	
		case EnemyState::Shooting:
			// 射撃攻撃アラートの更新
			this->UpdateAlertShootHUD(deltaTime);
			break;
	
		case EnemyState::LaserCannon:
			// 水平攻撃アラートの更新
			this->UpdateHorizontalAlertHUD(deltaTime);
			break;
	
		default:
			break;
		}
	} 
}

/*-----------------------------------------------------------------------------
/* 体力ゲージの更新処理
-----------------------------------------------------------------------------*/
void BossHUD::UpdateHealthBarHUD(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	const float screen_width = game_->GetGraphics()->GetScreenSize().x_;
	const float screen_height = game_->GetGraphics()->GetScreenSize().y_;

	const float offset_padding = 15.f;
	const float offset_padding_bg = 10.f;

	//　体力ゲージの本体
	{
		const float warning_value = (1.f / 3.f) * 2.f;
		const float danger_value = (1.f / 3.f);

		if (hp_rate_ >= warning_value)
		{
			health_bar_->SetVertexColor(0, 255, 0);
		}

		if (hp_rate_ <= warning_value)
		{
			health_bar_->SetVertexColor(255, 255, 0);
		}

		if (hp_rate_ <= danger_value)
		{
			health_bar_->SetVertexColor(255, 0, 0);
		}

		const float width = 500.f * hp_rate_;
		const float height = 60.f;

		//const float health_bar_width = health_bar_->GetScale()->x;
		const float health_bar_height = health_bar_->GetScale()->y;

		health_bar_->SetScaleX(width);
		health_bar_->SetScaleY(height);

		health_bar_->SetTranslationX(screen_width * 0.5f);
		health_bar_->SetTranslationY((health_bar_height * 0.5f) + offset_padding);
	}

	//　体力ゲージの空白部分
	{
		const float width = 500.f;
		const float height = 60.f;

		//const float health_bar_width = health_bar_blank_->GetScale()->x;
		const float health_bar_height = health_bar_blank_->GetScale()->y;

		health_bar_blank_->SetScaleX(width);
		health_bar_blank_->SetScaleY(height);

		health_bar_blank_->SetTranslationX(screen_width * 0.5f);
		health_bar_blank_->SetTranslationY((health_bar_height * 0.5f) + offset_padding);
	}

	//　体力ゲージの背景
	{
		const float width = 510.f;
		const float height = 70.f;

		//const float health_bar_width = health_bar_bg_->GetScale()->x;
		const float health_bar_height = health_bar_bg_->GetScale()->y;

		health_bar_bg_->SetScaleX(width);
		health_bar_bg_->SetScaleY(height);

		health_bar_bg_->SetTranslationX(screen_width * 0.5f);
		health_bar_bg_->SetTranslationY((health_bar_height * 0.5f) + offset_padding_bg);
	}
}

/*-----------------------------------------------------------------------------
/* 射撃のアラートHUDの更新処理
-----------------------------------------------------------------------------*/
void BossHUD::UpdateAlertShootHUD(float deltaTime)
{
	// アラートをするか？
	if (is_alert_ == false)
	{
		// 音声の再生
		alert_se_->Play();
		is_alert_ = true;
	}

	// アラートの全体の実行時間の計算
	alert_execute_time_ += deltaTime;

	if (alert_execute_time_ >= MAX_ALERT_TIME)
	{
		boss_state_ = EnemyState::Idle;
		alert_execute_time_ = 0.f;
		is_alert_ = false;
	}

	// 点滅の時の色
	int alert_color = 0;

	// 背景を点滅させる
	{	
		// アラートの局所の実行時間の計算
		alert_time_ += (deltaTime * 2.f);
		{
			alert_color = static_cast<int>(Math::Lerp(255.f, 128.f, alert_time_));
			if (alert_time_ >= 1.f)
			{
				alert_time_ = 0.f;
			}
		}
	}

	// ビックリマークの設定
	alert_exclamation_->IsSetDrawable(is_alert_);

	// 背景の設定
	alert_bg_->IsSetDrawable(is_alert_);
	alert_bg_->SetScaleX(12.f);
	alert_bg_->SetScaleY(8.f);
	alert_bg_->SetVertexColor(255, alert_color, alert_color, 128);
}

/*-----------------------------------------------------------------------------
/* 巨大レーザーと体当たり攻撃のアラートHUDの更新処理
-----------------------------------------------------------------------------*/
void BossHUD::UpdateHorizontalAlertHUD(float deltaTime)
{
	// アラートをするか？
	if (is_alert_ == false)
	{
		// 音声の再生
		alert_se_->Play();
		is_alert_ = true;
	}

	// アラートの全体の実行時間の計算
	alert_execute_time_ += deltaTime;

	if (alert_execute_time_ >= MAX_ALERT_TIME)
	{
		boss_state_ = EnemyState::Idle;
		alert_execute_time_ = 0.f;
		is_alert_ = false;
	}

	// 点滅の時の色
	int alert_color = 0;

	// 背景を点滅させる
	{
		// アラートの局所の実行時間の計算
		alert_time_ += (deltaTime * 2.f);
		{
			alert_color = static_cast<int>(Math::Lerp(255.f, 128.f, alert_time_));
			if (alert_time_ >= 1.f)
			{
				alert_time_ = 0.f;
			}
		}
	}

	// ビックリマークの設定
	alert_exclamation_->IsSetDrawable(is_alert_);

	// 背景の設定
	alert_bg_->IsSetDrawable(is_alert_);
	alert_bg_->SetScaleX(12.f);
	alert_bg_->SetScaleY(2.f);
	alert_bg_->SetVertexColor(255, alert_color, alert_color, 128);
}

/*=============================================================================
/*		End of File
=============================================================================*/