/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GizmoRendererComponent.h]  ギズモ描画コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ギズモ描画コンポーネント
=============================================================================*/
#ifndef GIZMO_RENDERER_COMPONENT_H_
#define	GIZMO_RENDERER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../RendererComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* コンポーネント
-------------------------------------*/
class GizmoRendererComponent : public RendererComponent
{
public:
	GizmoRendererComponent(class GameObject* owner, int drawOrder = 100);
	~GizmoRendererComponent(void);

public:
	bool Init(void) override;
	void Uninit(void) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::GizmoRendererComponent; };

private:
};

#endif //GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/