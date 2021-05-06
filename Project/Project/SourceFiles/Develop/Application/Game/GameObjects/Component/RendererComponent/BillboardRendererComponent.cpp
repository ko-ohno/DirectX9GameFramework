/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardRendererComponent.cpp] ビルボードレンダラーコンポネントクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ビルボードレンダラーコンポネントクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "BillboardRendererComponent.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "../../../VertexData.h"
#include "../../../Shader.h"
#include "../../../../Math.h"
#include "../../GameObject/Camera.h"
#include "../../../Resource/Texture.h"


//バッファ

LPDIRECT3DVERTEXBUFFER9 BillboardRendererComponent::vertex_buffer_ = nullptr;
LPDIRECT3DINDEXBUFFER9	BillboardRendererComponent::index_buffer_ = nullptr;

//各バッファのアドレス

VERTEX_MESH*  BillboardRendererComponent::vertex_buffer_address_ = nullptr;
LPWORD*		BillboardRendererComponent::index_buffer_address_ = nullptr;


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
BillboardRendererComponent::BillboardRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, texture_(nullptr)
	, is_compute_texcord_(false)
	, texture_cut_x_(0)
	, texture_cut_y_(0)
	, texture_cut_width_(256)
	, texture_cut_height_(256)
{
	// 初期化
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
BillboardRendererComponent::~BillboardRendererComponent(void)
{
	// 終了化
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool BillboardRendererComponent::Init(void)
{
	//描画シェーダーの指定
	this->shader_type_ = ShaderType::Billboard;

	//バッファの作成
	{
		//頂点バッファの作成
		bool vtx_buffer_init = this->CreateVertexBuffer();
		if (vtx_buffer_init == false)
		{
			assert(!"BillboardRendererComponent::Init()：頂点バッファの作成に失敗しました。");
			return false;
		}

		//インデックスバッファの作成
		bool idx_buffer_init = this->CreateIndexBuffer();
		if (idx_buffer_init == false)
		{
			assert(!"BillboardRendererComponent::Init()：インデックスバッファの作成に失敗しました。");
			return false;
		}
	}

	//バッファの初期化
	this->ComputeVertexBuffer();

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void BillboardRendererComponent::Uninit(void)
{
	SAFE_RELEASE_(vertex_buffer_);
	SAFE_RELEASE_(index_buffer_);
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void BillboardRendererComponent::Draw(Shader* shader, Camera* camera)
{
	auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//回転情報に逆ビュー行列渡す
	this->rotation_matrix_ = *camera->GetViewInverseMatrix();

	//頂点バッファの再構成
	this->ComputeVertexBuffer();

	//頂点バッファの登録
	lpd3d_device->SetStreamSource(0, vertex_buffer_, 0, sizeof(VERTEX_STD));

	//インデックスバッファの登録
	lpd3d_device->SetIndices(index_buffer_);

	//描画処理
	{
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
/*　頂点バッファの作成
-----------------------------------------------------------------------------*/
bool BillboardRendererComponent::CreateVertexBuffer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();
	if (lpd3d_device == nullptr)
	{
		assert("スプライトの頂点バッファ作成時に、デバイスが見つかりませんでした。");
		return false;
	}

	//
	// 頂点バッファインスタンスが既存の場合
	//
	if (vertex_buffer_ != nullptr)
	{
		return true;
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
		{ D3DXVECTOR3(-0.5f,  0.5f, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3( 0.5f,  0.5f, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR3( 0.5f, -0.5f, 0.f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 1.0f) }
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
bool BillboardRendererComponent::CreateIndexBuffer(void)
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
/* 頂点バッファの再構成
-----------------------------------------------------------------------------*/
void BillboardRendererComponent::ComputeVertexBuffer(void)
{
	//VRAMへ書き込みを行うためのRAM上での議事アドレス
	VERTEX_STD* vtx = nullptr;

	//VRAMとの接続を停止
	vertex_buffer_->Lock(0
						, 0
						, (void**)&vtx
						, D3DLOCK_DISCARD);

	//ポリゴンの頂点色を一括で管理
	for (int i = 0; i < MAX_VERTEX_COUNT; i++)
		vtx[i].vtx_color_ = vertex_color_;

	//UVアニメーションを選択できるように
	if (is_compute_texcord_ == true)
	{
		//テクスチャ情報の取得
		auto texture_image_info = *texture_->GetTextureImageInfo();

		//テクスチャの幅と高さを格納
		int texture_width_ = texture_image_info.Width;
		int texture_height_ = texture_image_info.Height;

		//格納されたテクスチャの幅と高さ元にUV座標を計算
		float u0 = (float)texture_cut_x_ / texture_width_;
		float v0 = (float)texture_cut_y_ / texture_height_;
		float u1 = (float)(texture_cut_x_ + texture_cut_width_) / texture_width_;
		float v1 = (float)(texture_cut_y_ + texture_cut_height_) / texture_height_;

		//UV座標を設定。
		vtx[0].texcoord_ = D3DXVECTOR2(u0, v0);
		vtx[1].texcoord_ = D3DXVECTOR2(u1, v0);
		vtx[2].texcoord_ = D3DXVECTOR2(u0, v1);
		vtx[3].texcoord_ = D3DXVECTOR2(u1, v1);
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
//void BillboardRendererComponent::ComputeTransform(void)
//{
//	ビルボードの最適化について
//
//	頂点バッファでの描画毎にVRAMとの接続を開け閉めするやり方は効率が悪いので、
//
//	姿勢制御情報で、拡縮、回転、平行移動などの情報を含んだworld行列をシェーダーへ転送することで
//
//	画面内での大きさや、回転角度などの姿勢情報を転送する
//
//	UVスクロールは、UV座標を直接シェーダーへ転送することで行う
//
//	シェーダーへ転送する情報
//	：拡縮・回転。平行移動情報を含んだワールド行列
//	：頂点カラー
//	：UV座標
//
//}

/*-----------------------------------------------------------------------------
/* テクスチャの設定
-----------------------------------------------------------------------------*/
void BillboardRendererComponent::SetTexture(TextureType textureTypeID)
{
	//テクスチャの読み込み
	this->texture_ = owner_->GetGame()->GetTextureManager()->LoadTexture(textureTypeID);
}

/*-----------------------------------------------------------------------------
/* テクスチャ情報の取得
-----------------------------------------------------------------------------*/
Texture* BillboardRendererComponent::GetTexture(void)
{
	//テクスチャ情報の取得
	if (this->texture_ == nullptr)
	{
		assert(!"GetTexture():BillboardRendererComponentにテクスチャ情報が設定されていません！");
	}
	return texture_;
}

/*-----------------------------------------------------------------------------
/* テクスチャ構成情報の取得
-----------------------------------------------------------------------------*/
D3DXIMAGE_INFO* BillboardRendererComponent::GetTextureImageInfo(void)
{
	//テクスチャ構成情報の取得
	if (this->texture_ == nullptr)
	{
		assert(!"GetTextureImageInfo():BillboardRendererComponentに情報の取得ができませんでした！");
	}
	return texture_->GetTextureImageInfo();
}

/*=============================================================================
/*		End of File
=============================================================================*/