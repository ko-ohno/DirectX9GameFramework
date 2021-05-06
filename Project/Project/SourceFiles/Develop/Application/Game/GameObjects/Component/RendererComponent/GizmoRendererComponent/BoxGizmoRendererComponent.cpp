/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BoxGizmoRendererComponent.cpp] ボックスギズモ描画コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボックスギズモ描画コンポーネント
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../../StdAfx.h"
#include "BoxGizmoRendererComponent.h"
#include "../../../GameObject.h"
#include "../../../../Shader.h"
#include "../../../../Resource/XFileMesh.h"
#include "../../../../Resource/Material.h"

/*-----------------------------------------------------------------------------
/*　コンストラクタ
-----------------------------------------------------------------------------*/
BoxGizmoRendererComponent::BoxGizmoRendererComponent(GameObject* owner, int drawOrder)
	: GizmoRendererComponent(owner, drawOrder)
	, xfile_mesh_(nullptr)
{
	// 初期化
	this->Init();
}

/*-----------------------------------------------------------------------------
/*　デストラクタ
-----------------------------------------------------------------------------*/
BoxGizmoRendererComponent::~BoxGizmoRendererComponent(void)
{
	// 終了化
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/*　初期化処理
-----------------------------------------------------------------------------*/
bool BoxGizmoRendererComponent::Init(void)
{
	//メッシュの読み込み
	this->xfile_mesh_ = owner_->GetGame()->GetMeshManager()->LoadMesh(XFileMeshType::Box);

	return true;
}

/*-----------------------------------------------------------------------------
/*　終了化処理
-----------------------------------------------------------------------------*/
void BoxGizmoRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/*　描画処理
-----------------------------------------------------------------------------*/
void BoxGizmoRendererComponent::Draw(Shader* shader, Camera* camera)
{
	//メッシュ情報の確認
	if (xfile_mesh_ == nullptr)
	{
		assert(!"BoxGizmoRendererComponent::Draw():メッシュ情報が設定されていません！");
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
XFileMesh* BoxGizmoRendererComponent::GetMesh(void)
{
	//メッシュ情報の取得
	if (this->xfile_mesh_ == nullptr)
	{
		assert(!"BoxGizmoRendererComponent::GetMesh():メッシュ情報が設定されていません！");
	}
	return xfile_mesh_;
}


/*=============================================================================
/*		End of File
=============================================================================*/