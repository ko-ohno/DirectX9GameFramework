/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[XFileMesh.h] X�t�@�C�����b�V���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FX�t�@�C�����b�V���N���X
=============================================================================*/
#ifndef XFILE_MESH_H_
#define	XFILE_MESH_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "../Manager/MeshManager.h"


/*-------------------------------------
/* X�t�@�C�����b�V���N���X
-------------------------------------*/
class XFileMesh
{
public:
	XFileMesh(class MeshManager* manager, XFileMeshType meshType);
	~XFileMesh(void);

	// ���b�V���̓ǂݍ���
	bool LoadMeshFile(XFileMeshType meshType);

	// �e�N�X�`���̓ǂݍ��݂��ł��Ă��邩
	bool IsGetLoadCompleted(void) { return is_loading_complete_; }

	// ���L���郁�b�V�����v���~�e�B�u�̃��b�V����
	bool IsGetLoadedPrimitiveMesh(void) { return is_loaded_primitive_mesh_; }

	// �e�N�X�`���̒ǉ�
	void AddTexture(LPDIRECT3DTEXTURE9 texture);
	
	//
	// ���b�V���̃f�[�^�擾�֐�
	//

	// ���b�V��ID�̎擾
	XFileMeshType GetMeshTypeID(void) { return mesh_type_id_; }

	// ���b�V�����̎擾
	LPD3DXMESH GetMesh(void) const { return lpd3dx_mesh_; }

	// �}�e���A�����̎擾
	DWORD GetMaterialCounts(void) { return material_count_; }

	// �}�e���A���o�b�t�@�̎擾
	LPD3DXBUFFER GetMaterialBuffer(void) { return material_buffer_; }

	std::vector<LPDIRECT3DTEXTURE9> GetMeshTextureList(void) { return mesh_texture_list_; }

private:
	//
	//�@�v���~�e�B�u�쐬�֐��̌Ăяo��
	//

	bool LoadD3DXPrimitiveMesh(XFileMeshType meshType);

	bool LoadD3DXMeshPolygon(void);
	bool LoadD3DXMeshBox(void);
	bool LoadD3DXMeshCylinder(void);
	bool LoadD3DXMeshSphere(void);


private:
	// ���b�V���̏��L��
	class MeshManager*	mesh_manager_;

	//
	// ���b�V���̃f�[�^
	//

	bool				is_loading_complete_;
	bool				is_loaded_primitive_mesh_;

	XFileMeshType		mesh_type_id_;
	LPD3DXMESH			lpd3dx_mesh_;
	DWORD				material_count_;
	LPD3DXBUFFER		material_buffer_;

	//�e�N�X�`���̃t�@�C���p�X
	std::string texture_filepath_;

	//���b�V�������L����e�N�X�`���̃��X�g
	std::vector<LPDIRECT3DTEXTURE9> mesh_texture_list_;
};

#endif //XFILE_MESH_H_
/*=============================================================================
/*		End of File
=============================================================================*/
