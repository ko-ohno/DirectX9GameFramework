/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshManager.cpp] ���b�V���Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���b�V���Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "MeshManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"
#include "../Resource/XFileMesh.h"

//���b�V���̖��O���X�g
const char* MeshManager::XFileMeshTypeNames[static_cast<int>(XFileMeshType::Max)] = {
	"Polygon"
	, "Box"
	, "Cylinder"
	, "Sphere"

	, "AirPlane"

	, "GreenBullet"
	, "BlueBullet"
	, "RedBullet"
};


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
MeshManager::MeshManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
MeshManager::~MeshManager(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
MeshManager* MeshManager::Create(Game* game)
{
	return NEW MeshManager(game);
}

/*-----------------------------------------------------------------------------
/* �N������
-----------------------------------------------------------------------------*/
bool MeshManager::StartUp(void)
{
	//���g�̏�����
	const bool mesh_manager_init = this->Init();
	if (mesh_manager_init == false)
	{
		return false;
	}

	//���b�V���̓ǂݍ���
	{
		//this->LoadMesh(XFileMeshType::Polygon);
		//this->LoadMesh(XFileMeshType::Box);
		//this->LoadMesh(XFileMeshType::Cylinder);
		//this->LoadMesh(XFileMeshType::Sphere);

		//this->LoadMesh(XFileMeshType::GreenBullet);


	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void MeshManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool MeshManager::Init(void)
{
	//���b�V���̃��[�g�p�X��ݒ�
	mesh_root_path_ = "Assets/Meshs/";

	//���b�V���̃��X�g��������
	mesh_list_.clear();

	//���b�V���̃t�@�C���p�X�̃��X�g��������
	unmap_mesh_path_list_.clear();
	{
		//
		// �v���~�e�B�u���b�V���̓ǂݍ��ݗp�t�@�C���p�X���X�g�̍쐬  
		//
		{
			// ���ł�XFileMesh�̂Ȃ��Œ�`�ς�

			//unmap_mesh_path_list_[XFileMeshType::Box];
			//unmap_mesh_path_list_[XFileMeshType::Cylinder];
			//unmap_mesh_path_list_[XFileMeshType::PlanePolygon];
			//unmap_mesh_path_list_[XFileMeshType::Sphere];
		}

		//
		// ���b�V���t�@�C���̓ǂݍ��ݗp�t�@�C���p�X���X�g�̍쐬  
		//
		{
			unmap_mesh_path_list_[XFileMeshType::BlueBullet]	= "Bullet/BlueBullet.x";
			unmap_mesh_path_list_[XFileMeshType::GreenBullet]	= "Bullet/GreenBullet.x";
			unmap_mesh_path_list_[XFileMeshType::RedBullet]		= "Bullet/RedBullet.x";
			unmap_mesh_path_list_[XFileMeshType::AirPlane]		= "AirPlane/f1.x";
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void MeshManager::Uninit(void)
{
	while (!mesh_list_.empty())
	{
		delete mesh_list_.back();
		mesh_list_.back() = nullptr;
		mesh_list_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* ���b�V���̓ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
XFileMesh* MeshManager::LoadMesh(XFileMeshType xfileMeshTypeID)
{
	//���b�V������������
	auto mesh = this->FindMesh(xfileMeshTypeID);
	if (mesh != nullptr)
	{
		return mesh;
	}
	else
	{
		//���b�V�����Ȃ�������
		const bool is_mesh_list_out_of_range = ((xfileMeshTypeID == XFileMeshType::None)
											   || (xfileMeshTypeID == XFileMeshType::Max));
		if (is_mesh_list_out_of_range)
		{
			assert(!"�͈͊O�̃��b�V��ID���Q�Ƃ��悤�Ƃ��Ă��܂��I");
			return nullptr;
		}
		this->AddMesh(NEW XFileMesh(this, xfileMeshTypeID));
	}
	return this->FindMesh(xfileMeshTypeID);
}

/*-----------------------------------------------------------------------------
/* ���b�V���̉������
-----------------------------------------------------------------------------*/
void MeshManager::ReleaseMesh(XFileMeshType xfileMeshTypeID)
{
	for (auto mesh : mesh_list_)
	{
		auto id = mesh->GetMeshTypeID();

		if (id == xfileMeshTypeID)
		{
			delete mesh;
		}
	}
}

/*-----------------------------------------------------------------------------
/* ���b�V���̌�������
-----------------------------------------------------------------------------*/
XFileMesh* MeshManager::FindMesh(XFileMeshType xfileMeshTypeID)
{
	//���b�V�����X�g�̌���
	for (auto mesh : mesh_list_)
	{
		//���݂̒����Ώۂ���ID���擾
		auto id = mesh->GetMeshTypeID();

		//�擾����ID��xfileMeshTypeID����v���邩
		if (id == xfileMeshTypeID)
		{
			return mesh;
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* ���b�V���̒ǉ�����
-----------------------------------------------------------------------------*/
void MeshManager::AddMesh(XFileMesh* xfileMesh)
{
	mesh_list_.emplace_back(xfileMesh);
}

/*-----------------------------------------------------------------------------
/* ���b�V���̍폜����
-----------------------------------------------------------------------------*/
void MeshManager::RemoveMesh(XFileMesh* xfileMesh)
{
	auto iter = std::find(mesh_list_.begin() //�͈�0�`
						 , mesh_list_.end()	 //�͈͍ő�܂�
						 , xfileMesh);		 //�T���Ώ�

	if (iter != mesh_list_.end())
	{
		mesh_list_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/