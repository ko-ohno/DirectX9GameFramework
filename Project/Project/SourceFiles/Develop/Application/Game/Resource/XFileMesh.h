/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[XFileMesh.h] Xファイルメッシュクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：Xファイルメッシュクラス
=============================================================================*/
#ifndef XFILE_MESH_H_
#define	XFILE_MESH_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "../Manager/MeshManager.h"


/*-------------------------------------
/* Xファイルメッシュクラス
-------------------------------------*/
class XFileMesh
{
public:
	XFileMesh(class MeshManager* manager, XFileMeshType meshType);
	~XFileMesh(void);

	// メッシュの読み込み
	bool LoadMeshFile(const XFileMeshType meshType);

	// プリミティブのメッシュか
	bool IsGetPrimitiveMesh(void) { return is_primitive_mesh_; }

	// テクスチャの読み込みができているか
	bool IsGetLoadCompleted(void) { return is_loading_complete_; }
	
	// マテリアルの追加
	void AddMaterial(class Material* material);

	//
	// メッシュのデータ取得関数
	//

	// メッシュIDの取得
	XFileMeshType GetMeshTypeID(void) { return mesh_type_id_; }

	// メッシュ情報の取得
	LPD3DXMESH GetMesh(void) const { return lpd3dx_mesh_; }

	// マテリアル数の取得
	DWORD GetMaterialCounts(void) { return material_count_; }

	// マテリアルバッファの取得
	LPD3DXBUFFER GetMaterialBuffer(void) { return material_buffer_; }

	std::vector<class Material*> GetMeshMaterialList(void) { return mesh_material_list_; }

private:
	bool MeshOptimization(const std::string& xfileMeshName, const LPD3DXBUFFER& adjacensy);
	bool MeshClone(const std::string& xfileMeshName, const LPDIRECT3DDEVICE9& lpd3dDevice);

private:
	//
	//　プリミティブ作成関数の呼び出し
	//

	bool LoadD3DXPrimitiveMesh(XFileMeshType meshType);

	bool LoadD3DXMeshPolygon(void);
	bool LoadD3DXMeshBox(void);
	bool LoadD3DXMeshCylinder(void);
	bool LoadD3DXMeshSphere(void);


private:
	// メッシュの所有者
	class MeshManager*	mesh_manager_;

	//
	// メッシュのデータ
	//

	bool				is_primitive_mesh_;
	bool				is_loading_complete_;

	XFileMeshType		mesh_type_id_;
	LPD3DXMESH			lpd3dx_mesh_;
	DWORD				material_count_;
	LPD3DXBUFFER		material_buffer_;

	//メッシュが所有するマテリアルのリスト
	std::vector<class Material*> mesh_material_list_;

};

#endif //XFILE_MESH_H_
/*=============================================================================
/*		End of File
=============================================================================*/
