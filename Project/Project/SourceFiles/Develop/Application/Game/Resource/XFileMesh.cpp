/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[XFileMesh.cpp] Xファイルメッシュクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：Xファイルメッシュクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "XFileMesh.h"
#include "../Manager/MeshManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
XFileMesh::XFileMesh(MeshManager* manager, XFileMeshType meshType)
	: mesh_manager_(manager)
	, mesh_type_id_(XFileMeshType::None)
	, is_loading_complete_(false)
	, lpd3dx_mesh_(nullptr)
	, material_count_(0UL)
	, material_buffer_(nullptr)
{
	//メッシュIDの設定
	mesh_type_id_ = meshType;

	//プリミティブメッシュの読み込みをするか
	const bool is_load_primitive_mesh = ((meshType == XFileMeshType::Polygon)
										|| (meshType == XFileMeshType::Box)
										|| (meshType == XFileMeshType::Cylinder)
										|| (meshType == XFileMeshType::Sphere));

	if(is_load_primitive_mesh)
	{
		//プリミティブメッシュの読み込み
		is_loading_complete_ = this->LoadD3DXPrimitiveMesh(meshType);
		
		//読み込んだメッシュがプリミティブのメッシュか
		is_loaded_primitive_mesh_ = true;
	}
	else
	{
		//メッシュファイルの読み込み
		is_loading_complete_ = this->LoadMeshFile(meshType);
	}
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
XFileMesh::~XFileMesh(void)
{
	SAFE_RELEASE_(lpd3dx_mesh_);
	SAFE_RELEASE_(material_buffer_);

	//メッシュのテクスチャの解放
	while (!mesh_texture_list_.empty())
	{
		mesh_texture_list_.back()->Release();
		mesh_texture_list_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* メッシュの読み込み処理
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadMeshFile(XFileMeshType meshType)
{
	// 描画デバイスの取得
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	// ルートパスの取得
	auto mesh_filepath = mesh_manager_->GetMeshRootpath();

	// ルートパスとファイルパスを合成
	mesh_filepath = mesh_filepath + mesh_manager_->GetMeshFilepathList().at(meshType);
	{
		HRESULT hr;
		LPD3DXBUFFER adjacensy = nullptr;

		//
		// メッシュの読み込み
		//
		{
			hr = D3DXLoadMeshFromX(mesh_filepath.c_str()
								  , D3DXMESH_SYSTEMMEM
								  , lpd3d_device
								  , &adjacensy
								  , &material_buffer_
								  , nullptr
								  , &material_count_
								  , &lpd3dx_mesh_);

			// 読み込みの失敗判定
			if (FAILED(hr)) 
			{
				MessageBox(nullptr
						  , "XFileMesh::LoadMesh():メッシュが読み込めませんでした。\n(拡張子[.X]ファイルの破損、あるいは日本語が内包されていないか確認して下さい。)"
						  , "警告"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}
		}
		
		//
		// メッシュの最適化
		//
		{
			hr = lpd3dx_mesh_->OptimizeInplace(D3DXMESHOPT_COMPACT			//どの三角形にも属していない頂点を取り除く
											  | D3DXMESHOPT_ATTRSORT		//パフォーマンス向上
											  | D3DXMESHOPT_VERTEXCACHE		//キャッシュのヒット率向上
											  , (DWORD*)adjacensy->GetBufferPointer()
											  , nullptr
											  , nullptr
											  , nullptr);

			// 失敗判定
			if (FAILED(hr))
			{
				MessageBox(nullptr
						  , "XFileMesh::LoadMesh():メッシュの最適化に失敗しました。"
						  , "警告"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}
		}

		//
		// クローンメッシュによるメッシュの最適化
		//
		{
			LPD3DXMESH clone_mesh;
			D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];

			lpd3dx_mesh_->GetDeclaration(elements);

			//作成処理
			hr = lpd3dx_mesh_->CloneMesh(D3DXMESH_MANAGED
										| D3DXMESH_WRITEONLY
										, elements
										, lpd3d_device
										, &clone_mesh);

			//失敗判定
			if (FAILED(hr))
			{
				MessageBox(nullptr
						  , "XFileMesh::LoadMesh():メッシュのクローン化に失敗しました。"
						  , "警告"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}

			if (lpd3dx_mesh_ != nullptr) { lpd3dx_mesh_->Release(); }
			lpd3dx_mesh_ = clone_mesh; //クローンしたメッシュのコピー
		}

		//
		// メッシュファイルからテクスチャ情報取得、メッシュのテクスチャを作成
		//
		{
			// 作成したテクスチャの一時格納先
			LPDIRECT3DTEXTURE9 texture;

			// マテリアルのバッファから、メッシュのテクスチャ情報を取得
			LPD3DXMATERIAL materials = (LPD3DXMATERIAL)material_buffer_->GetBufferPointer();

			// メッシュファイルに”貼り付けられたマテリアルの数”だけテクスチャを作成
			for (unsigned int i = 0; i < material_count_; i++)
			{
				// メッシュファイルの情報の中のテクスチャを情報を確認
				if (materials[i].pTextureFilename != nullptr)
				{
					// テクスチャのファイル名用変数を初期化
					texture_filepath_.clear();

					// マテリアルのバッファから"テクスチャ名"を取得
					std::string material_buffer_texture_name = materials[i].pTextureFilename;

					//ファイルパスを合成
					texture_filepath_ = mesh_manager_->GetMeshRootpath() + material_buffer_texture_name;
					
					// テクスチャの作成
					hr = D3DXCreateTextureFromFile(lpd3d_device, texture_filepath_.c_str(), &texture);
						
					// 失敗判定
					if (FAILED(hr))
					{
						MessageBox(nullptr
								  , "XFileMesh::LoadMesh():マテリアルのバッファからのテクスチャの作成に失敗しました。"
								  , "警告"
								  , (MB_OK | MB_ICONWARNING));

						// メッシュの面の隣接情報を解放
						SAFE_RELEASE_(adjacensy);
						SAFE_RELEASE_(texture);
						return false;
					}
					// メッシュが所有するテクスチャのリストへ追加
					this->AddTexture(texture);

					// テクスチャのリストへ追加したので解放
					SAFE_RELEASE_(texture);
				}
			}
			SAFE_RELEASE_(adjacensy);
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* メッシュのテクスチャのリストへテクスチャを追加
-----------------------------------------------------------------------------*/
void XFileMesh::AddTexture(LPDIRECT3DTEXTURE9 texture)
{
	mesh_texture_list_.push_back(texture);
}

/*-----------------------------------------------------------------------------
/* メッシュの読み込みと作成
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadD3DXPrimitiveMesh(XFileMeshType meshType)
{
	bool is_loading_complete = false;

	switch (meshType)
	{
	case XFileMeshType::Box:
		is_loading_complete = this->LoadD3DXMeshBox();
		break;
	case XFileMeshType::Polygon:
		is_loading_complete = this->LoadD3DXMeshPolygon();
		break;
	case XFileMeshType::Sphere:
		is_loading_complete = this->LoadD3DXMeshSphere();
		break;
	case XFileMeshType::Cylinder:
		is_loading_complete = this->LoadD3DXMeshCylinder();
		break;
	default:
		assert(!"XFileMesh::LoadD3DXMeshCreate():不正なメッシュを読み込もうとしています。");
		break;
	}

	return is_loading_complete;
}

/*-----------------------------------------------------------------------------
/* 正方形のペラポリゴンメッシュの読み込み作成処理
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadD3DXMeshPolygon(void)
{
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();
	
	//メッシュの読み込み
	HRESULT hr;
	{
		hr = D3DXCreatePolygon(lpd3d_device		// 描画デバイス
							  , 1.F				// 各辺の長さ
							  , 4U				// ポリゴンが持つ辺の数：Triangle == 3 / Rectangle == 4
							  , &lpd3dx_mesh_	// メッシュの格納先
							  , nullptr);

		if (FAILED(hr)) //読み込みの失敗判定
		{
			MessageBox(nullptr
					  , "XFileMesh::LoadD3DXMeshPolygon():正方形のペラポリゴンメッシュの読み込み作成処理が失敗しました！"
					  , "警告"
					  , (MB_OK | MB_ICONWARNING));
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ボックスのメッシュの読み込み作成処理
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadD3DXMeshBox(void)
{
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();
	
	//メッシュの読み込み
	HRESULT hr;
	{
		hr = D3DXCreateBox(lpd3d_device		// 描画デバイス
						  , 0.5F			// X軸:原点からの幅
						  , 0.5F			// Y軸:原点からの高さ
						  , 0.5F			// Z軸:原点からの奥行き
						  , &lpd3dx_mesh_	// メッシュの格納先
						  , nullptr);

		if (FAILED(hr)) //読み込みの失敗判定
		{
			MessageBox(nullptr
					  , "XFileMesh::LoadD3DXMeshBox():ボックスのメッシュの読み込み作成処理が失敗しました！"
					  , "警告"
					  , (MB_OK | MB_ICONWARNING));
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 円筒メッシュの読み込み作成処理
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadD3DXMeshCylinder(void)
{
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//メッシュの読み込み
	HRESULT hr;
	{
		hr = D3DXCreateCylinder(lpd3d_device	// 描画デバイス
							   , 0.5F			// 円筒の+Z軸の円盤の半径
							   , 0.5F			// 円筒の-Z軸の円盤の半径
							   , 1.F			// 円筒の長さ：Z軸に沿う
							   , 16U			// 主軸を中心としたスライスの数：縦割りの数
							   , 8U				// 主軸を中心としたスタックの数：横割りの数
							   , &lpd3dx_mesh_	// メッシュの格納先
							   , nullptr);

		if (FAILED(hr)) //読み込みの失敗判定
		{
			MessageBox(nullptr
					  , "XFileMesh::LoadD3DXMeshCylinder():円筒メッシュの読み込み作成処理が失敗しました！"
					  , "警告"
					  , (MB_OK | MB_ICONWARNING));
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 球体メッシュの読み込み作成処理
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadD3DXMeshSphere(void)
{
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();
	
	//メッシュの読み込み
	HRESULT hr;
	{
		hr = D3DXCreateSphere(lpd3d_device		// 描画デバイス
							 , 0.5F				// 球体の半径
							 , 16U				// 主軸を中心としたスライスの数：縦割りの数
							 , 8U				// 主軸に沿ったスタックの数	   ：横割りの数
							 , &lpd3dx_mesh_	// メッシュの格納先
							 , nullptr);

		if (FAILED(hr)) //読み込みの失敗判定
		{
			MessageBox(nullptr
					  , "XFileMesh::LoadD3DXMeshSphere():球体メッシュの読み込み作成処理が失敗しました！"
					  , "警告"
					  , (MB_OK | MB_ICONWARNING));
			return false;
		}
	}
	return true;
}

/*=============================================================================
/*		End of File
=============================================================================*/