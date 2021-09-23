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

public:
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::SphereGizmoRendererComponent; };

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

#endif //SPHERE_GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/