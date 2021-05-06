/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[VertexData.h]  ���_�̃f�[�^(����)���`�����w�b�_
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���_�̃f�[�^(����)���`�����w�b�_
=============================================================================*/
#ifndef VERTEX_DATA_H_
#define	VERTEX_DATA_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"


/*--- �N���X�̑O���錾 ---*/

/*-------------------------------------
/* 2D�̒��_�f�[�^�\����
-------------------------------------*/
typedef struct
{
	D3DXVECTOR3 position_;		//���[�J�����W
	D3DCOLOR	vtx_color_;		//�F���
	D3DXVECTOR2 texcoord_;		//UV���W
}VERTEX_STD;

// 2D�̒��_�t�H�[�}�b�g�̐ݒ�
#define FVF_VERTEX_STD (D3DFVF_XYZ		\
					 |  D3DFVF_DIFFUSE	\
					 |  D3DFVF_TEX1) 


/*-------------------------------------
/* 3D�̒��_�f�[�^�\����
-------------------------------------*/
typedef struct
{
	D3DXVECTOR3 position_;		//���[�J�����W
	D3DXVECTOR3 normal_;		//�@�����
	D3DCOLOR	vtx_color_;		//�F���
	D3DXVECTOR2 texcoord_;		//UV���W
}VERTEX_MESH;				

// 3D�̒��_�t�H�[�}�b�g�̐ݒ�
#define FVF_VERTEX_MESH (D3DFVF_XYZ		\
					  |  D3DFVF_NORMAL	\
					  |  D3DFVF_DIFFUSE	\
					  |  D3DFVF_TEX1) 



/*-------------------------------------
/* Gizmo�p�̒��_�f�[�^�\����
-------------------------------------*/
typedef struct
{
	D3DXVECTOR3 position_;		//���[�J�����W
	D3DCOLOR	vtx_color_;		//�F���
}VERTEX_GIZMO;			

// Gizmo�̒��_�t�H�[�}�b�g�̐ݒ�
#define FVF_VERTEX_GIZMO (D3DFVF_XYZ		\
				       |  D3DFVF_DIFFUSE) 



#endif //VERTEX_DATA_H_
/*=============================================================================
/*		End of File
=============================================================================*/