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
class GridGizmoRendererComponent : public GizmoRendererComponent
{
public:
	GridGizmoRendererComponent(class GameObject* owner, int drawOrder = 100);
	~GridGizmoRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::GridGizmoRendererComponent; };

private:
	bool CreateVertexBuffer(void);

private:
	// グリッドのサイズ
	static constexpr int GRID_SIZE = 10;

	// 一つの辺の頂点数
	static constexpr int ONE_EDGE_VERTEX_COUNT = 2;

	// 一つのストライプの頂点数
	static constexpr int ONE_STRIPES_VERTEX_COUNT = ONE_EDGE_VERTEX_COUNT * (GRID_SIZE + 1);

	//
	// 各軸ごとのストライプの頂点数
	//

	static constexpr int X_AXIS_STRIPES_VERTEX_COUNT = ONE_STRIPES_VERTEX_COUNT;
	static constexpr int Y_AXIS_STRIPES_VERTEX_COUNT = 0;
	static constexpr int Z_AXIS_STRIPES_VERTEX_COUNT = ONE_STRIPES_VERTEX_COUNT;

	// 合計の最大頂点数
	static constexpr int MAX_VERTEX_COUNT = X_AXIS_STRIPES_VERTEX_COUNT
										  + Y_AXIS_STRIPES_VERTEX_COUNT
										  + Z_AXIS_STRIPES_VERTEX_COUNT;	//頂点バッファ数

	static LPDIRECT3DVERTEXBUFFER9	vertex_buffer_;				//頂点バッファ

	static VERTEX_GIZMO*			vertex_buffer_address_;	//頂点バッファのアドレス
};

#endif //GRID_GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/