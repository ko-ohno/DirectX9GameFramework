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
	bool Init(void);	//������
	void Uninit(void);	//�I����

	void LoadShaders(void);		//�V�F�[�_�̓ǂݍ���
	void UnloadShaders(void);	//�V�F�[�_�̔j��

private:
	//�}�l�[�W���[�̏��L��
	class Game* game_;

	//�V�F�[�_�[�̃��X�g
	std::unordered_map<enum class XFileMeshType, class XFileMesh*> unmap_shader_list_;

};

