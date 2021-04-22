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
	bool LoadMeshFile(const XFileMeshType meshType);

	// �v���~�e�B�u�̃��b�V����
	bool IsGetPrimitiveMesh(void) { return is_primitive_mesh_; }

	// �e�N�X�`���̓ǂݍ��݂��ł��Ă��邩
	bool IsGetLoadCompleted(void) { return is_loading_complete_; }
	
	// �}�e���A���̒ǉ�
	void AddMaterial(class Material* material);

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

	std::vector<class Material*> GetMeshMaterialList(void) { return mesh_material_list_; }

private:
	bool MeshOptimization(const std::string& xfileMeshName, const LPD3DXBUFFER& adjacensy);
	bool MeshClone(const std::string& xfileMeshName, const LPDIRECT3DDEVICE9& lpd3dDevice);

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

	bool				is_primitive_mesh_;
	bool				is_loading_complete_;

	XFileMeshType		mesh_type_id_;
	LPD3DXMESH			lpd3dx_mesh_;
	DWORD				material_count_;
	LPD3DXBUFFER		material_buffer_;

	//���b�V�������L����}�e���A���̃��X�g
	std::vector<class Material*> mesh_material_list_;

};

#endif //XFILE_MESH_H_
/*=============================================================================
/*		End of File
=============================================================================*/
