/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[XFileMesh.h] モジュールヘッダ
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：
=============================================================================*/
#ifndef XFILE_MESH_H_
#define	XFILE_MESH_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/
enum class XFileMeshType
{
	None = -1

	, Max
};


/*-------------------------------------
/* XFileMeshクラス
-------------------------------------*/
class XFileMesh
{
public:
	XFileMesh(class MeshManager* manager, XFileMeshType meshType);
	~XFileMesh(void);

	bool Init(void);
	void Uninit(void);

private:
	LPD3DXMESH		   mesh_;
	DWORD			   material_count_;
	LPD3DXBUFFER	   material_buffer_;

	std::vector<LPDIRECT3DTEXTURE9> textures_;
};

#endif //XFILE_MESH_H_
/*=============================================================================
/*		End of File
=============================================================================*/
