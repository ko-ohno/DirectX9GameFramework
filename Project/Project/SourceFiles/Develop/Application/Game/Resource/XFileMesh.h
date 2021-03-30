/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[XFileMesh.h] ���W���[���w�b�_
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F
=============================================================================*/
#ifndef XFILE_MESH_H_
#define	XFILE_MESH_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* �\����
-------------------------------------*/
enum class XFileMeshType
{
	None = -1

	, Max
};


/*-------------------------------------
/* XFileMesh�N���X
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
