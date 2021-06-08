/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshManager.h] メッシュ管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メッシュ管理クラス
=============================================================================*/
#ifndef MESH_MANAGER_H_
#define	MESH_MANAGER_H_

/*--- インクルードファイル ---*/

/*-------------------------------------
/* メッシュの種類
-------------------------------------*/
enum class XFileMeshType
{
	None = -1
	, Polygon
	, Box
	, Cylinder
	, Sphere

	, AirPlane
	, SpaceShip

	, EnemyWeak
	, EnemyStrong
	, EnemyBoss

	, GreenBullet
	, BlueBullet
	, RedBullet

	, SkyBox
	, SkyDome
	, Max
};

/*-------------------------------------
/* メッシュ管理クラス
-------------------------------------*/
class MeshManager
{
public:
	static const char* XFileMeshTypeNames[static_cast<int>(XFileMeshType::Max)];

public:
	MeshManager(class Game* game);
	~MeshManager(void);

	static MeshManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止	

private:
	bool Init(void);	//初期化
	void Uninit(void);	//終了化

public:
	//テクスチャのルートパスの取得
	std::string GetMeshRootpath(void) const { return mesh_root_path_; }

	//メッシュの読み込み
	class XFileMesh* LoadMesh(XFileMeshType xfileMeshTypeID);

	//メッシュの解放
	void ReleaseMesh(XFileMeshType xfileMeshTypeID);

	//メッシュを検索する
	class XFileMesh* FindMesh(XFileMeshType xfileMeshTypeID);

	//
	// メッシュの追加と削除
	//

	void AddMesh(class XFileMesh* xfileMesh);
	void RemoveMesh(class XFileMesh* xfileMesh);

	std::unordered_map<enum class XFileMeshType, std::string> GetMeshFilepathList(void) { return unmap_mesh_path_list_; }

	class Game* GetGame(void) { return game_; }

private:
	//マネージャーの所有者
	class Game* game_;

	//メッシュのルートパス
	std::string mesh_root_path_;

	//メッシュのパスリスト
	std::unordered_map<enum class XFileMeshType, std::string> unmap_mesh_path_list_;

	//メッシュのコンテナ
	std::vector<class XFileMesh*> mesh_list_;
};

#endif //MESH_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/