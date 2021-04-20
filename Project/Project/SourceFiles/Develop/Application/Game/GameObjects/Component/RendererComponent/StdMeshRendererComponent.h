/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdMeshRendererComponent.h] 標準メッシュレンダラーコンポーネントクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：標準メッシュレンダラーコンポーネントクラス
=============================================================================*/
#ifndef STD_MESH_RENDERER_COMPONENT_H_
#define	STD_MESH_RENDERER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../RendererComponent.h"
#include "../../../../Math.h"


/*-----------------------------------------------
/* 標準メッシュレンダラーコンポーネントクラス
-----------------------------------------------*/
class StdMeshRendererComponent : public RendererComponent
{
public:
	StdMeshRendererComponent(class GameObject* owner, int drawOrder = 100);
	~StdMeshRendererComponent(void);

	bool Init(void) override;
	void Uninit(void) override;

	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::StdMeshRendererComponent; };

	// メッシュの設定
	void SetMesh(XFileMeshType xfileMeshTypeID);

	// メッシュ情報の取得
	class XFileMesh* GetMesh(void);

private:
	// メッシュのデータ
	class XFileMesh* xfile_mesh_;
};


#endif //STD_MESH_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/