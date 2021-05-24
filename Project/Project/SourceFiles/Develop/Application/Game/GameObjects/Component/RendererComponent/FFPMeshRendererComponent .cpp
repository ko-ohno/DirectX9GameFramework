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
#include "../TransformComponent.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
FFPMeshRendererComponent::FFPMeshRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, is_enable_lighting_(false)
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

	//// 自身の所有者のワールド行列と、自身のワールド行列を取得
	//auto owner_world_matrix = *owner_->GetTransform()->GetWorldMatrix();
	//auto mesh_world_matrix = *this->GetWorldMatrix();

	//// ワールド行列を計算
	//auto world_matrix = mesh_world_matrix * owner_world_matrix;

	//メッシュ情報の確認
	if (xfile_mesh_ == nullptr)
	{
		assert(!"FFPMeshRendererComponent::Draw():メッシュ情報が設定されていません！");
	}

	lpd3d_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	lpd3d_device->SetFVF(FVF_VERTEX_MESH);

	lpd3d_device->SetTransform(D3DTS_WORLD, &world_matrix_);

	if (is_enable_lighting_)
	{
		lpd3d_device->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	//描画処理
	{
		// マテリアル数の取得
		auto material_count = xfile_mesh_->GetMaterialCounts();

		// マテリアルの取得
		auto material_buffer = (LPD3DXMATERIAL)xfile_mesh_->GetMaterialBuffer()->GetBufferPointer();

		for (unsigned int i = 0; i < material_count; i++)
		{
			lpd3d_device->SetMaterial(&material_buffer[i].MatD3D);
			if (material_buffer[i].pTextureFilename != nullptr)
			{
				lpd3d_device->SetTexture(0, *xfile_mesh_->GetMeshMaterialList().at(i)->GetTexture());
			}
			else
			{
				lpd3d_device->SetTexture(0, nullptr);
			}

			xfile_mesh_->GetMesh()->DrawSubset(i);
		}
	}

	if (is_enable_lighting_)
	{
		lpd3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	lpd3d_device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
}

/*-----------------------------------------------------------------------------
/* ライト
-----------------------------------------------------------------------------*/
void FFPMeshRendererComponent::SetEnableLighting(bool isEnable)
{
	this->is_enable_lighting_ = isEnable;
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