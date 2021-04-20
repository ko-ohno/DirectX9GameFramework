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
	UNREFERENCED_PARAMETER(deltaTime);

	// エフェクトへのインスタンスがなかったら描画しない
	if (effect_ == nullptr)
	{
		assert(!"EffectRendererComponent::Update()：エフェクト情報が設定されていません。");
		return;
	}

	// 姿勢情報の更新
	{
		//回転情報
		D3DXMATRIX rotation_matrix = this->rotation_matrix_;

		//位置情報、拡縮情報
		D3DXVECTOR3 position = this->position_;
		D3DXVECTOR3 scale = this->scale_;


		//拡縮のベクトル値に、回転行列の値をくわえて計算

		//X軸
		world_matrix_._11 = scale.x * rotation_matrix._11;
		world_matrix_._12 = scale.x * rotation_matrix._12;
		world_matrix_._13 = scale.x * rotation_matrix._13;

		//Y軸
		world_matrix_._21 = scale.y * rotation_matrix._21;
		world_matrix_._22 = scale.y * rotation_matrix._22;
		world_matrix_._23 = scale.y * rotation_matrix._23;

		//Z軸
		world_matrix_._31 = scale.z * rotation_matrix._31;
		world_matrix_._32 = scale.z * rotation_matrix._32;
		world_matrix_._33 = scale.z * rotation_matrix._33;

		//平行移動
		world_matrix_._41 = position.x;
		world_matrix_._42 = position.y;
		world_matrix_._43 = position.z;

		//W成分
		world_matrix_._14 = world_matrix_._24 = world_matrix_._34 = 0.0f;

		//1.0fに設定することでworld_matrix_._4*をベクトル化
		world_matrix_._44 = 1.0f;
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

/*=============================================================================
/*		End of File
=============================================================================*/