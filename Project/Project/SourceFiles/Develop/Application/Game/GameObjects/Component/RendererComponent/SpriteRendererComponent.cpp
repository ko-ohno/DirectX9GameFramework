/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteRendererComponent.cpp] スプライト出力コンポーネントクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライト出力コンポーネントクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "SpriteRendererComponent.h"
#include "../../GameObject.h"
#include "../../../VertexData.h"
#include "../../../Shader.h"
#include "../../../../Math.h"
#include "../../../Resource/Texture.h"
#include "../../GameObject/Camera.h"


//バッファ

LPDIRECT3DVERTEXBUFFER9 SpriteRendererComponent::vertex_buffer_ = nullptr;
LPDIRECT3DINDEXBUFFER9	SpriteRendererComponent::index_buffer_ = nullptr;

//各バッファのアドレス

VERTEX_STD*	SpriteRendererComponent::vertex_buffer_address_ = nullptr;
LPWORD*		SpriteRendererComponent::index_buffer_address_ = nullptr;

/*---------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SpriteRendererComponent::SpriteRendererComponent(class GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, is_offset_scale_(false)
	, is_affine_(false)
	, degree_(0.f)
	, radian_(0.f)
	, texture_(nullptr)
	, is_compute_texcord_(false)
	, texture_cut_x_(0)
	, texture_cut_y_(0)
	, texture_cut_width_(256)
	, texture_cut_height_(256)
{
	const bool is_init_sprite_renderer = this->Init();
	if (is_init_sprite_renderer == false)
	{
		assert(!"スプライトレンダラーの初期化に失敗した");
	}
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SpriteRendererComponent::~SpriteRendererComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SpriteRendererComponent::Init(void)
{
	//描画シェーダーの指定
	this->shader_type_ = ShaderType::Sprite;

	//拡縮率の初期化
	scale_ = { 100.f, 100.f, 1.f };

	//バッファの作成
	{
		//頂点バッファの作成
		bool vtx_buffer_init = this->CreateVertexBuffer();
		if (vtx_buffer_init == false)
		{
			return false;
		}

		//インデックスバッファの作成
		bool idx_buffer_init = this->CreateIndexBuffer();
		if (idx_buffer_init == false)
		{
			return false;
		}
	
		//バッファの初期化
		this->ComputeVertexBuffer();
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SpriteRendererComponent::Uninit(void)
{
	// 静的変数(ポインタじゃ)ないので、解放は必要なし
	//SAFE_RELEASE_(vertex_buffer_);
	//SAFE_RELEASE_(index_buffer_);
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void SpriteRendererComponent::Draw(Shader* shader, Camera* camera)
{
	auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//頂点バッファの再構成
	this->ComputeVertexBuffer();

	//頂点バッファの登録
	lpd3d_device->SetStreamSource(0, vertex_buffer_, 0, sizeof(VERTEX_STD));

	//インデックスバッファの登録
	lpd3d_device->SetIndices(index_buffer_);

	//描画処理
	{
		//スクリーンプロジェクション行列の指定
		//lpd3d_device->SetTransform(D3DTS_PROJECTION, camera->GetProjection2DMatrix());

		//シェーダーのセット
		shader->ShaderSet(camera, this, texture_);

		//シェーダーパスの開始
		shader->ShaderPassBegin();

		// ポリゴン描画
		lpd3d_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST	//ポリゴンの描画タイプ
										  , 0					//頂点バッファの開始オフセットバイト座標
										  , 0					//0番目の頂点バッファ
										  , 4					//使用する頂点数
										  , 0					//インデックスバッファの開始オフセットバイト座標
										  , 2);					//三角形ポリゴンの面の数

		//シェーダーパスの終了
		shader->ShaderPassEnd();
	}
}

/*-----------------------------------------------------------------------------
/* 頂点バッファの作成
-----------------------------------------------------------------------------*/
bool SpriteRendererComponent::CreateVertexBuffer(void)
{
	//
	// 頂点バッファインスタンスが既存の場合
	//
	if (vertex_buffer_ != nullptr)
	{
		return true;
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();
	if (lpd3d_device == nullptr)
	{
		assert("スプライトの頂点バッファ作成時に、デバイスが見つかりませんでした。");
		return false;
	}

	//頂点バッファの作成
	if (FAILED(lpd3d_device->CreateVertexBuffer((MAX_VERTEX_COUNT * sizeof(VERTEX_STD))	//頂点バッファサイズ
											   , D3DUSAGE_WRITEONLY						//バッファの使用方法
											   , FVF_VERTEX_STD							//頂点のフォーマット
											   , D3DPOOL_MANAGED						//メモリ管理をデバイスに任せる
											   , &vertex_buffer_						//頂点バッファのインターフェース
											   , nullptr)))
	{
		assert("スプライトの頂点バッファ作成に失敗しました。");
		return false;
	}

	//システムメモリ上の頂点データ
	VERTEX_STD vtx[4] = {
		{ D3DXVECTOR3(-50.f,  50.0, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3( 50.f,  50.0, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(-50.f, -50.0, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR3( 50.f, -50.0, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) }
	};

	//VRAMとの接続を停止
	vertex_buffer_->Lock(0
						, 0
						, (void**)&vertex_buffer_address_
						, D3DLOCK_DISCARD);

	//頂点情報をメモリに書き込み
	memcpy(vertex_buffer_address_
		  , vtx
		  , sizeof(vtx));

	//VRAMとの接続を再開
	vertex_buffer_->Unlock();

	return true;
}

/*-----------------------------------------------------------------------------
/* インデックスバッファの作成
-----------------------------------------------------------------------------*/
bool SpriteRendererComponent::CreateIndexBuffer(void)
{
	//
	// インデックスバッファのインスタンスが既存の場合
	//
	if (index_buffer_ != nullptr)
	{
		return true;
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();
	if (lpd3d_device == nullptr)
	{
		assert("スプライトのインデックスバッファ作成時に、デバイスが見つかりませんでした。");
		return false;
	}

	//インデックスバッファの作成
	if (FAILED(lpd3d_device->CreateIndexBuffer((MAX_INDEX_COUNT * sizeof(VERTEX_STD))	//インデックスバッファサイズ
											  , D3DUSAGE_WRITEONLY						//バッファの使用方法
											  , D3DFMT_INDEX16							//インデックスのフォーマット
											  , D3DPOOL_MANAGED							//メモリ管理をデバイスに任せる
											  , &index_buffer_							//頂点バッファのインターフェース
											  , nullptr)))
	{
		assert("スプライトのインデックスバッファ作成に失敗しました。");
		return false;
	}

	//16bit版インデックス情報(足りなくなったら32bit版のDWORD型に変更)
	WORD index[] = {
		0,1,2,
		1,3,2,
	};

	//VRAMとの接続を停止
	index_buffer_->Lock(0
					   , 0
					   , (void**)&index_buffer_address_
					   , D3DLOCK_DISCARD);

	//インデックス情報をメモリに書き込み
	memcpy(index_buffer_address_				//コピー先のアドレス
		  , index								//コピー元のメモリ
		  , sizeof(WORD) * MAX_INDEX_COUNT);	//コピーするサイズ

	//VRAMとの接続を再開
	index_buffer_->Unlock();

	return true;
}

/*-----------------------------------------------------------------------------
/* 頂点バッファの計算
-----------------------------------------------------------------------------*/
void SpriteRendererComponent::ComputeVertexBuffer(void)
{
	if (vertex_buffer_ == nullptr) { return; }

	//VRAMへ書き込みを行うためのRAM上での議事アドレス
	VERTEX_STD* vtx = nullptr;

	//VRAMとの接続を停止
	vertex_buffer_->Lock(0
						, 0
						, (void**)&vtx
						, D3DLOCK_DISCARD);

	//頂点座標の計算

	//ポリゴンをオフセットしたときの値を保存する変数
	float scale_offset_x_ = 0.f;
	float scale_offset_y_ = 0.f;

	//ポリゴンの描画座標を、
	//ポリゴンの中心にオフセットするか選択出来るように
	if (is_offset_scale_)
	{
		scale_offset_x_ = scale_.x / 2.f;
		scale_offset_y_ = scale_.y / 2.f;
	}
	else
	{
		scale_offset_x_ = 0.f;
		scale_offset_y_ = 0.f;
	}

	//座標や拡縮、オフセットなどもろもろ計算
	float x   = (0.0f	  - 0.5f) - scale_offset_x_;
	float x_w = (scale_.x - 0.5f) - scale_offset_x_;

	float y	  = (0.0f	  - 0.5f) - scale_offset_y_;
	float y_h = (scale_.y - 0.5f) - scale_offset_y_;

	//ポリゴンを回転するか計算できるように
	if (is_affine_)
	{
		//ラジアンに加算しているからdegreeは関係ない
		degree_ = Math::NormalizeDegree( Math::ToDegree(radian_) );
		radian_ = Math::ToRadian(degree_);

		vtx[0].position_ = D3DXVECTOR3(position_.x + (x   * cosf(radian_) - y   * sinf(radian_)),
									   position_.y + (x   * sinf(radian_) + y   * cosf(radian_)), 0.f);
		vtx[1].position_ = D3DXVECTOR3(position_.x + (x_w * cosf(radian_) - y   * sinf(radian_)),
									   position_.y + (x_w * sinf(radian_) + y   * cosf(radian_)), 0.f);
		vtx[2].position_ = D3DXVECTOR3(position_.x + (x   * cosf(radian_) - y_h * sinf(radian_)),
									   position_.y + (x   * sinf(radian_) + y_h * cosf(radian_)), 0.f);
		vtx[3].position_ = D3DXVECTOR3(position_.x + (x_w * cosf(radian_) - y_h * sinf(radian_)),
									   position_.y + (x_w * sinf(radian_) + y_h * cosf(radian_)), 0.f);
	}
	else
	{
		vtx[0].position_ = D3DXVECTOR3(position_.x + x  ,
									   position_.y + y  , 0.f);
		vtx[1].position_ = D3DXVECTOR3(position_.x + x_w,
									   position_.y + y  , 0.f);
		vtx[2].position_ = D3DXVECTOR3(position_.x + x  ,
									   position_.y + y_h, 0.f);
		vtx[3].position_ = D3DXVECTOR3(position_.x + x_w,
									   position_.y + y_h, 0.f);
	}

	//ポリゴンの頂点色を一括で管理
	for (int i = 0; i < MAX_VERTEX_COUNT; i++)
		vtx[i].vtx_color_ = vertex_color_;

	//UVアニメーションを選択できるように
	if (is_compute_texcord_ == true)
	{
		if (texture_ == nullptr)
		{
			assert(!"ComputeVertexBuffer()：SpriteRendererComponentにテクスチャ情報が設定されていません！");
		}

		//テクスチャ情報の取得
		auto texture_image_info = *texture_->GetTextureImageInfo();

		//テクスチャの幅と高さを格納
		int texture_width_  = texture_image_info.Width;
		int texture_height_ = texture_image_info.Height;

		//格納されたテクスチャの幅と高さ元にUV座標を計算
		float u0 = (float)texture_cut_x_ / texture_width_;
		float v0 = (float)texture_cut_y_ / texture_height_;
		float u1 = (float)(texture_cut_x_ + texture_cut_width_)  / texture_width_;
		float v1 = (float)(texture_cut_y_ + texture_cut_height_) / texture_height_;

		//UV座標を設定。
		vtx[0].texcoord_ = D3DXVECTOR2(u0, v0);
		vtx[1].texcoord_ = D3DXVECTOR2(u1, v0);
		vtx[2].texcoord_ = D3DXVECTOR2(u0, v1);
		vtx[3].texcoord_ = D3DXVECTOR2(u1, v1);
		;
	}
	else
	{
		//UV座標を設定。
		vtx[0].texcoord_ = D3DXVECTOR2(0.f, 0.f);
		vtx[1].texcoord_ = D3DXVECTOR2(1.f, 0.f);
		vtx[2].texcoord_ = D3DXVECTOR2(0.f, 1.f);
		vtx[3].texcoord_ = D3DXVECTOR2(1.f, 1.f);
	}

	//VRAMとの接続を再開
	vertex_buffer_->Unlock();
}

/*-----------------------------------------------------------------------------
/* 頂点バッファの最適化について
-----------------------------------------------------------------------------*/
//void SpriteRendererComponent::ComputeTransform(void)
//{
//	スプライトの最適化について
//
//	頂点バッファでの描画毎にVRAMとの接続を開け閉めするやり方は効率が悪いので、
//
//	姿勢制御情報で、拡縮、回転、平行移動などの情報を含んだworld行列をシェーダーへ転送することで
//
//	画面内での大きさや、回転角度などの姿勢情報を転送する
//
//
//	UVスクロールは、UV座標を直接シェーダーへ転送することで行う
//
//}

/*-----------------------------------------------------------------------------
/* テクスチャの設定
-----------------------------------------------------------------------------*/
void SpriteRendererComponent::SetTexture(TextureType textureTypeID)
{
	//テクスチャの読み込み
	this->texture_ = owner_->GetGame()->GetTextureManager()->LoadTexture(textureTypeID);
}

/*-----------------------------------------------------------------------------
/* テクスチャ情報の取得
-----------------------------------------------------------------------------*/
Texture* SpriteRendererComponent::GetTexture(void)
{
	//テクスチャ情報の取得
	if (this->texture_ == nullptr)
	{
		assert(!"SpriteRendererComponent::GetTexture():テクスチャ情報が設定されていません！");
	}
	return texture_;
}

/*-----------------------------------------------------------------------------
/* テクスチャ構成情報の取得
-----------------------------------------------------------------------------*/
D3DXIMAGE_INFO* SpriteRendererComponent::GetTextureImageInfo(void)
{
	//テクスチャ構成情報の取得
	if (this->texture_ == nullptr)
	{
		assert(!"SpriteRendererComponent::GetTextureImageInfo():テクスチャ構成情報の取得ができませんでした！");
	}
	return texture_->GetTextureImageInfo();
}

/*=============================================================================
/*		End of File
=============================================================================*/