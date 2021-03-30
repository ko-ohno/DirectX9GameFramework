/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[RendererComponent.cpp] レンダリングコンポーネントのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：レンダリングコンポーネントに共通する処理の定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"	
#include "RendererComponent.h"
#include "../../Renderer.h"
#include "../GameObject.h"
#include "../../Game.h"
#include "../../../Math.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
RendererComponent::RendererComponent(GameObject* owner, int drawOrder)
	: Component(owner, drawOrder)
	, draw_order_(drawOrder)
	, renderer_layer_type_(RendererLayerType::None)
	, shader_type_(ShaderType::None)
	, camera_distance_(0.f)
	, vertex_color_(D3DCOLOR_RGBA(255, 255, 255, 255))
	, position_(0.f, 0.f, 0.f)
	, scale_(1.f, 1.f, 1.f)
{
	//コンポーネントの所有者の描画レイヤーを取得
	renderer_layer_type_ = owner->GetRendererLayerType();

	//所有者が不正なゲームオブジェクトじゃないか調べる
	if (renderer_layer_type_ == RendererLayerType::None)
	{
		assert(!"ゲームオブジェクトのレイヤーが選択されていません！");
	}

	owner_->GetGame()->GetRenderer()->AddRendererComponent(this);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
RendererComponent::~RendererComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool RendererComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void RendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void RendererComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//自分自身とカメラまでの距離を計測する
	D3DXVECTOR3 camera_pos;
	D3DXVECTOR3 vector_length;
	
	//長さベクトルの
	vector_length = this->position_ - camera_pos;
	camera_distance_ = D3DXVec3Length(&vector_length);
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void RendererComponent::Draw(class Shader* shader, class Camera* camera)
{
	UNREFERENCED_PARAMETER(shader);
}

/*=============================================================================
/*		End of File
=============================================================================*/