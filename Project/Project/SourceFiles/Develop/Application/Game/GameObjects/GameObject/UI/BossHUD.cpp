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
#include "../../../SandBoxManager/EnemieManager.h"

// 描画コンポーネント
#include "../../Component/RendererComponent/SpriteRendererComponent.h"
#include "../../Component/RendererComponent/BillboardRendererComponent.h"

// 音声コンポーネント
#include "../../Component/AudioComponent.h"

#include "../../../../ImGui/ImGuiManager.h"


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
	, is_execute_alert_(false)
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
	this->Uninit();
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

		health_bar_blank_ = NEW SpriteRendererComponent(this, 230);
		health_bar_blank_->SetTexture(TextureType::Blank);
		health_bar_blank_->SetVertexColor(0, 0, 0, 255); // 黒

		health_bar_bg_ = NEW SpriteRendererComponent(this);
		health_bar_bg_->SetTexture(TextureType::Blank);
		health_bar_bg_->SetVertexColor(255, 128, 128, 128); // 赤色
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
		alert_exclamation_->IsSetDrawable(false);

		// 背景
		alert_bg_ = NEW BillboardRendererComponent(this);
		alert_bg_->SetTexture(TextureType::Blank);
		alert_bg_->IsSetDrawable(false);
	}

	// 音声コンポーネントの生成
	{
		alert_se_ = NEW AudioComponent(this);
		alert_se_->SetSound(SoundType::DangerAlert);
	}
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
	// ゲームマネージャを探す
	if (game_manager_ == nullptr)
	{
		game_manager_ = this->FindGameObject(TypeID::GameManager);
	}

	// ボスへのポインタ取得
	if (boss_ == nullptr)
	{
		auto enemy_list = game_->GetEnemieManager()->GetEnemyGameObjectList();
		for(auto enemy : enemy_list)
		{
			auto enemy_type = enemy->GetType();
			if (enemy_type == GameObject::TypeID::Boss)
			{
				boss_ = enemy;
			}
		}
	}

	// HUDの値を更新
	this->UpdateHUDValue(deltaTime);

	// 体力バーの更新
	this->UpdateHealthBarHUD(deltaTime);

	// ボスの状態を取得
	if (boss_ != nullptr)
	{
		boss_state_ = boss_->GetEnemyState();
	}

	// アラートのステートの更新
	{
		if (boss_state_ != boss_state_old_)
		{
			is_execute_alert_ = true;
		}

		if (is_execute_alert_)
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

	// 1フレーム前の情報を更新
	boss_state_old_ = boss_state_;
}

/*-----------------------------------------------------------------------------
/* HUDの値の更新処理
-----------------------------------------------------------------------------*/
void BossHUD::UpdateHUDValue(float deltaTime)
{
	auto a = boss_->GetHitPoint();

	//hp_rate_ = (1.f / 100.f) * a;

	ImGui::Begin("hp_rate");
	ImGui::SliderFloat("##hp_rate", &hp_rate_, 0.f, 1.f);
	ImGui::End();

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

		health_bar_->IsSetDrawingPositionToCenter(true);
		health_bar_->SetScaleX(width);
		health_bar_->SetScaleY(height);

		health_bar_->SetTranslationX((screen_width * 0.5f) - (width * 0.5f));
		health_bar_->SetTranslationY(offset_padding);
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
		// アラートを実行しない状態へ
		is_execute_alert_ = false;

		// アラートを停止
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
	alert_exclamation_->IsSetDrawable(false);

	// 背景の設定
	alert_bg_->IsSetDrawable(false);
	alert_bg_->SetScaleX(2.f);
	alert_bg_->SetScaleY(2.f);
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
		// アラートを実行しない状態へ
		is_execute_alert_ = false;

		// アラートを停止
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
	alert_bg_->SetScaleY(3.f);
	alert_bg_->SetVertexColor(255, alert_color, alert_color, 128);
}

/*=============================================================================
/*		End of File
=============================================================================*/