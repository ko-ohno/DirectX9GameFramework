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

	//行列の初期化
	D3DXMatrixIdentity(&rotation_matrix_);
	D3DXMatrixIdentity(&world_matrix_);

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
/* 更新処理
-----------------------------------------------------------------------------*/
void RendererComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

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

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void RendererComponent::Draw(class Shader* shader, class Camera* camera)
{
	UNREFERENCED_PARAMETER(shader);
	UNREFERENCED_PARAMETER(camera);
}

/*=============================================================================
/*		End of File
=============================================================================*/