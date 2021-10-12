/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[FFPMeshRendererComponent.h] 固定機能パイプラインによるメッシュ描画
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：固定機能パイプラインによるメッシュ描画コンポーネントクラス
=============================================================================*/
#ifndef FFP_MESH_RENDERER_COMPONENT_H_
#define	FFP_MESH_RENDERER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../RendererComponent.h"

/*-----------------------------------------------
/* 標準メッシュレンダラーコンポーネントクラス
-----------------------------------------------*/
class FFPMeshRendererComponent : public RendererComponent
{
public:
	FFPMeshRendererComponent(class GameObject* owner, int drawOrder = 100);
	~FFPMeshRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::FFPMeshRendererComponent; };

	// ライトの有効化
	void SetEnableLighting(bool isEnable);

	// メッシュ情報の設定
	void SetMesh(XFileMeshType xfileMeshTypeID);

	// メッシュ情報の取得
	class XFileMesh* GetMesh(void);

private:
	//ライトが有効かどうか
	bool is_enable_lighting_;

	// メッシュのデータ
	class XFileMesh* xfile_mesh_;
};


#endif //FFP_MESH_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/