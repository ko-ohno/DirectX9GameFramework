/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBullet.cpp] チャージ弾のゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：チャージ弾のゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "ChargeBullet.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../Component/ColliderComponent/SphereColliderComponent.h"

#include "../../../Input/InputCheck.h"

#include "../../../../ImGui/ImGuiManager.h"



/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ChargeBullet::ChargeBullet(Game* game)
	: SandBox(game)
	, sphere_collider_(nullptr)
	, sphere_collider_gizmo_(nullptr)
	, charge_bullet_state_(ChargeBulletState::None)
	, charge_bullet_state_old_(ChargeBulletState::None)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
ChargeBullet::~ChargeBullet(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool ChargeBullet::Init(void)
{
	// 配列の初期化
	{
		// エフェクト番号の登録
		effect_type_[0] = EffectType::ChargeBulletState1Charge;
		effect_type_[1] = EffectType::ChargeBulletState2Hold;
		effect_type_[2] = EffectType::ChargeBulletState3Fire;
		effect_type_[3] = EffectType::ChargeBulletState4Bullet;
		effect_type_[4] = EffectType::ChargeBulletState5Explosion;

		for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
		{
			effect_[i] = nullptr;
		}
	}

	// 弾丸の生成
	{

		for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
		{
			effect_[i] = NEW EffectRendererComponent(this);
			effect_[i]->SetEffect(effect_type_[i]);
			effect_[i]->SetScale(0.5f);
			effect_[i]->SetTranslationX(-4.f + (i*2));
		}
	}

	// 衝突判定の作成
	{
		const float scale = 1.f;

		// 球の衝突判定
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);

		// ギズモの描画コンポーネント
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
	}

	//effect_[0]->Play();
	effect_[1]->Play();
	//effect_[2]->Play();
	effect_[3]->Play();
	//effect_[4]->Play();

	{
		charge_bullet_state_ = ChargeBulletState::Charge;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void ChargeBullet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void ChargeBullet::InputGameObject(void)
{
	//if ()
	//{
	//	charge_bullet_state_ = ChargeBulletState::Charge;
	//}
	//else
	//{
	//	charge_bullet_state_ = ChargeBulletState::Hold;
	//}
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateGameObject(float deltaTime)
{
	static float time = 0.f;
	static float time_X = 0.f;


	ImGui::Begin("KeyRepeat");
	ImGui::Text("A:%s", InputCheck::XInputRepeat(PadIndex::Pad1, XInputButton::XIB_A, 3.f) ? "true" : "false");

	ImGui::Text("X:%s", InputCheck::XInputRepeat(PadIndex::Pad1, XInputButton::XIB_Y, 8.f) ? "true" : "false");


	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_A))
	{
		time += deltaTime;
	}

	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_Y))
	{
		time_X += deltaTime;
	}

	ImGui::Text("%f", time);
	ImGui::Text("%f", time_X);

	ImGui::End();
	// チャージ弾の更新
	this->UpdateChargeBullet(deltaTime);

	// ステートが切り替わった時だけ再生されるように
	if (charge_bullet_state_ != charge_bullet_state_old_)
	{
		this->UpdateChargeBulletState(charge_bullet_state_);
	}

	// 1フレーム前の情報を更新
	charge_bullet_state_old_ = charge_bullet_state_;
}

/*-----------------------------------------------------------------------------
/* チャージ弾の状態の更新処理
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateChargeBullet(float deltaTime)
{
	static float t = 0;

	t += deltaTime;

	if (t >= 3.f)
	{


		effect_[0]->Play();
		//effect_[1]->Play();
		effect_[2]->Play();
		//effect_[3]->Play();
		effect_[4]->Play();

		t = 0;
	}

	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		break;

	case ChargeBulletState::Hold:
		break;

	case ChargeBulletState::Fire:
		break;
	
	case ChargeBulletState::Bullet:
		break;
	
	case ChargeBulletState::Explosion:
		break;
	
	default:
		assert(!"ChargeBullet::UpdateChargeBullet():チャージ弾のゲームオブジェクトが不正な処理を起こしています！");
		break;
	}



	// チャージ弾の位置を更新
	for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
	{
		effect_[i]->SetTranslation(0.f, 0.f, 0.f);
	}
}

/*-----------------------------------------------------------------------------
/* チャージ弾の状態の更新処理
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateChargeBulletState(ChargeBulletState chargeBulletState)
{
	switch (chargeBulletState)
	{
	case ChargeBulletState::Charge:
		effect_[static_cast<int>(ChargeBulletState::Charge)]->Play();
		break;

	case ChargeBulletState::Hold:
		effect_[static_cast<int>(ChargeBulletState::Hold)]->Play();
		break;

	case ChargeBulletState::Fire:
		effect_[static_cast<int>(ChargeBulletState::Hold)]->Stop();		// 持続再生するエフェクトの停止命令
		effect_[static_cast<int>(ChargeBulletState::Fire)]->Play();
		break;

	case ChargeBulletState::Bullet:
		effect_[static_cast<int>(ChargeBulletState::Bullet)]->Play();
		break;

	case ChargeBulletState::Explosion:
		effect_[static_cast<int>(ChargeBulletState::Bullet)]->Stop();	// 持続再生するエフェクトの停止命令
		effect_[static_cast<int>(ChargeBulletState::Explosion)]->Play();
		break;

	default:
		assert(!"ChargeBullet::UpdateGameObject():チャージ弾のゲームオブジェクトが不正な処理を起こしています！");
		break;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/