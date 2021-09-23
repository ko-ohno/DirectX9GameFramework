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

public:
	bool Init(void) override;
	void Uninit(void) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::BoxGizmoRendererComponent; };

	//拡縮成分の操作

	virtual inline void SetScale(float scaleValue) override { scale_ = { scaleValue * 2.f, scaleValue * 2.f, scaleValue * 2.f }; }
	virtual inline void SetScale(float scaleX, float scaleY, float scaleZ = 1.f)  override { scale_ = { scaleX * 2.f, scaleY * 2.f, scaleZ * 2.f }; }
	virtual inline void SetScale(const D3DXVECTOR3& scale)  override { scale_ = (scale * 2.f); }
	virtual inline void SetScaleX(float scaleX)  override { scale_.x = (scaleX * 2.f); }
	virtual inline void SetScaleY(float scaleY)  override { scale_.y = (scaleY * 2.f); }
	virtual inline void SetScaleZ(float scaleZ)  override { scale_.z = (scaleZ * 2.f); }

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