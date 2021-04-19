/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectRendererComponent.cpp] エフェクトコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エフェクトコンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "EffectRendererComponent.h"
#include "../../GameObject.h"
#include "../../../../Math.h"
#include "../../../Resource/Effect.h"
#include "../../GameObject/Camera.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
EffectRendererComponent::EffectRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, effect_(nullptr)
	, effekseer_manager_(nullptr)
{
	//描画レイヤーを指定
	renderer_layer_type_ = RendererLayerType::ParticleEffect;

	//自身の初期化
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
EffectRendererComponent::~EffectRendererComponent(void)
{
	//自身の終了化
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool EffectRendererComponent::Init(void)
{
	this->shader_type_ = ShaderType::ParticleEffect;
	
	//	エフェクトのマネージャの取得
	effect_manager_ = owner_->GetGame()->GetEffectManager();
	const bool effect_manager_init = (effect_manager_ != nullptr);
	if (effect_manager_init == false)
	{
		assert(!"EffectRendererComponent::Init()：エフェクトのマネージャの取得に失敗しました。");
		return false;
	}

	//	Effekseerへのマネージャの取得
	effekseer_manager_ = effect_manager_->GetEffekseerManager();
	const bool effekseer_manager_init = (effekseer_manager_ != nullptr);
	if (effekseer_manager_init == false)
	{
		assert(!"EffectRendererComponent::Init()：Effekseerへのマネージャの取得に失敗しました。");
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Update(float deltaTime)
{
	// エフェクトへのインスタンスがなかったら描画しない
	if (effect_ == nullptr)
	{
		assert(!"EffectRendererComponent::Update()：エフェクト情報が設定されていません。");
		return;
	}

	//エフェクトの表示座標を更新
	effekseer_manager_->SetBaseMatrix(*effect_->GetEffectHandle(), this->effect_manager_->Convert43Matrix(world_matrix_));

	//エフェクトをハンドル単位で更新
	effekseer_manager_->UpdateHandle(*effect_->GetEffectHandle());
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Draw(Shader* shader, Camera* camera)
{
	// エフェクトへのインスタンスがなかったら描画しない
	if (effect_ == nullptr) { return; }

	UNREFERENCED_PARAMETER(shader);
	UNREFERENCED_PARAMETER(camera);
	
	//エフェクトをハンドル単位で描画
	effekseer_manager_->DrawHandle(*effect_->GetEffectHandle());
}

/*-----------------------------------------------------------------------------
/* エフェクトの設定
-----------------------------------------------------------------------------*/
void EffectRendererComponent::SetEffect(EffectType effectTypeID)
{
	//エフェクトの読み込み
	this->effect_ = owner_->GetGame()->GetEffectManager()->LoadEffect(effectTypeID);
}

/*-----------------------------------------------------------------------------
/* エフェクト情報の取得
-----------------------------------------------------------------------------*/
Effect* EffectRendererComponent::GetEffect(void)
{
	//メッシュ情報の取得
	if (this->effect_ == nullptr)
	{
		assert(!"EffectRendererComponent::GetEffect():エフェクト情報が設定されていません！");
	}
	return effect_;
}

/*-----------------------------------------------------------------------------
/* エフェクト情報の取得
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Play(void)
{
	//エフェクトのハンドル書き換え
	*effect_->GetEffectHandle() = effekseer_manager_->Play(effect_->GetEffect(), Effekseer::Vector3D(0, 0, 0));
}

/*-----------------------------------------------------------------------------
/* エフェクト情報の取得
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Play(const D3DXVECTOR3& position = D3DXVECTOR3(0.f, 0.f, 0.f))
{
	//エフェクトのハンドル書き換え
	*effect_->GetEffectHandle() = effekseer_manager_->Play(effect_->GetEffect(), Effekseer::Vector3D(position.x, position.y, position.z));
}

/*-----------------------------------------------------------------------------
/* エフェクト再生処理
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Play(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f)
{
	//エフェクトのハンドル書き換え
	*effect_->GetEffectHandle() = effekseer_manager_->Play(effect_->GetEffect(), Effekseer::Vector3D(posX, posY, posZ));
}

/*-----------------------------------------------------------------------------
/* エフェクト一時停止処理
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Paused(bool isPaused)
{
	//エフェクトのハンドル書き換え
	effekseer_manager_->SetPaused(*effect_->GetEffectHandle(), isPaused);
}

/*-----------------------------------------------------------------------------
/* エフェクト停止処理
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Stop(void)
{
	//エフェクトのハンドル書き換え
	effekseer_manager_->StopEffect(*effect_->GetEffectHandle());
}

/*-----------------------------------------------------------------------------
/* エフェクトの姿勢情報の更新
-----------------------------------------------------------------------------*/
void EffectRendererComponent::SetBaseMatirx(const D3DXMATRIX& matrix)
{
	//エフェクトの姿勢情報の更新
	effekseer_manager_->SetBaseMatrix(*effect_->GetEffectHandle(), effect_manager_->Convert43Matrix(matrix));
}

/*=============================================================================
/*		End of File
=============================================================================*/