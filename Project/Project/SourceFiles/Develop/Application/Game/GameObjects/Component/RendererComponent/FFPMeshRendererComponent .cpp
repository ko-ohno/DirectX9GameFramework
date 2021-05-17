/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[FFPMeshRendererComponent.cpp] 固定機能パイプラインによるメッシュ描画
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：固定機能パイプラインによるメッシュ描画コンポーネントクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "FFPMeshRendererComponent.h"
#include "../../GameObject.h"
#include "../../../Shader.h"
#include "../../../Resource/XFileMesh.h"
#include "../../GameObject/Camera.h"
#include "../../../Resource/Material.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
FFPMeshRendererComponent::FFPMeshRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, xfile_mesh_(nullptr)
{
	// 初期化
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
FFPMeshRendererComponent::~FFPMeshRendererComponent(void)
{
	// 終了化
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool FFPMeshRendererComponent::Init(void)
{
	//描画シェーダーの指定
	this->shader_type_ = ShaderType::StandardMesh;
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void FFPMeshRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void FFPMeshRendererComponent::Draw(Shader* shader, Camera* camera)
{
	UNREFERENCED_PARAMETER(shader);
	UNREFERENCED_PARAMETER(camera);

	auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//メッシュ情報の確認
	if (xfile_mesh_ == nullptr)
	{
		assert(!"FFPMeshRendererComponent::Draw():メッシュ情報が設定されていません！");
	}

	//描画処理
	{
		// マテリアル数の取得
		auto material_count = xfile_mesh_->GetMaterialCounts();

		// マテリアルリストの取得
		auto material_list = xfile_mesh_->GetMeshMaterialList();

		//マテリアルの一時格納先
		class Material* material_buffers = nullptr;

		// Zfuncの有効化
		lpd3d_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

		// FVF(今から使用する頂点情報)の設定
		lpd3d_device->SetFVF(FVF_VERTEX_MESH);

		//ワールド座標変換
		lpd3d_device->SetTransform(D3DTS_WORLD, this->GetWorldMatrix()); 

		//マテリアルがあるか？
		if (material_count > 0)
		{
			// マテリアル数分だけ描画
			for (int i = 0; i < static_cast<int>(material_count); i++)
			{
				//マテリアルの初期化
				material_buffers = nullptr;

				// 作成されたマテリアルのリストが空ではない時
				if (!material_list.empty())
				{
					// 作成されたマテリアルリストとマテリアル数が食い違うとき
					const bool is_list_out_of_range = (static_cast<unsigned int>(i) < material_list.size());
					if (is_list_out_of_range)
					{
						material_buffers = xfile_mesh_->GetMeshMaterialList().at(i);
					}

					// マテリアルの設定
					lpd3d_device->SetMaterial(material_buffers->GetD3DMaterial());

					// テクスチャの設定
					lpd3d_device->SetTexture(0, *material_buffers->GetTexture());
				}

				// メッシュの描画
				xfile_mesh_->GetMesh()->DrawSubset(i);

			}
		}
		else
		{
			// メッシュの描画
			xfile_mesh_->GetMesh()->DrawSubset(0);
		}

		// Zfuncの無効化
		lpd3d_device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	}
}

/*-----------------------------------------------------------------------------
/* メッシュ情報の設定
-----------------------------------------------------------------------------*/
void FFPMeshRendererComponent::SetMesh(XFileMeshType xfileMeshTypeID)
{
	//メッシュの読み込み
	this->xfile_mesh_ = owner_->GetGame()->GetMeshManager()->LoadMesh(xfileMeshTypeID);
}

/*-----------------------------------------------------------------------------
/* メッシュ情報の取得
-----------------------------------------------------------------------------*/
XFileMesh* FFPMeshRendererComponent::GetMesh(void)
{
	//メッシュ情報の取得
	if (this->xfile_mesh_ == nullptr)
	{
		assert(!"FFPMeshRendererComponent::GetMesh():メッシュ情報が設定されていません！");
	}
	return xfile_mesh_;
}

/*=============================================================================
/*		End of File
=============================================================================*/