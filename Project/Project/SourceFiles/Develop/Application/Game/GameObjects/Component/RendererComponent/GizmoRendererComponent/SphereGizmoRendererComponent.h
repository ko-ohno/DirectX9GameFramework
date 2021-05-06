/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereGizmoRendererComponent.h]  スフィアギズモ描画コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スフィアギズモ描画コンポーネント
=============================================================================*/
#ifndef SPHERE_GIZMO_RENDERER_COMPONENT_H_
#define	SPHERE_GIZMO_RENDERER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../GizmoRendererComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* スフィアギズモ描画コンポーネント
-------------------------------------*/
class SphereGizmoRendererComponent : public GizmoRendererComponent
{
public:
	SphereGizmoRendererComponent(class GameObject* owner, int drawOrder = 100);
	~SphereGizmoRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::SphereGizmoRendererComponent; };

	// メッシュ情報の取得
	class XFileMesh* GetMesh(void);

private:
	// メッシュのデータ
	class XFileMesh* xfile_mesh_;
};

#endif //SPHERE_GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/