/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[XFileMesh.cpp] X�t�@�C�����b�V���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FX�t�@�C�����b�V���N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "XFileMesh.h"
#include "../Manager/MeshManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"
#include "../Resource/Texture.h"
#include "../Resource/Material.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
XFileMesh::XFileMesh(MeshManager* manager, XFileMeshType meshType)
	: mesh_manager_(manager)
	, mesh_type_id_(XFileMeshType::None)
	, is_primitive_mesh_(false)
	, is_loading_complete_(false)
	, lpd3dx_mesh_(nullptr)
	, material_count_(0UL)
	, material_buffer_(nullptr)
{
	//���b�V��ID�̐ݒ�
	mesh_type_id_ = meshType;

	//���X�g�̏�����
	mesh_material_list_.clear();

	//�v���~�e�B�u���b�V���̓ǂݍ��݂����邩
	const bool is_load_primitive_mesh = ((meshType == XFileMeshType::Polygon)
										|| (meshType == XFileMeshType::Box)
										|| (meshType == XFileMeshType::Cylinder)
										|| (meshType == XFileMeshType::Sphere));

	if(is_load_primitive_mesh)
	{
		//�v���~�e�B�u���b�V���̓ǂݍ���
		is_loading_complete_ = this->LoadD3DXPrimitiveMesh(meshType);

		is_primitive_mesh_ = true;
	}
	else
	{
		//���b�V���t�@�C���̓ǂݍ���
		is_loading_complete_ = this->LoadMeshFile(meshType);
	}
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
XFileMesh::~XFileMesh(void)
{
	SAFE_RELEASE_(lpd3dx_mesh_);
	SAFE_RELEASE_(material_buffer_);

	//���b�V���̃e�N�X�`���̉��
	while (!mesh_material_list_.empty())
	{
		delete mesh_material_list_.back();
		mesh_material_list_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* ���b�V���̓ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadMeshFile(XFileMeshType meshType)
{
	// �`��f�o�C�X�̎擾
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	// ���[�g�p�X�ƃt�@�C���p�X������
	auto mesh_filepath = mesh_manager_->GetMeshRootpath() + mesh_manager_->GetMeshFilepathList().at(meshType);
	{
		HRESULT hr;
		LPD3DXBUFFER adjacensy = nullptr;
		
		//���b�V���̎�ޖ����擾
		std::string xfile_mesh_name = MeshManager::XFileMeshTypeNames[static_cast<int>(meshType)];

		//
		// ���b�V���̓ǂݍ���
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

			// �ǂݍ��݂̎��s����
			if (FAILED(hr)) 
			{
				std::string err_msg = "XFileMesh::LoadMesh():���b�V�����ǂݍ��߂܂���ł����B\n";
				err_msg = err_msg + xfile_mesh_name + "�F(�g���q[.X]�t�@�C���̔j���A���邢�͓��{�ꂪ�����Ă��Ȃ����m�F���ĉ������B)";
				MessageBox(nullptr
						  , err_msg.c_str()
						  , "�x��"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}
		}

		// ���b�V���̍œK��
		if (this->MeshOptimization(xfile_mesh_name, adjacensy))
		{
			return false;
		}

		// ���b�V���̖ʂ̗אڏ������(�����g��Ȃ��̂�)
		{
			SAFE_RELEASE_(adjacensy);
		}


		// ���b�V���̒��_�f�[�^���C�A�E�g��ύX
		if (this->MeshClone(xfile_mesh_name, lpd3d_device))
		{
			return false;
		}

		//
		// ���b�V���t�@�C��������擾�A�e�N�X�`���ƃ}�e���A�����쐬
		//

		// ���b�V���̃��[�g�p�X�擾
		std::string texture_rootpath = mesh_manager_->GetMeshRootpath();

		// �}�e���A���̃o�b�t�@����A���b�V���̃e�N�X�`�������擾
		auto lpd3dx_materials = (LPD3DXMATERIAL)material_buffer_->GetBufferPointer();

		for(int i = 0; i < static_cast<int>(material_count_); i++)
		{
			if (lpd3dx_materials[i].pTextureFilename != nullptr)
			{
				// �e�N�X�`���̃t�@�C���p�X�擾
				std::string texture_filepath = lpd3dx_materials[i].pTextureFilename;

				// ���[�g�p�X�ƃt�@�C�����Ŋ��S�ȃt�@�C���p�X���쐬
				std::string filepath = texture_rootpath + texture_filepath;

				// �e�N�X�`���t�@�C�����̗L�����m�F
				if (filepath.size() == mesh_manager_->GetMeshRootpath().size())
				{
					continue;
				}

				// �}�e���A���̍쐬
				this->AddMaterial(NEW Material(lpd3d_device, filepath, lpd3dx_materials[i].MatD3D));
			}
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ���b�V���̃}�e���A���̃��X�g�փ}�e���A����ǉ�
-----------------------------------------------------------------------------*/
void XFileMesh::AddMaterial(Material* material)
{
	mesh_material_list_.emplace_back(material);
}

/*-----------------------------------------------------------------------------
/* ���b�V���̍œK��
-----------------------------------------------------------------------------*/
bool XFileMesh::MeshOptimization(const std::string& xfileMeshName, const LPD3DXBUFFER& adjacensy)
{
	HRESULT hr;
	hr = lpd3dx_mesh_->OptimizeInplace(D3DXMESHOPT_COMPACT			//�ǂ̎O�p�`�ɂ������Ă��Ȃ����_����菜��
									  | D3DXMESHOPT_ATTRSORT		//�p�t�H�[�}���X����
									  | D3DXMESHOPT_VERTEXCACHE		//�L���b�V���̃q�b�g������
									  , (DWORD*)adjacensy->GetBufferPointer()
									  , nullptr
									  , nullptr
									  , nullptr);

	// ���s����
	if (FAILED(hr))
	{
		std::string err_msg = "XFileMesh::MeshOptimization():���b�V���̍œK���Ɏ��s���܂����B\n";
		err_msg = err_msg + "�œK���������b�V���F" + xfileMeshName;

		MessageBox(nullptr
				  , err_msg.c_str()
				  , "�x��"
				  , (MB_OK | MB_ICONWARNING));
		return true;
	}
	return false;
}

/*-----------------------------------------------------------------------------
/* ���b�V���̃N���[��
-----------------------------------------------------------------------------*/
bool XFileMesh::MeshClone(const std::string& xfileMeshName, const LPDIRECT3DDEVICE9& lpd3dDevice)
{
	//
	// ���_�f�[�^�̃��C�A�E�g���ăt�H�[�}�b�g
	//
	LPD3DXMESH clone_mesh;
	D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];

	lpd3dx_mesh_->GetDeclaration(elements);

	HRESULT hr;
	hr = lpd3dx_mesh_->CloneMesh(D3DXMESH_MANAGED
								| D3DXMESH_WRITEONLY
								, elements
								, lpd3dDevice
								, &clone_mesh);

	//���s����
	if (FAILED(hr))
	{
		std::string err_msg = "XFileMesh::MeshClone():���b�V���̃N���[�����Ɏ��s���܂����B\n";
		err_msg = err_msg + "�N���[���������b�V���F" + xfileMeshName;

		MessageBox(nullptr
				  , err_msg.c_str()
				  , "�x��"
				  , (MB_OK | MB_ICONWARNING));
		return true;
	}

	//�N���[���������b�V���̃R�s�[
	{
		if (lpd3dx_mesh_ != nullptr)
		{
			lpd3dx_mesh_->Release();
		}
		lpd3dx_mesh_ = clone_mesh; 
	}
	return false;
}

/*-----------------------------------------------------------------------------
/* ���b�V���̓ǂݍ��݂ƍ쐬
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
		assert(!"XFileMesh::LoadD3DXMeshCreate():�s���ȃ��b�V����ǂݍ������Ƃ��Ă��܂��B");
		break;
	}
	return is_loading_complete;
}

/*-----------------------------------------------------------------------------
/* �����`�̃y���|���S�����b�V���̓ǂݍ��ݍ쐬����
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadD3DXMeshPolygon(void)
{
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();
	
	//���b�V���̓ǂݍ���
	HRESULT hr;
	{
		hr = D3DXCreatePolygon(lpd3d_device		// �`��f�o�C�X
							  , 1.F				// �e�ӂ̒���
							  , 4U				// �|���S�������ӂ̐��FTriangle == 3 / Rectangle == 4
							  , &lpd3dx_mesh_	// ���b�V���̊i�[��
							  , nullptr);

		if (FAILED(hr)) //�ǂݍ��݂̎��s����
		{
			MessageBox(nullptr
					  , "XFileMesh::LoadD3DXMeshPolygon():�����`�̃y���|���S�����b�V���̓ǂݍ��ݍ쐬���������s���܂����I"
					  , "�x��"
					  , (MB_OK | MB_ICONWARNING));
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �{�b�N�X�̃��b�V���̓ǂݍ��ݍ쐬����
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadD3DXMeshBox(void)
{
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();
	
	//���b�V���̓ǂݍ���
	HRESULT hr;
	{
		hr = D3DXCreateBox(lpd3d_device		// �`��f�o�C�X
						  , 0.5F			// X��:���_����̕�
						  , 0.5F			// Y��:���_����̍���
						  , 0.5F			// Z��:���_����̉��s��
						  , &lpd3dx_mesh_	// ���b�V���̊i�[��
						  , nullptr);

		if (FAILED(hr)) //�ǂݍ��݂̎��s����
		{
			MessageBox(nullptr
					  , "XFileMesh::LoadD3DXMeshBox():�{�b�N�X�̃��b�V���̓ǂݍ��ݍ쐬���������s���܂����I"
					  , "�x��"
					  , (MB_OK | MB_ICONWARNING));
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �~�����b�V���̓ǂݍ��ݍ쐬����
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadD3DXMeshCylinder(void)
{
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	//���b�V���̓ǂݍ���
	HRESULT hr;
	{
		hr = D3DXCreateCylinder(lpd3d_device	// �`��f�o�C�X
							   , 0.5F			// �~����+Z���̉~�Ղ̔��a
							   , 0.5F			// �~����-Z���̉~�Ղ̔��a
							   , 1.F			// �~���̒����FZ���ɉ���
							   , 16U			// �厲�𒆐S�Ƃ����X���C�X�̐��F�c����̐�
							   , 8U				// �厲�𒆐S�Ƃ����X�^�b�N�̐��F������̐�
							   , &lpd3dx_mesh_	// ���b�V���̊i�[��
							   , nullptr);

		if (FAILED(hr)) //�ǂݍ��݂̎��s����
		{
			MessageBox(nullptr
					  , "XFileMesh::LoadD3DXMeshCylinder():�~�����b�V���̓ǂݍ��ݍ쐬���������s���܂����I"
					  , "�x��"
					  , (MB_OK | MB_ICONWARNING));
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ���̃��b�V���̓ǂݍ��ݍ쐬����
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadD3DXMeshSphere(void)
{
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();
	
	//���b�V���̓ǂݍ���
	HRESULT hr;
	{
		hr = D3DXCreateSphere(lpd3d_device		// �`��f�o�C�X
							 , 0.5F				// ���̂̔��a
							 , 16U				// �厲�𒆐S�Ƃ����X���C�X�̐��F�c����̐�
							 , 8U				// �厲�ɉ������X�^�b�N�̐�	   �F������̐�
							 , &lpd3dx_mesh_	// ���b�V���̊i�[��
							 , nullptr);

		if (FAILED(hr)) //�ǂݍ��݂̎��s����
		{
			MessageBox(nullptr
					  , "XFileMesh::LoadD3DXMeshSphere():���̃��b�V���̓ǂݍ��ݍ쐬���������s���܂����I"
					  , "�x��"
					  , (MB_OK | MB_ICONWARNING));
			return false;
		}
	}
	return true;
}

/*=============================================================================
/*		End of File
=============================================================================*/