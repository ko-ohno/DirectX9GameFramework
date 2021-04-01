/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdMeshRendererComponent.cpp] 標準メッシュレンダラーコンポーネントクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：標準メッシュレンダラーコンポーネントクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "StdMeshRendererComponent.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "../../../VertexData.h"
#include "../../../Shader.h"
#include "../../../../Math.h"
#include "../../../Resource/XFileMesh.h"
#include "../../GameObject/Camera.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
StdMeshRendererComponent::StdMeshRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, xfile_mesh_(nullptr)
{
	// 初期化
	this->Init();
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
StdMeshRendererComponent::~StdMeshRendererComponent(void)
{
	// 終了化
	this->Uninit();
}


/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool StdMeshRendererComponent::Init(void)
{
	//描画シェーダーの指定
	this->shader_type_ = ShaderType::StandardMesh;

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void StdMeshRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void StdMeshRendererComponent::Draw(Shader* shader, Camera* camera)
{
	auto lpd3d_device = *owner_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//メッシュ情報の確認
	if (xfile_mesh_ == nullptr)
	{
		assert(!"StdMeshRendererComponent::Draw():メッシュ情報が設定されていません！");
	}

	//描画処理
	{
		//シェーダーのセット
		shader->ShaderSet(camera, this);

		//シェーダーパスの開始
		shader->ShaderPassBegin();

		//描画中のメッシュがプリミティブのメッシュか？
		const bool is_drawing_primitive_mesh = xfile_mesh_->IsGetLoadedPrimitiveMesh();
		if (is_drawing_primitive_mesh)
		{
			//プリミティブのメッシュならこれで描画できる
			xfile_mesh_->GetMesh()->DrawSubset(0);
		}
		else
		{
			// メッシュからマテリアル情報の取得
			auto materials = (LPD3DXMATERIAL)xfile_mesh_->GetMaterialBuffer()->GetBufferPointer();

			//マテリアルの数の取得
			auto material_counts = xfile_mesh_->GetMaterialCounts();

			//メッシュの保有する面の数だけ描画
			for (unsigned int i = 0; i < static_cast<int>(material_counts); i++)
			{
				lpd3d_device->SetMaterial(&materials[i].MatD3D);
				if (materials[i].pTextureFilename != nullptr)
				{
					lpd3d_device->SetTexture(0, xfile_mesh_->GetMeshTextureList().at(i));
				}
				else
				{
					lpd3d_device->SetTexture(0, nullptr);
				}
				xfile_mesh_->GetMesh()->DrawSubset(i);
			}
		}

		//シェーダーパスの終了
		shader->ShaderPassEnd();
	}
}

/*-----------------------------------------------------------------------------
/* メッシュの設定
-----------------------------------------------------------------------------*/
void StdMeshRendererComponent::SetMesh(XFileMeshType xfileMeshTypeID)
{
	//メッシュの読み込み
	this->xfile_mesh_ = owner_->GetGame()->GetMeshManager()->LoadMesh(xfileMeshTypeID);
}

/*-----------------------------------------------------------------------------
/* メッシュ情報の取得
-----------------------------------------------------------------------------*/
XFileMesh* StdMeshRendererComponent::GetMesh(void)
{
	//メッシュ情報の取得
	if (this->xfile_mesh_ == nullptr)
	{
		assert(!"StdMeshRendererComponent::GetMesh():メッシュ情報が設定されていません！");
	}
	return xfile_mesh_;
}

/*=============================================================================
/*		End of File
=============================================================================*/