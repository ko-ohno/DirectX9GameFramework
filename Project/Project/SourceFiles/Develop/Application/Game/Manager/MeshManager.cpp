/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshManager.cpp] メッシュ管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メッシュ管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "MeshManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"
#include "../Resource/XFileMesh.h"

//メッシュの名前リスト
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
/* コンストラクタ
-----------------------------------------------------------------------------*/
MeshManager::MeshManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
MeshManager::~MeshManager(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
MeshManager* MeshManager::Create(Game* game)
{
	return NEW MeshManager(game);
}

/*-----------------------------------------------------------------------------
/* 起動処理
-----------------------------------------------------------------------------*/
bool MeshManager::StartUp(void)
{
	//自身の初期化
	const bool mesh_manager_init = this->Init();
	if (mesh_manager_init == false)
	{
		return false;
	}

	//メッシュの読み込み
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
/* 停止処理
-----------------------------------------------------------------------------*/
void MeshManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool MeshManager::Init(void)
{
	//メッシュのルートパスを設定
	mesh_root_path_ = "Assets/Meshs/";

	//メッシュのリストを初期化
	mesh_list_.clear();

	//メッシュのファイルパスのリストを初期化
	unmap_mesh_path_list_.clear();
	{
		//
		// プリミティブメッシュの読み込み用ファイルパスリストの作成  
		//
		{
			// すでにXFileMeshのなかで定義済み

			//unmap_mesh_path_list_[XFileMeshType::Box];
			//unmap_mesh_path_list_[XFileMeshType::Cylinder];
			//unmap_mesh_path_list_[XFileMeshType::PlanePolygon];
			//unmap_mesh_path_list_[XFileMeshType::Sphere];
		}

		//
		// メッシュファイルの読み込み用ファイルパスリストの作成  
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
/* 終了化処理
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
/* メッシュの読み込み処理
-----------------------------------------------------------------------------*/
XFileMesh* MeshManager::LoadMesh(XFileMeshType xfileMeshTypeID)
{
	//メッシュがあったら
	auto mesh = this->FindMesh(xfileMeshTypeID);
	if (mesh != nullptr)
	{
		return mesh;
	}
	else
	{
		//メッシュがなかったら
		const bool is_mesh_list_out_of_range = ((xfileMeshTypeID == XFileMeshType::None)
											   || (xfileMeshTypeID == XFileMeshType::Max));
		if (is_mesh_list_out_of_range)
		{
			assert(!"範囲外のメッシュIDを参照しようとしています！");
			return nullptr;
		}
		this->AddMesh(NEW XFileMesh(this, xfileMeshTypeID));
	}
	return this->FindMesh(xfileMeshTypeID);
}

/*-----------------------------------------------------------------------------
/* メッシュの解放処理
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
/* メッシュの検索処理
-----------------------------------------------------------------------------*/
XFileMesh* MeshManager::FindMesh(XFileMeshType xfileMeshTypeID)
{
	//メッシュリストの検索
	for (auto mesh : mesh_list_)
	{
		//現在の調査対象からIDを取得
		auto id = mesh->GetMeshTypeID();

		//取得したIDとxfileMeshTypeIDが一致するか
		if (id == xfileMeshTypeID)
		{
			return mesh;
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* メッシュの追加処理
-----------------------------------------------------------------------------*/
void MeshManager::AddMesh(XFileMesh* xfileMesh)
{
	mesh_list_.emplace_back(xfileMesh);
}

/*-----------------------------------------------------------------------------
/* メッシュの削除処理
-----------------------------------------------------------------------------*/
void MeshManager::RemoveMesh(XFileMesh* xfileMesh)
{
	auto iter = std::find(mesh_list_.begin() //範囲0～
						 , mesh_list_.end()	 //範囲最大まで
						 , xfileMesh);		 //探す対象

	if (iter != mesh_list_.end())
	{
		mesh_list_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/