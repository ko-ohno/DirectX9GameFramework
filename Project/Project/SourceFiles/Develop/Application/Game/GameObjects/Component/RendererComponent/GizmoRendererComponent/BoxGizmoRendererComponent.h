/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BoxGizmoRendererComponent.h]  ボックスギズモ描画コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ボックスギズモ描画コンポーネント
=============================================================================*/
#ifndef BOX_GIZMO_RENDERER_COMPONENT_H_
#define	BOX_GIZMO_RENDERER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../GizmoRendererComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* ボックスギズモ描画コンポーネント
-------------------------------------*/
class BoxGizmoRendererComponent : public GizmoRendererComponent
{
public:
	BoxGizmoRendererComponent(class GameObject* owner, int drawOrder = 100);
	~BoxGizmoRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::BoxGizmoRendererComponent; };

	// メッシュ情報の取得
	class XFileMesh* GetMesh(void);

private:
	// メッシュのデータ
	class XFileMesh* xfile_mesh_;
};

#endif //BOX_GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/