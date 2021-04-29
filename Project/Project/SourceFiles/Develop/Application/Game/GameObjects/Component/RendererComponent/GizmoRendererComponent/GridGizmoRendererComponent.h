/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GridRendererComponent.h]  グリッドギズモ描画コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：グリッドギズモ描画コンポーネント
=============================================================================*/
#ifndef GRID_GIZMO_RENDERER_COMPONENT_H_
#define	GRID_GIZMO_RENDERER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../GizmoRendererComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* グリッドギズモ描画コンポーネント
-------------------------------------*/
class GridRendererComponent : public GizmoRendererComponent
{
public:
	GridRendererComponent(class GameObject* owner, int updateOrder = 100);
	~GridRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::GridRendererComponent; };

	void WireFlameON(void);
	void WireFlameOFF(void);

private:
};

#endif //GRID_GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/