/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GridGizmoRendererComponent.cpp] グリッドギズモ描画コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：グリッドギズモ描画コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "GridGizmoRendererComponent.h"
#include "../../../GameObject.h"
#include "../../../../VertexData.h"
#include "../../../../Shader.h"
#include "../../../../Resource/Material.h"
#include "../../../GameObject/Camera.h"

//バッファ

LPDIRECT3DVERTEXBUFFER9 GridGizmoRendererComponent::vertex_buffer_ = nullptr;

//各バッファのアドレス

VERTEX_GIZMO* GridGizmoRendererComponent::vertex_buffer_address_ = nullptr;


/*-----------------------------------------------------------------------------
/*　コンストラクタ
-----------------------------------------------------------------------------*/
GridGizmoRendererComponent::GridGizmoRendererComponent(GameObject* owner, int drawOrder)
	: GizmoRendererComponent(owner, drawOrder)
{
	const bool init_this_renderer = this->Init();
	if (init_this_renderer == false)
	{
		assert(!"グリッドギズモレンダラーの初期化に失敗した");
	}
}

/*-----------------------------------------------------------------------------
/*　デストラクタ
-----------------------------------------------------------------------------*/
GridGizmoRendererComponent::~GridGizmoRendererComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/*　初期化処理
-----------------------------------------------------------------------------*/
bool GridGizmoRendererComponent::Init(void)
{
	//描画シェーダーの指定
	this->shader_type_ = ShaderType::Gizmo;

	//バッファの作成
	{
		//頂点バッファの作成
		bool vtx_buffer_init = this->CreateVertexBuffer();
		if (vtx_buffer_init == false)
		{
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/*　終了化処理
-----------------------------------------------------------------------------*/
void GridGizmoRendererComponent::Uninit(void)
{
	SAFE_RELEASE_(vertex_buffer_);
}

/*-----------------------------------------------------------------------------
/*　描画処理
-----------------------------------------------------------------------------*/
void GridGizmoRendererComponent::Draw(Shader* shader, Camera* camera)
{
	auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//頂点バッファの登録
	lpd3d_device->SetStreamSource(0, vertex_buffer_, 0, sizeof(VERTEX_GIZMO));

	//描画処理
	{
		// NULLのマテリアルを渡す
		class Material* material_buffer = nullptr;

		// シェーダーのセット
		shader->ShaderSet(camera, this, material_buffer);

		//シェーダーパスの開始
		shader->ShaderPassBegin();

		// ポリゴン描画
		lpd3d_device->DrawPrimitive(D3DPT_LINELIST		//ポリゴンの描画タイプ
								   , 0					//0番目の頂点バッファ
								   , MAX_VERTEX_COUNT);	//プリミティブの数

		//シェーダーパスの終了
		shader->ShaderPassEnd();
	}

}

/*-----------------------------------------------------------------------------
/*　頂点バッファの作成
-----------------------------------------------------------------------------*/
bool GridGizmoRendererComponent::CreateVertexBuffer(void)
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
		assert("グリッドギズモの頂点バッファ作成時に、デバイスが見つかりませんでした。");
		return false;
	}

	//頂点バッファの作成
	if (FAILED(lpd3d_device->CreateVertexBuffer((MAX_VERTEX_COUNT * sizeof(VERTEX_GIZMO))	//頂点バッファサイズ
											   , D3DUSAGE_WRITEONLY							//バッファの使用方法
											   , FVF_VERTEX_GIZMO							//頂点のフォーマット
											   , D3DPOOL_MANAGED							//メモリ管理をデバイスに任せる
											   , &vertex_buffer_							//頂点バッファのインターフェース
											   , nullptr)))
	{
		assert("グリッドギズモの頂点バッファ作成に失敗しました。");
		return false;
	}

	//システムメモリ上の頂点データ
	VERTEX_GIZMO vtx[MAX_VERTEX_COUNT];

	const int StartLine = (GRID_SIZE / 2);
	const int EndLine	=-(GRID_SIZE / 2);

	//配置した線の数を初期化
	int line_count_ = 0;
	for (int i = 0; i < ONE_STRIPES_VERTEX_COUNT; i++)
	{
		// 横線の頂点の配置
		vtx[i] = { D3DXVECTOR3(StartLine,  0.f, static_cast<float>(StartLine - line_count_)), D3DCOLOR_RGBA(255, 255, 255, 255) };
		i++;
		vtx[i] = { D3DXVECTOR3(EndLine,	   0.f, static_cast<float>(StartLine - line_count_)), D3DCOLOR_RGBA(255, 255, 255, 255) };
		line_count_++;
	}

	//配置した線の数を初期化
	line_count_ = 0;
	for (int i = 0; i < ONE_STRIPES_VERTEX_COUNT; i++)
	{
		// 縦線の頂点の配置
		vtx[ONE_STRIPES_VERTEX_COUNT + i] = { D3DXVECTOR3(static_cast<float>(StartLine - line_count_),  0.f, StartLine), D3DCOLOR_RGBA(255, 255, 255, 255) };
		i++;
		vtx[ONE_STRIPES_VERTEX_COUNT + i] = { D3DXVECTOR3(static_cast<float>(StartLine - line_count_),  0.f, EndLine),   D3DCOLOR_RGBA(255, 255, 255, 255) };
		line_count_++;
	}

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

/*=============================================================================
/*		End of File
=============================================================================*/