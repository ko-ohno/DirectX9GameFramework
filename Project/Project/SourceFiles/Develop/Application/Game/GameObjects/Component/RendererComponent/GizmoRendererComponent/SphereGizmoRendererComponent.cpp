/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereGizmoRendererComponent.cpp] スフィアギズモ描画コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スフィアギズモ描画コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "SphereGizmoRendererComponent.h"
#include "../../../GameObject.h"
#include "../../../../Shader.h"
#include "../../../../Resource/XFileMesh.h"
#include "../../../../Resource/Material.h"


/*-----------------------------------------------------------------------------
/*　コンストラクタ
-----------------------------------------------------------------------------*/
SphereGizmoRendererComponent::SphereGizmoRendererComponent(GameObject* owner, int drawOrder)
	: GizmoRendererComponent(owner, drawOrder)
	, xfile_mesh_(nullptr)
{
	// 初期化
	this->Init();
}

/*-----------------------------------------------------------------------------
/*　デストラクタ
-----------------------------------------------------------------------------*/
SphereGizmoRendererComponent::~SphereGizmoRendererComponent(void)
{
	// 終了化
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/*　初期化処理
-----------------------------------------------------------------------------*/
bool SphereGizmoRendererComponent::Init(void)
{
	//メッシュの読み込み
	this->xfile_mesh_ = owner_->GetGame()->GetMeshManager()->LoadMesh(XFileMeshType::Sphere);

	return true;
}

/*-----------------------------------------------------------------------------
/*　終了化処理
-----------------------------------------------------------------------------*/
void SphereGizmoRendererComponent::Uninit(void)
{
	
}

/*-----------------------------------------------------------------------------
/*　描画処理
-----------------------------------------------------------------------------*/
void SphereGizmoRendererComponent::Draw(Shader* shader, Camera* camera)
{
	//メッシュ情報の確認
	if (xfile_mesh_ == nullptr)
	{
		assert(!"SphereGizmoRendererComponent::Draw():メッシュ情報が設定されていません！");
	}

	//描画処理
	{
		// NULLのマテリアルを渡す
		class Material* material_buffer = nullptr;

		// シェーダーのセット
		shader->ShaderSet(camera, this, material_buffer);

		//シェーダーパスの開始
		shader->ShaderPassBegin();

		// メッシュの描画
		xfile_mesh_->GetMesh()->DrawSubset(0);

		//シェーダーパスの終了
		shader->ShaderPassEnd();
	}
}

/*-----------------------------------------------------------------------------
/* メッシュ情報の取得
-----------------------------------------------------------------------------*/
XFileMesh* SphereGizmoRendererComponent::GetMesh(void)
{
	//メッシュ情報の取得
	if (this->xfile_mesh_ == nullptr)
	{
		assert(!"SphereGizmoRendererComponent::GetMesh():メッシュ情報が設定されていません！");
	}
	return xfile_mesh_;
}

/*=============================================================================
/*		End of File
=============================================================================*/