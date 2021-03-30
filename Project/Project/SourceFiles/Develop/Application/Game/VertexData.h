/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[VertexData.h]  頂点のデータ(性質)を定義したヘッダ
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：頂点のデータ(性質)を定義したヘッダ
=============================================================================*/
#ifndef VERTEX_DATA_H_
#define	VERTEX_DATA_H_

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"


/*--- クラスの前方宣言 ---*/

/*-------------------------------------
/* 2Dの頂点データ構造体
-------------------------------------*/
typedef struct
{
	D3DXVECTOR3 position_;		//ローカル座標
	D3DCOLOR	vtx_color_;		//色情報
	D3DXVECTOR2 texcoord_;		//UV座標
}VERTEX_STD;

// 2Dの頂点フォーマットの設定
#define FVF_VERTEX_STD (D3DFVF_XYZ		\
					 |  D3DFVF_DIFFUSE	\
					 |  D3DFVF_TEX1) 


/*-------------------------------------
/* 3Dの頂点データ構造体
-------------------------------------*/
typedef struct
{
	D3DXVECTOR3 position_;		//ローカル座標
	D3DXVECTOR3 normal_;		//法線情報
	D3DCOLOR	vtx_color_;		//色情報
	D3DXVECTOR2 texcoord_;		//UV座標
}VERTEX_MESH;				

// 3Dの頂点フォーマットの設定
#define FVF_VERTEX_MESH (D3DFVF_XYZ		\
					  |  D3DFVF_NORMAL	\
					  |  D3DFVF_DIFFUSE	\
					  |  D3DFVF_TEX1) 



/*-------------------------------------
/* Gizmo用の頂点データ構造体
-------------------------------------*/
typedef struct
{
	D3DXVECTOR3 position_;		//ローカル座標
	D3DCOLOR	vtx_color_;		//色情報
}VERTEX_GIZMO;			

// Gizmoの頂点フォーマットの設定
#define FVF_VERTEX_GIZMO (D3DFVF_XYZ		\
				       |  D3DFVF_DIFFUSE) 



#endif //VERTEX_DATA_H_
/*=============================================================================
/*		End of File
=============================================================================*/