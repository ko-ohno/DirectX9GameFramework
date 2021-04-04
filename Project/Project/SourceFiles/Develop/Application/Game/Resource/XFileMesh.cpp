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

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
XFileMesh::XFileMesh(MeshManager* manager, XFileMeshType meshType)
	: mesh_manager_(manager)
	, mesh_type_id_(XFileMeshType::None)
	, is_loading_complete_(false)
	, lpd3dx_mesh_(nullptr)
	, material_count_(0UL)
	, material_buffer_(nullptr)
{
	//���b�V��ID�̐ݒ�
	mesh_type_id_ = meshType;

	//�v���~�e�B�u���b�V���̓ǂݍ��݂����邩
	const bool is_load_primitive_mesh = ((meshType == XFileMeshType::Polygon)
										|| (meshType == XFileMeshType::Box)
										|| (meshType == XFileMeshType::Cylinder)
										|| (meshType == XFileMeshType::Sphere));

	if(is_load_primitive_mesh)
	{
		//�v���~�e�B�u���b�V���̓ǂݍ���
		is_loading_complete_ = this->LoadD3DXPrimitiveMesh(meshType);
		
		//�ǂݍ��񂾃��b�V�����v���~�e�B�u�̃��b�V����
		is_loaded_primitive_mesh_ = true;
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
	while (!mesh_texture_list_.empty())
	{
		mesh_texture_list_.back()->Release();
		mesh_texture_list_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* ���b�V���̓ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
bool XFileMesh::LoadMeshFile(XFileMeshType meshType)
{
	// �`��f�o�C�X�̎擾
	auto lpd3d_device = *mesh_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();

	// ���[�g�p�X�̎擾
	auto mesh_filepath = mesh_manager_->GetMeshRootpath();

	// ���[�g�p�X�ƃt�@�C���p�X������
	mesh_filepath = mesh_filepath + mesh_manager_->GetMeshFilepathList().at(meshType);
	{
		HRESULT hr;
		LPD3DXBUFFER adjacensy = nullptr;

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
				MessageBox(nullptr
						  , "XFileMesh::LoadMesh():���b�V�����ǂݍ��߂܂���ł����B\n(�g���q[.X]�t�@�C���̔j���A���邢�͓��{�ꂪ�����Ă��Ȃ����m�F���ĉ������B)"
						  , "�x��"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}
		}
		
		//
		// ���b�V���̍œK��
		//
		{
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
				MessageBox(nullptr
						  , "XFileMesh::LoadMesh():���b�V���̍œK���Ɏ��s���܂����B"
						  , "�x��"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}
		}

		//
		// �N���[�����b�V���ɂ�郁�b�V���̍œK��
		//
		{
			LPD3DXMESH clone_mesh;
			D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];

			lpd3dx_mesh_->GetDeclaration(elements);

			//�쐬����
			hr = lpd3dx_mesh_->CloneMesh(D3DXMESH_MANAGED
										| D3DXMESH_WRITEONLY
										, elements
										, lpd3d_device
										, &clone_mesh);

			//���s����
			if (FAILED(hr))
			{
				MessageBox(nullptr
						  , "XFileMesh::LoadMesh():���b�V���̃N���[�����Ɏ��s���܂����B"
						  , "�x��"
						  , (MB_OK | MB_ICONWARNING));
				return false;
			}

			if (lpd3dx_mesh_ != nullptr) { lpd3dx_mesh_->Release(); }
			lpd3dx_mesh_ = clone_mesh; //�N���[���������b�V���̃R�s�[
		}

		//
		// ���b�V���t�@�C������e�N�X�`�����擾�A���b�V���̃e�N�X�`�����쐬
		//
		{
			// �쐬�����e�N�X�`���̈ꎞ�i�[��
			LPDIRECT3DTEXTURE9 texture;

			// �}�e���A���̃o�b�t�@����A���b�V���̃e�N�X�`�������擾
			LPD3DXMATERIAL materials = (LPD3DXMATERIAL)material_buffer_->GetBufferPointer();

			// ���b�V���t�@�C���Ɂh�\��t����ꂽ�}�e���A���̐��h�����e�N�X�`�����쐬
			for (unsigned int i = 0; i < material_count_; i++)
			{
				// ���b�V���t�@�C���̏��̒��̃e�N�X�`���������m�F
				if (materials[i].pTextureFilename != nullptr)
				{
					// �e�N�X�`���̃t�@�C�����p�ϐ���������
					texture_filepath_.clear();

					// �}�e���A���̃o�b�t�@����"�e�N�X�`����"���擾
					std::string material_buffer_texture_name = materials[i].pTextureFilename;

					//�t�@�C���p�X������
					texture_filepath_ = mesh_manager_->GetMeshRootpath() + material_buffer_texture_name;
					
					// �e�N�X�`���̍쐬
					hr = D3DXCreateTextureFromFile(lpd3d_device, texture_filepath_.c_str(), &texture);
						
					// ���s����
					if (FAILED(hr))
					{
						MessageBox(nullptr
								  , "XFileMesh::LoadMesh():�}�e���A���̃o�b�t�@����̃e�N�X�`���̍쐬�Ɏ��s���܂����B"
								  , "�x��"
								  , (MB_OK | MB_ICONWARNING));

						// ���b�V���̖ʂ̗אڏ������
						SAFE_RELEASE_(adjacensy);
						SAFE_RELEASE_(texture);
						return false;
					}
					// ���b�V�������L����e�N�X�`���̃��X�g�֒ǉ�
					this->AddTexture(texture);

					// �e�N�X�`���̃��X�g�֒ǉ������̂ŉ��
					SAFE_RELEASE_(texture);
				}
			}
			SAFE_RELEASE_(adjacensy);
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ���b�V���̃e�N�X�`���̃��X�g�փe�N�X�`����ǉ�
-----------------------------------------------------------------------------*/
void XFileMesh::AddTexture(LPDIRECT3DTEXTURE9 texture)
{
	mesh_texture_list_.push_back(texture);
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