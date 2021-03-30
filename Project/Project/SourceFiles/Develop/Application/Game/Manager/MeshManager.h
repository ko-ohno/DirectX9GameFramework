#pragma once


enum class XFileMeshType
{
	None = -1
	, Box
	, PlanePolygon
	, Sphere
	, Cylinder

	, Max
};



class MeshManager
{
public:
	MeshManager(class Game* game);
	~MeshManager(void);

	static MeshManager* Create(class Game* game);

	bool StartUp(void);
	void Shutdown(void);

	class Game* GetGame(void) { return game_; }

private:
	void LoadD3DXBox();
	void LoadD3DXPolygon();
	void LoadD3DXSphere();
	void LoadD3DXCylinder();

private:
	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	void LoadShaders(void);		//シェーダの読み込み
	void UnloadShaders(void);	//シェーダの破棄

private:
	//マネージャーの所有者
	class Game* game_;

	//シェーダーのリスト
	std::unordered_map<enum class XFileMeshType, class XFileMesh*> unmap_shader_list_;

};

