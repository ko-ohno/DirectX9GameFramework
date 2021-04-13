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
#include "../../../Resource/Material.h"


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
	//メッシュ情報の確認
	if (xfile_mesh_ == nullptr)
	{
		assert(!"StdMeshRendererComponent::Draw():メッシュ情報が設定されていません！");
	}

	//描画処理
	{
		// マテリアル数の取得
		auto material_count = xfile_mesh_->GetMaterialCounts();

		// マテリアルリストの取得
		auto material_list = xfile_mesh_->GetMeshMaterialList();

		//マテリアルの一時格納先
		class Material* material_buffers = nullptr;

		//描画するメッシュがプリミティブのメッシュか
		const bool is_primitive_mesh = xfile_mesh_->IsGetPrimitiveMesh();
		if (is_primitive_mesh)
		{
			shader->SetTechnique("Tech2");
		}
		else
		{
			shader->SetTechnique("Tech");
		}

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
				}

				// シェーダーのセット
				shader->ShaderSet(camera, this, material_buffers);

				//シェーダーパスの開始
				shader->ShaderPassBegin();

				// メッシュの描画
				xfile_mesh_->GetMesh()->DrawSubset(i);

				//シェーダーパスの終了
				shader->ShaderPassEnd();
			}
		}
		else
		{
			// シェーダーのセット
			shader->ShaderSet(camera, this, material_buffers);

			//シェーダーパスの開始
			shader->ShaderPassBegin();

			// メッシュの描画
			xfile_mesh_->GetMesh()->DrawSubset(0);

			//シェーダーパスの終了
			shader->ShaderPassEnd();
		}
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