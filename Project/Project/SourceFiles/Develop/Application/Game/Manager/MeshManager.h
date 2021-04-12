/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Hoge.h] ���b�V���Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���b�V���Ǘ��N���X
=============================================================================*/
#ifndef MESH_MANAGER_H_
#define	MESH_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/

enum class XFileMeshType
{
	None = -1
	, Polygon
	, Box
	, Cylinder
	, Sphere

	, AirPlane

	, GreenBullet
	, BlueBullet
	, RedBullet


	, Max
};

/*-------------------------------------
/* ���b�V���Ǘ��N���X
-------------------------------------*/
class MeshManager
{
public:
	MeshManager(class Game* game);
	~MeshManager(void);

	static MeshManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~	

private:
	bool Init(void);	//������
	void Uninit(void);	//�I����

public:
	//�e�N�X�`���̃��[�g�p�X�̎擾
	std::string GetMeshRootpath(void) const { return mesh_root_path_; }

	//���b�V���̓ǂݍ���
	class XFileMesh* LoadMesh(XFileMeshType xfileMeshTypeID);

	//���b�V���̉��
	void ReleaseMesh(XFileMeshType xfileMeshTypeID);

	//���b�V������������
	class XFileMesh* FindMesh(XFileMeshType xfileMeshTypeID);

	//
	// ���b�V���̒ǉ��ƍ폜
	//

	void AddMesh(class XFileMesh* xfileMesh);
	void RemoveMesh(class XFileMesh* xfileMesh);

	std::unordered_map<enum class XFileMeshType, std::string> GetMeshFilepathList(void) { return unmap_mesh_path_list_; }

	class Game* GetGame(void) { return game_; }

private:
	//�}�l�[�W���[�̏��L��
	class Game* game_;

	//���b�V���̃��[�g�p�X
	std::string mesh_root_path_;

	//�V�F�[�_�[�̃��X�g
	std::unordered_map<enum class XFileMeshType, std::string> unmap_mesh_path_list_;

	//�e�N�X�`���[�̃R���e�i
	std::vector<class XFileMesh*> mesh_list_;
};

#endif //MESH_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/